#include "mqtt_client.h"
#include "config.h"
#include "actuators.h"
#include <WiFi.h>
#include <ArduinoJson.h>

static PubSubClient       mqttClient;
static ProfileSetCallback profileSetCb = nullptr;
static OtaTriggerCallback otaTriggerCb = nullptr;

// Topics construidos en init desde CAPSULE_ID
static char topicSensors[64];
static char topicStatus[64];
static char topicAlert[64];
static char topicProfileSet[64];
static char topicOta[64];

static void onMessage(char* topic, byte* payload, unsigned int len) {
  char msg[256] = {};
  unsigned int copyLen = min((unsigned int)sizeof(msg) - 1, len);
  memcpy(msg, payload, copyLen);
  msg[copyLen] = '\0';

  Serial.printf("[MQTT] RX [%s] %s\n", topic, msg);

  if (strcmp(topic, topicProfileSet) == 0) {
    JsonDocument doc;
    if (deserializeJson(doc, msg)) return;
    const char* perfil = doc["perfil"] | "";
    const char* etapa  = doc["etapa"]  | "incubacion";
    const char* conf   = doc["confirmacion"] | "";
    // Requiere confirmación explícita para cambios de perfil (seguridad)
    if (strcmp(conf, "CAMBIAR") != 0) {
      Serial.println("[MQTT] profile/set rechazado: falta confirmacion=CAMBIAR");
      return;
    }
    if (profileSetCb && strlen(perfil) > 0) profileSetCb(perfil, etapa);
  }

  if (strcmp(topic, topicOta) == 0) {
    if (strcmp(msg, "INICIAR") == 0 && otaTriggerCb) {
      Serial.println("[MQTT] OTA trigger recibido");
      otaTriggerCb();
    }
  }
}

void mqttInit(WiFiClient& wifiClient,
              ProfileSetCallback onProfileSet,
              OtaTriggerCallback onOtaTrigger) {
  profileSetCb = onProfileSet;
  otaTriggerCb = onOtaTrigger;

  snprintf(topicSensors,    sizeof(topicSensors),    "bichongos/%s/sensors",     CAPSULE_ID);
  snprintf(topicStatus,     sizeof(topicStatus),     "bichongos/%s/status",      CAPSULE_ID);
  snprintf(topicAlert,      sizeof(topicAlert),      "bichongos/%s/alert",       CAPSULE_ID);
  snprintf(topicProfileSet, sizeof(topicProfileSet), "bichongos/%s/profile/set", CAPSULE_ID);
  snprintf(topicOta,        sizeof(topicOta),        "bichongos/%s/ota",         CAPSULE_ID);

  mqttClient.setClient(wifiClient);
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(onMessage);
  mqttClient.setBufferSize(512);
}

bool mqttConnect() {
  if (mqttClient.connected()) return true;

  // Last will: publicar "offline" si el ESP32 se desconecta abruptamente
  char willTopic[64];
  snprintf(willTopic, sizeof(willTopic), "bichongos/%s/status", CAPSULE_ID);
  const char* willMsg = "{\"online\":false}";

  bool ok = mqttClient.connect(CAPSULE_ID, MQTT_USER, MQTT_PASS,
                               willTopic, 1, true, willMsg);
  if (ok) {
    mqttClient.subscribe(topicProfileSet);
    mqttClient.subscribe(topicOta);
    Serial.printf("[MQTT] Conectado al broker %s:%d\n", MQTT_SERVER, MQTT_PORT);

    // Anunciar que estamos online
    char onlineMsg[32];
    snprintf(onlineMsg, sizeof(onlineMsg), "{\"online\":true,\"id\":\"%s\"}", CAPSULE_ID);
    mqttClient.publish(willTopic, onlineMsg, true);
  } else {
    Serial.printf("[MQTT] Error de conexión, rc=%d\n", mqttClient.state());
  }
  return ok;
}

void mqttLoop() {
  mqttClient.loop();
}

void mqttPublishSensors(const SensorData& s, const ActuatorState& a, const Profile& p) {
  char buf[512];
  JsonDocument doc;

  doc["capsula_id"]     = CAPSULE_ID;
  doc["especie"]        = p.especie;
  doc["etapa"]          = p.etapaActual;
  doc["timestamp"]      = time(nullptr);
  doc["temperatura"]    = serialized(String(s.tempAire, 1));
  doc["humedad"]        = serialized(String(s.humedad, 1));
  doc["co2_ppm"]        = s.co2Ppm;
  doc["luz_lux"]        = serialized(String(s.luzLux, 0));
  doc["temp_sustrato"]  = serialized(String(s.tempSustrato, 1));

  JsonObject act = doc["actuadores"].to<JsonObject>();
  act["humidificador"] = a.humidificador;
  act["extractor"]     = a.extractor;
  act["calefactor"]    = a.calefactor;
  act["led"]           = a.led;

  JsonObject err = doc["errores_sensor"].to<JsonObject>();
  if (s.errorSHT31)    err["sht31"]   = true;
  if (s.errorMHZ19)    err["mhz19"]   = true;
  if (s.errorBH1750)   err["bh1750"]  = true;
  if (s.errorDS18B20)  err["ds18b20"] = true;

  serializeJson(doc, buf, sizeof(buf));
  mqttClient.publish(topicSensors, buf);
}

void mqttPublishAlert(const char* tipo, float valorActual, float umbral, const char* accion) {
  char buf[256];
  JsonDocument doc;
  doc["capsula_id"]    = CAPSULE_ID;
  doc["tipo"]          = tipo;
  doc["valor_actual"]  = serialized(String(valorActual, 1));
  doc["umbral"]        = serialized(String(umbral, 1));
  doc["accion"]        = accion;
  doc["timestamp"]     = time(nullptr);
  serializeJson(doc, buf, sizeof(buf));
  mqttClient.publish(topicAlert, buf);
  Serial.printf("[MQTT] ALERTA: %s val=%.1f umbral=%.1f\n", tipo, valorActual, umbral);
}

void mqttPublishStatus(const ActuatorState& a, const Profile& p) {
  char buf[256];
  JsonDocument doc;
  doc["capsula_id"]     = CAPSULE_ID;
  doc["perfil_activo"]  = p.id;
  doc["etapa"]          = p.etapaActual;
  doc["online"]         = true;
  doc["timestamp"]      = time(nullptr);
  JsonObject act = doc["actuadores"].to<JsonObject>();
  act["humidificador"]  = a.humidificador;
  act["extractor"]      = a.extractor;
  act["calefactor"]     = a.calefactor;
  act["led"]            = a.led;
  serializeJson(doc, buf, sizeof(buf));
  mqttClient.publish(topicStatus, buf, true); // retained
}

bool mqttIsConnected() {
  return mqttClient.connected();
}
