# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**Bichongos** is an IoT-controlled mushroom cultivation laboratory in Guarne, Antioquia, Colombia (2,150 msnm, 14–17 °C average). The core concept is hermetic **capsules** — independent climate-controlled chambers where each species runs its own JSON strain profile (temperature, humidity, CO₂, light). This makes cultivation location-independent and replicable across sites.

**Production categories:**
- Gourmet: orellana, shiitake, portobello, crimini, paris, enoki
- Functional/medicinal: reishi, melena de león, maitake, cordyceps, cola de pavo, chaga
- Restricted (research only): psilocybe (Ley 30/1986)

---

## Repository Structure

```
Bichongos/
├── README.md                     # Main project documentation
├── BACKLOG.md                    # Product backlog (10 epics, 114 tasks)
├── .gitignore
├── docs/
│   ├── capsula/
│   │   └── diseno-capsula.md     # Capsule types (Mini/Standard/Rack), wiring, BOM
│   ├── especies/                 # Per-species technical docs (12 files, N1–N4)
│   │   ├── N1-orellana.md
│   │   ├── N2-shiitake.md
│   │   ├── N2-portobello.md
│   │   ├── N2-melena-de-leon.md
│   │   ├── N3-enoki.md
│   │   ├── N3-reishi.md
│   │   ├── N3-maitake.md
│   │   ├── N3-cola-de-pavo.md
│   │   ├── N4-cordyceps.md
│   │   ├── N4-psilocybe.md
│   │   ├── N4-chaga.md           # sin perfil JSON todavía (ver BACKLOG.md)
│   │   └── N4-trufas.md          # sin perfil JSON todavía (ver BACKLOG.md)
│   ├── protocolos/               # SOPs (Standard Operating Procedures)
│   │   ├── SOP-pasteurizacion.md
│   │   ├── SOP-esterilizacion.md
│   │   ├── SOP-inoculacion.md
│   │   ├── SOP-cultivo-liquido.md
│   │   └── SOP-postcosecha.md
│   └── roadmap-equipo.md         # 5-stage skill ladder for the team
├── firmware/
│   ├── capsula_core/             # ESP32 Arduino firmware — implementado y compila (PlatformIO)
│   │   ├── capsula_core.ino      # Sketch principal
│   │   ├── platformio.ini        # Entorno de build (esp32dev)
│   │   ├── profile.h / .cpp      # Carga y parseo de perfil JSON
│   │   ├── mqtt_client.h / .cpp  # Publicación/suscripción MQTT
│   │   ├── sensors.h / .cpp, actuators.h / .cpp, stage_tracker.h / .cpp
│   │   ├── data/profiles/        # Copia de los perfiles JSON para subir a SPIFFS
│   │   └── README.md             # Setup, GPIO pinout, MQTT topics
│   └── profiles/                 # JSON strain profiles (10 species — chaga/trufas aún sin perfil)
│       ├── N1-orellana.json
│       ├── N2-shiitake.json
│       ├── N2-portobello.json
│       ├── N2-melena-de-leon.json
│       ├── N3-enoki.json
│       ├── N3-reishi.json
│       ├── N3-maitake.json
│       ├── N3-cola-de-pavo.json
│       ├── N4-cordyceps.json
│       └── N4-psilocybe.json
├── gateway/                      # Raspberry Pi 4 configuration — implementado
│   ├── scripts/                  # setup.sh, setup-cloud.sh, add-capsule.sh, backup.sh, ups-shutdown.sh
│   ├── mosquitto/, node-red-flows.json, grafana dashboards
│   └── README.md                 # Mosquitto + Node-RED + InfluxDB + Grafana setup
├── webapp/                       # Future Next.js web app (planned Phase 2)
├── docs/superpowers/             # Specs y planes de diseño (proceso spec-driven)
│   ├── specs/                    # Un archivo por decisión de diseño significativa
│   └── plans/                    # Planes de implementación derivados de las specs
└── .claude/                      # Automatizaciones de Claude Code para este repo
    ├── settings.json             # Hooks: anti-credenciales (commit), validador de esquema JSON
    ├── hooks/                    # Scripts de los hooks anteriores
    ├── agents/                   # firmware-iot-reviewer (revisión de firmware bajo demanda)
    └── skills/nueva-especie/     # Genera doc + JSON + fila de BACKLOG para una especie nueva
```

---

## Tech Stack

### IoT Layer (per capsule)
- **MCU:** ESP32 (Arduino framework)
- **Build:** PlatformIO (`firmware/capsula_core/platformio.ini`, entorno `esp32dev`, `platform = espressif32@7.0.1` fijado)
- **Sensors:** SHT31 (temp+humidity, I2C), MH-Z19B (CO₂, UART), BH1750 (light, I2C), DS18B20 (substrate temp, 1-Wire)
- **Actuators:** 4-channel relay (humidifier, FAE extractor, heater, LED)
- **Protocol:** MQTT via PubSubClient library
- **Storage:** SPIFFS for JSON strain profiles

### Gateway (Raspberry Pi 4)
- **Broker:** Mosquitto (port 1883)
- **Automation:** Node-RED (port 1880)
- **Time-series DB:** InfluxDB 2.x (port 8086)
- **Visualization:** Grafana (port 3000)
- **Cloud sync:** Firebase Realtime Database (free tier)
- **Alerts:** Telegram Bot

### Future Web App
- Next.js + Firebase + Tailwind CSS

---

## Key Concepts

### Strain Profile (JSON)
Each species has a JSON file in `firmware/profiles/` defining parameters per cultivation stage. The ESP32 firmware loads the active profile from SPIFFS and uses it for all control decisions. **Profiles are versioned in git and portable across any capsule at any site.**

```json
{
  "id": "N1-orellana",
  "etapa_actual": "incubacion",
  "etapas": {
    "incubacion": { "temp_min": 20, "temp_max": 24, "humedad_min": 70, ... },
    "fructificacion": { "temp_min": 14, "temp_max": 20, "co2_max": 1000, ... }
  },
  "alertas": { "temp_critica_max": 26, ... }
}
```

### MQTT Topics
```
bichongos/{capsula_id}/sensors    # Sensor readings (30s interval)
bichongos/{capsula_id}/alert      # Critical out-of-range events
bichongos/{capsula_id}/status     # Actuator state
bichongos/{capsula_id}/profile/set  # Change active profile remotely
```

### Critical Species Notes
- **Enoki:** inverted logic — needs COLD (7–12 °C) + HIGH CO₂ (>2000 ppm). Firmware must support `co2_min` as well as `co2_max`.
- **Melena de León:** most CO₂-sensitive species (max 700 ppm). High CO₂ causes deformed spines.
- **Reishi:** tropical species — needs active heating (25–30 °C) in Guarne throughout all stages.
- **Cordyceps:** total darkness during incubation; strict 12/12 light cycle for fruiting; inoculate with liquid culture only.
- **Psilocybe:** legally restricted in Colombia (Ley 30/1986); profile includes `zona_restringida: true`.

---

## Credentials & Secrets

**Never commit:**
- `firmware/capsula_core/config.h` (WiFi credentials, MQTT server IP, capsule ID)
- `gateway/.env` (Firebase credentials, Telegram bot token)
- `webapp/.env` / `webapp/.env.local`

Use `*.example` template files for each. These are listed in `.gitignore`.

---

## Development Status

See `BACKLOG.md` for the full product backlog. Current phase: **firmware (`firmware/capsula_core/`) y gateway (`gateway/`) implementados y compilando** (IOT-02 a IOT-07 y GW-01 a GW-06 completos). **Infraestructura física en obra activa** desde julio 2026 — la sede de Guarne (invernadero 7×14 m) se está construyendo en el marco de la consultoría con La Jobiteka (Juan, socio de Songo Sorhongo), que está ejecutando la obra civil (ver Épica 1 y Épica 15 en `BACKLOG.md`, y `docs/reuniones/`). Meta: dos habitaciones terminadas para la semana del 3 de agosto de 2026.

**Immediate blockers:**
1. Infraestructura física en construcción pero no terminada (épica E1, 0/19 tareas completas — obra civil en curso, meta parcial 3-ago-2026 para 2 habitaciones)
2. No certified mushroom strain acquired yet (`CUL-01` pending) — semilla en pedido con dos proveedores, ~20 días de entrega
3. Firmware nunca se ha probado en un ESP32 real — está compilado y revisado (`pio run -e esp32dev`), pero no validado en hardware físico

**Next priorities** (from BACKLOG.md):
- `F1-01`/`F1-05`: sellar pisos del invernadero, construir la primera cápsula Mini
- `CUL-01`: acquire certified Orellana strain
- Desplegar el firmware a un ESP32 real una vez exista la primera cápsula, y validar sensores/actuadores contra `docs/capsula/diagrama-electrico-capsula-mini.md`
