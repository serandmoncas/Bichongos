# Gateway — Raspberry Pi 4

> Cerebro local del sistema Bichongos. Recibe datos de todos los ESP32 vía MQTT, los almacena en InfluxDB, los visualiza en Grafana y los sincroniza con Firebase.

---

## Hardware requerido

| Componente | Especificación |
|------------|---------------|
| Raspberry Pi 4 | 2 GB RAM mínimo |
| SSD por USB | 64 GB (más confiable que SD card) |
| UPS | 600 VA mínimo (evitar pérdida de datos) |
| Cable Ethernet | Conexión estable a router del invernadero |

---

## Stack de software

| Servicio | Puerto | Rol |
|---------|--------|-----|
| Mosquitto | 1883 | Broker MQTT — recibe datos de los ESP32 |
| Node-RED | 1880 | Flujos de automatización y lógica de alertas |
| InfluxDB | 8086 | Base de datos de serie temporal |
| Grafana | 3000 | Dashboard de visualización |
| Firebase Sync | — | Script de sincronización a nube |

---

## Instalación rápida

### 1. Sistema base

```bash
# Actualizar el sistema
sudo apt update && sudo apt upgrade -y

# Configurar SSD como disco principal (si aplica)
# Ver: https://www.raspberrypi.com/documentation/computers/raspberry-pi.html
```

### 2. Mosquitto (MQTT Broker)

```bash
sudo apt install -y mosquitto mosquitto-clients
sudo systemctl enable mosquitto
sudo systemctl start mosquitto

# Probar broker
mosquitto_pub -h localhost -t "test/hello" -m "hola"
mosquitto_sub -h localhost -t "test/hello"
```

Copiar `mosquitto.conf.example` → `/etc/mosquitto/conf.d/bichongos.conf` y editar.

### 3. Node-RED

```bash
bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered)
sudo systemctl enable nodered
sudo systemctl start nodered
# Acceder en: http://[IP-RPi]:1880
```

Importar el flujo desde `node-red-flows.json` (Menú → Import en la UI de Node-RED).

### 4. InfluxDB

```bash
# Instalar InfluxDB 2.x
wget -q https://repos.influxdata.com/influxdata-archive_compat.key
echo '393e8779c89ac8d958f81f942f9ad7fb82a25e133faddaf92e15b16e6ac9ce4c influxdata-archive_compat.key' | sha256sum -c && cat influxdata-archive_compat.key | gpg --dearmor | sudo tee /etc/apt/trusted.gpg.d/influxdata-archive_compat.gpg > /dev/null
echo 'deb [signed-by=/etc/apt/trusted.gpg.d/influxdata-archive_compat.gpg] https://repos.influxdata.com/debian stable main' | sudo tee /etc/apt/sources.list.d/influxdata.list
sudo apt update && sudo apt install influxdb2
sudo systemctl enable influxdb
sudo systemctl start influxdb
# Configurar en: http://[IP-RPi]:8086
```

### 5. Grafana

```bash
sudo apt install -y apt-transport-https software-properties-common
sudo mkdir -p /etc/apt/keyrings/
wget -q -O - https://apt.grafana.com/gpg.key | gpg --dearmor | sudo tee /etc/apt/keyrings/grafana.gpg > /dev/null
echo "deb [signed-by=/etc/apt/keyrings/grafana.gpg] https://apt.grafana.com stable main" | sudo tee /etc/apt/sources.list.d/grafana.list
sudo apt update && sudo apt install grafana
sudo systemctl enable grafana-server
sudo systemctl start grafana-server
# Acceder en: http://[IP-RPi]:3000 (admin/admin por defecto)
```

---

## Topics MQTT esperados

El gateway suscribe a:
```
bichongos/+/sensors    # Datos de sensores de todas las cápsulas
bichongos/+/alert      # Alertas críticas
bichongos/+/status     # Estado de actuadores
```

---

## Archivos de configuración

| Archivo | Descripción |
|---------|-------------|
| `mosquitto.conf.example` | Template de configuración del broker |
| `node-red-flows.json` | Flujos Node-RED exportados |
| `grafana-dashboards/` | Dashboards Grafana en JSON |
| `.env.example` | Template de variables de entorno (Firebase, Telegram) |

---

## Estado: 🔲 Pendiente de implementación

Ver `BACKLOG.md` épica E3 (GW-01 a GW-10) y épica E4 (CLD-01 a CLD-06).
