# Firmware — Cápsula Core (ESP32)

> Firmware Arduino para el nodo ESP32 de cada cápsula. Lee sensores, aplica el perfil JSON de la especie activa y controla los actuadores vía relés.

---

## Dependencias (librerías Arduino)

Instalar desde el Gestor de Librerías del IDE Arduino:

| Librería | Versión recomendada | Para |
|---------|-------------------|------|
| `PubSubClient` | ≥ 2.8 | Comunicación MQTT |
| `ArduinoJson` | ≥ 7.x | Parsear perfiles JSON |
| `Adafruit SHT31` | ≥ 2.2 | Sensor temperatura/humedad |
| `BH1750` | ≥ 1.3 | Sensor de luz |
| `MHZ19` | ≥ 1.5 | Sensor CO₂ |
| `OneWire` + `DallasTemperature` | latest | Sensor DS18B20 |
| `SPIFFS` | (incluida en ESP32 core) | Almacenamiento de perfiles JSON |
| `WiFi` | (incluida en ESP32 core) | Conectividad WiFi |
| `ArduinoOTA` | (incluida en ESP32 core) | Actualizaciones OTA |

---

## Configuración

1. Copiar `config.h.example` → `config.h`
2. Editar `config.h` con las credenciales del entorno:

```cpp
// config.h — NO subir a git
#define WIFI_SSID     "nombre_red_wifi"
#define WIFI_PASSWORD "contraseña_wifi"
#define MQTT_SERVER   "192.168.1.X"   // IP del Raspberry Pi
#define MQTT_PORT     1883
#define CAPSULA_ID    "capsula-01"    // ID único por nodo
#define PERFIL_JSON   "/profiles/N1-orellana.json"  // Perfil activo
```

3. Cargar el perfil JSON de la especie a la memoria SPIFFS del ESP32:
   - Herramienta: **ESP32 Sketch Data Upload** (plugin para Arduino IDE)
   - Los archivos JSON van en la carpeta `data/` del sketch

---

## Estructura del sketch

```
firmware/capsula_core/
├── capsula_core.ino      # Sketch principal
├── config.h.example      # Template de credenciales
├── sensors.h / .cpp      # Lectura de sensores
├── actuators.h / .cpp    # Control de relés
├── profile.h / .cpp      # Carga y parseo de perfil JSON
├── mqtt_client.h / .cpp  # Publicación/suscripción MQTT
└── data/                 # Perfiles JSON (se sube a SPIFFS)
    └── profiles/         # Los 10 perfiles de especie (copia de firmware/profiles/)
        └── N1-orellana.json, N3-enoki.json, ...
```

---

## Topics MQTT

| Topic | Dirección | Contenido |
|-------|----------|----------|
| `bichongos/{capsula_id}/sensors` | ESP32 → Broker | JSON con todos los valores de sensores |
| `bichongos/{capsula_id}/status` | ESP32 → Broker | Estado de actuadores (on/off) |
| `bichongos/{capsula_id}/alert` | ESP32 → Broker | Alertas cuando valor fuera de rango crítico |
| `bichongos/{capsula_id}/profile/set` | Broker → ESP32 | Cambiar perfil activo remotamente |
| `bichongos/{capsula_id}/ota` | Broker → ESP32 | Trigger de actualización OTA |

### Ejemplo de mensaje de sensores

```json
{
  "capsula_id": "capsula-01",
  "especie": "N1-orellana",
  "etapa": "fructificacion",
  "timestamp": 1751286400,
  "temperatura": 17.3,
  "humedad": 89.5,
  "co2_ppm": 820,
  "luz_lux": 450,
  "temp_sustrato": 16.8,
  "actuadores": {
    "humidificador": false,
    "extractor": false,
    "calefactor": false,
    "led": true
  }
}
```

---

## Pines GPIO

| Pin | Componente | Tipo |
|-----|-----------|------|
| GPIO 21 (SDA) | SHT31, BH1750 | I2C |
| GPIO 22 (SCL) | SHT31, BH1750 | I2C |
| GPIO 16 (RX2) | MH-Z19B | UART |
| GPIO 17 (TX2) | MH-Z19B | UART |
| GPIO 4 | DS18B20 | 1-Wire |
| GPIO 26 | Relé CH1 → Humidificador | Salida digital |
| GPIO 27 | Relé CH2 → Extractor FAE | Salida digital |
| GPIO 14 | Relé CH3 → Calefactor | Salida digital |
| GPIO 12 | Relé CH4 → LED / Luz | Salida digital |

---

## Primer despliegue

```bash
# 1. Instalar librerías en Arduino IDE
# 2. Copiar config.h.example → config.h y editar
# 3. Conectar ESP32 por USB
# 4. En Arduino IDE: Herramientas → ESP32 Sketch Data Upload (sube SPIFFS)
# 5. Compilar y subir: Sketch → Upload
# 6. Abrir Monitor Serial (115200 baud) para ver logs
# 7. Verificar que aparece en Grafana dentro de 60 segundos
```

---

## Estado: 🔲 Pendiente de implementación

Ver `BACKLOG.md` épica E2 — tareas IOT-01 a IOT-18.
