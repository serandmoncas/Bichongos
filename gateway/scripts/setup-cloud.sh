#!/bin/bash
# gateway/scripts/setup-cloud.sh
# Configuración guiada de Firebase y Telegram Bot para Bichongos.
# Ejecutar una sola vez después de setup.sh.
# Requiere: gateway/.env completado con tokens reales.

set -e
ENV_FILE="$HOME/bichongos/gateway/.env"

log() { echo -e "\n\033[1;36m>>> $1\033[0m"; }
ok()  { echo -e "\033[1;32m    ✓ $1\033[0m"; }
err() { echo -e "\033[1;31m    ✗ $1\033[0m"; }

if [ ! -f "$ENV_FILE" ]; then
    echo "ERROR: no existe $ENV_FILE"
    echo "Copiar gateway/.env.example → $ENV_FILE y completar los tokens"
    exit 1
fi

set -a
source "$ENV_FILE"
set +a

log "[1/4] Verificando Telegram Bot"
if [ -z "$TELEGRAM_BOT_TOKEN" ] || [ "$TELEGRAM_BOT_TOKEN" = "123456789:ABCdefGhIJKlmNoPQRstuVWXyz" ]; then
    err "TELEGRAM_BOT_TOKEN no configurado en .env"
    echo ""
    echo "Para crear el bot:"
    echo "  1. Abrir Telegram y buscar @BotFather"
    echo "  2. Enviar /newbot"
    echo "  3. Nombre: Bichongos IoT"
    echo "  4. Username: bichongos_iot_bot (o similar disponible)"
    echo "  5. Copiar el token que devuelve BotFather → TELEGRAM_BOT_TOKEN en .env"
    echo ""
    echo "Para obtener el CHAT_ID:"
    echo "  1. Crear grupo en Telegram e invitar al bot"
    echo "  2. Enviar cualquier mensaje al grupo"
    echo "  3. Visitar: https://api.telegram.org/bot<TOKEN>/getUpdates"
    echo "  4. Buscar \"chat\":{\"id\": ... } — ese número es el CHAT_ID"
    echo "  5. Copiarlo → TELEGRAM_CHAT_ID en .env (grupos tienen ID negativo)"
else
    # Probar el bot enviando un mensaje de prueba
    RESULT=$(curl -s "https://api.telegram.org/bot${TELEGRAM_BOT_TOKEN}/sendMessage" \
        -d "chat_id=${TELEGRAM_CHAT_ID}" \
        -d "text=🍄 Bichongos Gateway — conexión verificada ✓" \
        -d "parse_mode=Markdown")
    if echo "$RESULT" | grep -q '"ok":true'; then
        ok "Telegram Bot OK — mensaje de prueba enviado al chat $TELEGRAM_CHAT_ID"
    else
        err "Telegram falló: $RESULT"
    fi
fi

log "[2/4] Verificando InfluxDB"
if [ -z "$INFLUXDB_TOKEN" ] || [ "$INFLUXDB_TOKEN" = "tu-token-de-influxdb-aqui" ]; then
    err "INFLUXDB_TOKEN no configurado"
    echo ""
    echo "Para obtener el token:"
    echo "  1. Abrir http://$(hostname -I | awk '{print $1}'):8086"
    echo "  2. Completar el setup inicial (org: bichongos, bucket: capsulas)"
    echo "  3. En el setup, copiar el token generado"
    echo "  4. O ir a: Data → API Tokens → Generate API Token → All Access Token"
    echo "  5. Copiar → INFLUXDB_TOKEN en .env"
else
    HEALTH=$(curl -s -o /dev/null -w "%{http_code}" \
        "${INFLUXDB_URL:-http://localhost:8086}/health")
    if [ "$HEALTH" = "200" ]; then
        ok "InfluxDB accesible en ${INFLUXDB_URL:-http://localhost:8086}"
        # Verificar que el bucket existe
        BUCKETS=$(curl -s \
            -H "Authorization: Token $INFLUXDB_TOKEN" \
            "${INFLUXDB_URL:-http://localhost:8086}/api/v2/buckets?name=capsulas" \
            | grep -c '"name":"capsulas"' || true)
        if [ "$BUCKETS" -gt 0 ]; then
            ok "Bucket 'capsulas' existe"
        else
            err "Bucket 'capsulas' no encontrado — crearlo en la UI de InfluxDB"
        fi
    else
        err "InfluxDB no responde (HTTP $HEALTH)"
    fi
fi

log "[3/4] Verificando Firebase"
if [ -z "$FIREBASE_PROJECT_ID" ] || [ "$FIREBASE_PROJECT_ID" = "bichongos-iot" ]; then
    err "Firebase no configurado"
    echo ""
    echo "Para configurar Firebase:"
    echo "  1. Ir a https://console.firebase.google.com"
    echo "  2. Crear proyecto: bichongos-iot"
    echo "  3. Activar Realtime Database (modo bloqueado inicialmente)"
    echo "  4. En Configuración → Cuentas de servicio → Generar nueva clave privada"
    echo "  5. Guardar el JSON en: $HOME/bichongos/gateway/firebase-credentials.json"
    echo "  6. Actualizar FIREBASE_PROJECT_ID y FIREBASE_DATABASE_URL en .env"
    echo ""
    echo "Reglas de seguridad Firebase (Realtime Database):"
    echo "  Ver: docs/seguridad-iot.md sección Firebase Rules"
else
    ok "Firebase configurado: proyecto $FIREBASE_PROJECT_ID"
    ok "Database URL: $FIREBASE_DATABASE_URL"
    if [ -f "${FIREBASE_CREDENTIALS_PATH:-}" ]; then
        ok "Credenciales encontradas en $FIREBASE_CREDENTIALS_PATH"
    else
        err "Archivo de credenciales no encontrado: ${FIREBASE_CREDENTIALS_PATH}"
    fi
fi

log "[4/4] Configurando Node-RED con variables de entorno"
# Node-RED puede leer variables del sistema operativo en los function nodes
# usando process.env.VARIABLE_NAME

NODE_RED_ENV="$HOME/.node-red/node-red.env"
if [ ! -f "$NODE_RED_ENV" ]; then
    cat > "$NODE_RED_ENV" <<EOF
# Variables de entorno para Node-RED — Bichongos
# Generado por setup-cloud.sh — no editar manualmente, editar .env
TELEGRAM_BOT_TOKEN=$TELEGRAM_BOT_TOKEN
TELEGRAM_CHAT_ID=$TELEGRAM_CHAT_ID
INFLUXDB_TOKEN=$INFLUXDB_TOKEN
INFLUXDB_URL=${INFLUXDB_URL:-http://localhost:8086}
INFLUXDB_ORG=${INFLUXDB_ORG:-bichongos}
INFLUXDB_BUCKET=${INFLUXDB_BUCKET:-capsulas}
FIREBASE_DATABASE_URL=$FIREBASE_DATABASE_URL
EOF
    ok "Variables exportadas a $NODE_RED_ENV"
    # Agregar carga del archivo en settings.js de Node-RED
    if ! grep -q "node-red.env" ~/.node-red/settings.js 2>/dev/null; then
        sed -i 's/module.exports = {/require("dotenv").config({path: process.env.HOME + "\/.node-red\/node-red.env"});\nmodule.exports = {/' \
            ~/.node-red/settings.js 2>/dev/null || true
    fi
    sudo systemctl restart nodered
    ok "Node-RED reiniciado con nuevas variables"
else
    ok "node-red.env ya existe — actualizando..."
    sed -i "s|TELEGRAM_BOT_TOKEN=.*|TELEGRAM_BOT_TOKEN=$TELEGRAM_BOT_TOKEN|" "$NODE_RED_ENV"
    sed -i "s|TELEGRAM_CHAT_ID=.*|TELEGRAM_CHAT_ID=$TELEGRAM_CHAT_ID|" "$NODE_RED_ENV"
    sed -i "s|INFLUXDB_TOKEN=.*|INFLUXDB_TOKEN=$INFLUXDB_TOKEN|" "$NODE_RED_ENV"
    sudo systemctl restart nodered
    ok "Node-RED reiniciado"
fi

echo ""
echo "============================================================"
echo " CONFIGURACIÓN CLOUD COMPLETADA"
echo "============================================================"
echo " Importar flujos en Node-RED:"
echo "   http://$(hostname -I | awk '{print $1}'):1880"
echo "   Menú (≡) → Import → Pegar gateway/node-red-flows.json"
echo ""
echo " Importar dashboard en Grafana:"
echo "   http://$(hostname -I | awk '{print $1}'):3000"
echo "   Dashboards → New → Import → Subir grafana-dashboards/capsulas.json"
echo "============================================================"
