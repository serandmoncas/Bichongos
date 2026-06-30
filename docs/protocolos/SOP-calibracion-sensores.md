# SOP — Calibración de Sensores IoT

> Protocolo de verificación y calibración de los sensores de cada cápsula antes del primer despliegue y periódicamente durante la operación.

**Versión:** 1.0 · **Fecha:** 2026-06-30
**Aplica a:** SHT31 (temp+humedad), MH-Z19B (CO₂), BH1750 (luz), DS18B20 (temp sustrato)

---

## 1. Cuándo calibrar

| Momento | Motivo |
|---------|--------|
| Antes del primer despliegue | Verificar que los sensores leen correctamente antes de confiar en el sistema |
| Si una alerta parece incorrecta | El sensor puede estar leyendo mal |
| Cada 6 meses en operación | Deriva natural de los sensores |
| Después de reemplazar un sensor | Verificar que el nuevo está dentro del rango esperado |
| Después de limpieza con químicos | Algunos sensores son sensibles a vapores |

---

## 2. Sensor SHT31 — Temperatura y Humedad

### 2.1 Materiales
- Termómetro de referencia calibrado (termómetro médico digital ≥ ±0.1°C, o termómetro de cocina de buena calidad)
- Higrómetro de referencia (psicrómetro o higrómetro digital de referencia)
- Vaso con agua y hielo (para punto de 0°C)
- Agua tibia (para punto de ~40°C)

### 2.2 Verificación de temperatura

**Punto 1 — Ambiente (~15-20°C, típico Guarne):**
1. Colocar el SHT31 y el termómetro de referencia en el mismo espacio por 10 minutos.
2. Leer ambos simultáneamente.
3. Diferencia aceptable: **≤ ±0.5°C**.

**Punto 2 — Frío (usando agua con hielo ~1-3°C):**
1. Sellar el ESP32+SHT31 en bolsa plástica impermeable.
2. Sumergir (sin mojar) en agua con hielo.
3. Esperar 5 minutos y comparar.
4. Este punto verifica el rango de fructificación de Enoki.

**Punto 3 — Calor moderado (~35°C):**
1. Colocar junto a foco de calor suave.
2. Verificar que el SHT31 llega al mismo valor que el termómetro de referencia.
3. Importante: **nunca superar 40°C — daña el sensor**.

### 2.3 Verificación de humedad

El SHT31 típicamente tiene ±2% HR de precisión de fábrica. Para verificar:

**Método sal saturada (punto de referencia 75% HR):**
1. En recipiente cerrado: colocar sal de mesa saturada en agua (solución sobresaturada con cristales visibles).
2. Esperar 12 horas a temperatura constante.
3. El interior se estabiliza a **75.3% HR a 25°C**.
4. Colocar el sensor en el recipiente (sin tocar la sal) y leer después de 30 min.
5. Tolerancia aceptable: **75% ± 3%**.

**Método sal de potasio (punto 86% HR):**
- Cloruro de potasio (KCl) saturado → 86% HR a 25°C.
- Útil para verificar el rango de fructificación de orellana (85-95%).

### 2.4 Registro

```
Fecha: ___________  Sensor ID: SHT31-___  Cápsula: ___________
Temperatura ambiente referencia: ___°C  SHT31 lee: ___°C  Diferencia: ___°C
Humedad referencia: ___%  SHT31 lee: ___%  Diferencia: ___%
Resultado: ☐ Aprobado  ☐ Rechazar (diferencia > tolerancia)
Firmado: ___________
```

---

## 3. Sensor MH-Z19B — CO₂

### ⚠️ Advertencia: calentamiento mínimo 3 minutos, recomendado 10 minutos antes de leer

### 3.1 Punto de referencia: aire exterior (≈400-420 ppm)

El CO₂ en el exterior es una referencia confiable y gratuita:

1. Llevar el ESP32 al exterior del invernadero, lejos de plantas y personas.
2. Esperar 10 minutos de calentamiento.
3. El sensor debe leer entre **400 y 450 ppm**.
4. Si lee fuera de este rango, el sensor necesita calibración de punto cero.

### 3.2 Calibración de punto cero (Zero Calibration)

Solo si la lectura exterior está fuera de 400-450 ppm:

**Método automático (recomendado para uso normal):**
```cpp
// En firmware: deshabilitar la autocal durante el cultivo
mhz19.autoCalibration(false);
// Habilitar SOLO para calibración inicial en exterior
mhz19.autoCalibration(true);
// Dejar 20 minutos en exterior, luego volver a false
```

**Método manual (pin HD):**
1. Llevar el sensor al exterior.
2. Conectar el pin HD a GND por exactamente 7 segundos.
3. Soltar. El sensor se reinicia al punto de 400 ppm.
4. Esperar 3 minutos antes de tomar lecturas.

### 3.3 Verificación con referencia conocida (avanzado)

Si se dispone de un analizador de CO₂ certificado o una segunda unidad MH-Z19B:

| Ambiente | CO₂ esperado | Tolerancia |
|---------|-------------|-----------|
| Exterior abierto | 400–420 ppm | ±50 ppm |
| Interior invernadero sin cápsulas | 500–800 ppm | ±100 ppm |
| Dentro de cápsula fructificación | 600–1200 ppm | ±150 ppm |
| Dentro de cápsula incubación | 1500–3000 ppm | ±200 ppm |

### 3.4 Precauciones MH-Z19B

- **Nunca alimentar con 3.3V** — requiere **5V** en VCC. El nivel lógico TX/RX sí es 3.3V-compatible.
- No exponer a humedad superior al 95% por periodos prolongados.
- No limpiar con solventes.
- Vida útil estimada: 5 años si no se expone a concentraciones > 5000 ppm.
- Tiempo de calentamiento: 3 min mínimo, 10 min para lecturas confiables, **24 horas para la primera puesta en marcha**.

### 3.5 Registro

```
Fecha: ___________  Sensor: MH-Z19B-___  Cápsula: ___________
Lectura exterior (10 min calentamiento): ___ ppm
Referencia esperada: 400-450 ppm
¿Calibración de cero necesaria? ☐ No  ☐ Sí (método: _________)
Lectura post-calibración: ___ ppm
Resultado: ☐ Aprobado  ☐ Rechazado
Firmado: ___________
```

---

## 4. Sensor BH1750 — Luz

### 4.1 Verificación básica

El BH1750 tiene buena precisión de fábrica (±20%). Para verificar:

**Oscuridad total (0 lux):**
1. Cubrir el sensor completamente con cinta negra.
2. Debe leer **0-5 lux** (no exactamente cero por ruido electrónico).
3. Si lee > 20 lux con cubierta: sensor defectuoso.

**Luz ambiente (referencia subjetiva):**
- Habitación iluminada normal: 200–500 lux
- Bajo tira LED de cultivo a 10 cm: 1000–3000 lux
- Luz solar directa exterior: 30000–100000 lux

**Para cultivo, lo importante es la consistencia entre cápsulas**, no la calibración absoluta. Si dos cápsulas con el mismo LED leen valores similares (±20%), está bien.

### 4.2 Dirección I2C

El BH1750 puede estar en dirección `0x23` (pin ADDR a GND o flotante) o `0x57` (pin ADDR a VCC). Verificar con I2C scanner si hay conflictos:

```cpp
// Sketch de I2C scanner para verificar
#include <Wire.h>
void setup() {
  Wire.begin(21, 22);
  Serial.begin(115200);
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0)
      Serial.printf("Dispositivo I2C en 0x%02X\n", addr);
  }
}
void loop() {}
```

Salida esperada con SHT31 + BH1750:
```
Dispositivo I2C en 0x23  ← BH1750
Dispositivo I2C en 0x44  ← SHT31
```

---

## 5. Sensor DS18B20 — Temperatura de Sustrato

### 5.1 Verificación

**Punto de referencia agua con hielo (0°C):**
1. Preparar mezcla de agua e hielo picado en vaso.
2. Sumergir la sonda DS18B20 (no el conector).
3. Esperar 3 minutos.
4. Debe leer **0°C ± 0.5°C**.

**Punto de referencia agua tibia (~40°C):**
1. Agua caliente + termómetro de referencia.
2. Ajustar hasta estabilizar en 40°C.
3. DS18B20 debe leer **40°C ± 0.5°C**.

### 5.2 Verificar pull-up

El DS18B20 **requiere resistencia pull-up de 4.7 kΩ entre DQ y VCC (3.3V)**. Sin ella, el sensor no responde o da lecturas -127°C. Verificar:

```
Lectura -127°C → pull-up ausente o defectuoso
Lectura 85°C → error de conversión (parasite power issue)
Lectura 0°C fija → CRC error (cable demasiado largo o sin pull-up)
```

### 5.3 Múltiples sensores en el mismo bus

El 1-Wire soporta varios DS18B20 en paralelo. Para identificar cuál es cuál:
1. Conectar los sensores de uno en uno.
2. Leer la dirección única de 64-bit con `ds18b20.getAddress()`.
3. Anotar la dirección de cada sensor y su posición física.

---

## 6. Checklist de puesta en marcha — primera cápsula

Completar este checklist **antes** de colocar el primer lote de bloques:

```
☐ SHT31: temperatura dentro de ±0.5°C del termómetro de referencia
☐ SHT31: humedad dentro de ±3% usando sal saturada o higrómetro de ref.
☐ MH-Z19B: 24 horas de calentamiento completadas
☐ MH-Z19B: lectura exterior entre 400-450 ppm
☐ BH1750: lee 0-5 lux en oscuridad total
☐ BH1750: I2C scanner detecta dispositivo en 0x23
☐ DS18B20: lectura 0°C ± 0.5°C en agua con hielo
☐ Todos los sensores aparecen en el monitor serial sin errores
☐ Primera publicación MQTT recibida correctamente en Node-RED
☐ Grafana muestra los datos en tiempo real
☐ Alerta de prueba enviada a Telegram (publicar manualmente en topic /alert)
```

---

## 7. Frecuencia de recalibración en operación

| Sensor | Frecuencia | Método |
|--------|-----------|--------|
| SHT31 temperatura | Cada 6 meses | Comparar con termómetro de referencia |
| SHT31 humedad | Cada 3 meses | Sal saturada NaCl (75% HR) |
| MH-Z19B | Cada 6 meses | Punto cero en exterior |
| BH1750 | Anual | Verificación de 0 lux en oscuridad |
| DS18B20 | Cada 6 meses | Agua con hielo (0°C) |

---

*Bichongos · docs/protocolos/SOP-calibracion-sensores.md · v1.0 · 2026-06-30*
