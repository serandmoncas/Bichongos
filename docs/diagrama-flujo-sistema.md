# Diagrama de Flujo — Sistema Completo Bichongos

> Flujos de datos, control, alertas y ciclo de producción del sistema IoT de cultivo.

**Versión:** 1.0 · **Fecha:** 2026-06-30

---

## Índice

1. [Arquitectura general](#1-arquitectura-general)
2. [Flujo principal — lectura de sensores y control (30 s)](#2-flujo-principal--lectura-de-sensores-y-control-30-s)
3. [Lógica de control de actuadores](#3-lógica-de-control-de-actuadores)
4. [Flujo de alertas](#4-flujo-de-alertas)
5. [Flujo de gestión de perfil](#5-flujo-de-gestión-de-perfil)
6. [Flujo de datos hacia la nube](#6-flujo-de-datos-hacia-la-nube)
7. [Flujo de contingencia — red caída](#7-flujo-de-contingencia--red-caída)
8. [Ciclo de vida completo de un lote](#8-ciclo-de-vida-completo-de-un-lote)
9. [Flujo de postcosecha y trazabilidad](#9-flujo-de-postcosecha-y-trazabilidad)
10. [Flujo de acceso multi-usuario](#10-flujo-de-acceso-multi-usuario)

---

## 1. Arquitectura general

```
╔══════════════════════════════════════════════════════════════════════════════╗
║                     SISTEMA BICHONGOS — ARQUITECTURA                        ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                              ║
║  CAPA FÍSICA                CAPA DE BORDE            CAPA DE NUBE           ║
║  (Invernadero)              (Invernadero)             (Internet)             ║
║                                                                              ║
║  ┌─────────────┐            ┌─────────────────┐      ┌─────────────────┐    ║
║  │  CÁPSULA 1  │            │  RASPBERRY PI 4 │      │    FIREBASE     │    ║
║  │  ─────────  │  MQTT/TLS  │  ─────────────  │      │  Realtime DB    │    ║
║  │  ESP32      ├───────────►│  Mosquitto      │─────►│  (backup nube)  │    ║
║  │  SHT31      │            │  Node-RED       │      └─────────────────┘    ║
║  │  MH-Z19B    │            │  InfluxDB       │                             ║
║  │  BH1750     │            │  Grafana        │      ┌─────────────────┐    ║
║  │  DS18B20    │            │                 │─────►│    TELEGRAM     │    ║
║  │  Relés ×4   │            └─────────────────┘      │  Bot alertas    │    ║
║  └─────────────┘                    ▲                └─────────────────┘    ║
║                                     │                                        ║
║  ┌─────────────┐                    │                ┌─────────────────┐    ║
║  │  CÁPSULA 2  ├────────────────────┤                │    WEB APP      │    ║
║  │  ESP32 ...  │       WiFi 2.4G    │                │  Next.js        │    ║
║  └─────────────┘                    │                │  (Fase 2)       │    ║
║                                     │                └─────────────────┘    ║
║  ┌─────────────┐                    │                                        ║
║  │  CÁPSULA N  ├────────────────────┘                ┌─────────────────┐    ║
║  │  ESP32 ...  │                                     │   APP MÓVIL     │    ║
║  └─────────────┘                                     │  (Fase 3)       │    ║
║                                                      └─────────────────┘    ║
╚══════════════════════════════════════════════════════════════════════════════╝
```

---

## 2. Flujo principal — lectura de sensores y control (30 s)

> El ciclo más importante del sistema. Se repite cada 30 segundos en cada ESP32.

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                        ESP32 — CICLO PRINCIPAL (30 s)                       │
└─────────────────────────────────────────────────────────────────────────────┘

  INICIO DEL CICLO
        │
        ▼
  ┌─────────────┐     Error de
  │  Leer todos │────lectura────►  Publicar alerta sensor
  │  los        │                  bichongos/{id}/alert
  │  sensores   │                  {"tipo":"sensor_error","sensor":"SHT31"}
  └──────┬──────┘
         │  OK
         ▼
  ┌──────────────────────────────────────────────────────┐
  │                   DATOS LEÍDOS                        │
  │  temp_aire   = 17.3 °C    humedad     = 88.5 %       │
  │  co2_ppm     = 820        luz_lux     = 450           │
  │  temp_sust   = 16.8 °C                               │
  └──────────────────────┬───────────────────────────────┘
                         │
                         ▼
  ┌─────────────────────────────┐
  │  Cargar perfil activo       │
  │  desde SPIFFS               │
  │  (etapa_actual: fructif.)   │
  └──────────────┬──────────────┘
                 │
                 ▼
  ┌──────────────────────────────────────────────────────┐
  │           LÓGICA DE CONTROL (ver sección 3)           │
  │  → decidir estado de cada relé                        │
  └──────────────────────────────────────────────────────┘
                 │
                 ▼
  ┌─────────────────────────────┐
  │  ¿Valor fuera de rango      │
  │  CRÍTICO?                   │
  └──────────┬──────────────────┘
        SÍ   │    NO
             │     └───────────────────────────────┐
             ▼                                     │
  ┌──────────────────────┐                         │
  │  Publicar ALERTA     │                         │
  │  bichongos/{id}/alert│                         │
  │  (ver sección 4)     │                         │
  └──────────────────────┘                         │
                                                   │
             ┌─────────────────────────────────────┘
             ▼
  ┌──────────────────────────────────────────────────────┐
  │  Publicar datos de sensores                           │
  │  bichongos/{id}/sensors                              │
  │  {                                                    │
  │    "capsula_id": "capsula-01",                       │
  │    "especie":    "N1-orellana",                      │
  │    "etapa":      "fructificacion",                   │
  │    "timestamp":  1751286400,                         │
  │    "temperatura": 17.3,  "humedad": 88.5,            │
  │    "co2_ppm":    820,    "luz_lux": 450,             │
  │    "temp_sustrato": 16.8,                            │
  │    "actuadores": {                                    │
  │      "humidificador": false,                         │
  │      "extractor": false,                             │
  │      "calefactor": false,                            │
  │      "led": true                                     │
  │    }                                                  │
  │  }                                                    │
  └──────────────────────────────────────────────────────┘
             │
             ▼
  ┌──────────────────────┐
  │  Publicar estado     │
  │  bichongos/{id}/status│
  └──────────────────────┘
             │
             ▼
  ┌──────────────────────┐
  │  Esperar 30 segundos │
  └──────────────────────┘
             │
             └──────────────► INICIO DEL CICLO


  ┌─────────────────────────────────────────────────────┐
  │                GATEWAY — LADO RECEPTOR               │
  │                                                     │
  │  Mosquitto recibe mensaje                           │
  │         │                                           │
  │         ▼                                           │
  │  Node-RED procesa                                   │
  │         │                                           │
  │         ├──► InfluxDB  (almacenar serie temporal)   │
  │         │                                           │
  │         ├──► Firebase  (sincronizar nube)           │
  │         │                                           │
  │         └──► ¿Alerta?  →  Telegram Bot             │
  │                                                     │
  │  Grafana consulta InfluxDB cada 10 s               │
  │  y actualiza el dashboard en tiempo real            │
  └─────────────────────────────────────────────────────┘
```

---

## 3. Lógica de control de actuadores

> Árbol de decisión que el ESP32 ejecuta en cada ciclo para decidir el estado de cada relé.

```
                    PERFIL ACTIVO CARGADO
                    (etapa: fructificacion)
                    temp_min:14  temp_max:20
                    hum_min:85   hum_max:95
                    co2_max:1000
                    luz_horas:12

        ┌───────────────┬───────────────┬─────────────────┐
        │               │               │                 │
        ▼               ▼               ▼                 ▼
  ──TEMPERATURA──  ──HUMEDAD──    ──CO₂──          ──LUZ──
        │               │               │                 │
        ▼               ▼               ▼                 ▼
  temp < temp_min?  hum < hum_min?  co2 > co2_max?  ¿Dentro del
        │               │               │             horario?
       SÍ NO           SÍ NO           SÍ NO         07:00–19:00
        │  │            │  │            │  │               │
        ▼  ▼            ▼  ▼            ▼  ▼              SÍ NO
      ON OFF          ON OFF          ON OFF              │   │
  CALEFACTOR      HUMIDIF.        EXTRACTOR              ▼   ▼
                                                       ON  OFF
                  ─────────────────────────────       LED
                  hum > hum_max?
                     SÍ → OFF HUMIDIF. (override)
                  ─────────────────────────────
                  temp > temp_max?
                     SÍ → ON EXTRACTOR (refrigeración pasiva)
                     SÍ + calefactor ON → OFF CALEFACTOR (conflicto)


  CASO ESPECIAL — ENOKI (lógica invertida):
  ┌──────────────────────────────────────────────────────┐
  │  Perfil tiene co2_min además de co2_max              │
  │                                                      │
  │  co2 < co2_min (2000 ppm)?                          │
  │    SÍ → OFF EXTRACTOR  (acumular CO₂)               │
  │    NO → continuar lógica normal                      │
  │                                                      │
  │  temp > temp_max (12 °C)?                           │
  │    SÍ → ON SISTEMA DE FRÍO (relé adicional)         │
  └──────────────────────────────────────────────────────┘


  PROTECCIONES TRANSVERSALES (aplican siempre):
  ┌──────────────────────────────────────────────────────┐
  │  • Tiempo mínimo entre encendidos de un relé: 30 s   │
  │    (evita ciclado rápido que daña actuadores)        │
  │                                                      │
  │  • Calefactor y sistema de frío NUNCA simultáneos    │
  │                                                      │
  │  • Si temp_sustrato > 35 °C → OFF CALEFACTOR + ALERTA│
  │    (sensor de seguridad independiente)               │
  │                                                      │
  │  • Si humedad > 99 % → OFF HUMIDIFICADOR + ALERTA    │
  │    (condensación puede dañar sensores)               │
  └──────────────────────────────────────────────────────┘
```

---

## 4. Flujo de alertas

```
  ESP32 detecta valor fuera de rango CRÍTICO
  (definido en "alertas" del perfil JSON)
          │
          ▼
  ┌───────────────────────────────────┐
  │  Publicar en MQTT:                │
  │  bichongos/{id}/alert             │
  │  {                                │
  │    "tipo": "temperatura_critica", │
  │    "valor_actual": 27.5,          │
  │    "umbral": 26,                  │
  │    "accion": "calefactor_off",    │
  │    "timestamp": 1751286400        │
  │  }                                │
  └───────────────────────────────────┘
          │
          ▼
  Mosquitto → Node-RED
          │
          ├──► InfluxDB: registrar evento de alerta
          │
          ├──► Firebase: actualizar estado de alerta
          │
          └──► ¿Nivel crítico?
                    │
               SÍ ──┴── NO
               │          │
               ▼          ▼
         Telegram    Solo registrar
         inmediato   (sin notificación)
               │
               ▼
  ┌────────────────────────────────────────────────────────┐
  │  MENSAJE TELEGRAM:                                     │
  │  ─────────────────                                     │
  │  🔴 ALERTA CRÍTICA — Cápsula 01 (Orellana)            │
  │  ──────────────────────────────────────                │
  │  ⚠️  Temperatura fuera de rango                       │
  │  📊 Valor actual:  27.5 °C                            │
  │  📋 Límite:        26.0 °C                            │
  │  🕐 Hora:          14:23                              │
  │  ✅ Acción tomada: calefactor apagado                  │
  │  ──────────────────────────────────────                │
  │  /ver_capsula_01   /silenciar_1h                      │
  └────────────────────────────────────────────────────────┘
          │
          ▼
  ┌─────────────────────────────┐
  │  Operario recibe notif.     │
  │  en teléfono                │
  └──────────────┬──────────────┘
                 │
         ┌───────┴────────┐
         ▼                ▼
   Revisar físico    /silenciar_1h
   el invernadero    (alerta se suprime
         │            por 1 hora)
         ▼
   ¿Problema resuelto?
         │
    SÍ ──┴── NO
    │          │
    ▼          ▼
  Alerta    Escalar:
  se cierra  llamada
  sola en    directa
  Grafana


  TIPOS DE ALERTA Y NIVELES:
  ┌───────────────────────────────────────┬──────────┬──────────────────┐
  │ Tipo de alerta                        │ Nivel    │ Acción           │
  ├───────────────────────────────────────┼──────────┼──────────────────┤
  │ Temperatura fuera de rango crítico    │ 🔴 Alta  │ Telegram inmediato│
  │ CO₂ fuera de rango crítico            │ 🔴 Alta  │ Telegram inmediato│
  │ Humedad crítica (< 60 % o > 99 %)    │ 🔴 Alta  │ Telegram inmediato│
  │ Sin datos de sensor por > 5 min       │ 🔴 Alta  │ Telegram inmediato│
  │ ESP32 desconectado (> 10 min)         │ 🔴 Alta  │ Telegram inmediato│
  │ Temperatura fuera de rango normal     │ 🟡 Media │ Solo log          │
  │ BE% bajo en lote cerrado              │ 🟡 Media │ Resumen diario    │
  │ Fin de etapa próximo (3 días)         │ 🟢 Baja  │ Resumen diario    │
  │ Contaminación reportada               │ 🟡 Media │ Telegram inmediato│
  └───────────────────────────────────────┴──────────┴──────────────────┘
```

---

## 5. Flujo de gestión de perfil

```
  ESCENARIO A — Cambio de etapa en la misma especie
  (ej. incubación → fructificación)

  Operario detecta colonización > 90 %
          │
          ▼
  Admin publica en MQTT (con doble confirmación — ver doc seguridad):
  bichongos/capsula-01/profile/set
  { "perfil": "N1-orellana", "etapa": "fructificacion",
    "confirmacion": "CAMBIAR" }
          │
          ▼
  ESP32 suscriptor recibe mensaje
          │
          ▼
  ┌────────────────────────────────────┐
  │  Validar payload:                  │
  │  ¿El perfil existe en SPIFFS?      │
  │  ¿La etapa existe en el perfil?    │
  └───────────────────┬────────────────┘
                      │
              SÍ ─────┴───── NO
              │                │
              ▼                ▼
  Actualizar           Publicar error:
  etapa_actual         bichongos/{id}/alert
  en RAM               {"tipo":"perfil_invalido"}
              │
              ▼
  Publicar confirmación:
  bichongos/capsula-01/status
  { "perfil_activo": "N1-orellana",
    "etapa": "fructificacion",
    "cambiado_en": 1751286400 }
              │
              ▼
  Próximo ciclo (30 s) usa nuevos umbrales
  Grafana refleja el cambio en tiempo real


  ESCENARIO B — Cambio de especie (nuevo lote)

  Nuevo bloque inoculado en cápsula
          │
          ▼
  ┌────────────────────────────────────────┐
  │  OPCIÓN 1: Remotamente (web/MQTT)      │
  │  Publicar nuevo perfil completo        │
  │  bichongos/capsula-01/profile/set      │
  │  { "perfil": "N2-shiitake",            │
  │    "etapa": "incubacion" }             │
  └────────────────────────────────────────┘
          │
          ó
          ▼
  ┌────────────────────────────────────────┐
  │  OPCIÓN 2: Físicamente (actualizar     │
  │  config.h y recompilar firmware)       │
  │  Solo si no hay conectividad MQTT      │
  └────────────────────────────────────────┘
          │
          ▼
  ESP32 carga nuevo perfil desde SPIFFS
  Reinicia contadores de etapa (día 0)
  Publica nuevo estado en MQTT
```

---

## 6. Flujo de datos hacia la nube

```
  RASPBERRY PI 4 (192.168.10.10)
  ─────────────────────────────────────────────────────────────
        │
        │  Recibe datos de todas las cápsulas cada 30 s
        │
        ▼
  ┌─────────────────┐     ┌─────────────────┐
  │   Mosquitto     │────►│   Node-RED      │
  │   broker        │     │   (orquestador) │
  │   :1883         │     │   :1880         │
  └─────────────────┘     └────────┬────────┘
                                   │
              ┌────────────────────┼────────────────────┐
              │                    │                    │
              ▼                    ▼                    ▼
  ┌───────────────────┐  ┌────────────────┐  ┌─────────────────┐
  │   InfluxDB        │  │  Firebase      │  │  Telegram Bot   │
  │   :8086           │  │  Realtime DB   │  │  API            │
  │                   │  │                │  │                 │
  │  Retención:       │  │  Escribe:      │  │  Envía si:      │
  │  • 30 días full   │  │  • Estado      │  │  • Alerta activa│
  │  • 1 año resumen  │  │    actual      │  │                 │
  │    (1 dato/hora)  │  │  • Últimas     │  │                 │
  └───────────────────┘  │    24 h        │  └─────────────────┘
              │           └────────┬───────┘
              │                    │
              ▼                    ▼
  ┌───────────────────┐  ┌────────────────────────────────┐
  │  Grafana :3000    │  │  Web App / App Móvil (Fase 2+) │
  │                   │  │  Lee desde Firebase en tiempo   │
  │  Dashboards:      │  │  real mediante WebSocket        │
  │  • Tiempo real    │  └────────────────────────────────┘
  │  • Histórico      │
  │  • Por especie    │
  │  • Por cápsula    │
  └───────────────────┘


  POLÍTICA DE SINCRONIZACIÓN CON FIREBASE:
  ┌────────────────────────────────────────────────────────────┐
  │                                                            │
  │  Cada 30 s → Estado actual de cada cápsula (sobrescribe)  │
  │  Cada 5 min → Promedio de lecturas (histórico 24 h)       │
  │  Inmediato  → Alertas activas                             │
  │  Bajo demanda → Cambios de perfil o etapa                 │
  │                                                            │
  │  No se sincroniza a Firebase:                             │
  │  • Historial completo > 24 h (se mantiene solo en         │
  │    InfluxDB local para no exceder cuota gratuita)         │
  └────────────────────────────────────────────────────────────┘
```

---

## 7. Flujo de contingencia — red caída

```
  ESTADO NORMAL
  ESP32 ──WiFi──► Mosquitto ──► Node-RED ──► InfluxDB
                                         ──► Firebase
                                         ──► Telegram

  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  WiFi pierde señal o router se apaga
  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

  ESP32 detecta pérdida de conexión
          │
          ▼
  Intentar reconexión WiFi
  (cada 30 s, hasta 10 intentos)
          │
  ┌───────┴─────────────────────────────────┐
  │                                         │
  ▼ Reconectó (< 5 min)           ▼ Sin conexión (> 5 min)
  │                                         │
  Reanuda                          MODO SEGURO LOCAL
  operación                                 │
  normal                                    ▼
  Publica buffer                   Sigue leyendo sensores (30 s)
  acumulado                        Sigue controlando actuadores
  con timestamps                   con últimos umbrales del perfil
                                   Guarda lecturas en buffer RAM
                                   (hasta 240 lecturas = 2 horas)
                                   LED: 3 parpadeos cortos
                                            │
                                   ┌────────┴──────────┐
                                   │ ¿Reconectó WiFi?  │
                                   └────────┬──────────┘
                                       SÍ   │   NO (> 2 horas)
                                            │         │
                                    Publicar│   Buffer lleno
                                    buffer  │   Descartar más
                                    acumulado│   antiguo
                                            │   Continuar
                                    Reanudar│   modo seguro
                                    normal  │
                                            │
                            ┌───────────────┘
                            │
                            ▼
               ─────────────────────────────────
               Si el RPi también está caído:

               ESP32 sigue en modo seguro
               Grafana no disponible
               Telegram no disponible
               CULTIVO SIGUE FUNCIONANDO
               ─────────────────────────────────
               Acción manual: ir al invernadero
               y verificar estado visual de la cápsula

               Cuando el RPi vuelve:
               Node-RED detecta brecha de datos
               y registra el período sin datos
               ─────────────────────────────────
```

---

## 8. Ciclo de vida completo de un lote

```
  ══════════════════════════════════════════════════════════
                    CICLO DE UN LOTE — ORELLANA
                  (ejemplo: 20 bolsas, 1 kg seco c/u)
  ══════════════════════════════════════════════════════════

  DÍA 0 — PREPARACIÓN
  ────────────────────
  Sustrato seco: 20 kg paja
          │
          ▼
  Pasteurización 80 °C × 90 min
          │
          ▼
  Enfriar a < 30 °C
          │
          ▼
  Inoculación (Zona D)
  Semilla: 3 kg (15 %)
  Registro lote en sistema
  ┌────────────────────────────────────────┐
  │  LOTE-2026-001 creado en Firebase      │
  │  especie: orellana  •  bolsas: 20      │
  │  inoculado: 2026-07-01  •  etapa: INC  │
  └────────────────────────────────────────┘
          │
          ▼

  DÍAS 1–18 — INCUBACIÓN
  ───────────────────────
  Cápsula configurada: perfil N1-orellana / etapa incubacion
  temp: 20–24 °C  •  HR: 70–80 %  •  CO₂: libre  •  luz: 0 h
          │
          │  Ciclo IoT cada 30 s
          │  Datos → InfluxDB → Grafana
          │
          ▼ Día ~14: micelio visible > 90 %
  ┌────────────────────────────────────────┐
  │  Alerta Telegram: "Lote 001 listo para │
  │  inspección — 14 días completados"     │
  └────────────────────────────────────────┘
          │
          ▼

  DÍA 18 — CAMBIO DE ETAPA
  ─────────────────────────
  Admin publica: profile/set → etapa: fructificacion
  ESP32 actualiza umbrales en el próximo ciclo
  ┌────────────────────────────────────────┐
  │  Grafana muestra línea vertical        │
  │  marcando el cambio de etapa           │
  └────────────────────────────────────────┘
          │
          ▼

  DÍAS 18–25 — FRUCTIFICACIÓN
  ────────────────────────────
  temp: 14–20 °C  •  HR: 85–95 %  •  CO₂: < 1000 ppm  •  luz: 12 h
          │
          ▼ Día ~22: primordios visibles
          ▼ Día ~25: cosecha lista (bordes enrollados)

  DÍA 25 — PRIMERA COSECHA (OLEADA 1)
  ─────────────────────────────────────
  Cosechar, limpiar, pesar
  ┌────────────────────────────────────────┐
  │  Registro en sistema:                  │
  │  Oleada: 1  •  Peso: 18.5 kg frescos  │
  │  BE%: 92.5 %  •  Cat A: 14 kg         │
  │  Cat B: 3.5 kg  •  Cat C: 1 kg        │
  └────────────────────────────────────────┘
          │
          ▼
  Retirar pinesado, limpiar superficie del bloque
  Mantener cápsula en fructificación

  DÍAS 26–35 — OLEADAS 2 Y 3
  ────────────────────────────
  Mismo proceso • 5–10 días entre oleadas
  Oleada 2: ~14 kg  •  Oleada 3: ~8 kg

  DÍA 38 — CIERRE DEL LOTE
  ──────────────────────────
  ┌────────────────────────────────────────────────┐
  │  RESUMEN LOTE-2026-001 (generado automático)   │
  │  ─────────────────────────────────────────     │
  │  Duración: 38 días                             │
  │  Sustrato: 20 kg seco                          │
  │  Cosecha total: 40.5 kg frescos                │
  │  BE% global: 202.5 % (3 oleadas acumuladas)   │
  │  Tasa contaminación: 0 / 20 bolsas (0 %)      │
  │  Ingresos: 40.5 kg × $14.000 = $567.000 COP  │
  │  Costo estimado: $182.000 COP                 │
  │  Margen bruto: $385.000 (67.9 %)              │
  └────────────────────────────────────────────────┘
          │
          ▼
  Bloques gastados → compost / sustrato secundario
  Lote cerrado en sistema
  Cápsula disponible para nuevo lote
```

---

## 9. Flujo de postcosecha y trazabilidad

```
  COSECHA REALIZADA
  (peso registrado en sistema)
          │
          ▼
  ┌───────────────────────────────────────────┐
  │  CLASIFICACIÓN MANUAL (Zona C)            │
  │  Cat A: ___kg  Cat B: ___kg  Cat C: ___kg │
  └───────────────────────────────┬───────────┘
                                  │
               ┌──────────────────┼──────────────────┐
               ▼                  ▼                  ▼
          CAT A                CAT B              CAT C
      Restaurantes /        Plaza de          Deshidratación
      mercado premium       mercado           / Extracto
               │                  │                  │
               ▼                  ▼                  ▼
      Empaque bandeja       Bolsa kraft        Deshidratador
      + film perforado      perforada          50–55 °C × 8 h
      Etiqueta con QR       Etiqueta           → Polvo/trozo
               │                  │                  │
               └──────────────────┴──────────────────┘
                                  │
                                  ▼
                    REGISTRO DE VENTA EN SISTEMA
                    ┌─────────────────────────────┐
                    │  lote: LOTE-2026-001         │
                    │  oleada: 1                   │
                    │  peso_vendido: 14 kg (Cat A) │
                    │  precio: $18.000/kg          │
                    │  canal: Restaurante XYZ      │
                    │  ingreso: $252.000 COP       │
                    └─────────────────────────────┘
                                  │
                                  ▼
                    QR de trazabilidad por lote:
                    Escanear → ver historial completo
                    ┌─────────────────────────────┐
                    │  ▣▣▣                        │
                    │  ▣ ▣  LOTE-2026-001         │
                    │  ▣▣▣  Orellana · 2026-07-25 │
                    │       BE: 202 %             │
                    │       IoT: ✅ 38 días       │
                    │       Contam: 0 %           │
                    └─────────────────────────────┘
```

---

## 10. Flujo de acceso multi-usuario

```
  ┌─────────────────────────────────────────────────────────────────────┐
  │                    ACTORES Y SUS FLUJOS                             │
  └─────────────────────────────────────────────────────────────────────┘

  SERGIO (Admin)                    EQUIPO (Operador)
  ─────────────────                 ─────────────────
  Accede a Grafana                  Accede a Grafana
  (lectura + config)                (solo lectura)
         │                                │
         │                                │
  Cambia perfiles          Registra cosechas en sistema
  de cápsulas              Llena registros de lote
         │                                │
         │                                ▼
  ┌──────┴──────────────────────────────────────────────────┐
  │  Node-RED verifica permisos antes de ejecutar cambios   │
  │  Firebase Rules bloquean escritura no autorizada        │
  └─────────────────────────────────────────────────────────┘
         │
         ▼
  TELEGRAM BOT (todos los roles)
  ─────────────────────────────
  Todos reciben alertas críticas
  Solo admin puede ejecutar comandos:
    /perfil_capsula_01    → ver perfil activo
    /cambiar_etapa        → inicia flujo de doble confirmación
    /silenciar_alerta_1h  → suprime notificaciones 1 hora
    /resumen_diario       → reporte de todas las cápsulas


  LÍNEA DE TIEMPO DE UN DÍA TÍPICO:
  ──────────────────────────────────
  07:00  LED de todas las cápsulas enciende (perfil: fructificacion 12h)
  07:00  Node-RED envía resumen diario a Telegram:
         "☀️ Buenos días — 3 cápsulas activas, sin alertas"
  07:30  Equipo llega, revisa Grafana desde el teléfono
  12:00  Sensor de cápsula-02 reporta CO₂ 980 ppm (cerca del límite)
         → Node-RED incrementa frecuencia de publicación a 10 s
         → Sin alerta (aún dentro del rango)
  14:23  Cápsula-01 supera temp. crítica 26 °C
         → Calefactor apagado automáticamente por firmware
         → Telegram: 🔴 alerta crítica
         → Sergio revisa, confirma que el invernadero se calentó
         → Abre ventilación, temperatura vuelve a rango en 20 min
         → Alerta se cierra automáticamente en Grafana
  19:00  LED de todas las cápsulas apaga (fin del ciclo de 12 h)
  20:00  Node-RED envía resumen nocturno:
         "🌙 Resumen 20:00 — Cápsula 01: incidente resuelto,
          Cápsula 02: CO₂ promedio 850 ppm (OK),
          Cápsula 03: colonización al 70 %"
```

---

*Bichongos · docs/diagrama-flujo-sistema.md · v1.0 · 2026-06-30*
