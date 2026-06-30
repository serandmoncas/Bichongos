# Seguridad IoT — Bichongos

> Modelo de seguridad del sistema: autenticación MQTT, cifrado en tránsito, reglas Firebase, control de acceso y respuesta a incidentes.

**Versión:** 1.0 · **Fecha:** 2026-06-30
**Épica:** E13 (SEC-01 a SEC-06) del BACKLOG.md

---

## Por qué importa en un sistema de cultivo

Un sistema IoT sin autenticación permite que cualquier dispositivo en la red publique datos falsos en los topics MQTT. Un actor malicioso (o un error de configuración) podría:

- Enviar temperatura falsa de 35 °C → el firmware activa el calefactor → el cultivo muere
- Apagar el humidificador de todas las cápsulas simultáneamente sin dejar traza
- Cambiar el perfil activo de una cápsula a una especie incorrecta
- Leer el historial de producción y ventas almacenado en Firebase

La superficie de ataque es pequeña (red local privada), pero el impacto de un fallo es directo en producción real.

---

## 1. Autenticación MQTT — Mosquitto

> **Tarea SEC-01** — usuario/contraseña obligatorio por nodo ESP32.

### 1.1 Modelo de usuarios

| Usuario | Contraseña | Permisos | Quién lo usa |
|---------|-----------|---------|-------------|
| `capsula-01` | [generada] | Publicar en `bichongos/capsula-01/#` | ESP32 cápsula 01 |
| `capsula-02` | [generada] | Publicar en `bichongos/capsula-02/#` | ESP32 cápsula 02 |
| `capsula-03` | [generada] | Publicar en `bichongos/capsula-03/#` | ESP32 cápsula 03 |
| `nodered` | [generada] | Suscribir en `bichongos/#`, publicar en `bichongos/+/profile/set` | Node-RED en RPi |
| `monitor` | [generada] | Solo suscribir en `bichongos/#` (solo lectura) | Laptop/teléfono admin |

**Principio:** cada cápsula solo puede publicar en su propio topic. No puede leer ni escribir en el topic de otra cápsula.

### 1.2 Configurar Mosquitto con autenticación

```bash
# En el Raspberry Pi — crear archivo de contraseñas
sudo mosquitto_passwd -c /etc/mosquitto/passwd capsula-01
# (pide contraseña — ingresar y confirmar)
sudo mosquitto_passwd /etc/mosquitto/passwd capsula-02
sudo mosquitto_passwd /etc/mosquitto/passwd capsula-03
sudo mosquitto_passwd /etc/mosquitto/passwd nodered
sudo mosquitto_passwd /etc/mosquitto/passwd monitor
```

Crear el archivo de configuración de Mosquitto:

```bash
sudo nano /etc/mosquitto/conf.d/bichongos.conf
```

```
# /etc/mosquitto/conf.d/bichongos.conf

# Puerto estándar MQTT
listener 1883

# Requerir autenticación — rechazar conexiones anónimas
allow_anonymous false
password_file /etc/mosquitto/passwd

# Control de acceso por usuario (ACL)
acl_file /etc/mosquitto/acl

# Logging
log_type error
log_type warning
log_type notice
log_type information
log_dest file /var/log/mosquitto/mosquitto.log
```

### 1.3 Archivo ACL — control de acceso por topic

```bash
sudo nano /etc/mosquitto/acl
```

```
# /etc/mosquitto/acl — Control de acceso por topic

# Node-RED: suscribir a todo, publicar comandos de perfil
user nodered
topic readwrite bichongos/#

# Monitor: solo lectura
user monitor
topic read bichongos/#

# Cápsula 01: solo puede publicar en su propio namespace
user capsula-01
topic write bichongos/capsula-01/sensors
topic write bichongos/capsula-01/status
topic write bichongos/capsula-01/alert
topic read  bichongos/capsula-01/profile/set
topic read  bichongos/capsula-01/ota

# Cápsula 02
user capsula-02
topic write bichongos/capsula-02/sensors
topic write bichongos/capsula-02/status
topic write bichongos/capsula-02/alert
topic read  bichongos/capsula-02/profile/set
topic read  bichongos/capsula-02/ota

# Cápsula 03
user capsula-03
topic write bichongos/capsula-03/sensors
topic write bichongos/capsula-03/status
topic write bichongos/capsula-03/alert
topic read  bichongos/capsula-03/profile/set
topic read  bichongos/capsula-03/ota
```

```bash
# Reiniciar Mosquitto para aplicar cambios
sudo systemctl restart mosquitto

# Verificar que arranca sin errores
sudo systemctl status mosquitto

# Probar que el acceso anónimo fue bloqueado
mosquitto_pub -h localhost -t "test" -m "hola"
# Debe fallar con: Connection Refused: not authorised

# Probar acceso con credenciales válidas
mosquitto_pub -h localhost -t "bichongos/capsula-01/sensors" \
  -u "capsula-01" -P "contraseña" -m '{"temp":17.3}'
# Debe publicar exitosamente
```

### 1.4 Credenciales en el firmware ESP32

En `firmware/capsula_core/config.h` (no subir a git):

```cpp
// config.h — credenciales MQTT (NO commitear)
#define MQTT_USER     "capsula-01"
#define MQTT_PASSWORD "contraseña-segura-aqui"
```

En el sketch principal:

```cpp
// En la función de conexión MQTT
if (client.connect(CAPSULA_ID, MQTT_USER, MQTT_PASSWORD)) {
    Serial.println("MQTT conectado");
} else {
    Serial.print("MQTT falló, rc=");
    Serial.println(client.state());
}
```

---

## 2. TLS — Cifrado en tránsito

> **Tarea SEC-02** — cifrar todo el tráfico MQTT entre ESP32 y el broker.

### 2.1 Por qué TLS en red local

Sin TLS, cualquier dispositivo en la red WiFi `bichongos-lab` puede capturar el tráfico MQTT con un sniffer y leer contraseñas en texto plano. Con TLS, aunque alguien capture los paquetes, no puede descifrarlos.

### 2.2 Generar certificados autofirmados en el RPi

```bash
# Crear directorio de certificados
sudo mkdir -p /etc/mosquitto/certs
cd /etc/mosquitto/certs

# Generar CA (Autoridad Certificadora privada)
sudo openssl genrsa -out ca.key 2048
sudo openssl req -new -x509 -days 3650 -key ca.key -out ca.crt \
  -subj "/CN=Bichongos-CA/O=Bichongos/C=CO"

# Generar certificado del servidor (broker)
sudo openssl genrsa -out server.key 2048
sudo openssl req -new -key server.key -out server.csr \
  -subj "/CN=192.168.10.10/O=Bichongos/C=CO"
sudo openssl x509 -req -days 3650 -in server.csr \
  -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt

# Permisos correctos
sudo chown mosquitto:mosquitto /etc/mosquitto/certs/*
sudo chmod 600 /etc/mosquitto/certs/ca.key
sudo chmod 600 /etc/mosquitto/certs/server.key
```

### 2.3 Configurar Mosquitto con TLS

```
# Agregar a /etc/mosquitto/conf.d/bichongos.conf

# Puerto TLS (adicional al 1883 interno)
listener 8883
certfile  /etc/mosquitto/certs/server.crt
keyfile   /etc/mosquitto/certs/server.key
cafile    /etc/mosquitto/certs/ca.crt
tls_version tlsv1.2

# El puerto 1883 puede dejarse solo para localhost (Node-RED)
listener 1883
bind_address 127.0.0.1
```

### 2.4 Configurar TLS en el ESP32

```cpp
// En el firmware — requiere librería WiFiClientSecure

#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Copiar el contenido de ca.crt aquí
const char* ca_cert = R"EOF(
-----BEGIN CERTIFICATE-----
[contenido del archivo ca.crt]
-----END CERTIFICATE-----
)EOF";

WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup() {
    espClient.setCACert(ca_cert);
    client.setServer(MQTT_SERVER, 8883);  // Puerto TLS
}
```

> **Nota de implementación:** TLS en ESP32 consume ≈ 36 KB de RAM adicional y agrega ≈ 200–500 ms de latencia en la conexión inicial. Las lecturas periódicas (cada 30 s) no se ven afectadas. Si la RAM es limitada (ESP32 con 520 KB), verificar que no genere reinicios por heap insuficiente.

---

## 3. Reglas de seguridad Firebase

> **Tarea SEC-03** — controlar quién puede leer y escribir en la base de datos.

### 3.1 Estructura de datos en Firebase

```
bichongos-realtime-db/
├── capsulas/
│   ├── capsula-01/
│   │   ├── sensors/          ← lecturas actuales
│   │   ├── history/          ← últimas 24 h
│   │   └── profile/          ← perfil activo actual
│   └── capsula-02/ ...
├── alertas/                  ← alertas activas
├── lotes/                    ← registro de producción
└── config/                   ← configuración del sistema
```

### 3.2 Reglas de seguridad (Firebase Realtime Database Rules)

```json
{
  "rules": {
    ".read": false,
    ".write": false,

    "capsulas": {
      "$capsula_id": {
        "sensors": {
          ".read": "auth != null",
          ".write": "auth != null && auth.token.role === 'gateway'"
        },
        "history": {
          ".read": "auth != null",
          ".write": "auth != null && auth.token.role === 'gateway'"
        },
        "profile": {
          ".read": "auth != null",
          ".write": "auth != null && (auth.token.role === 'admin' || auth.token.role === 'gateway')"
        }
      }
    },

    "alertas": {
      ".read": "auth != null",
      ".write": "auth != null && auth.token.role === 'gateway'"
    },

    "lotes": {
      ".read": "auth != null",
      ".write": "auth != null && (auth.token.role === 'admin' || auth.token.role === 'operador')"
    },

    "config": {
      ".read": "auth != null && auth.token.role === 'admin'",
      ".write": "auth != null && auth.token.role === 'admin'"
    }
  }
}
```

### 3.3 Roles y permisos

| Rol | Puede leer | Puede escribir | Asignado a |
|-----|-----------|---------------|-----------|
| `admin` | Todo | Todo | Sergio (dueño del sistema) |
| `gateway` | Sensores, alertas | Sensores, alertas, historial | Raspberry Pi (script de sync) |
| `operador` | Sensores, lotes, alertas | Lotes | Miembros del equipo |
| *(sin autenticar)* | Nada | Nada | Cualquier persona sin login |

### 3.4 Crear usuarios Firebase con roles (Node.js en el RPi)

```javascript
// Script: gateway/scripts/setup-firebase-users.js
// Ejecutar una sola vez para crear los usuarios del sistema

const admin = require('firebase-admin');
const serviceAccount = require('./firebase-service-account.json');

admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: 'https://[tu-proyecto].firebaseio.com'
});

// Crear usuario gateway con rol
admin.auth().createUser({
  email: 'gateway@bichongos.local',
  password: process.env.GATEWAY_PASSWORD,
  displayName: 'Gateway RPi'
}).then(user => {
  return admin.auth().setCustomUserClaims(user.uid, { role: 'gateway' });
}).then(() => {
  console.log('Usuario gateway creado');
});
```

---

## 4. Política de acceso

> **Tarea SEC-04** — quién puede leer, quién puede cambiar perfiles de cápsulas.

### 4.1 Matriz de control de acceso

| Acción | Admin | Operador | Monitor (solo lectura) |
|--------|:-----:|:--------:|:---------------------:|
| Ver datos en tiempo real (Grafana) | ✅ | ✅ | ✅ |
| Ver historial de sensores | ✅ | ✅ | ✅ |
| Registrar cosechas y lotes | ✅ | ✅ | ❌ |
| Cambiar perfil activo de una cápsula | ✅ | ❌ | ❌ |
| Editar parámetros de un perfil JSON | ✅ | ❌ | ❌ |
| Crear nuevas cápsulas en el sistema | ✅ | ❌ | ❌ |
| Ver alertas | ✅ | ✅ | ✅ |
| Silenciar alertas | ✅ | ✅ | ❌ |
| Acceso SSH al Raspberry Pi | ✅ | ❌ | ❌ |
| Acceder a Node-RED | ✅ | ❌ | ❌ |
| Ver reportes financieros | ✅ | ❌ | ❌ |

### 4.2 Cambio de perfil — procedimiento con doble confirmación

Cambiar el perfil activo de una cápsula es una operación de alto impacto (puede matar un cultivo si se equivoca de especie). Requiere doble confirmación:

```
Flujo de cambio de perfil:

1. Admin publica en MQTT:
   Topic: bichongos/capsula-01/profile/set
   Payload: { "perfil": "N2-shiitake", "etapa": "fructificacion",
              "confirmacion": "CAMBIAR", "solicitado_por": "sergio" }

2. Node-RED recibe el mensaje y:
   a. Verifica que la solicitud incluye el campo "confirmacion": "CAMBIAR"
   b. Verifica que el perfil existe en /firmware/profiles/
   c. Envía notificación Telegram al admin:
      "⚠️ Solicitud de cambio de perfil en capsula-01:
       N1-orellana → N2-shiitake (etapa: fructificacion)
       Solicitado por: sergio
       Responde /confirmar o /cancelar"

3. Admin responde /confirmar en Telegram

4. Node-RED ejecuta el cambio y notifica:
   "✅ Perfil actualizado en capsula-01"
```

### 4.3 Contraseñas — política mínima

| Servicio | Longitud mínima | Complejidad | Rotación |
|---------|----------------|------------|---------|
| WiFi bichongos-lab | 16 caracteres | Letras + números + símbolo | Cada 6 meses |
| SSH Raspberry Pi | 20 caracteres | Letras + números + símbolo | Cada 6 meses |
| MQTT por cápsula | 16 caracteres | Alfanumérico | Al cambiar hardware |
| Grafana admin | 16 caracteres | Letras + números + símbolo | Cada 6 meses |
| Firebase admin | 20 caracteres | Google recomendado | Nunca (usa 2FA) |

**Dónde guardar las contraseñas:** gestor de contraseñas (Bitwarden, 1Password o KeePass). Nunca en texto plano, nunca en el repositorio git.

---

## 5. Segmentación de red

> **Tarea SEC-05** — aislar dispositivos IoT del resto de la red.

### 5.1 Topología recomendada con VLAN

Si el router soporta VLANs (MikroTik hAP, o routers Ubiquiti):

```
VLAN 10 — IoT (192.168.10.0/24)
  Dispositivos: ESP32, Raspberry Pi
  Acceso a internet: solo saliente (para Firebase y Telegram)
  Acceso entre VLANs: bloqueado (no puede tocar la red de casa)

VLAN 20 — Admin (192.168.20.0/24)
  Dispositivos: laptop, teléfonos del equipo
  Acceso a internet: completo
  Acceso a VLAN IoT: solo hacia puertos 3000 (Grafana) y 1880 (Node-RED)
```

### 5.2 Configuración sin VLAN (router doméstico simple)

Si el router no soporta VLANs, usar la función "red de invitados":

```
Red principal:  bichongos-lab   → RPi + ESP32 (acceso completo entre sí)
Red invitados:  bichongos-admin → Laptops y teléfonos

Configurar la red de invitados con:
  - Aislamiento entre clientes: SÍ
  - Acceso a red local: SÍ (para llegar a Grafana en el RPi)
  - Acceso a internet: SÍ
```

### 5.3 Reglas de firewall en el Raspberry Pi

```bash
# Configurar UFW (Uncomplicated Firewall) en el RPi
sudo apt install ufw -y

# Política por defecto: bloquear entradas, permitir salidas
sudo ufw default deny incoming
sudo ufw default allow outgoing

# Permitir SSH solo desde la red local
sudo ufw allow from 192.168.10.0/24 to any port 22

# Permitir MQTT desde ESP32 (red IoT)
sudo ufw allow from 192.168.10.0/24 to any port 1883
sudo ufw allow from 192.168.10.0/24 to any port 8883

# Permitir Grafana desde red admin
sudo ufw allow from 192.168.10.0/24 to any port 3000

# Permitir Node-RED solo desde localhost y admin
sudo ufw allow from 127.0.0.1 to any port 1880
sudo ufw allow from 192.168.10.0/24 to any port 1880

# InfluxDB: solo acceso local (Node-RED lo consulta internamente)
sudo ufw allow from 127.0.0.1 to any port 8086

# Activar
sudo ufw enable
sudo ufw status verbose
```

---

## 6. Plan de respuesta a incidentes

> **Tarea SEC-06** — qué hacer cuando algo falla o se detecta comportamiento anómalo.

### 6.1 Tipos de incidentes y clasificación

| Nivel | Tipo | Ejemplos |
|-------|------|---------|
| 🔴 Crítico | Afecta cultivos activos | ESP32 envía datos fuera de rango, actuador no responde, broker caído |
| 🟡 Medio | Afecta monitoreo | Grafana inaccesible, alertas Telegram detenidas, pérdida de datos históricos |
| 🟢 Bajo | No afecta producción | Acceso no autorizado fallido, latencia de red alta, log de errores inusual |

### 6.2 Árbol de decisión ante anomalía de un ESP32

```
ESP32 publica datos anómalos (temperatura 99°C, CO₂ -500 ppm, etc.)
                │
                ▼
  ¿El actuador reaccionó de forma peligrosa?
          │               │
         SÍ              NO
          │               │
          ▼               ▼
  CORTE INMEDIATO    Revisar sensor
  • Desconectar      • Verificar conexión física del sensor
    el relé del      • Revisar código de lectura en Monitor Serial
    actuador         • Comparar con lectura manual (termómetro / medidor CO₂)
    físicamente      • Si el sensor está dañado → reemplazar
  • Revisar el       • Si el firmware tiene bug → corregir y hacer OTA update
    cultivo          • Documentar en registro de incidentes
  • Documentar
```

### 6.3 Procedimiento de respuesta por tipo de incidente

#### Incidente: ESP32 desconectado (sin datos en > 5 minutos)

```
1. Verificar en Grafana: ¿cuándo fue el último dato?
2. Verificar en el invernadero: ¿el LED del ESP32 parpadea?
   - Parpadeo lento: conectado y operando → revisar MQTT en RPi
   - Parpadeo rápido: intentando conectar WiFi → verificar router
   - 3 parpadeos cortos: modo seguro → los actuadores siguen funcionando
   - Sin LED: sin energía → verificar fuente de 5V y fusible
3. Si no hay respuesta: reiniciar el ESP32 (desconectar y reconectar energía)
4. Si persiste: conectar USB y abrir Monitor Serial para leer el log
5. Documentar en el registro de incidentes
```

#### Incidente: Broker MQTT caído

```
1. Verificar estado:
   ssh pi@192.168.10.10
   sudo systemctl status mosquitto

2. Si está detenido:
   sudo systemctl start mosquitto
   sudo journalctl -u mosquitto -n 50  # Ver errores recientes

3. Causas comunes:
   - Archivo de configuración con error de sintaxis → revisar /etc/mosquitto/conf.d/
   - Archivo de contraseñas corrupto → regenerar con mosquitto_passwd
   - Disco lleno (logs) → sudo df -h; sudo journalctl --vacuum-size=100M

4. Los ESP32 en modo seguro siguen controlando actuadores
   — el cultivo no está en riesgo inmediato, pero sin monitoreo remoto
```

#### Incidente: Intento de acceso no autorizado detectado

```
Señal de alerta: el log de Mosquitto muestra conexiones rechazadas repetidas
  grep "Connection Refused" /var/log/mosquitto/mosquitto.log

1. Identificar la IP del dispositivo que intenta conectarse:
   grep "new connection" /var/log/mosquitto/mosquitto.log

2. Si la IP no pertenece a ningún ESP32 registrado → bloquear en firewall:
   sudo ufw deny from [IP-sospechosa]

3. Cambiar contraseñas MQTT de todas las cápsulas:
   sudo mosquitto_passwd /etc/mosquitto/passwd capsula-01
   # Actualizar config.h en cada ESP32 y subir firmware

4. Revisar si el SSID WiFi fue comprometido → cambiar contraseña WiFi
   (esto requiere actualizar config.h en todos los ESP32)

5. Documentar en el registro de incidentes
```

#### Incidente: Actuador bloqueado (no responde al relay)

```
1. Verificar en Grafana: ¿el topic .../status muestra el estado correcto?
2. Verificar en Monitor Serial: ¿el ESP32 reporta que activó el pin GPIO?
3. Verificar físicamente:
   - ¿El LED del módulo relé se enciende cuando debería?
   - ¿Hay voltaje en los terminales de salida del relé? (medir con multímetro)
   - ¿El actuador funciona si se conecta directamente sin pasar por el relé?
4. Si el relé está dañado: reemplazar el módulo ($ 16.000 COP, ver BOM)
5. Mientras se repara: operar el actuador manualmente
6. Documentar en el registro de incidentes
```

### 6.4 Registro de incidentes

Llenar por cada incidente, sin importar el nivel.

```
REGISTRO DE INCIDENTE

Fecha/hora:      ___________
Nivel:           [ ] 🔴 Crítico  [ ] 🟡 Medio  [ ] 🟢 Bajo
Cápsula(s):      ___________
Descripción:     ___________________________________________
                 ___________________________________________

Detección:       [ ] Alerta Telegram  [ ] Grafana  [ ] Físico  [ ] Log
Tiempo detección → respuesta: _______ minutos

Causa raíz:      ___________________________________________
Acciones:        1. ________________________________________
                 2. ________________________________________
                 3. ________________________________________

¿Afectó cultivos?: [ ] Sí — describir daño: _______________
                   [ ] No

Resolución:      ___________________________________________
Tiempo total:    _______ minutos desde detección hasta resolución
Responsable:     ___________

Acción preventiva para que no se repita:
                 ___________________________________________
```

---

## 7. Checklist de seguridad — antes de poner en producción

### MQTT y red

- [ ] Autenticación MQTT activada — `allow_anonymous false` en Mosquitto
- [ ] ACL configurado — cada cápsula solo escribe en su propio topic
- [ ] TLS activado en puerto 8883 (o al menos autenticación en 1883)
- [ ] Contraseñas de al menos 16 caracteres generadas con gestor de contraseñas
- [ ] Contraseñas guardadas en gestor de contraseñas (no en texto plano, no en git)
- [ ] Firewall UFW activo en el RPi
- [ ] `config.h` está en `.gitignore` y nunca fue commiteado

### Firebase

- [ ] Reglas de seguridad aplicadas — sin `.read: true` o `.write: true` globales
- [ ] Usuarios creados con roles correctos (admin, gateway, operador)
- [ ] 2FA activado en la cuenta de Google que administra Firebase
- [ ] Service account key (JSON) guardada fuera del repositorio git

### Acceso remoto

- [ ] Tailscale instalado en el RPi — acceso remoto sin exponer puertos
- [ ] Sin port forwarding abierto en el router hacia el RPi
- [ ] SSH solo accesible desde la red local (no desde internet)
- [ ] Contraseña de SSH cambiada (no usar la contraseña por defecto `raspberry`)

### Monitoreo de seguridad

- [ ] Alerta Node-RED configurada si Mosquitto no recibe datos en > 5 min
- [ ] Alerta si un ESP32 publica un valor físicamente imposible (> 50 °C, CO₂ < 0)
- [ ] Log de Mosquitto guardado con retención de 30 días
- [ ] Procedimiento de rotación de contraseñas documentado en equipo

---

## 8. Actualizaciones de firmware — OTA seguro

Cuando se actualiza el firmware de los ESP32 de forma remota (tarea IOT-15), aplicar:

```cpp
// En el firmware — verificar que OTA solo acepta desde la red local
ArduinoOTA.setHostname(CAPSULA_ID);
ArduinoOTA.setPassword(OTA_PASSWORD);  // Definido en config.h

// Opcional: verificar que la IP del solicitante es el RPi
ArduinoOTA.onStart([]() {
    Serial.println("OTA: inicio de actualización");
    // Apagar todos los actuadores antes de actualizar
    digitalWrite(RELAY_HUMIDIFIER, HIGH);
    digitalWrite(RELAY_EXTRACTOR, HIGH);
    digitalWrite(RELAY_HEATER, HIGH);
    digitalWrite(RELAY_LED, HIGH);
});
```

**Regla:** antes de hacer un OTA update de producción, probarlo primero en la cápsula Mini de I+D.

---

*Bichongos · docs/seguridad-iot.md · v1.0 · 2026-06-30*
