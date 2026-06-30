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
│   │   └── N4-psilocybe.md
│   ├── protocolos/               # SOPs (Standard Operating Procedures)
│   │   ├── SOP-pasteurizacion.md
│   │   ├── SOP-esterilizacion.md
│   │   ├── SOP-inoculacion.md
│   │   ├── SOP-cultivo-liquido.md
│   │   └── SOP-postcosecha.md
│   └── roadmap-equipo.md         # 5-stage skill ladder for the team
├── firmware/
│   ├── capsula_core/             # ESP32 Arduino firmware (not yet implemented)
│   │   └── README.md             # Setup, GPIO pinout, MQTT topics
│   └── profiles/                 # JSON strain profiles (10 species)
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
├── gateway/                      # Raspberry Pi 4 configuration (not yet implemented)
│   └── README.md                 # Mosquitto + Node-RED + InfluxDB + Grafana setup
└── webapp/                       # Future Next.js web app (planned Phase 2)
```

---

## Tech Stack

### IoT Layer (per capsule)
- **MCU:** ESP32 (Arduino framework)
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

See `BACKLOG.md` for the full product backlog. Current phase: **Fase 0 completed** (documentation base). Starting Fase 1 (hardware build + firmware).

**Immediate blockers:**
1. Firmware `capsula_core/` is not yet implemented (no `.ino` files)
2. Gateway Raspberry Pi not yet configured
3. No physical capsule built yet

**Next Sprint 1 priorities** (from BACKLOG.md):
- `IOT-01` through `IOT-07`: firmware skeleton with sensor reading and MQTT publishing
- `GW-01` through `GW-06`: Raspberry Pi + Mosquitto + InfluxDB + Grafana setup
- `CUL-01`: acquire certified Orellana strain
