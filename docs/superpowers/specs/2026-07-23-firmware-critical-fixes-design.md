# Fixes críticos de firmware — `capsula_core`

**Fecha:** 2026-07-23
**Estado:** Aprobado, en implementación

## Contexto

Una auditoría completa del proyecto (4 agentes en paralelo: código técnico, documentación,
negocio, configuración de Claude Code) encontró que el firmware ESP32 (`firmware/capsula_core/`),
marcado como completado en `BACKLOG.md` (IOT-01 a IOT-20), tiene defectos de seguridad y lógica
reales que nunca fueron verificados — ni siquiera compilados: no existe `platformio.ini` ni
ningún proyecto de build en el repo.

Esto es exactamente el antipatrón "aceptación delegada a la IA" / "confianza silenciosa"
descrito en la guía de desarrollo unificado (Jorge Johnson, jun-2026): código generado que
funciona en apariencia pero nunca pasó ni el primer nivel de la pirámide de verificación.

No hay cápsula física construida todavía (F1-05 pendiente), así que esta ronda de fixes se
verifica por **compilación real + revisión de diff**, no por ejecución en hardware.

## Alcance

### Dentro de alcance — 7 fixes en `firmware/capsula_core/`

1. **`parseStage()` silencioso** (`profile.cpp:5-24`) — no valida si `stage` (JsonObject) es
   nulo antes de leer sus campos con operador `|` (default). Si `etapa_actual` no existe en el
   JSON, carga valores genéricos (15-25°C, 70-95% HR, CO2 9999) sin loguear ni fallar.
   **Fix:** agregar `if (stage.isNull()) return false;` al inicio de `parseStage()`.

2. **Sin watchdog de hardware** — ningún archivo usa `esp_task_wdt`. Un `loop()` colgado
   (I2C bloqueado, etc.) deja los actuadores en su último estado indefinidamente, sin
   recuperación automática, en una cámara sellada.
   **Fix:** inicializar `esp_task_wdt` con timeout ~60s (el ciclo normal de control es de 30s,
   da margen de un ciclo perdido antes de forzar reinicio), alimentarlo en cada vuelta de `loop()`.

3. **`profile/set` no cambia de especie, solo de etapa** (`capsula_core.ino:41-51`,
   `profile.cpp:81-90`) — `onProfileSet()` recibe `newProfile` pero nunca lo usa;
   `reloadProfileStage()` siempre relee el mismo `PROFILE_PATH` fijo en compilación. La
   funcionalidad documentada en `CLAUDE.md` ("cambiar perfil remotamente") no existe.
   **Fix:**
   - Precargar los 10 perfiles de especie en SPIFFS bajo `/profiles/<id>.json`
     (mismo naming que `firmware/profiles/*.json`).
   - Sanitizar el campo `perfil` recibido por MQTT contra `^[A-Za-z0-9_-]+$` antes de
     construir la ruta (evita path traversal tipo `../../`).
   - Cambiar `onProfileSet()` para llamar `loadProfile()` completo con la nueva ruta
     (no solo `reloadProfileStage()`, que no actualiza id/especie/alertas).

4. **Alerta `co2_critico_min` de Enoki nunca se evalúa** — `N3-enoki.json` define
   `alertas.co2_critico_min: 1500` pero `AlertThresholds` (`profile.h`) no tiene ese campo y
   `checkAlerts()` no lo comprueba.
   **Fix:** agregar `co2CriticoMin` a `AlertThresholds` (0 = no aplica, mismo patrón que
   `co2Min` en `StageParams`), parsearlo en `loadProfile()`, chequearlo en `checkAlerts()`.

5. **Arbitraje frío-crítico + CO2-crítico simultáneo** (`capsula_core.ino:84-85`) —
   `if (next.calefactor && next.extractor) next.extractor = false;` apaga el extractor
   incondicionalmente aunque el CO2 esté en zona crítica alta. Es el escenario normal de
   Enoki (frío + CO2 alto conviven).
   **Fix (decisión de usuario):** ventilar en pulsos cortos en vez de todo-o-nada. Dado que
   el ciclo de control ya corre cada `SENSOR_INTERVAL_MS` = 30s, "30s ON / 90s OFF" se mapea
   exactamente a **1 de cada 4 ciclos** sin necesitar temporización adicional: cuando coinciden
   `calefactor` requerido y CO2 en zona crítica (no solo `co2Max` de etapa, sino el umbral
   `co2CriticoMax`/`co2CriticoMin` de alertas), el extractor se activa 1 tick de cada 4 en vez
   de quedar apagado por completo.

6. **Ruta SPIFFS inconsistente + duplicado** — `config.h.example:24` apunta a
   `/profiles/N1-orellana.json`, pero `firmware/capsula_core/data/` solo tiene `profile.json`
   (sin subcarpeta, nombre distinto) — con la config de ejemplo tal cual, el equipo arranca en
   modo seguro desde el primer boot. Además `data/profile.json` es un duplicado byte-a-byte de
   `firmware/profiles/N1-orellana.json`, con riesgo de divergencia silenciosa.
   **Fix:** se resuelve junto con el punto 3 — reemplazar `data/profile.json` por
   `data/profiles/*.json` (copia de los 10 perfiles reales de `firmware/profiles/`), y el
   `PROFILE_PATH` de `config.h.example` queda como `/profiles/N1-orellana.json` (ahora sí
   existe esa ruta).

7. **Posible overread en `strlcpy` del payload MQTT** (`mqtt_client.cpp:20`) —
   `strlcpy(msg, (char*)payload, min(sizeof(msg)-1, len)+1)` puede, cuando `len >= 255`,
   activar el escaneo interno de `strlcpy` que busca `\0` más allá del buffer real de
   `payload` (que PubSubClient no garantiza null-terminado).
   **Fix:** reemplazar por `memcpy` de `min(sizeof(msg)-1, len)` bytes + `msg[copyLen] = '\0'`
   explícito, sin depender del escaneo de `strlcpy`.

### Fuera de alcance (explícitamente diferido)

- **Refrigeración activa de Enoki** — no es un bug de código; es una decisión de hardware sin
  resolver (`diseno-capsula.md` especifica Peltier TEC1-12706, `N3-enoki.md`/`README.md`
  especifican mini-split 9000 BTU — se contradicen, y ninguno de los dos existe como canal de
  relé en `actuators.h`). Requiere decisión de hardware antes de poder tocar firmware. Queda
  como ítem de backlog/ADR, no como fix de esta ronda.
- **Campos "decorativos" nunca leídos** (`luz_max_lux`, `oscuridad_total`, `choque_frio`,
  `induccion_inmersion`, etc.) — son funcionalidad faltante, no bugs de un flujo existente.
  Ronda aparte.
- **Hallazgos del lado del gateway** (Node-RED instalado sin verificar checksum, usuario
  `admin` huérfano en `mosquitto/acl.example`, parsing frágil de `.env` en bash) — fuera de
  alcance porque el usuario pidió específicamente "firmware".

## Verificación

- Crear `firmware/capsula_core/platformio.ini` mínimo (entorno `esp32dev`, librerías del
  `README.md`: PubSubClient, ArduinoJson, Adafruit SHT31, BH1750, MHZ19, OneWire,
  DallasTemperature) — **no existía ningún proyecto de build antes de este fix.**
- Correr `pio run` tras cada fix para confirmar compilación real.
- Revisión manual de diff por cambio (una preocupación a la vez, siguiendo la guía de Jorge).
- **Honestidad explícita:** esto es "compila y se revisó", no "probado en dispositivo real" —
  no hay cápsula física construida (bloqueador conocido en `BACKLOG.md`). Se documentará así
  en el changelog/commit, no como "verificado" sin calificar.

## Riesgos abiertos

- El sanitizado de `perfil` (punto 3) rechaza silenciosamente IDs que no matcheen el patrón;
  se debe loguear el rechazo por Serial y MQTT alert para que sea visible, no un fallo mudo.
- Los 10 archivos de perfil ocupan espacio en SPIFFS (partición típica de ESP32 ~1.5MB con el
  particionado por defecto de Arduino) — los JSON son pequeños (~1-2KB c/u), no debería ser un
  problema, pero no se ha medido con la partición real que se use en el proyecto.
