# 🍄 Bichongos — Sistema de Cápsulas de Cultivo Controlado

> **Concepto central:** cápsulas de bajo costo con control total de temperatura, humedad, CO₂ y luz que permiten cultivar cualquier especie de hongo independientemente de la ubicación geográfica y sus condiciones externas.

**Sede piloto:** Guarne, Antioquia, Colombia · Escala: Microempresa · Replicable en nuevas sedes

---

## Tabla de Contenidos

1. [Visión del Proyecto](#1-visión-del-proyecto)
2. [Concepto de Cápsula de Cultivo](#2-concepto-de-cápsula-de-cultivo)
3. [Ruta de Cultivo: de lo más fácil a lo más difícil](#3-ruta-de-cultivo)
4. [Documentación Técnica por Especie](#4-documentación-técnica-por-especie)
5. [Distribución del Espacio](#5-distribución-del-espacio)
6. [Sistema IoT — Arquitectura](#6-sistema-iot--arquitectura)
7. [Materiales y Equipos](#7-materiales-y-equipos)
8. [Plan Financiero](#8-plan-financiero)
9. [Metodologías de Cultivo](#9-metodologías-de-cultivo)
10. [Hoja de Ruta del Software](#10-hoja-de-ruta-del-software)
11. [Roadmap de Habilidades del Equipo](#11-roadmap-de-habilidades-del-equipo)
12. [Referencias](#12-referencias)

---

## 1. Visión del Proyecto

**Bichongos** es un sistema modular de cápsulas de cultivo de hongos que elimina la dependencia del clima local. Cada cápsula recrea con precisión las condiciones ideales de una especie específica — temperatura, humedad, CO₂ y luz — usando hardware de bajo costo controlado por IoT.

Esto permite:
- **Cultivar cualquier especie en cualquier lugar:** desde Bogotá (frío) hasta Barranquilla (tropical), la cápsula entrega siempre las mismas condiciones.
- **Escalar abriendo nuevas sedes:** el mismo diseño de cápsula + los mismos archivos de configuración de parámetros reproducen el cultivo en una nueva ubicación.
- **Optimizar por cepa:** cada cápsula puede tener un perfil de parámetros distinto, permitiendo cultivar simultáneamente especies con requerimientos opuestos (ej. Enoki a 8 °C y Reishi a 28 °C) en el mismo local.

### Categorías de producción

| Categoría | Especies | Mercado objetivo |
|-----------|----------|-----------------|
| **Gourmet** | Orellana, Shiitake, Portobello, Crimini, Paris, Enoki | Restaurantes, plazas, supermercados |
| **Funcional** | Reishi, Melena de León, Maitake, Cordyceps, Cola de Pavo, Chaga | Tiendas naturistas, suplementos, venta directa |
| **Medicinal** | Psilocybe spp. y otros | Investigación, terapia asistida (marco regulatorio) |

---

## 2. Concepto de Cápsula de Cultivo

Una **cápsula Bichongos** es una cámara hermética aislada térmicamente con control activo de todos los parámetros ambientales que influyen en el crecimiento de hongos.

### Principio de operación

```
┌──────────────────────────────────────────────────┐
│              CÁPSULA DE CULTIVO                   │
│                                                  │
│   Sensores ──→ ESP32 ──→ Lógica de control       │
│      │                        │                  │
│   [SHT31]              [Relés → Actuadores]       │
│   [MH-Z19B]                   │                  │
│   [BH1750]          ┌─────────┼─────────┐        │
│   [DS18B20]         ▼         ▼         ▼        │
│                 Calefactor Humidif. Extractor     │
│                 /Enfriador  FAE      LED          │
│                                                  │
│   Perfil activo: "shiitake-fructificacion.json"  │
│   Temp: 18°C · HR: 90% · CO₂: <800ppm · Luz: 12h│
└──────────────────────────────────────────────────┘
```

### Tipos de cápsula según escala

| Tipo | Dimensiones | Capacidad | Ideal para |
|------|------------|-----------|-----------|
| **Mini** | Nevera modificada 150 L | 10–20 bolsas | Pruebas, I+D, cepas nuevas |
| **Estándar** | Caja construida 60×60×120 cm | 30–50 bolsas | Producción por especie |
| **Rack** | Estantería con cortina 90×50×180 cm | 80–120 bolsas | Producción principal |
| **Contenedor** | Contenedor 20 pies modificado | 500–1.000 bolsas | Nueva sede / exportación |

### Perfil de cepa (Strain Profile)

Cada especie tiene un archivo de configuración `JSON` que define los parámetros exactos de cada etapa. El mismo perfil se carga en cualquier cápsula de cualquier sede:

```json
{
  "especie": "Lentinula edodes",
  "nombre_comun": "Shiitake",
  "etapa_actual": "fructificacion",
  "etapas": {
    "incubacion": {
      "temp_min": 20, "temp_max": 25,
      "humedad_min": 70, "humedad_max": 80,
      "co2_max": 5000,
      "luz_horas": 0,
      "duracion_dias": 60
    },
    "fructificacion": {
      "temp_min": 15, "temp_max": 22,
      "humedad_min": 85, "humedad_max": 95,
      "co2_max": 1000,
      "luz_horas": 12,
      "duracion_dias": 14,
      "choque_frio": true,
      "temp_choque": 10,
      "duracion_choque_horas": 12
    }
  }
}
```

### Ventajas del modelo de cápsula vs. invernadero tradicional

| Aspecto | Invernadero tradicional | Cápsula Bichongos |
|---------|------------------------|-------------------|
| Dependencia del clima | Alta | Ninguna |
| Reproducibilidad | Varía por temporada | Consistente |
| Escalabilidad | Requiere nueva infraestructura | Añadir cápsulas |
| Nuevas sedes | Limitado por clima local | Replicable globalmente |
| Costo de climatización | Alto (toda la estructura) | Bajo (solo el volumen de la cápsula) |
| Control por especie | Difícil (mismo ambiente para todo) | Total (cada cápsula tiene su perfil) |

---

## 3. Ruta de Cultivo

De la especie más accesible a la más compleja. La secuencia define también el **orden de implementación de cápsulas** — cada nivel añade complejidad técnica y de control.

### Nivel 1 — Principiante

#### 🌸 Orellana (Pleurotus ostreatus / djamor / citrinopileatus)
- **Por qué primero:** mayor tolerancia a contaminación, ciclo corto (4–6 semanas), sustrato económico (paja), colonización agresiva.
- **Cápsula:** la más simple — solo humedad y ventilación básica. No requiere calefacción en Guarne.
- **Rentabilidad:** eficiencia biológica 100–150 %.
- **📄 [Ver especificaciones técnicas completas →](docs/especies/N1-orellana.md)**

---

### Nivel 2 — Intermedio

#### 🍄 Shiitake (Lentinula edodes)
- **Complejidad añadida:** bloque compactado, colonización lenta, choque de frío o inmersión para inducir fructificación.
- **Cápsula:** control de temperatura preciso para el choque de inducción.
- **📄 [Ver especificaciones técnicas completas →](docs/especies/N2-shiitake.md)**

#### 🟤 Portobello / Crimini / Paris (Agaricus bisporus)
- **Complejidad añadida:** compost en dos fases, capa de casing, control estricto de CO₂.
- **📄 [Ver especificaciones técnicas completas →](docs/especies/N2-portobello.md)**

#### 🦁 Melena de León (Hericium erinaceus)
- **Complejidad añadida:** muy sensible al CO₂ elevado — control de FAE crítico para producir pompones blancos.
- **📄 [Ver especificaciones técnicas completas →](docs/especies/N2-melena-de-leon.md)**

---

### Nivel 3 — Avanzado

#### 🧊 Enoki (Flammulina velutipes)
- **Complejidad añadida:** requiere enfriamiento activo (7–12 °C). Alto CO₂ intencional para tallos largos.
- **Cápsula:** primer uso de sistema de frío activo. Parámetros invertidos vs. resto de especies.
- **📄 [Ver especificaciones técnicas completas →](docs/especies/N3-enoki.md)**

#### 🌿 Maitake (Grifola frondosa)
- **Complejidad añadida:** colonización extremadamente lenta (14–20 semanas), sustrato de aserrín de roble.
- **📄 [Ver especificaciones técnicas completas →](docs/especies/N3-maitake.md)**

#### 🦃 Cola de Pavo (Trametes versicolor)
- **Complejidad añadida:** producción orientada a extractos, no a consumo fresco. Ciclo largo.
- **📄 [Ver especificaciones técnicas completas →](docs/especies/N3-cola-de-pavo.md)**

#### 🔴 Reishi (Ganoderma lucidum)
- **Complejidad añadida:** especie tropical, requiere calefacción activa (25–30 °C). Producto en polvo.
- **Cápsula:** primer uso intensivo de calefacción activa.
- **📄 [Ver especificaciones técnicas completas →](docs/especies/N3-reishi.md)**

---

### Nivel 4 — Experto / Especializado

#### 🐛 Cordyceps (Cordyceps militaris)
- **Complejidad añadida:** sustrato de arroz o pupas, ciclos de luz/oscuridad precisos, técnica casi estéril.
- **Valor de mercado:** el más alto — $50–125 USD/kg seco.
- **📄 [Ver especificaciones técnicas completas →](docs/especies/N4-cordyceps.md)**

#### 🌲 Chaga (Inonotus obliquus)
- **Nota:** cultivo artificial experimental. Estrategia recomendada: micelio líquido o troncos de abedul importados.
- **📄 [Ver especificaciones técnicas completas →](docs/especies/N4-chaga.md)**

#### 🍄 Trufas (Tuber spp.)
- **Nota:** simbiosis micorrícica con árboles. Horizonte de 5–10 años. Proyecto de largo plazo paralelo.
- **📄 [Ver especificaciones técnicas completas →](docs/especies/N4-trufas.md)**

#### 🔬 Psilocybe spp.
- **Marco legal Colombia:** posesión personal no penalizada (Ley 30/1986). Producción comercial regulada.
- **Estrategia:** cultivo experimental bajo protocolo documentado para investigación.
- **📄 [Ver especificaciones técnicas completas →](docs/especies/N4-psilocybe.md)**

---

## 4. Documentación Técnica por Especie

Cada especie tiene su ficha técnica completa con parámetros de cápsula, receta de sustrato, protocolos por etapa, guía de contaminación y métricas de mercado.

### Índice de especies

| Nivel | Especie | Dificultad | Documentación |
|-------|---------|-----------|---------------|
| 1 | Orellana | ⭐ | [docs/especies/N1-orellana.md](docs/especies/N1-orellana.md) |
| 2 | Shiitake | ⭐⭐ | [docs/especies/N2-shiitake.md](docs/especies/N2-shiitake.md) |
| 2 | Portobello / Crimini / Paris | ⭐⭐ | [docs/especies/N2-portobello.md](docs/especies/N2-portobello.md) |
| 2 | Melena de León | ⭐⭐ | [docs/especies/N2-melena-de-leon.md](docs/especies/N2-melena-de-leon.md) |
| 3 | Enoki | ⭐⭐⭐ | [docs/especies/N3-enoki.md](docs/especies/N3-enoki.md) |
| 3 | Maitake | ⭐⭐⭐ | [docs/especies/N3-maitake.md](docs/especies/N3-maitake.md) |
| 3 | Cola de Pavo | ⭐⭐⭐ | [docs/especies/N3-cola-de-pavo.md](docs/especies/N3-cola-de-pavo.md) |
| 3 | Reishi | ⭐⭐⭐ | [docs/especies/N3-reishi.md](docs/especies/N3-reishi.md) |
| 4 | Cordyceps | ⭐⭐⭐⭐ | [docs/especies/N4-cordyceps.md](docs/especies/N4-cordyceps.md) |
| 4 | Chaga | ⭐⭐⭐⭐ | [docs/especies/N4-chaga.md](docs/especies/N4-chaga.md) |
| 4 | Trufas | ⭐⭐⭐⭐⭐ | [docs/especies/N4-trufas.md](docs/especies/N4-trufas.md) |
| 4 | Psilocybe | ⭐⭐⭐⭐ | [docs/especies/N4-psilocybe.md](docs/especies/N4-psilocybe.md) |

### Otros documentos

| Documento | Descripción |
|-----------|-------------|
| [docs/capsula/diseno-capsula.md](docs/capsula/diseno-capsula.md) | Especificaciones técnicas de construcción de la cápsula |
| [docs/roadmap-equipo.md](docs/roadmap-equipo.md) | Roadmap de habilidades y conocimientos del equipo |
| [docs/protocolos/](docs/protocolos/) | SOPs de inoculación, pasteurización y postcosecha |

---

## 5. Distribución del Espacio

**Sede piloto — Invernadero Guarne:** 7×14 m · Área útil: 5×10 m (50 m²)

El espacio está organizado en zonas de proceso, no en cuartos climáticos — el control climático ocurre dentro de cada cápsula.

```
┌─────────────────────────────────────────────────────┐
│  INVERNADERO 7×14m                                  │
│                                                     │
│  ┌──────────────┬─────────────────┬──────────────┐  │
│  │  ZONA A      │    ZONA B       │   ZONA C     │  │
│  │  Bodega +    │  Prep sustrato  │  Secado +    │  │
│  │  Materiales  │  Pasteurización │  Postcosecha │  │
│  │  (5×2 m)     │  (5×2 m)        │  (5×2 m)     │  │
│  ├──────────────┼─────────────────┼──────────────┤  │
│  │  ZONA D      │    ZONA E       │   ZONA F     │  │
│  │  Inoculación │ CÁPSULAS        │  CÁPSULAS    │  │
│  │  (sala limpia│  Incubación     │  Fructific.  │  │
│  │  2.5×2 m)    │  (5×2.5 m)      │  (5×3.5 m)   │  │
│  └──────────────┴─────────────────┴──────────────┘  │
└─────────────────────────────────────────────────────┘
```

| Zona | Área | Función |
|------|------|---------|
| **A — Bodega / Materiales** | 5×2 m | Sustratos secos, bolsas, insumos, repuestos IoT |
| **B — Preparación / Pasteurización** | 5×2 m | Hidratación y pasteurización de sustrato |
| **C — Secado / Postcosecha** | 5×2 m | Deshidratación, empaque, conservación en frío |
| **D — Inoculación** | 2.5×2 m | Zona limpia: flujo laminar, siembra de micelio |
| **E — Cápsulas de Incubación** | 5×2.5 m | Racks/cápsulas en etapa de colonización |
| **F — Cápsulas de Fructificación** | 5×3.5 m | Racks/cápsulas en etapa de producción y cosecha |

**Notas de construcción:**
- Pisos: concreto sellado o epoxi resistente a la humedad y al lavado.
- Paredes internas: lámina PVC o plástico calibre 6.
- Electricidad: circuito 220V dedicado para autoclave. Protección GFCI en zonas húmedas.

---

## 6. Sistema IoT — Arquitectura

### Diagrama de capas

```
┌──────────────────────────────────────────────────────┐
│                    CAPA DE NUBE                       │
│     Firebase Realtime DB · Telegram Bot · Web App    │
└────────────────────────┬─────────────────────────────┘
                         │ HTTPS / WebSocket
┌────────────────────────▼─────────────────────────────┐
│               GATEWAY LOCAL (Raspberry Pi 4)          │
│    Mosquitto MQTT · Node-RED · InfluxDB · Grafana    │
└───────┬──────────────┬──────────────┬────────────────┘
        │ MQTT         │ MQTT         │ MQTT
┌───────▼──────┐ ┌─────▼──────┐ ┌────▼───────┐
│  CÁPSULA #1  │ │ CÁPSULA #2 │ │ CÁPSULA #3 │  ...
│  Orellana    │ │  Shiitake  │ │   Reishi   │
│  Fructific.  │ │  Incubac.  │ │  Fructif.  │
│              │ │            │ │            │
│  ESP32       │ │  ESP32     │ │  ESP32     │
│  SHT31       │ │  SHT31     │ │  SHT31     │
│  MH-Z19B     │ │  DS18B20   │ │  MH-Z19B   │
│  BH1750      │ │            │ │  BH1750    │
│              │ │            │ │            │
│  → Humidif.  │ │ → Calefac. │ │ → Calefac. │
│  → Extractor │ │ → Ventil.  │ │ → Humidif. │
│  → LED       │ │            │ │ → Extractor│
└──────────────┘ └────────────┘ └────────────┘
   perfil JSON      perfil JSON    perfil JSON
```

### Hardware por cápsula (nodo ESP32)

| Componente | Cantidad | Función |
|------------|----------|---------|
| ESP32 DevKit v1 | 1 | Microcontrolador WiFi + lógica de control |
| Sensor SHT31 | 1 | Temperatura + humedad relativa |
| Sensor MH-Z19B | 1 | CO₂ en ppm (fructificación) |
| Sensor BH1750 | 1 | Intensidad lumínica en lux (fructificación) |
| Sensor DS18B20 | 1 | Temperatura del sustrato (incubación) |
| Módulo relé 4 canales | 1 | Control de actuadores |
| Fuente 5V 2A | 1 | Alimentación |
| Caja IP65 | 1 | Protección en ambiente húmedo |

### Stack de software

| Capa | Tecnología | Rol |
|------|-----------|-----|
| Firmware | Arduino C++ + PubSubClient | Lectura sensores, control actuadores, publicación MQTT |
| Broker | Mosquitto (RPi) | Mensajería entre cápsulas y gateway |
| Automatización | Node-RED (RPi) | Lógica de control por perfil de especie |
| Base de datos | InfluxDB (RPi) | Serie de tiempo — historial por cápsula |
| Dashboard local | Grafana (RPi) | Visualización en red local |
| Nube | Firebase Realtime DB | Respaldo + acceso remoto entre sedes |
| Alertas | Telegram Bot API | Notificaciones críticas al celular |
| Perfiles de cepa | JSON por especie/etapa | Configuración portátil y versionada en git |
| Web App (fase 2) | Next.js + Firebase | Panel de gestión de lotes y cápsulas |
| App móvil (fase 3) | React Native o Flutter | Control remoto desde el celular |

### Lógica de control por perfil

```
Al iniciar cápsula:
  Cargar perfil JSON de la especie/etapa activa

Cada 30 segundos:
  Leer todos los sensores
  Comparar con los rangos del perfil activo

  SI humedad < perfil.humedad_min → activar humidificador
  SI humedad > perfil.humedad_max → desactivar humidificador
  SI CO₂ > perfil.co2_max        → activar extractor (FAE)
  SI temp  < perfil.temp_min     → activar calefactor
  SI temp  > perfil.temp_max     → activar enfriamiento / alerta

  Publicar todos los valores → MQTT → InfluxDB → Firebase
  SI valor fuera de rango crítico → alerta Telegram inmediata
  SI fin de etapa (días >= perfil.duracion_dias) → notificar cambio de etapa
```

### Estructura del repositorio

```
bichongos/
├── firmware/                    # Código Arduino para ESP32
│   ├── capsula_core/            # Firmware base (aplica a todas las cápsulas)
│   └── profiles/                # Perfiles JSON por especie y etapa
├── gateway/                     # Configuración Raspberry Pi
│   ├── mosquitto.conf
│   ├── node-red-flows.json
│   └── grafana-dashboards/
├── webapp/                      # Panel de gestión (Fase 2)
├── docs/                        # Documentación técnica
│   ├── especies/                # Ficha técnica por especie
│   ├── capsula/                 # Diseño y construcción de cápsulas
│   ├── protocolos/              # SOPs de laboratorio
│   └── roadmap-equipo.md        # Roadmap de habilidades
└── README.md
```

---

## 7. Materiales y Equipos

### 7.1 Equipos de laboratorio

| Equipo | Especificación mínima | Costo aprox. (USD) |
|--------|----------------------|-------------------|
| Olla a presión / autoclave | 30–50 L, 15 PSI | 200–500 |
| Campana de flujo laminar | DIY con filtro HEPA | 300–600 |
| Deshidratador | 6–10 bandejas, 70 °C | 150–300 |
| pH-metro digital | Rango 0–14 | 40–80 |
| Microscopio | 400× mínimo | 100–300 |
| Báscula digital | 0.1 g – 10 kg | 40–80 |
| Selladora al vacío | — | 80–200 |
| Humidificadores ultrasónicos | 5 L | 40–80 c/u |
| Extractores FAE | 4"–6" | 30–60 c/u |
| Mini split 9.000 BTU | Para cápsulas de Enoki / Reishi | 500–800 |
| Estanterías metálicas | 5 niveles 90×40×180 cm | 80–150 c/u |
| Nevera de conservación | 200–300 L | 300–500 |

### 7.2 Consumibles e insumos

| Material | Uso | Costo aprox. |
|----------|-----|-------------|
| Paja de arroz o trigo | Sustrato orellana | $3–5 USD/fardo |
| Aserrín de maderas duras | Shiitake, melena, reishi | $5–10 USD/50 kg |
| Salvado de trigo / arroz | Suplemento nutricional | $8–15 USD/50 kg |
| Arroz integral | Sustrato cordyceps / semilla | $1–2 USD/kg |
| Compost pasteurizado | Portobello / Paris | $10–20 USD/bulto |
| Turba + cal dolomita | Casing Agaricus | $15–25 USD |
| Bolsas polipropileno 0.003" | Bloques de sustrato | $10–20 USD/x100 |
| Alcohol isopropílico 70 % | Desinfección | $5–10 USD/galón |
| Guantes nitrilo | Inoculación | $8–15 USD/caja |
| Mascarillas N95 | Inoculación y polvos | $15–25 USD/caja |

### 7.3 Hardware IoT por cápsula

| Componente | Costo aprox. (USD) |
|------------|-------------------|
| ESP32 DevKit v1 | 8 |
| SHT31 | 6 |
| MH-Z19B (CO₂) | 25 |
| BH1750 (luz) | 3 |
| DS18B20 (temp sustrato) | 4 |
| Módulo relé 4 canales | 6 |
| Fuente 5V 2A + caja IP65 | 13 |
| Cables y conectores | 10 |
| **Total por cápsula** | **~75 USD** |

**Gateway central (una vez):**

| Componente | Costo aprox. (USD) |
|------------|-------------------|
| Raspberry Pi 4 (2 GB) | 55 |
| SSD USB 64 GB | 15 |
| UPS 600 VA | 60 |
| **Total gateway** | **~130 USD** |

---

## 8. Plan Financiero

### 8.1 Inversión inicial — Fase 1 (3–5 cápsulas, Orellana + Shiitake)

| Categoría | Costo estimado (USD) |
|-----------|---------------------|
| Adecuación del invernadero | 1.500 – 2.500 |
| Equipos de laboratorio esenciales | 1.200 – 2.000 |
| Hardware IoT (5 cápsulas + gateway) | 500 – 650 |
| Consumibles e insumos iniciales (3 meses) | 400 – 600 |
| Cepas y semilla de partida | 200 – 400 |
| Software y servicios | 50 – 100 |
| Imprevistos (10 %) | 400 – 700 |
| **Total Fase 1** | **~4.250 – 6.950 USD** |

### 8.2 Proyección de producción — Orellana (base)

| Variable | Valor |
|----------|-------|
| Capacidad inicial | 5 cápsulas rack × 50 bolsas = 250 bolsas/ciclo |
| Producción por bolsa (1 kg sustrato seco) | ~1.0 – 1.5 kg |
| Producción por ciclo (4–6 semanas) | 250 – 375 kg |
| Ciclos por año | 8 – 10 |
| Producción anual estimada | 2.000 – 3.750 kg |

### 8.3 Precios de mercado Colombia (2024–2025)

| Especie | Mayorista | Restaurantes | Directo / CSA |
|---------|----------|-------------|--------------|
| Orellana | $10.000–12.000/kg | $14.000–20.000/kg | $18.000–25.000/kg |
| Shiitake | $25.000–35.000/kg | $35.000–50.000/kg | $40.000–60.000/kg |
| Melena de León | $35.000–50.000/kg | $50.000–80.000/kg | $60.000–100.000/kg |
| Reishi (seco) | $80.000–120.000/kg | — | $120.000–200.000/kg |
| Cordyceps (seco) | $200.000–400.000/kg | — | $400.000–600.000/kg |

### 8.4 Roadmap financiero por fases

| Fase | Especies / producto | Inversión adicional | Ingreso bruto anual estimado |
|------|--------------------|--------------------|------------------------------|
| 1 — MVP | Orellana | $4.250–7.000 USD | $5.000–12.000 USD |
| 2 — Expansión | + Shiitake, Melena de León | $2.000–3.000 USD | $15.000–30.000 USD |
| 3 — Funcionales | + Reishi, Cola de Pavo, Cordyceps | $3.000–5.000 USD | $25.000–60.000 USD |
| 4 — Procesamiento | Extractos, polvos, suplementos | $5.000–10.000 USD | $50.000–120.000 USD |
| 5 — Nuevas sedes | Replicar modelo en otra ciudad | $8.000–15.000 USD/sede | Multiplicar por sede |

> **ROI estimado Fase 1:** 14–20 meses. El costo de hardware IoT por cápsula (~$75 USD) se recupera en el primer ciclo de producción.

---

## 9. Metodologías de Cultivo

### 9.1 Flujo general de producción

```
Cepa madre (agar) → Expansión en agar → Semilla en grano
        ↓
Inoculación de sustrato en bolsa/bloque (Zona D)
        ↓
Carga en CÁPSULA DE INCUBACIÓN con perfil JSON activo
        ↓
Colonización completa (monitoreo IoT continuo)
        ↓
Cambio de perfil: inducción / choque (según especie)
        ↓
Carga en CÁPSULA DE FRUCTIFICACIÓN
        ↓
Cosecha (cortar antes de que los bordes se enrollen)
        ↓
Postcosecha: pesaje, empaque, frío o secado (Zona C)
        ↓
2.ª y 3.ª oleada (reutilizar bloque)
```

### 9.2 Técnicas por nivel

| Técnica | Para qué sirve | Nivel |
|---------|---------------|-------|
| Pasteurización en caliente (80 °C × 1–2 h) | Paja para orellana | Principiante |
| Fermentación en frío / cal | Paja sin calor | Principiante |
| Esterilización en autoclave (121 °C × 2.5 h) | Grano, aserrín suplementado | Intermedio |
| Cultivo en agar (MEA / MYA) | Expansión y aislamiento de cepas | Intermedio |
| Cultivo líquido (LC) | Propagación masiva de micelio | Avanzado |
| Clonación desde tejido frutal | Preservar características de un ejemplar | Intermedio |
| Aislamiento monoespórico | Crear cepas nuevas desde esporas | Experto |

### 9.3 Control de contaminación

| Contaminante | Síntoma | Causa común |
|-------------|---------|------------|
| **Trichoderma** | Moho verde | Exceso CO₂ / temp alta |
| **Neurospora** | Moho naranja | Pasteurización insuficiente |
| **Cobwebs** | Micelio de araña | Baja humedad |
| **Bacterias** | Sustrato viscoso / olor ácido | pH incorrecto o agua contaminada |

**Protocolo:** cuarentena inmediata en bolsa sellada → salida del área → registro del lote en el sistema para identificar el origen.

---

## 10. Hoja de Ruta del Software

| Fase | Módulo | Estado | Descripción |
|------|--------|--------|-------------|
| **0** | README + diseño del proyecto | ✅ | Documento actual |
| **1** | Firmware ESP32 + perfiles JSON | 🔲 | Control de cápsulas con lógica parametrizada por especie |
| **1** | Gateway RPi (Mosquitto + Node-RED + Grafana) | 🔲 | Broker, automatización y dashboard local |
| **1** | Firebase + Telegram Bot | 🔲 | Respaldo en nube y alertas críticas |
| **2** | Web App — Panel de gestión | 🔲 | Registro de lotes, cápsulas, cosechas e historial |
| **2** | API REST (backend) | 🔲 | Integración IoT ↔ panel de gestión |
| **3** | Wiki técnica integrada | 🔲 | Protocolos y fichas de especie en el panel |
| **3** | App móvil | 🔲 | Dashboard y alertas desde el celular |
| **4** | Trazabilidad por lote | 🔲 | QR por lote, historial de condiciones, rendimiento por cepa |
| **4** | Módulo financiero | 🔲 | Costos por lote, ingresos y rentabilidad por especie |
| **5** | Multi-sede | 🔲 | Un dashboard que consolida varias sedes con sus cápsulas |

---

## 11. Roadmap de Habilidades del Equipo

El equipo necesita desarrollar habilidades en tres áreas simultáneas: **micología**, **electrónica/IoT** y **operaciones de laboratorio**. La secuencia de aprendizaje sigue la ruta de cultivo — cada especie nueva agrega una habilidad nueva.

**[→ Ver roadmap completo de habilidades del equipo](docs/roadmap-equipo.md)**

### Resumen por etapas

| Etapa | Duración | Enfoque micológico | Enfoque técnico/IoT |
|-------|----------|-------------------|---------------------|
| **0 — Fundamentos** | Mes 1–2 | Higiene de lab, conceptos básicos de micología | Montaje de primera cápsula, sensores y relés |
| **1 — Principiante** | Mes 2–4 | Orellana completa (sustrato, inoculación, cosecha) | Firmware ESP32, dashboard Grafana |
| **2 — Intermedio** | Mes 4–10 | Shiitake, melena, portobello; trabajo en agar | Node-RED, Firebase, Telegram Bot, perfiles JSON |
| **3 — Avanzado** | Mes 10–18 | Enoki, reishi, maitake; cultivo líquido | Multi-cápsula, gateway robusto, web app |
| **4 — Experto** | Mes 18+ | Cordyceps, psilocybe; aislamiento de cepas | Multi-sede, trazabilidad, módulo financiero |

---

## 12. Referencias

### Libros fundamentales

- Stamets, P. (1993). *Growing Gourmet and Medicinal Mushrooms*. Ten Speed Press.
- Stamets, P. (2005). *Mycelium Running: How Mushrooms Can Help Save the World*. Ten Speed Press.
- Stamets, P. & Chilton, J.S. (1983). *The Mushroom Cultivator*. Agarikon Press.
- Cotter, T. (2014). *Organic Mushroom Farming and Mycoremediation*. Chelsea Green Publishing.
- Oei, P. (2003). *Mushroom Cultivation: Appropriate Technology for Mushroom Growers*. Backhuys Publishers.

### Recursos técnicos en línea

- [Shroomery.org](https://www.shroomery.org) — foros técnicos y base de datos de técnicas.
- [r/MushroomGrowing](https://reddit.com/r/MushroomGrowing) — comunidad activa de cultivadores.
- [Fungi Perfecti](https://www.fungi.com) — recursos de Paul Stamets.

### IoT / Hardware

- [ESP32 Arduino Core Documentation](https://docs.espressif.com/projects/arduino-esp32)
- [Node-RED Documentation](https://nodered.org/docs/)
- [InfluxDB + Grafana Stack](https://grafana.com/docs/grafana/latest/)
- [PubSubClient — MQTT para Arduino](https://github.com/knolleary/pubsubclient)

### Marco legal — Colombia

- Ley 30 de 1986 — Estatuto Nacional de Estupefacientes, art. 2 (dosis personal).
- Sentencia C-491/12, Corte Constitucional — posesión personal no penalizada.
- Decreto 780 de 2016 — marco de referencia para uso medicinal.

### Papers científicos

- Wasser, S.P. (2002). Medicinal mushrooms as a source of antitumor and immunomodulating polysaccharides. *Applied Microbiology and Biotechnology*, 60, 258–274.
- Phan, C.W. et al. (2015). Therapeutic potential of culinary-medicinal mushrooms. *Critical Reviews in Biotechnology*, 35(3), 355–368.
- Friedman, M. (2016). Mushroom polysaccharides. *Foods*, 5(4), 80.

---

*Proyecto en desarrollo activo — Bichongos · Guarne, Antioquia, Colombia*
*Última actualización: 2026-06-30*
