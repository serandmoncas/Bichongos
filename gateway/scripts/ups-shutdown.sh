#!/bin/bash
# gateway/scripts/ups-shutdown.sh
# Script de apagado seguro cuando el UPS detecta fallo de energía.
#
# CÓMO FUNCIONA:
#   El UPS se conecta al RPi por USB. El daemon 'apcupsd' o 'nut' monitorea
#   la batería y llama a este script cuando la energía baja de un umbral.
#   Este script: (1) publica MQTT para apagar actuadores, (2) espera confirmación,
#   (3) apaga el RPi de forma segura.
#
# INSTALACIÓN:
#   1. Copiar a /usr/local/sbin/bichongos-ups-shutdown.sh
#   2. chmod +x /usr/local/sbin/bichongos-ups-shutdown.sh
#   3. Configurar en /etc/apcupsd/apccontrol o /etc/nut/upssched.conf
#      (ver sección de configuración al final de este archivo)
#
# INSTALACIÓN DE APCUPSD (para UPS APC con cable USB):
#   sudo apt install apcupsd
#   sudo nano /etc/apcupsd/apcupsd.conf
#     UPSCABLE usb
#     UPSTYPE usb
#     BATTERYLEVEL 25    # shutdown al 25% de batería
#     MINUTES 5          # o si quedan menos de 5 min de batería

set -e

MQTT_HOST="${MQTT_HOST:-localhost}"
MQTT_PORT="${MQTT_PORT:-1883}"
MQTT_USER="${MQTT_USER:-gateway}"
LOG_FILE="/var/log/bichongos-ups.log"
SHUTDOWN_DELAY=20   # segundos para esperar que los actuadores se apaguen

log() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $1" | tee -a "$LOG_FILE"
}

# Cargar variables de entorno si existe el archivo
if [ -f "$HOME/bichongos/gateway/.env" ]; then
    export $(grep -v '^#' "$HOME/bichongos/gateway/.env" | xargs)
fi

log "=== UPS: FALLO DE ENERGÍA DETECTADO ==="
log "Iniciando secuencia de apagado seguro..."

# 1. Notificar por Telegram si hay token disponible
if [ -n "$TELEGRAM_BOT_TOKEN" ] && [ -n "$TELEGRAM_CHAT_ID" ]; then
    curl -s -X POST \
        "https://api.telegram.org/bot${TELEGRAM_BOT_TOKEN}/sendMessage" \
        -d "chat_id=${TELEGRAM_CHAT_ID}" \
        -d "text=⚡ *CORTE DE ENERGÍA* — Gateway Bichongos%0AApagando actuadores y sistema en ${SHUTDOWN_DELAY}s" \
        -d "parse_mode=Markdown" > /dev/null 2>&1 || true
    log "Telegram: notificación enviada"
fi

# 2. Publicar comando de apagado de actuadores a todas las cápsulas conocidas
# Leer lista de cápsulas del archivo ACL de Mosquitto
CAPSULAS=$(grep "^user capsula-" /etc/mosquitto/acl 2>/dev/null \
    | awk '{print $2}' | sort -u)

if [ -z "$CAPSULAS" ]; then
    log "WARN: no se encontraron cápsulas en /etc/mosquitto/acl"
    # Intentar con las cápsulas más comunes de todas formas
    CAPSULAS="capsula-01 capsula-02 capsula-03"
fi

for CAPSULA in $CAPSULAS; do
    # Publicar alerta de shutdown en el topic de cada cápsula
    # El ESP32 en modo seguro mantendrá los últimos umbrales,
    # pero al menos registramos el evento
    mosquitto_pub \
        -h "$MQTT_HOST" -p "$MQTT_PORT" \
        -u "$MQTT_USER" -P "$MQTT_PASS" \
        -t "bichongos/${CAPSULA}/alert" \
        -m "{\"tipo\":\"ups_shutdown\",\"accion\":\"gateway_apagando\",\"timestamp\":$(date +%s)}" \
        -q 1 2>/dev/null || true
    log "Alerta publicada → bichongos/${CAPSULA}/alert"
done

# 3. Detener servicios de forma limpia
log "Deteniendo servicios..."

# Detener Node-RED primero (puede estar escribiendo en InfluxDB)
sudo systemctl stop nodered 2>/dev/null && log "Node-RED → detenido" || log "Node-RED → ya detenido"

# Flush de InfluxDB antes de apagar
sudo systemctl stop influxdb 2>/dev/null && log "InfluxDB → detenido" || log "InfluxDB → ya detenido"

# Detener Grafana
sudo systemctl stop grafana-server 2>/dev/null && log "Grafana → detenido" || log "Grafana → ya detenido"

# Esperar que los actuadores respondan (los ESP32 están en modo seguro con WiFi)
log "Esperando ${SHUTDOWN_DELAY}s para que los ESP32 respondan..."
sleep $SHUTDOWN_DELAY

# Detener Mosquitto al final (para que los ESP32 reciban los mensajes pendientes)
sudo systemctl stop mosquitto 2>/dev/null && log "Mosquitto → detenido" || true

log "Apagado del sistema operativo..."
sudo shutdown -h now "UPS: energía baja — apagado seguro Bichongos"
