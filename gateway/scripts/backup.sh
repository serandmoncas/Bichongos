#!/bin/bash
# gateway/scripts/backup.sh
# Backup diario de InfluxDB + configuración Mosquitto + flows Node-RED
# Agregar a crontab: 0 3 * * * /home/pi/bichongos/gateway/scripts/backup.sh

set -e

BACKUP_DIR="$HOME/bichongos/backups"
DATE=$(date +%Y-%m-%d)
DEST="$BACKUP_DIR/$DATE"

mkdir -p "$DEST"

# InfluxDB — exportar todos los buckets
if command -v influx &> /dev/null; then
  source "$HOME/bichongos/gateway/.env" 2>/dev/null || true
  influx backup "$DEST/influxdb" \
    --host "${INFLUXDB_URL:-http://localhost:8086}" \
    --token "$INFLUXDB_TOKEN" 2>/dev/null \
    && echo "InfluxDB backup → OK" \
    || echo "InfluxDB backup → FALLÓ (verificar token en .env)"
fi

# Mosquitto — config y ACL
sudo cp /etc/mosquitto/conf.d/bichongos.conf "$DEST/mosquitto.conf" 2>/dev/null || true
sudo cp /etc/mosquitto/acl                   "$DEST/mosquitto.acl"  2>/dev/null || true
echo "Mosquitto config → OK"

# Node-RED — flows
cp ~/.node-red/flows.json "$DEST/node-red-flows.json" 2>/dev/null \
  && echo "Node-RED flows → OK" \
  || echo "Node-RED flows → no encontrado"

# Grafana — dashboards (requiere API key si auth está activo)
# curl -s "http://admin:admin@localhost:3000/api/dashboards/home" > "$DEST/grafana-home.json"

# Comprimir
tar -czf "$BACKUP_DIR/bichongos-backup-$DATE.tar.gz" -C "$BACKUP_DIR" "$DATE"
rm -rf "$DEST"

# Mantener solo los últimos 14 backups
ls -t "$BACKUP_DIR"/*.tar.gz 2>/dev/null | tail -n +15 | xargs rm -f 2>/dev/null || true

echo "Backup completado: $BACKUP_DIR/bichongos-backup-$DATE.tar.gz"
