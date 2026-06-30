# Diagrama Eléctrico — Cápsula Mini (Nevera Modificada)

> Esquema completo de conexiones, distribución de energía y cableado para la primera cápsula de producción. Compatible con el nodo IoT descrito en `docs/bom-precios-cop.md`.

**Versión:** 1.0 · **Fecha:** 2026-06-30
**Tarea:** F1-14 del BACKLOG.md

---

## 1. Diagrama de bloques general

```
╔══════════════════════════════════════════════════════════════════════╗
║                  CÁPSULA MINI — SISTEMA ELÉCTRICO                   ║
╠══════════════════════════════════════════════════════════════════════╣
║                                                                      ║
║  ┌─────────────┐     ┌──────────────────────┐     ┌──────────────┐  ║
║  │  FUENTE 1   │     │                      │     │  FUENTE 2    │  ║
║  │  5V / 2A   │     │     MÓDULO DE         │     │  12V / 3A   │  ║
║  │  (USB-C)   │     │      RELÉS            │     │  (DC)        │  ║
║  └──────┬──────┘     │   4 canales          │     └──────┬───────┘  ║
║         │             │   opto-aislado       │            │          ║
║         ▼             └──────────────────────┘            │          ║
║  ┌──────────────┐           │ │ │ │                       │          ║
║  │              │           │ │ │ │                       │          ║
║  │   ESP32      ├──GPIO26───┘ │ │ │         ┌────────────┘          ║
║  │   DevKit V1  ├──GPIO27─────┘ │ │         │                       ║
║  │              ├──GPIO14───────┘ │         │                       ║
║  │              ├──GPIO12─────────┘         │                       ║
║  │              │                           │                       ║
║  │    SENSORES  │    CH1 ──────────────────►│──► Humidificador 12V  ║
║  │    ─────── ◄─┤    CH2 ──────────────────►│──► Extractor FAE 12V  ║
║  │    SHT31     │    CH3 ──────────────────►└──► Calefactor 110V AC ║
║  │    BH1750    │    CH4 ──────────────────────► LED Strip 12V      ║
║  │    MH-Z19B   │                                                    ║
║  │    DS18B20   │    WiFi ─────────────────────► Router → RPi MQTT  ║
║  │              │                                                    ║
║  └──────────────┘                                                    ║
╚══════════════════════════════════════════════════════════════════════╝
```

---

## 2. Distribución de energía

```
TOMACORRIENTE 110V AC (con GFCI)
         │
         ├──► [Fusible 2A] ──► Fuente 5V/2A ──► ESP32 + sensores
         │
         ├──► [Fusible 5A] ──► Fuente 12V/3A ──┬──► Humidificador
         │                                      ├──► Extractor FAE
         │                                      └──► Tira LED
         │
         └──► [Fusible 2A] ──► RELÉ CH3 ──► Calefactor PTC 100W (110V AC)
                                             (el relé es el interruptor de línea AC)

NOTA DE SEGURIDAD:
  ┌────────────────────────────────────────────────────────────┐
  │ El calefactor es el único componente que trabaja con 110V  │
  │ AC directamente. Todo lo demás es DC (5V o 12V).          │
  │ El relé CH3 interrumpe la LÍNEA (cable negro/fase), nunca │
  │ el neutro.                                                 │
  └────────────────────────────────────────────────────────────┘
```

---

## 3. Esquema de pines ESP32 DevKit V1

```
                    ┌─────────────────┐
               3.3V ┤01             38├ GND
            ENABLE  ┤02             37├ TX0  
          SENSOR_VP ┤03             36├ RX0  
          SENSOR_VN ┤04             35├ GPIO22 (SCL) ──► SHT31 + BH1750
               IO34 ┤05             34├ GPIO21 (SDA) ──► SHT31 + BH1750
               IO35 ┤06             33├ GPIO19
               IO32 ┤07             32├ GPIO18
               IO33 ┤08             31├ GPIO05
               IO25 ┤09             30├ GPIO17 (TX2) ──► MH-Z19B RX
               IO26 ┤10  ESP32      29├ GPIO16 (RX2) ◄── MH-Z19B TX
                    ┤   DevKit V1   ├
               IO27 ┤11             28├ GPIO04 ──► DS18B20 DATA
               IO14 ┤12             27├ GND
               IO12 ┤13             26├ GPIO00
               GND  ┤14             25├ GPIO02
               IO13 ┤15             24├ GPIO15
               SD2  ┤16             23├ SD1
               SD3  ┤17             22├ CMD
               CMD  ┤18             21├ SD0
               CLK  ┤19             20├ CLK
                    └─────────────────┘

Pines usados:
  GPIO04  → DS18B20 (1-Wire sustrato)
  GPIO12  → Relé CH4 (LED)
  GPIO14  → Relé CH3 (calefactor)
  GPIO16  → MH-Z19B TX → RX2 ESP32  (entrada CO₂)
  GPIO17  → MH-Z19B RX ← TX2 ESP32  (salida CO₂)
  GPIO21  → SDA (SHT31 + BH1750)
  GPIO22  → SCL (SHT31 + BH1750)
  GPIO26  → Relé CH1 (humidificador)
  GPIO27  → Relé CH2 (extractor FAE)
```

---

## 4. Conexiones por componente

### 4.1 SHT31 — Temperatura y Humedad

```
SHT31          ESP32 DevKit
─────          ────────────
VCC   ─────►   3.3V
GND   ─────►   GND
SDA   ◄────►   GPIO21
SCL   ◄────►   GPIO22
ADDR  ─────►   GND  (dirección I2C = 0x44)

Notas:
  - Alimentar con 3.3V, NO con 5V (el chip opera a máx 3.6V)
  - ADDR a GND → dirección 0x44 (ADDR a VCC → 0x45, si se instala un segundo SHT31)
  - Cable máximo recomendado: 30 cm para I2C sin resistencias de pull-up adicionales
  - El DevKit ya tiene pull-ups internos en GPIO21/22
```

### 4.2 BH1750 — Sensor de luz

```
BH1750         ESP32 DevKit
──────         ────────────
VCC   ─────►   3.3V
GND   ─────►   GND
SDA   ◄────►   GPIO21         (compartido con SHT31)
SCL   ◄────►   GPIO22         (compartido con SHT31)
ADDR  ─────►   GND            (dirección I2C = 0x23)

Notas:
  - Comparte el bus I2C con el SHT31 — direcciones distintas (0x44 y 0x23)
  - ADDR a GND → 0x23 / ADDR a VCC → 0x5C
  - Montar orientado hacia arriba, no cubierto por elementos de la cápsula
```

### 4.3 MH-Z19B — Sensor de CO₂

```
MH-Z19B        ESP32 DevKit      Fuente 5V
───────        ────────────      ─────────
VCC (5V) ─────────────────────► 5V (fuente externa)
GND      ─────► GND             GND (común)
TX       ─────► GPIO16 (RX2)
RX       ◄───── GPIO17 (TX2)

Notas:
  - REQUIERE 5V — NO conectar al pin 3.3V del ESP32 (consume 150 mA en pico)
  - GND debe ser común entre el ESP32 y la fuente de 5V
  - Tiempo de estabilización: 3 minutos desde encendido antes de lecturas confiables
  - Calibración automática (ABC): desactivar en firmware si la cápsula permanece cerrada
    (el ABC asume que el CO₂ mínimo diario = 400 ppm, lo que NO aplica dentro de la cápsula)
  - Montar en posición horizontal, ventana de medición libre de condensación
```

### 4.4 DS18B20 — Temperatura de sustrato

```
DS18B20 (impermeable)    ESP32 DevKit
─────────────────        ────────────
Rojo   (VCC)  ─────►    3.3V
Negro  (GND)  ─────►    GND
Amarillo (DATA)──┬──►   GPIO04
                 │
              [4.7 kΩ]
                 │
              3.3V   ← pull-up obligatorio

Notas:
  - La resistencia de 4.7 kΩ entre DATA y 3.3V es OBLIGATORIA — sin ella no funciona
  - Cable puede extenderse hasta 3 m sin degradación
  - Enterrar la sonda 3–5 cm dentro del bloque de sustrato para medir temperatura interna
  - Dirección del sensor se lee automáticamente (protocolo 1-Wire)
```

### 4.5 Módulo relé 4 canales

```
Módulo Relé     ESP32 DevKit     Actuadores
───────────     ────────────     ──────────
VCC   ──────►   5V (de fuente externa)
GND   ──────►   GND (común)
IN1   ◄──────   GPIO26           CH1 → Humidificador 12V
IN2   ◄──────   GPIO27           CH2 → Extractor FAE 12V
IN3   ◄──────   GPIO14           CH3 → Calefactor 110V AC
IN4   ◄──────   GPIO12           CH4 → Tira LED 12V

Lógica de los relés:
  IN = LOW (0V)  → Relé ACTIVA  → actuador ENCENDIDO
  IN = HIGH (3.3V) → Relé DESACTIVA → actuador APAGADO
  (lógica invertida — típica de módulos con opto-aislador)
  ⚠ Ajustar en firmware: pinMode(PIN, OUTPUT); digitalWrite(PIN, HIGH) = apagado inicial

Notas:
  - Usar módulo con JD-VCC separado del VCC de control:
      JD-VCC ──► 5V (fuente externa para bobinas del relé)
      VCC ──────► 3.3V (señal de control del ESP32)
      Puente JD-VCC/VCC REMOVIDO
    → Esto protege el ESP32 de picos de la bobina del relé
```

---

## 5. Actuadores — conexiones de salida

### 5.1 Humidificador ultrasónico 12V

```
Fuente 12V (+) ──► RELÉ CH1 COM ──► RELÉ CH1 NO ──► Humidificador (+)
Fuente 12V (−) ──────────────────────────────────►  Humidificador (−)

NO = Normally Open (circuito abierto cuando relé inactivo)
```

### 5.2 Extractor FAE 12V

```
Fuente 12V (+) ──► RELÉ CH2 COM ──► RELÉ CH2 NO ──► Extractor (+)
Fuente 12V (−) ──────────────────────────────────►  Extractor (−)
```

### 5.3 Calefactor PTC 110V AC ⚠ ALTA TENSIÓN

```
110V AC (L/fase)  ──► [Fusible 2A] ──► RELÉ CH3 COM ──► RELÉ CH3 NO ──► Calefactor (L)
110V AC (N/neutro)────────────────────────────────────────────────────► Calefactor (N)
Tierra/PE ────────────────────────────────────────────────────────────► Chasis calefactor

IMPORTANTE:
  ┌────────────────────────────────────────────────────────────┐
  │  El relé interrumpe la FASE (L), nunca el neutro (N).     │
  │  El chasis del calefactor DEBE conectarse a tierra.        │
  │  Usar cable 3×16 AWG mínimo (temperatura resistente).      │
  │  Distancia mínima entre cableado AC y DC: 5 cm.           │
  │  Cubrir terminales AC con cinta autofundente.              │
  └────────────────────────────────────────────────────────────┘
```

### 5.4 Tira LED 12V

```
Fuente 12V (+) ──► RELÉ CH4 COM ──► RELÉ CH4 NO ──► LED Strip (+)
Fuente 12V (−) ──────────────────────────────────►  LED Strip (−)

Nota: si la tira LED consume > 2A (>24W en 1 m de tira 5050), 
      interponer un MOSFET IRLZ44N entre el relé y la tira.
```

---

## 6. Diagrama de cableado interno de la caja de control

```
┌─────────────────────────────────────────────────────────┐
│               CAJA ESTANCA IP65 (150×100×70 mm)         │
│                                                         │
│  ┌──────────┐    ┌──────────┐    ┌──────────────────┐   │
│  │ ESP32    │    │ MÓDULO   │    │ BORNES DE SALIDA │   │
│  │ DevKit   ├───►│ RELÉ 4ch ├───►│ CH1 Humidif.    │   │
│  │          │    │          │    │ CH2 Extractor    │   │
│  │ ◄──────  │    │          │    │ CH3 Calefactor   │   │
│  │ Sensores │    └──────────┘    │ CH4 LED          │   │
│  └──────────┘                    └──────────────────┘   │
│                                                         │
│  ┌────────────────────────────────────────────────────┐  │
│  │  DISTRIBUCIÓN DE ENERGÍA                           │  │
│  │  ○ Fuente 5V/2A   → ESP32 + relé (VCC control)    │  │
│  │  ○ Fuente 12V/3A  → Actuadores 12V                 │  │
│  │  ○ Línea AC 110V  → Calefactor (via relé CH3)      │  │
│  └────────────────────────────────────────────────────┘  │
│                                                         │
│  ENTRADAS (prensaestopas PG9):                          │
│  [PG1] Cable sensores SHT31+BH1750 (I2C)               │
│  [PG2] Cable sensor MH-Z19B (UART + 5V)                │
│  [PG3] Cable DS18B20 (1-Wire)                          │
│  [PG4] Cable alimentación 110V AC                      │
│                                                         │
│  SALIDAS (borneras):                                    │
│  [B1] Humidificador 12V                                 │
│  [B2] Extractor FAE 12V                                 │
│  [B3] Calefactor 110V AC                                │
│  [B4] Tira LED 12V                                      │
└─────────────────────────────────────────────────────────┘
```

---

## 7. Tabla resumen de conexiones

| Componente | Pin/Terminal | Conecta a | Voltaje | Corriente |
|-----------|-------------|-----------|---------|-----------|
| SHT31 VCC | VCC | 3.3V ESP32 | 3.3V | 1.5 mA |
| SHT31 GND | GND | GND común | — | — |
| SHT31 SDA | SDA | GPIO21 | 3.3V lógica | < 1 mA |
| SHT31 SCL | SCL | GPIO22 | 3.3V lógica | < 1 mA |
| BH1750 VCC | VCC | 3.3V ESP32 | 3.3V | 0.2 mA |
| BH1750 SDA | SDA | GPIO21 | 3.3V lógica | < 1 mA |
| BH1750 SCL | SCL | GPIO22 | 3.3V lógica | < 1 mA |
| MH-Z19B VCC | VCC | Fuente 5V | 5V | 150 mA pico |
| MH-Z19B TX | TX | GPIO16 (RX2) | 3.3V TTL | < 1 mA |
| MH-Z19B RX | RX | GPIO17 (TX2) | 3.3V TTL | < 1 mA |
| DS18B20 VCC | Rojo | 3.3V ESP32 | 3.3V | 4 mA |
| DS18B20 DATA | Amarillo | GPIO04 + 4.7kΩ a 3.3V | 3.3V | < 1 mA |
| Relé VCC | VCC | 3.3V ESP32 | 3.3V | — |
| Relé JD-VCC | JD-VCC | Fuente 5V | 5V | 360 mA (4 bobinas) |
| Relé IN1 | IN1 | GPIO26 | 3.3V | < 1 mA |
| Relé IN2 | IN2 | GPIO27 | 3.3V | < 1 mA |
| Relé IN3 | IN3 | GPIO14 | 3.3V | < 1 mA |
| Relé IN4 | IN4 | GPIO12 | 3.3V | < 1 mA |
| Humidificador | +/− | Relé CH1 → Fuente 12V | 12V | 500 mA |
| Extractor FAE | +/− | Relé CH2 → Fuente 12V | 12V | 200 mA |
| Calefactor | L/N/PE | Relé CH3 → 110V AC | 110V AC | 900 mA (100W) |
| Tira LED 1m | +/− | Relé CH4 → Fuente 12V | 12V | 1.5 A |

**Balance de corriente fuente 5V/2A:**
- ESP32: 240 mA (pico WiFi)
- MH-Z19B: 150 mA
- Relé JD-VCC: 360 mA
- Sensores I2C + 1-Wire: 10 mA
- **Total: 760 mA** ✅ (margen del 62 % sobre la fuente de 2A)

**Balance de corriente fuente 12V/3A:**
- Humidificador: 500 mA
- Extractor: 200 mA
- LED 1 m: 1.500 mA
- **Total: 2.200 mA** ✅ (margen del 26 % sobre la fuente de 3A)

---

## 8. Direcciones I2C y configuración serial

```
Bus I2C (GPIO21/22):
  0x44  →  SHT31  (ADDR a GND)
  0x23  →  BH1750 (ADDR a GND)

Puerto UART2 (GPIO16/17):
  Baud:  9600
  Bits:  8N1
  Uso:   MH-Z19B

Puerto 1-Wire (GPIO04):
  ROM:   detectada automáticamente al arrancar
  Uso:   DS18B20
```

---

## 9. Precauciones de instalación

### Cableado

- Separar físicamente el cableado de 110V AC del cableado DC (mínimo 5 cm o canal separado)
- Usar cable rojo para positivo DC, negro para negativo DC, verde para tierra
- Para 110V AC: cable blanco para neutro, negro para fase, verde/amarillo para tierra
- Cubrir todos los empalmes con cinta autofundente en las conexiones de 110V
- Usar borneras de tornillo en la caja — no empalmes volantes

### Montaje de la caja de control

- Montar la caja de control en el **exterior** de la nevera (no dentro de la cápsula)
- Pasar los cables de sensores a través de prensaestopas PG9 perforadas en la pared de la nevera
- Sellar con silicona alrededor de los prensaestopas una vez instalados

### Protecciones obligatorias

- [ ] Fusible 2A en la línea de 110V AC antes del relé CH3
- [ ] Protección GFCI (diferencial) en el tomacorriente de la cápsula
- [ ] El módulo relé debe tener JD-VCC separado del VCC de señal (ver sección 4.5)
- [ ] La fuente 5V y la fuente 12V deben compartir el GND (tierra común)
- [ ] El chasis de la nevera debe estar conectado a la tierra de la instalación

---

## 10. Lista de verificación antes del primer encendido

### Verificación de cableado (sin energía)

- [ ] Multímetro en modo continuidad: verificar que 110V AC NO tiene continuidad con ningún cable DC
- [ ] Continuidad del cable de tierra del calefactor hacia el chasis
- [ ] Resistencia de 4.7 kΩ instalada entre GPIO04 y 3.3V
- [ ] Puente JD-VCC/VCC del módulo relé REMOVIDO
- [ ] Todos los prensaestopas apretados y sellados con silicona

### Verificación con energía, sin actuadores conectados

- [ ] 3.3V presente en pin VCC del ESP32 (medir con multímetro)
- [ ] 5V presente en MH-Z19B VCC
- [ ] Monitor Serial del Arduino IDE muestra lecturas del SHT31
- [ ] Monitor Serial muestra lecturas del BH1750
- [ ] Monitor Serial muestra lecturas del MH-Z19B (esperar 3 min)
- [ ] Monitor Serial muestra temperatura del DS18B20

### Verificación de relés y actuadores (un canal a la vez)

- [ ] CH1: enviar comando → LED del relé se activa → humidificador enciende → apagar
- [ ] CH2: enviar comando → LED del relé se activa → extractor gira → apagar
- [ ] CH3: ⚠ con cuidado → calefactor calienta 5 seg → apagar → verificar que la nevera no acumula calor excesivo
- [ ] CH4: enviar comando → LED strip enciende → apagar

### Verificación de conectividad MQTT

- [ ] ESP32 se conecta a WiFi (IP asignada visible en Serial)
- [ ] ESP32 publica en `bichongos/capsula-01/sensors` cada 30 seg
- [ ] Datos visibles en Grafana o en el cliente MQTT de prueba (`mosquitto_sub -t "bichongos/#"`)

---

## 11. Plano de ubicación de sensores dentro de la nevera

```
VISTA FRONTAL — Interior de la nevera

  ┌──────────────────────────────────────┐
  │   TECHO                              │
  │   ┌─────────────────────────────┐    │
  │   │  BH1750 (luz) ───────────── │    │ ← Montar en techo, apuntando hacia abajo
  │   └─────────────────────────────┘    │
  │                                      │
  │   ┌──────────────┐                   │
  │   │  SHT31       │ ←── Centro de la  │
  │   │  (temp+HR)   │     cápsula,      │
  │   │              │     aprox 1/2 alt │
  │   └──────────────┘                   │
  │                                      │
  │   ┌──────────────┐                   │
  │   │  MH-Z19B     │ ←── Mismo nivel   │
  │   │  (CO₂)       │     que SHT31,    │
  │   │              │     horizontal    │
  │   └──────────────┘                   │
  │                                      │
  │   [Humidificador] [Extractor FAE]    │ ← Fondo de la nevera
  │   ══════════════════════════════     │ ← Rejilla / bandejas de cultivo
  │                                      │
  │   DS18B20 ←── enterrado en sustrato  │ ← Dentro de un bloque de muestra
  │                                      │
  │   [Calefactor PTC]                   │ ← Esquina inferior trasera
  │   [Tira LED]                         │ ← Lateral superior
  └──────────────────────────────────────┘
```

---

*Bichongos · docs/capsula/diagrama-electrico-capsula-mini.md · v1.0 · 2026-06-30*
