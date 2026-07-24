# Fixes Críticos de Firmware `capsula_core` — Plan de Implementación

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Corregir 7 bugs críticos de seguridad/lógica en `firmware/capsula_core/` (ESP32) encontrados en la auditoría del proyecto, y establecer por primera vez un build real (PlatformIO) para verificar que el código compila — nunca lo había hecho.

**Architecture:** Cambios quirúrgicos en los archivos existentes (`profile.h/.cpp`, `capsula_core.ino`, `mqtt_client.cpp`), sin reestructurar el sketch. Se agrega `platformio.ini` como entorno de build nuevo. Una preocupación por tarea, commit tras cada una.

**Tech Stack:** ESP32 Arduino framework, PlatformIO (`platform = espressif32`, `board = esp32dev`), ArduinoJson 7.x, PubSubClient.

Spec de referencia: `docs/superpowers/specs/2026-07-23-firmware-critical-fixes-design.md`

## Global Constraints

- **Verificación = compilar de verdad, no revisar a ojo.** Cada tarea termina corriendo `pio run -e esp32dev` desde `firmware/capsula_core/` y debe terminar en `[SUCCESS]`. No hay hardware físico ni framework de test unitario en este repo — no se dice "probado", se dice "compila y se revisó el diff" (regla de honestidad de la spec).
- **Librerías y plataforma ya verificadas por un build real** (no son suposición):
  `platform = espressif32` resuelve a `7.0.1` (Arduino-ESP32 core `3.20017.241212`), y estas versiones de librería instalan y compilan limpio:
  `knolleary/PubSubClient@^2.8`, `bblanchon/ArduinoJson@^7.0.0`, `adafruit/Adafruit SHT31 Library@^2.2.2`, `claws/BH1750@^1.3.0`, `wifwaf/MH-Z19@^1.5.4`, `paulstoffregen/OneWire@^2.3.7`, `milesburton/DallasTemperature@^3.11.0`.
- **API de watchdog para esta versión exacta de core:** `esp_task_wdt_init(uint32_t timeout_segundos, bool panic)` (firma simple, NO la variante con `esp_task_wdt_config_t` de cores más nuevos — se verificó leyendo el header real instalado).
- Comentarios y mensajes `Serial`/`mqttPublishAlert` en español, igual que el resto del archivo.
- No tocar: refrigeración activa de Enoki, campos de perfil no leídos (`luz_max_lux`, `oscuridad_total`, etc.), ni nada en `gateway/` — fuera de alcance según la spec.
- `config.h` es local y nunca se commitea (ya está en `.gitignore`); para compilar localmente, copiar `config.h.example` → `config.h` una vez (paso 0 de la Tarea 1).

---

### Task 1: Entorno de build PlatformIO + fix de compilación pre-existente

**Files:**
- Create: `firmware/capsula_core/platformio.ini`
- Modify: `firmware/capsula_core/mqtt_client.h`
- Modify: `.gitignore`

**Interfaces:**
- Produce: comando de verificación `pio run -e esp32dev` (ejecutado desde `firmware/capsula_core/`) que todas las tareas siguientes deben volver a correr.

- [ ] **Step 1: Crear `firmware/capsula_core/platformio.ini`**

```ini
[platformio]
src_dir = .

[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps =
    knolleary/PubSubClient@^2.8
    bblanchon/ArduinoJson@^7.0.0
    adafruit/Adafruit SHT31 Library@^2.2.2
    claws/BH1750@^1.3.0
    wifwaf/MH-Z19@^1.5.4
    paulstoffregen/OneWire@^2.3.7
    milesburton/DallasTemperature@^3.11.0
monitor_speed = 115200
```

- [ ] **Step 2: Fix — `mqtt_client.h` usa `WiFiClient` sin incluir `<WiFi.h>`**

En `firmware/capsula_core/mqtt_client.h`, cambiar:

```cpp
#pragma once
#include <Arduino.h>
#include <PubSubClient.h>
```

por:

```cpp
#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
```

- [ ] **Step 3: Agregar carpeta de build de PlatformIO a `.gitignore`**

En `.gitignore`, dentro de la sección "Compilados Arduino", agregar la línea:

```
firmware/capsula_core/.pio/
```

- [ ] **Step 4: Crear `config.h` local (no se commitea) para poder compilar**

```bash
cp firmware/capsula_core/config.h.example firmware/capsula_core/config.h
```

- [ ] **Step 5: Compilar y verificar que corre limpio**

```bash
cd firmware/capsula_core && pio run -e esp32dev
```

Esperado: termina en `========================= [SUCCESS] ... =========================`
con un resumen de memoria similar a:
```
RAM:   [==        ]  15.4% (used ~50460 bytes from 327680 bytes)
Flash: [=======   ]  69.0% (used ~903829 bytes from 1310720 bytes)
```

- [ ] **Step 6: Commit**

```bash
cd /Users/sergiomonsalve/Code/Bichongos
git add firmware/capsula_core/platformio.ini firmware/capsula_core/mqtt_client.h .gitignore
git commit -m "firmware: agregar entorno PlatformIO y fix de include faltante (WiFi.h)

Primer build real del firmware capsula_core — nunca se había compilado.
mqtt_client.h usaba WiFiClient sin incluir <WiFi.h>, error de compilación
inmediato que confirma que el código nunca pasó ni el primer nivel de
verificación."
```

---

### Task 2: Fix — `parseStage()` carga valores genéricos en silencio si la etapa no existe

**Files:**
- Modify: `firmware/capsula_core/profile.cpp:5`

**Interfaces:**
- Consume: nada nuevo.
- Produce: `parseStage()` ahora retorna `false` (no solo `true`) cuando la etapa no existe — comportamiento del que ya depende `loadProfile()` (línea 60), que ya maneja el caso de retorno `false` correctamente pero nunca lo recibía.

- [ ] **Step 1: Agregar el chequeo de nulo**

En `firmware/capsula_core/profile.cpp`, cambiar:

```cpp
static bool parseStage(JsonObject stage, StageParams& out) {
  out.tempMin     = stage["temp_min"]    | 15.0f;
```

por:

```cpp
static bool parseStage(JsonObject stage, StageParams& out) {
  if (stage.isNull()) return false;

  out.tempMin     = stage["temp_min"]    | 15.0f;
```

- [ ] **Step 2: Compilar**

```bash
cd firmware/capsula_core && pio run -e esp32dev
```

Esperado: `[SUCCESS]`.

- [ ] **Step 3: Commit**

```bash
cd /Users/sergiomonsalve/Code/Bichongos
git add firmware/capsula_core/profile.cpp
git commit -m "firmware: parseStage() ya no carga valores genéricos en silencio

Si etapa_actual no existe en el JSON del perfil, ahora retorna false
(el llamador loadProfile() ya sabía manejar esto, pero nunca lo recibía
porque parseStage() siempre devolvía true)."
```

---

### Task 3: Fix — posible lectura fuera de límites al copiar el payload MQTT

**Files:**
- Modify: `firmware/capsula_core/mqtt_client.cpp:18-20`

**Interfaces:**
- Consume: nada nuevo.
- Produce: nada nuevo expuesto a otros archivos (cambio interno de `onMessage`).

- [ ] **Step 1: Reemplazar `strlcpy` por copia acotada explícita**

En `firmware/capsula_core/mqtt_client.cpp`, cambiar:

```cpp
static void onMessage(char* topic, byte* payload, unsigned int len) {
  char msg[256] = {};
  strlcpy(msg, (char*)payload, min((unsigned int)sizeof(msg) - 1, len) + 1);
```

por:

```cpp
static void onMessage(char* topic, byte* payload, unsigned int len) {
  char msg[256] = {};
  unsigned int copyLen = min((unsigned int)sizeof(msg) - 1, len);
  memcpy(msg, payload, copyLen);
  msg[copyLen] = '\0';
```

(`strlcpy` escanea internamente el origen buscando `\0` más allá de `len` si el buffer se llena por completo — PubSubClient no garantiza que `payload` esté null-terminado. `memcpy` con longitud explícita no tiene ese problema.)

- [ ] **Step 2: Compilar**

```bash
cd firmware/capsula_core && pio run -e esp32dev
```

Esperado: `[SUCCESS]`.

- [ ] **Step 3: Commit**

```bash
cd /Users/sergiomonsalve/Code/Bichongos
git add firmware/capsula_core/mqtt_client.cpp
git commit -m "firmware: evitar posible overread al copiar payload MQTT

strlcpy() escanea más allá del buffer buscando el terminador nulo cuando
no lo encuentra dentro de 'len' bytes; payload de PubSubClient no
garantiza null-termination. memcpy + terminador explícito lo evita."
```

---

### Task 4: Agregar watchdog de hardware

**Files:**
- Modify: `firmware/capsula_core/capsula_core.ino`

**Interfaces:**
- Consume: nada nuevo.
- Produce: nada expuesto a otros archivos — el ESP32 se reinicia solo si `loop()` no llama `esp_task_wdt_reset()` dentro de `WDT_TIMEOUT_S` segundos.

- [ ] **Step 1: Incluir el header**

En `firmware/capsula_core/capsula_core.ino`, cambiar:

```cpp
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <time.h>
```

por:

```cpp
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <time.h>
#include <esp_task_wdt.h>
```

- [ ] **Step 2: Agregar la constante de timeout**

Cambiar:

```cpp
static const unsigned long MQTT_RETRY_INTERVAL = 10000UL;
```

por:

```cpp
static const unsigned long MQTT_RETRY_INTERVAL = 10000UL;
static const uint32_t      WDT_TIMEOUT_S       = 60;   // ciclo normal es 30s; da margen de 1 ciclo perdido
```

- [ ] **Step 3: Inicializar el watchdog en `setup()`**

Cambiar:

```cpp
  initActuators();
  initSensors();
  stageTrackerInit();
```

por:

```cpp
  esp_task_wdt_init(WDT_TIMEOUT_S, true); // reinicia el ESP32 si loop() se cuelga
  esp_task_wdt_add(NULL);

  initActuators();
  initSensors();
  stageTrackerInit();
```

- [ ] **Step 4: Alimentar el watchdog en cada vuelta de `loop()`**

Cambiar:

```cpp
void loop() {
  // OTA tiene prioridad total cuando está pendiente
```

por:

```cpp
void loop() {
  esp_task_wdt_reset();

  // OTA tiene prioridad total cuando está pendiente
```

- [ ] **Step 5: Compilar**

```bash
cd firmware/capsula_core && pio run -e esp32dev
```

Esperado: `[SUCCESS]`. (Nota: la firma `esp_task_wdt_init(uint32_t, bool)` es la correcta para el core resuelto por este `platformio.ini` — si en el futuro se actualiza el `platform` de espressif32 a una versión con Arduino-ESP32 core 3.x, esta firma cambia a una basada en `esp_task_wdt_config_t`; no aplica hoy.)

- [ ] **Step 6: Commit**

```bash
cd /Users/sergiomonsalve/Code/Bichongos
git add firmware/capsula_core/capsula_core.ino
git commit -m "firmware: agregar watchdog de hardware (esp_task_wdt)

Sin esto, un loop() colgado (ej. I2C bloqueado) deja los actuadores en
su último estado indefinidamente sin recuperación, en una cámara sellada.
Timeout de 60s da margen de un ciclo de control perdido (30s) antes de
forzar el reinicio."
```

---

### Task 5: Agregar alerta de CO2 mínimo crítico (Enoki)

**Files:**
- Modify: `firmware/capsula_core/profile.h`
- Modify: `firmware/capsula_core/profile.cpp`
- Modify: `firmware/capsula_core/capsula_core.ino`

**Interfaces:**
- Produce: nuevo campo `AlertThresholds.co2CriticoMin` (int, 0 = no aplica — mismo patrón que `StageParams.co2Min`), leído por `checkAlerts()`.

- [ ] **Step 1: Agregar el campo a `AlertThresholds`**

En `firmware/capsula_core/profile.h`, cambiar:

```cpp
struct AlertThresholds {
  float tempCriticaMax;
  float tempCriticaMin;
  float humedadCriticaMin;
  int   co2CriticoMax;
};
```

por:

```cpp
struct AlertThresholds {
  float tempCriticaMax;
  float tempCriticaMin;
  float humedadCriticaMin;
  int   co2CriticoMax;
  int   co2CriticoMin;  // solo Enoki; 0 = no aplica
};
```

- [ ] **Step 2: Parsear el campo en `loadProfile()`**

En `firmware/capsula_core/profile.cpp`, cambiar:

```cpp
  out.alertas.co2CriticoMax    = doc["alertas"]["co2_critico_max"]     | 5000;
```

por:

```cpp
  out.alertas.co2CriticoMax    = doc["alertas"]["co2_critico_max"]     | 5000;
  out.alertas.co2CriticoMin    = doc["alertas"]["co2_critico_min"]     | 0;
```

- [ ] **Step 3: Chequear el umbral en `checkAlerts()`**

En `firmware/capsula_core/capsula_core.ino`, cambiar:

```cpp
  if (!s.errorMHZ19 && s.co2Ppm > a.co2CriticoMax)
    mqttPublishAlert("co2_critico_max", s.co2Ppm, a.co2CriticoMax, "extractor_on");
```

por:

```cpp
  if (!s.errorMHZ19 && s.co2Ppm > a.co2CriticoMax)
    mqttPublishAlert("co2_critico_max", s.co2Ppm, a.co2CriticoMax, "extractor_on");
  if (!s.errorMHZ19 && a.co2CriticoMin > 0 && s.co2Ppm < a.co2CriticoMin)
    mqttPublishAlert("co2_critico_min", s.co2Ppm, a.co2CriticoMin, "revisar_sellado_camara");
```

- [ ] **Step 4: Compilar**

```bash
cd firmware/capsula_core && pio run -e esp32dev
```

Esperado: `[SUCCESS]`.

- [ ] **Step 5: Commit**

```bash
cd /Users/sergiomonsalve/Code/Bichongos
git add firmware/capsula_core/profile.h firmware/capsula_core/profile.cpp firmware/capsula_core/capsula_core.ino
git commit -m "firmware: evaluar alerta co2_critico_min (Enoki)

N3-enoki.json define alertas.co2_critico_min=1500 desde hace tiempo,
pero AlertThresholds no tenía el campo y checkAlerts() nunca lo
comprobaba — un sellado defectuoso que baje el CO2 en Enoki no
generaba ninguna alerta."
```

---

### Task 6: `profile/set` cambia de especie de verdad (no solo de etapa)

**Files:**
- Modify: `firmware/capsula_core/profile.h`
- Modify: `firmware/capsula_core/profile.cpp`
- Modify: `firmware/capsula_core/capsula_core.ino`
- Modify: `firmware/capsula_core/README.md:56-57`
- Create: `firmware/capsula_core/data/profiles/N1-orellana.json` (+ 9 más, copiados de `firmware/profiles/`)
- Delete: `firmware/capsula_core/data/profile.json`

**Interfaces:**
- Consume: `parseStage()` con el chequeo de nulo de la Tarea 2 (se reutiliza sin cambios).
- Produce: `bool loadProfile(const char* path, const char* stageOverride, Profile& out)` — nueva firma (antes `loadProfile(const char* path, Profile& out)`), usada por `setup()` y por `onProfileSet()`. `stageOverride` en `nullptr` o `""` usa la etapa que el propio JSON declara en `etapa_actual`; si no, fuerza esa etapa.
- Elimina: `setStage()` y `reloadProfileStage()` (quedaban sin otro llamador tras este cambio — ver verificación de la Tarea, tarea de grep incluida en Step 1).

- [ ] **Step 1: Confirmar que `setStage`/`reloadProfileStage` no se usan en ningún otro lado**

```bash
grep -rn "setStage\|reloadProfileStage" firmware/
```

Esperado: solo apariciones en `profile.h` (declaración), `profile.cpp` (definición) y `capsula_core.ino:44` (el único llamador, que esta tarea reemplaza). Si aparece algo más, detener y ajustar el plan — no eliminar una función que otro archivo sigue usando.

- [ ] **Step 2: Cambiar la firma de `loadProfile` y quitar `setStage`/`reloadProfileStage` en `profile.h`**

Cambiar:

```cpp
bool    loadProfile(const char* path, Profile& out);
bool    setStage(Profile& p, const char* stage, JsonDocument& doc);
bool    reloadProfileStage(const char* stage, Profile& out);
void    printProfile(const Profile& p);
```

por:

```cpp
bool    loadProfile(const char* path, const char* stageOverride, Profile& out);
void    printProfile(const Profile& p);
```

- [ ] **Step 3: Implementar el `stageOverride` y quitar `setStage`/`reloadProfileStage` en `profile.cpp`**

Cambiar:

```cpp
bool loadProfile(const char* path, Profile& out) {
```

por:

```cpp
bool loadProfile(const char* path, const char* stageOverride, Profile& out) {
```

Cambiar:

```cpp
  strlcpy(out.etapaActual, doc["etapa_actual"]  | "incubacion",  sizeof(out.etapaActual));
```

por:

```cpp
  strlcpy(out.etapaActual, doc["etapa_actual"]  | "incubacion",  sizeof(out.etapaActual));
  if (stageOverride && strlen(stageOverride) > 0) {
    strlcpy(out.etapaActual, stageOverride, sizeof(out.etapaActual));
  }
```

Borrar por completo estas dos funciones (ya no tienen llamador tras el Step 4):

```cpp
bool setStage(Profile& p, const char* stage, JsonDocument& doc) {
  JsonObject stageObj = doc["etapas"][stage];
  if (stageObj.isNull()) {
    Serial.printf("[PROFILE] ERROR: etapa '%s' no existe en perfil\n", stage);
    return false;
  }
  strlcpy(p.etapaActual, stage, sizeof(p.etapaActual));
  return parseStage(stageObj, p.etapa);
}

bool reloadProfileStage(const char* stage, Profile& out) {
  // Lee el perfil completo desde SPIFFS y cambia a la etapa indicada
  if (!SPIFFS.begin(false)) return false;
  File f = SPIFFS.open(PROFILE_PATH, "r");
  if (!f) return false;
  JsonDocument doc;
  if (deserializeJson(doc, f)) { f.close(); return false; }
  f.close();
  return setStage(out, stage, doc);
}
```

- [ ] **Step 4: Reescribir `onProfileSet()` en `capsula_core.ino` para cambiar de especie de verdad**

Agregar el include de `<ctype.h>` (para `isalnum`). Cambiar:

```cpp
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <time.h>
#include <esp_task_wdt.h>
```

por:

```cpp
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <time.h>
#include <esp_task_wdt.h>
#include <ctype.h>
```

Cambiar:

```cpp
void onProfileSet(const char* newProfile, const char* newStage) {
  Serial.printf("[MAIN] Cambio de etapa solicitado → perfil:%s etapa:%s\n",
                newProfile, newStage);
  if (reloadProfileStage(newStage, activeProfile)) {
    stageTrackerSetStage(newStage);  // reiniciar contador de días
    Serial.printf("[MAIN] Etapa actualizada a '%s'\n", newStage);
    mqttPublishStatus(getCurrentActuatorState(), activeProfile);
  } else {
    Serial.printf("[MAIN] Error: etapa '%s' no encontrada en perfil\n", newStage);
  }
}
```

por:

```cpp
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
```

(`profileIdIsSafe` restringe el id recibido por MQTT a `[A-Za-z0-9_-]` antes de usarlo para construir una ruta de archivo — evita path traversal tipo `../../algo`.)

- [ ] **Step 5: Actualizar la llamada a `loadProfile` en `setup()`**

Cambiar:

```cpp
  if (!loadProfile(PROFILE_PATH, activeProfile)) {
```

por:

```cpp
  if (!loadProfile(PROFILE_PATH, nullptr, activeProfile)) {
```

- [ ] **Step 6: Reestructurar `data/` — perfiles reales en vez del duplicado único**

```bash
mkdir -p firmware/capsula_core/data/profiles
cp firmware/profiles/N1-orellana.json firmware/capsula_core/data/profiles/
cp firmware/profiles/N2-melena-de-leon.json firmware/capsula_core/data/profiles/
cp firmware/profiles/N2-portobello.json firmware/capsula_core/data/profiles/
cp firmware/profiles/N2-shiitake.json firmware/capsula_core/data/profiles/
cp firmware/profiles/N3-cola-de-pavo.json firmware/capsula_core/data/profiles/
cp firmware/profiles/N3-enoki.json firmware/capsula_core/data/profiles/
cp firmware/profiles/N3-maitake.json firmware/capsula_core/data/profiles/
cp firmware/profiles/N3-reishi.json firmware/capsula_core/data/profiles/
cp firmware/profiles/N4-cordyceps.json firmware/capsula_core/data/profiles/
cp firmware/profiles/N4-psilocybe.json firmware/capsula_core/data/profiles/
rm firmware/capsula_core/data/profile.json
```

- [ ] **Step 7: Actualizar el diagrama de estructura en `firmware/capsula_core/README.md`**

Cambiar:

```
└── data/                 # Perfiles JSON (se sube a SPIFFS)
    └── profile.json      # Perfil activo (copia del elegido)
```

por:

```
└── data/                 # Perfiles JSON (se sube a SPIFFS)
    └── profiles/         # Los 10 perfiles de especie (copia de firmware/profiles/)
        └── N1-orellana.json, N3-enoki.json, ...
```

- [ ] **Step 8: Compilar**

```bash
cd firmware/capsula_core && pio run -e esp32dev
```

Esperado: `[SUCCESS]`. (El build no valida el contenido de `data/` — esa carpeta se sube a SPIFFS por separado con la herramienta de subida; la compilación solo verifica el código C++.)

- [ ] **Step 9: Commit**

```bash
cd /Users/sergiomonsalve/Code/Bichongos
git add firmware/capsula_core/profile.h firmware/capsula_core/profile.cpp \
        firmware/capsula_core/capsula_core.ino firmware/capsula_core/README.md \
        firmware/capsula_core/data/
git commit -m "firmware: profile/set ahora cambia de especie de verdad

Antes solo cambiaba de etapa dentro del mismo perfil fijo en compilación
(PROFILE_PATH); la 'especie' recibida por MQTT se ignoraba por completo.
Ahora precarga los 10 perfiles en SPIFFS bajo /profiles/<id>.json,
sanitiza el id recibido (evita path traversal) y carga el perfil completo
con loadProfile(path, stage, out). setStage()/reloadProfileStage()
quedaron sin uso y se eliminaron."
```

---

### Task 7: Arbitraje en pulsos cuando coinciden frío crítico y CO2 crítico (Enoki)

**Files:**
- Modify: `firmware/capsula_core/capsula_core.ino`

**Interfaces:**
- Consume: `Profile::alertas.co2CriticoMax` (ya existía antes de este plan).
- Produce: nada expuesto a otros archivos.

- [ ] **Step 1: Agregar el contador de ciclos**

Cambiar:

```cpp
static bool          wasOffline    = false;
```

por:

```cpp
static bool          wasOffline    = false;
static uint32_t      controlTickCount = 0; // cuenta ciclos de control, usado para el pulso de ventilacion en conflicto frio/CO2
```

- [ ] **Step 2: Reemplazar el apagado incondicional del extractor por pulsos**

En `computeControl()`, cambiar:

```cpp
  // Calefactor y extractor no deben ser simultáneos
  if (next.calefactor && next.extractor) next.extractor = false;
```

por:

```cpp
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
```

- [ ] **Step 3: Incrementar el contador una vez por ciclo de control**

En `loop()`, cambiar:

```cpp
  SensorData    s = readAllSensors();
  ActuatorState a = computeControl(s, activeProfile);
  setAllActuators(a);
```

por:

```cpp
  controlTickCount++;
  SensorData    s = readAllSensors();
  ActuatorState a = computeControl(s, activeProfile);
  setAllActuators(a);
```

- [ ] **Step 4: Compilar**

```bash
cd firmware/capsula_core && pio run -e esp32dev
```

Esperado: `[SUCCESS]`.

- [ ] **Step 5: Commit**

```bash
cd /Users/sergiomonsalve/Code/Bichongos
git add firmware/capsula_core/capsula_core.ino
git commit -m "firmware: ventilar en pulsos cuando Enoki tiene frío+CO2 crítico a la vez

Antes, si calefactor y extractor debían activarse simultáneamente
(el caso normal de Enoki: frío + CO2 alto conviven), el extractor se
apagaba incondicionalmente y el CO2 podía seguir subiendo sin ventilar.
Ahora, cuando el CO2 está en zona crítica (co2_critico_max), el
extractor pulsa 1 de cada 4 ciclos de control (30s ON / 90s OFF) en vez
de quedar apagado por completo. Decisión de arbitraje confirmada por
el usuario."
```

---

## Verificación final de todo el plan

Tras la Tarea 7, correr una vez más desde cero para confirmar que no quedó nada roto por el orden de aplicación:

```bash
cd firmware/capsula_core && rm -rf .pio && pio run -e esp32dev
```

Esperado: `[SUCCESS]`. Este comando ya fue probado con los 7 fixes aplicados juntos (fuera de este repo, en una copia temporal) y compiló limpio con `RAM: 15.4% (50468 bytes) / Flash: 69.0% (904145 bytes)` — los números reales tras aplicar el plan deberían ser muy cercanos a estos.

**Pendiente explícito, no incluido en este plan:** ninguna de estas tareas fue probada en un ESP32 físico — no existe cápsula construida (bloqueador conocido `F1-05` en `BACKLOG.md`). El primer despliegue real a hardware debe repetir esta verificación en campo antes de confiar en el comportamiento.
