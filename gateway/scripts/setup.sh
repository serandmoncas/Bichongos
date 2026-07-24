#!/bin/bash
# gateway/scripts/setup.sh
# Script de instalación del gateway Bichongos en Raspberry Pi 4
# Ejecutar como usuario pi (no como root):
#   bash setup.sh
#
# Probado en: Raspberry Pi OS Bookworm (64-bit) · Debian 12

set -e
BICHONGOS_DIR="$HOME/bichongos/gateway"
LOG="$BICHONGOS_DIR/setup.log"

mkdir -p "$BICHONGOS_DIR"
exec > >(tee -a "$LOG") 2>&1
echo "=== Bichongos Gateway Setup — $(date) ==="

# ─── 1. Sistema base ────────────────────────────────────────────────────────
echo ""
echo ">>> [1/6] Actualizando sistema..."
sudo apt update && sudo apt upgrade -y
sudo apt install -y curl wget gnupg apt-transport-https software-properties-common git

# ─── 2. Mosquitto ───────────────────────────────────────────────────────────
echo ""
echo ">>> [2/6] Instalando Mosquitto..."
sudo apt install -y mosquitto mosquitto-clients

# Copiar configuración
sudo cp "$HOME/bichongos/gateway/mosquitto/bichongos.conf.example" \
        /etc/mosquitto/conf.d/bichongos.conf
sudo cp "$HOME/bichongos/gateway/mosquitto/acl.example" \
        /etc/mosquitto/acl

echo ""
echo "    Creando usuarios MQTT..."
echo "    (Se te pedirá contraseña para cada usuario)"
sudo mosquitto_passwd -c /etc/mosquitto/passwd gateway
sudo mosquitto_passwd    /etc/mosquitto/passwd capsula-01
echo ""
echo "    Usuario 'admin' (acceso de superusuario para diagnóstico — ver mosquitto/acl.example)."
echo "    Usa una contraseña distinta a la de 'gateway'; guárdala aparte, no en este repo."
sudo mosquitto_passwd    /etc/mosquitto/passwd admin

sudo systemctl enable mosquitto
sudo systemctl restart mosquitto
echo "    Mosquitto → OK (puerto 1883)"

# ─── 3. Node-RED ────────────────────────────────────────────────────────────
echo ""
echo ">>> [3/6] Instalando Node-RED..."
NODE_RED_INSTALLER="/tmp/update-nodejs-and-nodered.sh"
curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered \
  -o "$NODE_RED_INSTALLER"
echo "    Instalador descargado → $NODE_RED_INSTALLER"
echo "    SHA256: $(sha256sum "$NODE_RED_INSTALLER" | awk '{print $1}')"
echo "    (guardar este hash la primera vez; si cambia en una reinstalación, revisar el script antes de correrlo)"
bash "$NODE_RED_INSTALLER" --confirm-install --confirm-pi
rm -f "$NODE_RED_INSTALLER"

# Instalar nodos adicionales necesarios
cd ~/.node-red
npm install node-red-contrib-influxdb node-red-contrib-telegrambot 2>/dev/null || true

sudo systemctl enable nodered
sudo systemctl start nodered
echo "    Node-RED → OK (puerto 1880)"

# ─── 4. InfluxDB 2.x ────────────────────────────────────────────────────────
echo ""
echo ">>> [4/6] Instalando InfluxDB 2.x..."
wget -q https://repos.influxdata.com/influxdata-archive_compat.key -O /tmp/influx.key
echo '393e8779c89ac8d958f81f942f9ad7fb82a25e133faddaf92e15b16e6ac9ce4c  /tmp/influx.key' \
  | sha256sum -c
cat /tmp/influx.key | gpg --dearmor \
  | sudo tee /etc/apt/trusted.gpg.d/influxdata-archive_compat.gpg > /dev/null
echo 'deb [signed-by=/etc/apt/trusted.gpg.d/influxdata-archive_compat.gpg] https://repos.influxdata.com/debian stable main' \
  | sudo tee /etc/apt/sources.list.d/influxdata.list
sudo apt update && sudo apt install -y influxdb2

sudo systemctl enable influxdb
sudo systemctl start influxdb
echo "    InfluxDB → OK (puerto 8086)"
echo "    Completar setup en: http://$(hostname -I | awk '{print $1}'):8086"
echo "    Organización: bichongos · Bucket: capsulas · Retención: 30d"

# ─── 5. Grafana ─────────────────────────────────────────────────────────────
echo ""
echo ">>> [5/6] Instalando Grafana..."
sudo mkdir -p /etc/apt/keyrings/
wget -q -O - https://apt.grafana.com/gpg.key \
  | gpg --dearmor \
  | sudo tee /etc/apt/keyrings/grafana.gpg > /dev/null
echo "deb [signed-by=/etc/apt/keyrings/grafana.gpg] https://apt.grafana.com stable main" \
  | sudo tee /etc/apt/sources.list.d/grafana.list
sudo apt update && sudo apt install -y grafana

sudo systemctl enable grafana-server
sudo systemctl start grafana-server
echo "    Grafana → OK (puerto 3000)"
echo "    Login inicial: admin / admin (cambiar en primer acceso)"

# ─── 6. Firewall (UFW) ──────────────────────────────────────────────────────
echo ""
echo ">>> [6/6] Configurando firewall UFW..."
sudo apt install -y ufw
sudo ufw default deny incoming
sudo ufw default allow outgoing
sudo ufw allow ssh
sudo ufw allow 1883/tcp comment 'MQTT'
sudo ufw allow 1880/tcp comment 'Node-RED'
sudo ufw allow 8086/tcp comment 'InfluxDB'
sudo ufw allow 3000/tcp comment 'Grafana'
sudo ufw --force enable
echo "    UFW → OK"

# ─── Resumen ────────────────────────────────────────────────────────────────
RPi_IP=$(hostname -I | awk '{print $1}')
echo ""
echo "============================================================"
echo " INSTALACIÓN COMPLETA"
echo "============================================================"
echo " Mosquitto  → mqtt://${RPi_IP}:1883"
echo " Node-RED   → http://${RPi_IP}:1880"
echo " InfluxDB   → http://${RPi_IP}:8086"
echo " Grafana    → http://${RPi_IP}:3000"
echo "============================================================"
echo ""
echo " PRÓXIMOS PASOS:"
echo " 1. Completar setup InfluxDB en el navegador"
echo "    Copiar el token generado → gateway/.env (INFLUXDB_TOKEN)"
echo " 2. Copiar gateway/.env.example → gateway/.env y completar"
echo " 3. Importar flujos en Node-RED:"
echo "    Menú → Import → gateway/node-red-flows.json"
echo " 4. Importar dashboard en Grafana:"
echo "    Dashboards → Import → gateway/grafana-dashboards/capsulas.json"
echo " 5. Instalar Tailscale para acceso remoto seguro:"
echo "    curl -fsSL https://tailscale.com/install.sh | sh"
echo "    sudo tailscale up"
echo "============================================================"
echo " Log guardado en: $LOG"
