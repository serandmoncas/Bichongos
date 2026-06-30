# Plan de Red WiFi — Invernadero Bichongos

> Diseño de la red local del invernadero: topología, direccionamiento IP, ubicación del AP, seguridad y plan de contingencia.

**Versión:** 1.0 · **Fecha:** 2026-06-30
**Tarea:** F1-15 del BACKLOG.md

---

## 1. Topología general

```
                         INTERNET
                            │
                     ┌──────┴──────┐
                     │   ROUTER    │  192.168.10.1
                     │  WiFi 2.4G  │  SSID: bichongos-lab
                     │  (con UPS)  │  WPA3 / AES-256
                     └──────┬──────┘
                            │ Ethernet Cat5e
                            │
              ┌─────────────┴─────────────┐
              │      RASPBERRY PI 4       │  192.168.10.10
              │      Gateway Central      │
              │  Mosquitto  :1883         │
              │  Node-RED   :1880         │
              │  InfluxDB   :8086         │
              │  Grafana    :3000         │
              └───────────────────────────┘
                            │
              ┌─────────────┴──────────────────────────────┐
              │              WiFi 2.4 GHz                   │
              │                                             │
    ┌─────────┴──┐  ┌────────────┐  ┌────────────┐         │
    │  ESP32     │  │  ESP32     │  │  ESP32     │  . . .  │
    │  capsula-01│  │  capsula-02│  │  capsula-03│         │
    │ .20        │  │ .21        │  │ .22        │         │
    └────────────┘  └────────────┘  └────────────┘         │
                                                           │
                                          ┌────────────────┘
                                          │
                                 ┌────────┴────────┐
                                 │  Teléfonos /    │  .100–.199
                                 │  Tablets /      │  (DHCP)
                                 │  Laptop admin   │
                                 └─────────────────┘
```

---

## 2. Mapa de cobertura WiFi en el invernadero

```
INVERNADERO — Vista superior (7 × 14 m)

  Norte
  ┌─────────────────────────────────────────────────────────────┐
  │                                                             │
  │   Zona E — Incubación       Zona F — Fructificación        │
  │  ┌──────────────────┐      ┌──────────────────────────┐    │
  │  │                  │      │                          │    │
  │  │  [C-01] .20      │      │  [C-03] .22              │    │
  │  │  [C-02] .21      │      │  [C-04] .23              │    │
  │  │                  │      │                          │    │
  │  └──────────────────┘      └──────────────────────────┘    │
  │                                                             │
  │             ░░░░░░░░░░░░░░░░░░░░░░░░                        │
  │           ░░░░░░░░░░░░░░░░░░░░░░░░░░░░                      │
  │          ░░░░░░  ZONA DE COBERTURA   ░░░░                   │
  │   ╔══════░░░░░░════════════════════░░░░════╗                │
  │   ║      ░░░░░░░  ÓPTIMA (-60 dBm) ░░░░░  ║                │
  │   ║     ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░   ║                │
  │   ║    ░░░[  AP / ROUTER  ]░░░░░░░░░░░░░  ║ ← Centro-Norte │
  │   ║     ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░   ║                │
  │   ╚══════░░░░░░░░░░░░░░░░░░░░░░░░░░░░════╝                │
  │           ░░░░░░░░░░░░░░░░░░░░░░░░░░░░                      │
  │             ░░░░░░░░░░░░░░░░░░░░░░░░                        │
  │                                                             │
  │   Zona D — Inoculación   Zona B — Sustrato   Zona C — Seco │
  │  ┌──────────┐            ┌──────────┐        ┌──────────┐  │
  │  │          │            │          │        │          │  │
  │  │ [Laptop] │            │          │        │          │  │
  │  │ admin    │            │          │        │          │  │
  │  └──────────┘            └──────────┘        └──────────┘  │
  │                                                             │
  │            Zona A — Almacenamiento / Bodega                │
  └─────────────────────────────────────────────────────────────┘
  Sur

  ░ = Zona de cobertura WiFi óptima (señal > -70 dBm)
  AP montado a 2 m de altura, orientado al centro del invernadero
  Distancia máxima ESP32 ↔ AP en este invernadero: ≈ 12 m (señal excelente)
```

**Nota sobre el ESP32:** el módulo WiFi del ESP32 opera solo en 2.4 GHz. Tiene sensibilidad de recepción de -97 dBm y potencia de transmisión de +20 dBm. En espacio abierto, la cobertura es superior a 50 m. Dentro del invernadero (estructuras metálicas, humedad elevada) se estima cobertura real de 20–30 m sin problemas — más que suficiente para 14 m de largo.

---

## 3. Plan de direccionamiento IP

### Segmento de red

```
Red:       192.168.10.0 / 24
Router:    192.168.10.1
Broadcast: 192.168.10.255
Máscara:   255.255.255.0
DNS:       8.8.8.8 (Google) / 1.1.1.1 (Cloudflare)
```

### IPs estáticas (reservadas por MAC en el router)

| Dispositivo | Hostname | IP estática | MAC (llenar al instalar) |
|------------|---------|------------|--------------------------|
| Router / AP | router | 192.168.10.1 | — (es el gateway) |
| Raspberry Pi 4 | bichongos-gw | 192.168.10.10 | `__:__:__:__:__:__` |
| ESP32 Cápsula 01 | capsula-01 | 192.168.10.20 | `__:__:__:__:__:__` |
| ESP32 Cápsula 02 | capsula-02 | 192.168.10.21 | `__:__:__:__:__:__` |
| ESP32 Cápsula 03 | capsula-03 | 192.168.10.22 | `__:__:__:__:__:__` |
| ESP32 Cápsula 04 | capsula-04 | 192.168.10.23 | `__:__:__:__:__:__` |
| ESP32 Cápsula 05 | capsula-05 | 192.168.10.24 | `__:__:__:__:__:__` |
| *(Reserva futura)* | capsula-06..10 | 192.168.10.25–.29 | — |

### IPs dinámicas (DHCP para dispositivos de administración)

| Rango | Uso |
|-------|-----|
| 192.168.10.100 – .199 | Laptops, teléfonos, tablets del equipo |
| 192.168.10.200 – .254 | Reserva / dispositivos temporales |

### Cómo configurar IP estática en el ESP32

En `firmware/capsula_core/config.h`:

```cpp
// IP estática (recomendado — evita que el ESP32 cambie de IP si el router reinicia)
#define USE_STATIC_IP true
#define STATIC_IP     "192.168.10.20"   // Cambiar por número de cápsula
#define GATEWAY_IP    "192.168.10.1"
#define SUBNET_MASK   "255.255.255.0"
#define DNS_PRIMARY   "8.8.8.8"
#define DNS_SECONDARY "1.1.1.1"
```

En el firmware Arduino:

```cpp
IPAddress local_IP(192, 168, 10, 20);
IPAddress gateway(192, 168, 10, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);

WiFi.config(local_IP, gateway, subnet, dns);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
```

---

## 4. Mapa de puertos y servicios

### Servicios en el Raspberry Pi (192.168.10.10)

| Puerto | Protocolo | Servicio | Acceso desde |
|--------|----------|---------|-------------|
| 1883 | TCP | Mosquitto MQTT | ESP32 + red local |
| 1880 | TCP | Node-RED UI | Red local (solo LAN) |
| 8086 | TCP | InfluxDB API | Node-RED (localhost) |
| 3000 | TCP | Grafana Dashboard | Red local + VPN |
| 22 | TCP | SSH | Red local (solo LAN) |

### Puertos bloqueados en el router (no exponer a internet)

```
FIREWALL ROUTER — Reglas de entrada desde Internet:
  DENEGAR TODO por defecto
  No abrir ningún puerto hacia el RPi desde internet

Acceso remoto → usar VPN (Tailscale o WireGuard instalado en el RPi)
                NO usar port forwarding de Grafana/Node-RED
```

### Diagrama de flujo de datos

```
ESP32 (capsula-01)
       │
       │  MQTT publish  →  bichongos/capsula-01/sensors
       ▼
Mosquitto :1883
       │
       │  Suscripción interna
       ▼
Node-RED :1880
       │
       ├──► InfluxDB :8086  (almacenamiento histórico)
       │
       ├──► Telegram Bot API  (alertas críticas)
       │
       └──► Firebase HTTPS  (sincronización nube)

Grafana :3000
       │
       └──► Consulta InfluxDB :8086  (visualización)
```

---

## 5. Configuración del router / AP

### Especificaciones mínimas del router

| Parámetro | Requisito |
|-----------|----------|
| Banda | 2.4 GHz (obligatorio — ESP32 no soporta 5 GHz) |
| Estándar | 802.11n o superior |
| Potencia de transmisión | ≥ 20 dBm |
| DHCP con reserva por MAC | Sí (necesario para IPs estáticas) |
| Firewall básico | Sí |
| Encriptación | WPA2 mínimo, WPA3 preferido |

### Routers recomendados (disponibles en Colombia)

| Modelo | Precio COP | Notas |
|--------|-----------|-------|
| TP-Link TL-WR940N | $ 65.000 | Económico, suficiente para el invernadero |
| TP-Link Archer C6 | $ 120.000 | Dual-band — usar canal 2.4G para ESP32 |
| MikroTik hAP lite | $ 85.000 | Mayor control, configurable por terminal |

### Configuración recomendada del SSID

```
SSID:       bichongos-lab
Contraseña: [mínimo 16 caracteres, alfanumérica + símbolo]
Banda:      2.4 GHz exclusivo (o separar SSID del 5 GHz)
Canal:      1, 6 o 11 (canales no solapados — verificar con app WiFi Analyzer)
Modo:       802.11n (N only o B/G/N)
DHCP:       Rango .100 a .199 (estáticas reservadas fuera de este rango)
```

### Dónde montar el router

```
POSICIÓN ÓPTIMA:
  ✅ Centro-Norte del invernadero, a 2,0 m de altura
  ✅ Montado en mástil o pared, no sobre estantería metálica
  ✅ Dentro de una caja estanca IP54 si la HR supera el 80 % en esa zona
  ✅ Conectado al UPS del gateway (mismo circuito que el RPi)

EVITAR:
  ✗ Junto a la pared metálica o cubierta de zinc (reflexión de señal)
  ✗ Cerca del humidificador o fuentes de vapor de agua
  ✗ Dentro de las cápsulas (temperatura variable, humedad extrema)
  ✗ En el suelo (baja cobertura, riesgo de agua)
```

---

## 6. Seguridad de la red

### Segmentación (si el router lo permite)

```
Red principal (LAN):  192.168.10.0/24   ← Todo el invernadero
  ├── Dispositivos IoT:  .10 – .29      ← RPi + ESP32
  └── Dispositivos admin: .100 – .199   ← Laptops, teléfonos

Si el router soporta VLAN o red de invitados:
  Red IoT (VLAN 10):   Solo ESP32 y RPi, sin acceso a internet directo
  Red Admin (VLAN 20): Laptops y teléfonos con acceso completo
```

### Acceso remoto seguro (sin exponer puertos)

```
OPCIÓN RECOMENDADA — Tailscale (VPN mesh, gratuito hasta 3 dispositivos):

1. Instalar Tailscale en el Raspberry Pi:
   curl -fsSL https://tailscale.com/install.sh | sh
   sudo tailscale up

2. Instalar Tailscale en el teléfono/laptop del administrador

3. Resultado: acceso a Grafana desde cualquier lugar del mundo
   mediante:  http://[IP-tailscale-del-RPi]:3000
   Sin abrir ningún puerto en el router del invernadero.
```

### Contraseñas a documentar (guardar en gestor de contraseñas, NO en git)

| Servicio | Usuario | Contraseña |
|---------|---------|-----------|
| WiFi SSID bichongos-lab | — | [definir al instalar] |
| SSH Raspberry Pi | pi / bichongos | [definir al instalar] |
| Grafana admin | admin | [cambiar en primer login] |
| InfluxDB admin | bichongos | [definir al instalar] |
| MQTT broker | capsula-XX | [definir en config.h] |
| Tailscale | cuenta Google/email | [cuenta personal] |

---

## 7. Plan de contingencia — WiFi caído

El firmware del ESP32 debe funcionar en modo autónomo cuando pierde la red. Estado definido en tarea IOT-20.

```
Estado normal:
  ESP32 conectado a WiFi → publica MQTT → gateway recibe → controla actuadores

Cuando WiFi cae:
  ESP32 intenta reconexión cada 30 segundos (hasta 10 intentos)
  │
  ├── Si reconecta → reanuda operación normal
  │
  └── Si no reconecta en 5 minutos → MODO SEGURO LOCAL:
        • Continúa leyendo sensores
        • Sigue controlando actuadores con los últimos umbrales del perfil en SPIFFS
        • Guarda lecturas en buffer circular en RAM (últimas 2 horas)
        • LED de estado parpadea en patrón distinto (ej. 3 parpadeos cortos)
        • Al reconectar: publica buffer acumulado con timestamps correctos
```

### Indicador LED de estado del ESP32

```
LED integrado GPIO2 del DevKit:

Parpadeo lento (1 seg ON / 1 seg OFF):  Conectado y operando normal
Parpadeo rápido (200 ms):               Intentando conectar a WiFi
3 parpadeos cortos + pausa:             Modo seguro (sin WiFi)
LED fijo:                               Error crítico (reiniciar)
Sin señal:                              Sin energía o firmware colgado
```

---

## 8. Registro de dispositivos de red

> Llenar esta tabla al momento de instalar cada dispositivo.

```
REGISTRO DE RED — INVERNADERO BICHONGOS
Última actualización: ___________

┌────────────────┬──────────────────┬──────────────┬────────────────────┬──────────────┐
│  Dispositivo   │    Hostname      │  IP estática │  Dirección MAC     │  Instalado   │
├────────────────┼──────────────────┼──────────────┼────────────────────┼──────────────┤
│  Router TP-Link│  router          │ 192.168.10.1 │  (es el gateway)   │              │
│  RPi 4         │  bichongos-gw    │ 192.168.10.10│                    │              │
│  ESP32 C-01    │  capsula-01      │ 192.168.10.20│                    │              │
│  ESP32 C-02    │  capsula-02      │ 192.168.10.21│                    │              │
│  ESP32 C-03    │  capsula-03      │ 192.168.10.22│                    │              │
│  ESP32 C-04    │  capsula-04      │ 192.168.10.23│                    │              │
│  ESP32 C-05    │  capsula-05      │ 192.168.10.24│                    │              │
└────────────────┴──────────────────┴──────────────┴────────────────────┴──────────────┘

Cómo obtener la MAC de un ESP32:
  En el Monitor Serial de Arduino IDE, el firmware imprime:
  "MAC: AA:BB:CC:DD:EE:FF" al arrancar.
  O en código: Serial.println(WiFi.macAddress());
```

---

## 9. Checklist de instalación de red

### Antes de instalar el router

- [ ] Verificar que hay tomacorriente cerca del punto de montaje (o extensión con supresor de picos)
- [ ] Definir el canal WiFi con la app "WiFi Analyzer" en el teléfono — elegir el canal 1, 6 o 11 menos congestionado
- [ ] Comprar caja estanca IP54 si la HR en la zona de montaje supera 80 %
- [ ] Conectar el router al mismo UPS que el Raspberry Pi

### Al configurar el router

- [ ] Cambiar contraseña de admin del router (no dejar la de fábrica)
- [ ] Configurar SSID: `bichongos-lab` con contraseña de al menos 16 caracteres
- [ ] Deshabilitar el SSID de 5 GHz o configurar SSID separado (los ESP32 no lo usan)
- [ ] Configurar canal fijo (no "auto") — el cambio automático de canal desconecta los ESP32
- [ ] Configurar rango DHCP: 192.168.10.100 a 192.168.10.199
- [ ] Reservar IPs por MAC para el RPi y cada ESP32

### Al instalar cada ESP32

- [ ] Editar `config.h` con SSID, contraseña y IP estática correcta
- [ ] Encender y verificar en Monitor Serial que se conecta: `WiFi conectado. IP: 192.168.10.2X`
- [ ] Registrar la MAC en la tabla de la sección 8
- [ ] Hacer ping desde el laptop: `ping 192.168.10.2X`
- [ ] Verificar que publica MQTT: `mosquitto_sub -h 192.168.10.10 -t "bichongos/#" -v`

### Al instalar el Raspberry Pi

- [ ] Conectar por Ethernet al router (no WiFi — conexión más estable)
- [ ] Asignar IP estática 192.168.10.10 por reserva MAC en el router
- [ ] Verificar SSH desde laptop: `ssh pi@192.168.10.10`
- [ ] Instalar Tailscale para acceso remoto seguro

---

## 10. Diagnóstico de problemas comunes

| Síntoma | Causa probable | Solución |
|---------|---------------|---------|
| ESP32 no se conecta al WiFi | Contraseña incorrecta en config.h | Verificar SSID y contraseña, recompilar |
| ESP32 se conecta pero pierde IP | DHCP cambia la IP | Configurar IP estática en firmware o reserva por MAC en router |
| Señal débil en una cápsula | Interferencia de estantería metálica | Reubicar el router o instalar repetidor WiFi entre ellos |
| MQTT no recibe datos | Mosquitto detenido o IP del broker incorrecta | `sudo systemctl status mosquitto` en el RPi |
| Grafana inaccesible desde teléfono | Dispositivo en red diferente | Verificar que el teléfono esté en `bichongos-lab`, no en datos móviles |
| ESP32 en modo seguro constante | Router apagado o cápsula fuera de rango | Verificar router encendido; verificar nivel de señal con Serial |
| Canal WiFi cambia solo | Router en modo "auto" de canal | Fijar canal 1, 6 o 11 en la configuración del router |

---

*Bichongos · docs/red-wifi-invernadero.md · v1.0 · 2026-06-30*
