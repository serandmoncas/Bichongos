/*
 * Bichongos — Cápsula Core Firmware
 * ESP32 con Arduino framework
 *
 * Dependencias (Gestor de Librerías Arduino):
 *   PubSubClient ≥ 2.8 · ArduinoJson ≥ 7.x · Adafruit SHT31 ≥ 2.2
 *   BH1750 ≥ 1.3 · MHZ19 ≥ 1.5 · OneWire · DallasTemperature · Preferences (builtin)
 *
 * Ver docs/capsula/diagrama-electrico-capsula-mini.md para pinout y cableado.
 * Ver firmware/profiles/ para los perfiles JSON de cada especie.
 */

#include <WiFi.h>
#include <ArduinoOTA.h>
#include <time.h>
#include <esp_task_wdt.h>
#include <ctype.h>
#include "config.h"
#include "sensors.h"
#include "actuators.h"
#include "profile.h"
#include "mqtt_client.h"
#include "stage_tracker.h"

// ─── Constantes de tiempo ──────────────────────────────────────────────────
static const unsigned long SENSOR_INTERVAL_MS  = 30000UL; // ciclo normal
static const unsigned long OFFLINE_BUFFER_MAX  = 240;     // lecturas en RAM sin WiFi (2 h)
static const unsigned long WIFI_RETRY_INTERVAL = 30000UL;
static const unsigned long MQTT_RETRY_INTERVAL = 10000UL;
static const uint32_t      WDT_TIMEOUT_S       = 60;   // ciclo normal es 30s; da margen de 1 ciclo perdido

// ─── Estado global ─────────────────────────────────────────────────────────
static WiFiClient  wifiClient;
static Profile     activeProfile;
static bool        otaPending = false;

static unsigned long lastSensorMs  = 0;
static unsigned long lastWifiRetry = 0;
static unsigned long lastMqttRetry = 0;
static unsigned long offlineSince  = 0;
static bool          wasOffline    = false;
static uint32_t      controlTickCount = 0; // cuenta ciclos de control, usado para el pulso de ventilacion en conflicto frio/CO2

// ─── Callbacks para comandos MQTT entrantes ────────────────────────────────
static bool profileIdIsSafe(const char* id) {
  if (!id || strlen(id) == 0) return false;
  for (const char* c = id; *c; c++) {
    if (!isalnum((unsigned char)*c) && *c != '_' && *c != '-') return false;
  }
  return true;
}

void onProfileSet(const char* newProfile, const char* newStage) {
  Serial.printf("[MAIN] Cambio de perfil solicitado → perfil:%s etapa:%s\n",
                newProfile, newStage);

  if (!profileIdIsSafe(newProfile)) {
    Serial.printf("[MAIN] Rechazado: id de perfil '%s' contiene caracteres invalidos\n", newProfile);
    mqttPublishAlert("profile_set_rechazado", 0, 0, "id_invalido");
    return;
  }

  char path[64];
  snprintf(path, sizeof(path), "/profiles/%s.json", newProfile);

  Profile candidate;
  if (!loadProfile(path, newStage, candidate)) {
    Serial.printf("[MAIN] Error: no se pudo cargar perfil '%s' en '%s'\n", newProfile, path);
    mqttPublishAlert("profile_set_rechazado", 0, 0, "perfil_no_encontrado");
    return;
  }

  activeProfile = candidate;
  stageTrackerSetStage(activeProfile.etapaActual);  // reiniciar contador de días
  Serial.printf("[MAIN] Perfil activo: '%s' etapa '%s'\n", activeProfile.especie, activeProfile.etapaActual);
  mqttPublishStatus(getCurrentActuatorState(), activeProfile);
}

void onOtaTrigger() {
  // No iniciar OTA si hay actuadores encendidos — apagar primero
  emergencyShutdown();
  otaPending = true;
  Serial.println("[MAIN] OTA autorizado — actuadores apagados, esperando upload");
}

// ─── Control ───────────────────────────────────────────────────────────────
ActuatorState computeControl(const SensorData& s, const Profile& p) {
  ActuatorState next = {};
  const StageParams& e = p.etapa;

  if (s.errorSHT31) return getCurrentActuatorState(); // sin datos → mantener estado

  // Humidificador
  next.humidificador = (s.humedad < e.humedadMin);
  if (s.humedad > e.humedadMax) next.humidificador = false; // override: demasiada HR

  // Calefactor
  next.calefactor = (s.tempAire < e.tempMin);

  // Extractor FAE — activo si CO₂ alto O temperatura alta (ventilación pasiva)
  bool co2Alto = (!s.errorMHZ19) && (s.co2Ppm > e.co2Max);
  bool tempAlta = (s.tempAire > e.tempMax);
  next.extractor = co2Alto || tempAlta;

  // Caso Enoki: CO₂ mínimo (extractor OFF para acumular CO₂)
  if (e.co2Min > 0 && !s.errorMHZ19 && s.co2Ppm < e.co2Min) {
    next.extractor = false;
  }

  // Conflicto: calefactor necesario y CO2 en zona critica a la vez (caso normal de Enoki).
  // En vez de apagar el extractor por completo, se ventila en pulsos cortos:
  // el ciclo de control corre cada 30s (SENSOR_INTERVAL_MS), asi que "30s ON / 90s OFF"
  // se logra activando el extractor solo 1 de cada 4 ciclos.
  if (next.calefactor && next.extractor) {
    bool co2Critico = (!s.errorMHZ19) && (s.co2Ppm > p.alertas.co2CriticoMax);
    if (co2Critico) {
      next.extractor = (controlTickCount % 4 == 0);
    } else {
      next.extractor = false;
    }
  }

  // LED — controlado por horario de la etapa
  next.led = false;
  if (e.luzHoras > 0) {
    struct tm ti;
    if (getLocalTime(&ti)) {
      int ahora = ti.tm_hour * 60 + ti.tm_min;
      int ini   = e.luzInicioH * 60 + e.luzInicioM;
      int fin   = e.luzFinH    * 60 + e.luzFinM;
      next.led  = (ahora >= ini && ahora < fin);
    }
  }

  // Protección: DS18B20 sustrato demasiado caliente → calefactor OFF
  if (!s.errorDS18B20 && s.tempSustrato > 35.0f) {
    next.calefactor = false;
  }

  return next;
}

void checkAlerts(const SensorData& s, const Profile& p) {
  const AlertThresholds& a = p.alertas;

  if (!s.errorSHT31) {
    if (s.tempAire > a.tempCriticaMax)
      mqttPublishAlert("temp_critica_max", s.tempAire, a.tempCriticaMax, "calefactor_off");
    if (s.tempAire < a.tempCriticaMin)
      mqttPublishAlert("temp_critica_min", s.tempAire, a.tempCriticaMin, "revisar_ambiente");
    if (s.humedad < a.humedadCriticaMin)
      mqttPublishAlert("humedad_critica_min", s.humedad, a.humedadCriticaMin, "revisar_humidificador");
  }
  if (!s.errorMHZ19 && s.co2Ppm > a.co2CriticoMax)
    mqttPublishAlert("co2_critico_max", s.co2Ppm, a.co2CriticoMax, "extractor_on");
  if (!s.errorMHZ19 && a.co2CriticoMin > 0 && s.co2Ppm < a.co2CriticoMin)
    mqttPublishAlert("co2_critico_min", s.co2Ppm, a.co2CriticoMin, "revisar_sellado_camara");

  // Alertas de sensor caído
  if (s.errorSHT31)   mqttPublishAlert("sensor_error", 0, 0, "sht31_sin_respuesta");
  if (s.errorMHZ19)   mqttPublishAlert("sensor_error", 0, 0, "mhz19_sin_respuesta");
  if (s.errorDS18B20) mqttPublishAlert("sensor_error", 0, 0, "ds18b20_sin_respuesta");
}

// ─── Conectividad ──────────────────────────────────────────────────────────
void connectWifi() {
  IPAddress ip    STATIC_IP;
  IPAddress gw    GATEWAY_IP;
  IPAddress sn    SUBNET_MASK;
  IPAddress dns   DNS_SERVER;
  WiFi.config(ip, gw, sn, dns);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.printf("[WIFI] Conectando a %s...\n", WIFI_SSID);
}

bool wifiConnected() {
  return WiFi.status() == WL_CONNECTED;
}

void setupOta() {
  ArduinoOTA.setPassword(OTA_PASSWORD);
  ArduinoOTA.setHostname(CAPSULE_ID);
  ArduinoOTA.onStart([]() {
    emergencyShutdown();
    Serial.println("[OTA] Iniciando update...");
  });
  ArduinoOTA.onEnd([]()   { Serial.println("[OTA] Completado. Reiniciando."); });
  ArduinoOTA.onError([](ota_error_t e) {
    Serial.printf("[OTA] ERROR %u\n", e);
    otaPending = false;
  });
  ArduinoOTA.begin();
}

// ─── Setup ─────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.printf("\n[MAIN] Bichongos Capsula Core — %s\n", CAPSULE_ID);

  esp_task_wdt_init(WDT_TIMEOUT_S, true); // reinicia el ESP32 si loop() se cuelga
  esp_task_wdt_add(NULL);

  initActuators();
  initSensors();
  stageTrackerInit();

  if (!loadProfile(PROFILE_PATH, nullptr, activeProfile)) {
    Serial.println("[MAIN] CRITICO: sin perfil. Entrando en modo seguro mínimo.");
    // Con perfil fallido: sensores siguen funcionando pero sin control activo
  }

  connectWifi();
  unsigned long wifiWait = millis();
  while (!wifiConnected() && millis() - wifiWait < 15000) { delay(500); }

  if (wifiConnected()) {
    Serial.printf("[WIFI] Conectado — IP: %s\n", WiFi.localIP().toString().c_str());
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
    // Actualizar startTime en NVS si se guardó sin NTP (era 0)
    StageInfo si = stageTrackerGet();
    if (si.startTime == 0 && strlen(si.stage) > 0) {
      delay(1500); // esperar primer sync NTP
      stageTrackerSetStage(si.stage);
    }
    mqttInit(wifiClient, onProfileSet, onOtaTrigger);
    mqttConnect();
    setupOta();
  } else {
    Serial.println("[WIFI] Sin conexión — modo seguro local activado");
    wasOffline = true;
    offlineSince = millis();
  }
}

// ─── Loop ──────────────────────────────────────────────────────────────────
void loop() {
  esp_task_wdt_reset();

  // OTA tiene prioridad total cuando está pendiente
  if (otaPending) {
    ArduinoOTA.handle();
    return;
  }

  // Mantener WiFi
  if (!wifiConnected()) {
    if (!wasOffline) {
      wasOffline   = true;
      offlineSince = millis();
      Serial.println("[WIFI] Conexión perdida — modo seguro local");
    }
    unsigned long now = millis();
    if (now - lastWifiRetry > WIFI_RETRY_INTERVAL) {
      lastWifiRetry = now;
      connectWifi();
    }
  } else {
    if (wasOffline) {
      wasOffline = false;
      Serial.printf("[WIFI] Reconectado tras %.0f min offline\n",
                    (millis() - offlineSince) / 60000.0f);
      configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
      mqttInit(wifiClient, onProfileSet, onOtaTrigger);
    }
    // Mantener MQTT
    if (!mqttIsConnected()) {
      unsigned long now = millis();
      if (now - lastMqttRetry > MQTT_RETRY_INTERVAL) {
        lastMqttRetry = now;
        mqttConnect();
      }
    } else {
      mqttLoop();
      ArduinoOTA.handle();
    }
  }

  // Ciclo de sensores y control (cada 30 s)
  unsigned long now = millis();
  if (now - lastSensorMs < SENSOR_INTERVAL_MS) return;
  lastSensorMs = now;

  if (!activeProfile.loaded) return; // sin perfil → solo esperar

  controlTickCount++;
  SensorData    s = readAllSensors();
  ActuatorState a = computeControl(s, activeProfile);
  setAllActuators(a);

  if (mqttIsConnected()) {
    mqttPublishSensors(s, getCurrentActuatorState(), activeProfile);
    checkAlerts(s, activeProfile);

    // Publicar status completo cada 5 ciclos (~2.5 min)
    static uint8_t statusCounter = 0;
    if (++statusCounter >= 5) {
      statusCounter = 0;
      mqttPublishStatus(getCurrentActuatorState(), activeProfile);
    }

    // Alerta de fin de etapa — una vez por día cuando se cumple duracion_dias
    if (stageTrackerShouldAlert(activeProfile.etapa.duracionDias)) {
      StageInfo si = stageTrackerGet();
      char msg[128];
      snprintf(msg, sizeof(msg), "etapa_%s_completada", activeProfile.etapaActual);
      mqttPublishAlert(msg,
                       (float)si.dayElapsed,
                       (float)activeProfile.etapa.duracionDias,
                       "revisar_y_cambiar_etapa");
    }
  }
  // En modo offline: el ESP32 sigue leyendo y controlando — sin publicar
}
