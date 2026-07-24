# SOP — Primer Despliegue: Gateway + Cápsula Mini + Firmware

> Guía secuencial para poner en funcionamiento la primera cápsula física de Bichongos, de principio
> a fin. Referencia otros documentos del proyecto en vez de duplicarlos — este documento es el
> **orden de ejecución**, no la fuente de verdad de cada detalle técnico.

**Tarea relacionada:** F1-05, GW-11, IOT-18 en `BACKLOG.md`
**Documentos de referencia:** `docs/bom-precios-cop.md` · `docs/capsula/diagrama-electrico-capsula-mini.md` · `gateway/README.md` · `firmware/capsula_core/README.md`

---

## Por qué este orden

El gateway va primero porque la cápsula necesita un broker MQTT al que publicar desde el primer
encendido — sin gateway, no hay forma de confirmar que el ESP32 realmente está funcionando más
allá del Monitor Serial. El firmware va al final porque depende de que el cableado ya esté
verificado con el checklist de seguridad — nunca se energiza un cableado sin verificar primero.

---

## Fase A — Gateway (Raspberry Pi)

**Criterio de aceptación:** los 4 servicios (Mosquitto, Node-RED, InfluxDB, Grafana) responden en
sus puertos y un mensaje de prueba MQTT se ve reflejado en Grafana.

- [ ] Montar el Raspberry Pi con SSD por USB y UPS (`gateway/README.md` — sección "Hardware requerido")
- [ ] Correr `gateway/scripts/setup.sh` — instala Mosquitto, Node-RED, InfluxDB y Grafana en orden
- [ ] Copiar `gateway/mosquitto/mosquitto.conf.example` → conf real y crear usuario/contraseña MQTT para `capsula-01` (`mosquitto_passwd`)
- [ ] Verificar Mosquitto: `mosquitto_pub -h localhost -t "test/hello" -m "hola"` + `mosquitto_sub` en otra terminal
- [ ] Verificar Node-RED en `http://<ip-rpi>:1880`
- [ ] Verificar Grafana en `http://<ip-rpi>:3000` (dashboard inicial cargado)
- [ ] Configurar backup automático (`gateway/scripts/backup.sh`) y shutdown seguro de UPS (`gateway/scripts/ups-shutdown.sh`)

**Al terminar:** marcar GW-11 como ✅ en `BACKLOG.md` — recién ahí el gateway está realmente
desplegado, no solo revisado como código.

---

## Fase B — Construcción física de la cápsula Mini

**Criterio de aceptación:** los 4 sensores muestran lecturas correctas en el Monitor Serial y los
4 canales de relé responden a un comando manual, antes de cerrar la cápsula.

### B.1 Materiales (ver `docs/bom-precios-cop.md` sección 2 para specs y proveedores)

- [ ] Nevera usada 150–200 L, buen sello
- [ ] Nodo IoT completo: ESP32 DevKit V1, SHT31, MH-Z19B, BH1750, DS18B20, módulo relé 4 canales
- [ ] Actuadores: humidificador ultrasónico, extractor FAE 12V, calefactor PTC 100W, tira LED 12V
- [ ] Fuentes: 5V/2A (ESP32+sensores) y 12V/3A (actuadores DC)
- [ ] Caja estanca IP65, prensaestopas PG9 (x4), resistencia 4.7 kΩ, cableado y borneras

### B.2 Preparar la nevera

- [ ] Perforar 4 entradas para prensaestopas (sensores I2C, MH-Z19B, DS18B20, alimentación 110V AC)
- [ ] Sellar cada perforación con silicona alrededor del prensaestopa
- [ ] Montar la caja de control **por fuera** de la nevera, nunca adentro

### B.3 Cablear el módulo de relés

- [ ] **Remover el puente JD-VCC/VCC** del módulo (si no se hace, se arriesga el ESP32)
- [ ] `JD-VCC → 5V` (fuente externa, alimenta las bobinas)
- [ ] `VCC → 3.3V` (señal de control del ESP32)
- [ ] Confirmar lógica invertida: `IN = LOW` enciende el actuador, `IN = HIGH` lo apaga

### B.4 Conectar sensores (ver `docs/capsula/diagrama-electrico-capsula-mini.md` secciones 3–4 para el detalle completo)

| Sensor | Pines | Nota crítica |
|---|---|---|
| SHT31 + BH1750 (bus compartido) | SDA→GPIO21, SCL→GPIO22 | VCC → **3.3V**, no 5V |
| MH-Z19B | TX→GPIO16, RX→GPIO17 | VCC → **5V externo**, no el 3.3V del ESP32 |
| DS18B20 | DATA→GPIO4 | Resistencia 4.7 kΩ entre DATA y 3.3V — **obligatoria** |

### B.5 Conectar relés → actuadores

GPIO26 (humidificador) · GPIO27 (extractor) · GPIO14 (calefactor, **110V AC**) · GPIO12 (LED)

- [ ] El calefactor es el único componente en 110V AC directo — el relé interrumpe la **fase**, nunca el neutro
- [ ] Chasis del calefactor conectado a tierra
- [ ] Cableado AC separado del DC por mínimo 5 cm

### B.6 Checklist de seguridad ANTES de dar corriente (multímetro, todo apagado)

- [ ] Sin continuidad entre 110V AC y ningún cable DC
- [ ] Continuidad de tierra del calefactor hasta el chasis
- [ ] Resistencia 4.7 kΩ instalada en GPIO4
- [ ] Puente JD-VCC/VCC removido
- [ ] Todos los prensaestopas sellados
- [ ] Protección GFCI en el tomacorriente de la cápsula

### B.7 Primer encendido (sin actuadores conectados)

- [ ] 3.3V presente en el ESP32 (multímetro)
- [ ] 5V presente en el MH-Z19B (multímetro)
- [ ] Monitor Serial (115200 baud) muestra lecturas de SHT31, BH1750, MH-Z19B (esperar 3 min de estabilización) y DS18B20

### B.8 Conectar y probar actuadores (uno a la vez)

- [ ] CH1 humidificador: enciende → apaga
- [ ] CH2 extractor: enciende → apaga
- [ ] CH3 calefactor: ⚠️ 5 segundos con cuidado → apaga → verificar que la nevera no acumula calor excesivo
- [ ] CH4 LED: enciende → apaga

---

## Fase C — Firmware

**Criterio de aceptación:** el ESP32 publica en `bichongos/capsula-01/sensors` cada 30 s y los
datos aparecen en Grafana.

- [ ] `cp firmware/capsula_core/config.h.example firmware/capsula_core/config.h`
- [ ] Editar `config.h`: WiFi real, IP del gateway, usuario/contraseña MQTT de `capsula-01`, `PROFILE_PATH "/profiles/N1-orellana.json"`
- [ ] `cd firmware/capsula_core && pio run -e esp32dev -t uploadfs` (sube los 10 perfiles JSON a SPIFFS)
- [ ] `pio run -e esp32dev -t upload` (flashea el firmware — primera vez en hardware físico real)
- [ ] Monitor Serial: confirmar conexión WiFi y MQTT
- [ ] Confirmar en Grafana o con `mosquitto_sub -t "bichongos/#"` que los datos llegan

---

## Fase D — Primera prueba real (IOT-18)

**Criterio de aceptación:** un ciclo completo de incubación de orellana corre con control
automático y sin intervención manual durante al menos 48 h continuas.

- [ ] Cargar el primer lote de orellana (cuando llegue la cepa — ver CUL-01) siguiendo `docs/protocolos/SOP-pasteurizacion.md` e `SOP-inoculacion.md`
- [ ] Confirmar que el perfil activo es el correcto (`etapa_actual: "incubacion"` en el JSON)
- [ ] Dejar correr 48 h y revisar en Grafana que temperatura/humedad se mantienen dentro de rango sin intervención
- [ ] Registrar cualquier alerta recibida por MQTT/Telegram y su causa real

---

## Qué hacer si algo falla

No marcar ninguna fase como completa si un paso de verificación no pasó — repórtalo y corrige
antes de avanzar a la siguiente fase. Si el firmware no compila o el hardware no responde como se
espera, usar el subagente `firmware-iot-reviewer` (`.claude/agents/`) para revisar antes de asumir
que es un problema de hardware.

---

*Bichongos · docs/capsula/SOP-primer-despliegue.md · v1.0 · 2026-07-23*
