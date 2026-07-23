#!/bin/bash
# gateway/scripts/add-capsule.sh
# Agrega una nueva cápsula al sistema: usuario MQTT + ACL
# Uso: bash add-capsule.sh capsula-02
#
# Requiere: mosquitto_passwd, acceso sudo

set -e

CAPSULA_ID="${1:-}"
if [ -z "$CAPSULA_ID" ]; then
  echo "Uso: $0 <capsula-id>"
  echo "Ejemplo: $0 capsula-02"
  exit 1
fi

ACL_FILE="/etc/mosquitto/acl"
PASSWD_FILE="/etc/mosquitto/passwd"

# Verificar que no existe ya
if grep -q "user $CAPSULA_ID" "$ACL_FILE" 2>/dev/null; then
  echo "ERROR: $CAPSULA_ID ya existe en el ACL"
  exit 1
fi

echo "Agregando $CAPSULA_ID al sistema Bichongos..."

# Crear usuario MQTT (pide contraseña interactivamente)
sudo mosquitto_passwd "$PASSWD_FILE" "$CAPSULA_ID"

# Agregar entradas ACL
sudo tee -a "$ACL_FILE" > /dev/null <<EOF

user $CAPSULA_ID
topic write  bichongos/$CAPSULA_ID/sensors
topic write  bichongos/$CAPSULA_ID/status
topic write  bichongos/$CAPSULA_ID/alert
topic read   bichongos/$CAPSULA_ID/profile/set
topic read   bichongos/$CAPSULA_ID/ota
EOF

sudo systemctl reload mosquitto
echo "OK: $CAPSULA_ID registrado y Mosquitto recargado"
echo "Ahora actualiza config.h en el ESP32 con:"
echo "  #define CAPSULE_ID  \"$CAPSULA_ID\""
echo "  #define MQTT_USER   \"$CAPSULA_ID\""
