# BOM — Lista de Materiales con Precios en COP

> Precios de referencia para el mercado colombiano. Verificar antes de comprar — varían según proveedor, disponibilidad y tasa de cambio.
> **Referencia:** COP/USD ≈ $ 4.200 · **Fecha:** 2026-06-30

**Tarea:** F1-13 del BACKLOG.md

---

## Índice

1. [Nodo IoT por cápsula (ESP32)](#1-nodo-iot-por-cápsula-esp32)
2. [Cápsula Mini (nevera modificada)](#2-cápsula-mini-nevera-modificada)
3. [Cápsula Estándar (caja construida)](#3-cápsula-estándar-caja-construida)
4. [Cápsula Rack (producción)](#4-cápsula-rack-producción)
5. [Gateway — Raspberry Pi 4](#5-gateway--raspberry-pi-4)
6. [Equipamiento de laboratorio](#6-equipamiento-de-laboratorio)
7. [Consumibles por ciclo (100 kg sustrato)](#7-consumibles-por-ciclo-100-kg-sustrato)
8. [Resumen de inversión por fase](#8-resumen-de-inversión-por-fase)
9. [Proveedores recomendados](#9-proveedores-recomendados)

---

## 1. Nodo IoT por cápsula (ESP32)

> Un nodo completo para una cápsula: sensores + actuadores + control.

| # | Componente | Especificación | Cantidad | P. unitario (COP) | Total (COP) | Fuente |
|---|-----------|---------------|----------|-------------------|-------------|--------|
| 1 | ESP32 DevKit V1 | 38 pines, WiFi+BT | 1 | $ 22.000 | $ 22.000 | ML / Local |
| 2 | Sensor SHT31 | Temp + HR, I2C | 1 | $ 32.000 | $ 32.000 | ML / AliExpress |
| 3 | Sensor MH-Z19B | CO₂ NDIR, UART | 1 | $ 95.000 | $ 95.000 | AliExpress |
| 4 | Sensor BH1750 | Luz lux, I2C | 1 | $ 12.000 | $ 12.000 | ML / Local |
| 5 | Sensor DS18B20 | Temp sustrato, 1-Wire, impermeable | 1 | $ 14.000 | $ 14.000 | ML |
| 6 | Módulo relé 4 canales | 5V, opto-aislado | 1 | $ 16.000 | $ 16.000 | ML / Local |
| 7 | Fuente de poder | 5V 2A, conector USB-C | 1 | $ 18.000 | $ 18.000 | Local |
| 8 | Caja estanca IP65 | 150×100×70 mm | 1 | $ 28.000 | $ 28.000 | Ferrería / ML |
| 9 | Resistencia 4.7 kΩ | Para DS18B20 pull-up | 1 | $ 500 | $ 500 | Local |
| 10 | Cables Dupont M-M / M-H | 40 cm, surtido | 1 set | $ 8.000 | $ 8.000 | ML / Local |
| 11 | Borneras y conectores | Para actuadores | 1 set | $ 6.000 | $ 6.000 | Local |
| 12 | PCB universal 5×7 cm | Para soldadura final | 1 | $ 4.000 | $ 4.000 | ML |
| 13 | Cinta de doble faz + tuercas | Montaje interno | 1 | $ 3.000 | $ 3.000 | Ferrería |
| | | | | **Subtotal nodo** | **$ 258.500** | |

> **Nota AliExpress:** el MH-Z19B cuesta ~$ 25.000 COP importado directo vs. ~$ 95.000 en stock local. Si se compran 3+ unidades en AliExpress, el ahorro cubre el envío (15–30 días hábiles).

---

## 2. Cápsula Mini (nevera modificada)

> Cápsula de I+D para pruebas iniciales y especies de nivel 1–2.

### 2.1 Estructura

| # | Componente | Especificación | Cantidad | P. unitario (COP) | Total (COP) | Fuente |
|---|-----------|---------------|----------|-------------------|-------------|--------|
| 1 | Nevera usada 120–150 L | Buen sello, sin fuga de frío | 1 | $ 180.000 | $ 180.000 | Marketplace / Usados |
| 2 | Silicona estructural | Para sellar penetraciones de cables | 1 tubo | $ 12.000 | $ 12.000 | Ferrería |
| 3 | Prensaestopa PG9 | Entrada de cables estanca | 4 | $ 2.500 | $ 10.000 | Ferrería eléctrica |
| 4 | Bisagra de piano 30 cm | Refuerzo de puerta si es necesario | 1 | $ 8.000 | $ 8.000 | Ferrería |

### 2.2 Actuadores

| # | Componente | Especificación | Cantidad | P. unitario (COP) | Total (COP) | Fuente |
|---|-----------|---------------|----------|-------------------|-------------|--------|
| 5 | Humidificador ultrasónico | 2.4 MHz, 300 ml/h, 12V o 110V | 1 | $ 55.000 | $ 55.000 | ML |
| 6 | Extractor axial FAE | 80 mm, 12V, 30–50 CFM | 1 | $ 22.000 | $ 22.000 | ML / computadores |
| 7 | Calefactor PTC cerámico | 100W, 110V, con ventilador | 1 | $ 35.000 | $ 35.000 | ML |
| 8 | Tira LED 12V | 5050, blanco frío, 1 m | 1 | $ 18.000 | $ 18.000 | ML / eléctrica |
| 9 | Fuente 12V 3A | Para humidificador + extractor + LED | 1 | $ 28.000 | $ 28.000 | ML |
| 10 | Manguera silicona Ø6 mm | Conexión humidificador → cápsula | 50 cm | $ 3.000 | $ 3.000 | Ferrería |
| 11 | Filtro HEPA disco | Ventilación FAE de entrada | 2 | $ 8.000 | $ 16.000 | ML / naturista |

### 2.3 Nodo IoT (ver tabla 1)

| | Nodo IoT completo | | 1 | $ 258.500 | $ 258.500 | |

| | | | | **Total Cápsula Mini** | **$ 447.500** | |

---

## 3. Cápsula Estándar (caja construida)

> Cápsula de producción para especies nivel 2–3. Dimensiones: 60 × 60 × 120 cm.

### 3.1 Estructura

| # | Componente | Especificación | Cantidad | P. unitario (COP) | Total (COP) | Fuente |
|---|-----------|---------------|----------|-------------------|-------------|--------|
| 1 | Lámina melamina blanca 18 mm | 244 × 122 cm | 2 | $ 95.000 | $ 190.000 | Madecor / carpintería |
| 2 | Ángulo de aluminio 3/4" | Para esquinas, barra 3 m | 4 | $ 18.000 | $ 72.000 | Ferrería |
| 3 | Espuma de poliuretano 25 mm | Aislamiento, plancha 100×50 cm | 4 | $ 22.000 | $ 88.000 | Ferretería grande |
| 4 | Bisagra de piano 60 cm | Puerta | 2 | $ 14.000 | $ 28.000 | Ferrería |
| 5 | Manija con cierre magnético | Cierre hermético | 1 | $ 22.000 | $ 22.000 | Herrería |
| 6 | Silicona estructural blanca | Sellado de juntas | 2 tubos | $ 12.000 | $ 24.000 | Ferrería |
| 7 | Prensaestopa PG9 | Entradas de cable | 6 | $ 2.500 | $ 15.000 | Ferrería eléctrica |
| 8 | Pintura epóxica blanca | Acabado interior impermeable | 1 L | $ 45.000 | $ 45.000 | Pinturas |

### 3.2 Actuadores (mismos que Mini)

| | Humidificador + extractor + calefactor + LED + fuente 12V | | 1 set | $ 172.000 | $ 172.000 | Ver tabla 2 |

### 3.3 Nodo IoT

| | Nodo IoT completo | | 1 | $ 258.500 | $ 258.500 | |

| | | | | **Total Cápsula Estándar** | **$ 914.500** | |

---

## 4. Cápsula Rack (producción a escala)

> Para orellana y especies N1 en producción — bolsas colgantes sobre estantería con cortina PVC.

| # | Componente | Especificación | Cantidad | P. unitario (COP) | Total (COP) | Fuente |
|---|-----------|---------------|----------|-------------------|-------------|--------|
| 1 | Estantería metálica 180×90×45 cm | Carga ≥ 200 kg | 1 | $ 180.000 | $ 180.000 | Homecenter / ML |
| 2 | Cortina PVC transparente 0.5 mm | Para crear microclima | 4 m² | $ 18.000 | $ 72.000 | Plásticos / ferrería |
| 3 | Tubo PVC 3/4" | Marco superior para colgar bolsas | 3 m | $ 8.000 | $ 8.000 | Homecenter |
| 4 | Ganchos S de acero inox | Colgar bolsas | 20 | $ 1.500 | $ 30.000 | Ferrería |
| 5 | Humidificador ultrasónico 5L/h | Para volumen mayor | 1 | $ 95.000 | $ 95.000 | ML |
| 6 | Extractor 120 mm con speed control | FAE ajustable | 1 | $ 35.000 | $ 35.000 | ML |
| 7 | Tira LED 12V 3 m | Iluminación uniforme | 1 | $ 28.000 | $ 28.000 | ML |
| 8 | Fuente 12V 5A | Humidificador + LED + extractor | 1 | $ 42.000 | $ 42.000 | ML |
| 9 | Nodo IoT completo | | 1 | $ 258.500 | $ 258.500 | Ver tabla 1 |

| | | | | **Total Cápsula Rack** | **$ 748.500** | |

> Un rack de 180 cm puede alojar 60–80 bolsas de 1 kg de sustrato seco.

---

## 5. Gateway — Raspberry Pi 4

| # | Componente | Especificación | Cantidad | P. unitario (COP) | Total (COP) | Fuente |
|---|-----------|---------------|----------|-------------------|-------------|--------|
| 1 | Raspberry Pi 4 | 2 GB RAM mínimo | 1 | $ 320.000 | $ 320.000 | ML (importado) |
| 2 | SSD USB 3.0 | 64 GB, más confiable que SD | 1 | $ 65.000 | $ 65.000 | ML |
| 3 | MicroSD 32 GB clase 10 | Arranque inicial del SO | 1 | $ 28.000 | $ 28.000 | ML / papelería |
| 4 | Fuente USB-C 5V 3A oficial | Subvoltaje causa inestabilidad | 1 | $ 42.000 | $ 42.000 | ML |
| 5 | Case con ventilador activo | Temperatura máx 85 °C sin case | 1 | $ 35.000 | $ 35.000 | ML |
| 6 | Cable Ethernet Cat 5e 3 m | Conexión estable al router | 1 | $ 12.000 | $ 12.000 | Eléctrica / ML |
| 7 | UPS 600 VA | Protección ante cortes de energía | 1 | $ 245.000 | $ 245.000 | ML / Éxito / tecnología |
| 8 | Regleta con protección | 5 tomas, supresor de picos | 1 | $ 35.000 | $ 35.000 | Homecenter |

| | | | | **Total Gateway** | **$ 782.000** | |

> **Alternativa al RPi 4:** un mini-PC con Linux (Orange Pi 5, Radxa Rock) puede ser más económico y tener más disponibilidad local. Verificar precios actuales.

---

## 6. Equipamiento de laboratorio

### 6.1 Zona B — Preparación de sustrato

| # | Equipo | Especificación | Cantidad | P. unitario (COP) | Total (COP) | Fuente |
|---|--------|---------------|----------|-------------------|-------------|--------|
| 1 | Olla a presión 23 L | 15 PSI, para esterilización | 1 | $ 195.000 | $ 195.000 | Homecenter / ML |
| 2 | Olla grande 50 L | Para pasteurización | 1 | $ 85.000 | $ 85.000 | Plaza de mercado |
| 3 | Estufa industrial 2 fogones | Alta potencia (BTU) para autoclave | 1 | $ 145.000 | $ 145.000 | Homecenter |
| 4 | Báscula digital 10 kg | Pesar sustrato y cosechas | 1 | $ 45.000 | $ 45.000 | ML |
| 5 | Báscula de cocina 2 kg | Pesar inoculante con precisión | 1 | $ 22.000 | $ 22.000 | ML |
| 6 | Termómetro de cocina digital | Verificar temperatura de pasteurización | 1 | $ 18.000 | $ 18.000 | ML / supermercado |
| 7 | Manguera agua 1/2" | Para lavar y remojar sustrato | 5 m | $ 5.000 | $ 5.000 | Ferrería |
| 8 | Colador industrial 40 cm | Escurrir paja post-pasteurización | 1 | $ 28.000 | $ 28.000 | Plaza / implementos |

### 6.2 Zona D — Inoculación

| # | Equipo | Especificación | Cantidad | P. unitario (COP) | Total (COP) | Fuente |
|---|--------|---------------|----------|-------------------|-------------|--------|
| 9 | Cámara de flujo laminar DIY | Filtro HEPA H14 + ventilador | 1 | $ 350.000 | $ 350.000 | Construir (ver nota) |
| 10 | Lámpara UV germicida 15W | Para esterilizar zona D | 1 | $ 55.000 | $ 55.000 | ML |
| 11 | Encendedor de cocina | Para flambear herramientas | 1 | $ 8.000 | $ 8.000 | Supermercado |
| 12 | Cucharas de acero inox | Para inoculación | 3 | $ 5.000 | $ 15.000 | Supermercado |
| 13 | Jeringa 10 ml + agujas | Para cultivo líquido | 10 | $ 3.500 | $ 35.000 | Droguería / ML |
| 14 | Micropore 2,5 cm | Sellado de filtros en bolsas | 2 rollos | $ 12.000 | $ 24.000 | Droguería |
| 15 | Medidor de pH digital | Rango 0–14, calibrable | 1 | $ 42.000 | $ 42.000 | ML |
| 16 | Tiras de pH (respaldo) | Rango 4–9 | 1 caja x 100 | $ 15.000 | $ 15.000 | Droguería / ML |

### 6.3 Zona C — Postcosecha y secado

| # | Equipo | Especificación | Cantidad | P. unitario (COP) | Total (COP) | Fuente |
|---|--------|---------------|----------|-------------------|-------------|--------|
| 17 | Deshidratador de alimentos | 5–10 bandejas, 35–70 °C, 500W | 1 | $ 220.000 | $ 220.000 | ML / Éxito |
| 18 | Termómetro datalogger | Para línea de base ambiental | 1 | $ 115.000 | $ 115.000 | ML |
| 19 | Medidor CO₂ portátil NDIR | Línea de base + verificación cápsulas | 1 | $ 220.000 | $ 220.000 | ML / AliExpress |
| 20 | Selladora de bolsas 30 cm | Para empaque al vacío | 1 | $ 65.000 | $ 65.000 | ML |
| 21 | Brocha suave 3 cm | Limpiar hongos en postcosecha | 3 | $ 4.000 | $ 12.000 | Papelería / ferrería |

> **Flujo laminar DIY:** filtro HEPA H14 (≈ $ 180.000) + ventilador 120 mm (≈ $ 35.000) + caja de madera (≈ $ 80.000) + tela de filtro previa (≈ $ 25.000) = ≈ $ 320.000–$ 380.000 total. Mucho más económico que una campana comercial (> $ 2.000.000).

**Subtotal laboratorio:** $ 1.369.000

---

## 7. Consumibles por ciclo (100 kg sustrato seco)

> Costo de insumos para procesar 100 kg de sustrato seco (≈ 100 bloques de 1 kg).

### 7.1 Sustrato

| # | Insumo | Cantidad | P. unitario (COP) | Total (COP) | Fuente |
|---|--------|----------|-------------------|-------------|--------|
| 1 | Paja de arroz o trigo | 100 kg | $ 800/kg | $ 80.000 | Finca / mercado campesino |
| 2 | Aserrín maderas duras (alternativa) | 80 kg | $ 600/kg | $ 48.000 | Aserradero local |
| 3 | Salvado de trigo | 15 kg | $ 1.800/kg | $ 27.000 | Plaza de mercado |
| 4 | Yeso agrícola | 5 kg | $ 1.200/kg | $ 6.000 | Agroveterinaria |
| 5 | Cal hidratada | 2 kg | $ 1.000/kg | $ 2.000 | Ferrería / agro |

### 7.2 Empaque e inoculación

| # | Insumo | Cantidad | P. unitario (COP) | Total (COP) | Fuente |
|---|--------|----------|-------------------|-------------|--------|
| 6 | Bolsas PP 0,003" 20×40 cm | 110 unidades | $ 380/u | $ 41.800 | ML / plásticos |
| 7 | Filtros de disco sintético | 110 unidades | $ 350/u | $ 38.500 | ML |
| 8 | Clip de metal | 110 unidades | $ 100/u | $ 11.000 | Papelería |
| 9 | Semilla de grano (orellana) | 15 kg | $ 35.000/kg | $ 525.000 | Proveedor cepas |
| 10 | Cinta indicadora autoclave | 1 rollo | $ 18.000 | $ 18.000 | ML / lab supply |

### 7.3 Limpieza y bioseguridad

| # | Insumo | Cantidad | P. unitario (COP) | Total (COP) | Fuente |
|---|--------|----------|-------------------|-------------|--------|
| 11 | Alcohol isopropílico 70 % | 2 L | $ 18.000/L | $ 36.000 | Droguería / ML |
| 12 | Guantes nitrilo (caja × 100) | 1 caja | $ 35.000 | $ 35.000 | ML / droguería |
| 13 | Mascarillas N95 (caja × 10) | 1 caja | $ 28.000 | $ 28.000 | ML / droguería |
| 14 | Micropore (rollo 2,5 cm) | 1 rollo | $ 12.000 | $ 12.000 | Droguería |

**Subtotal consumibles / 100 bloques:** $ 908.300

**Costo consumibles por bloque:** ≈ $ 9.100

> Con BE% 100 % (1 kg orellana fresca por bloque) y precio de $ 15.000/kg → margen bruto por bloque ≈ $ 5.900 (39 %). Ver `docs/kpis-criterios-exito.md`.

---

## 8. Resumen de inversión por fase

### Fase 0 — Pre-implementación (sin hardware, ya en curso)

| Ítem | Costo (COP) |
|------|------------|
| Termohigrómetro datalogger (línea de base) | $ 115.000 |
| Medidor CO₂ portátil (línea de base) | $ 220.000 |
| **Subtotal Fase 0** | **$ 335.000** |

---

### Fase 1 — Piloto (1 cápsula Mini + gateway + laboratorio básico)

| Ítem | Cantidad | Costo (COP) |
|------|----------|------------|
| Cápsula Mini completa (nodo + estructura + actuadores) | 1 | $ 447.500 |
| Gateway Raspberry Pi 4 | 1 | $ 782.000 |
| Equipamiento de laboratorio | 1 set | $ 1.369.000 |
| Consumibles primer ciclo (100 bloques orellana) | 1 ciclo | $ 908.300 |
| Imprevistos y transporte (10 %) | — | $ 350.680 |
| **Subtotal Fase 1** | | **$ 3.857.480** |

---

### Fase 2 — Escala nivel 1 (3 racks orellana + 1 cápsula estándar shiitake)

| Ítem | Cantidad | Costo (COP) |
|------|----------|------------|
| Cápsulas Rack (producción orellana) | 3 | $ 2.245.500 |
| Cápsula Estándar (shiitake) | 1 | $ 914.500 |
| Consumibles 3 ciclos simultáneos | 3 | $ 2.724.900 |
| Imprevistos (10 %) | — | $ 588.490 |
| **Subtotal Fase 2** | | **$ 6.473.390** |

---

### Resumen de inversión acumulada

| Fase | Inversión fase | Acumulado |
|------|--------------|----------|
| Fase 0 (medición base) | $ 335.000 | $ 335.000 |
| Fase 1 (piloto) | $ 3.857.480 | $ 4.192.480 |
| Fase 2 (escala N1) | $ 6.473.390 | $ 10.665.870 |

> **Punto de equilibrio estimado Fase 1:** con 1 rack de orellana (80 bloques/ciclo × 1 kg × $ 15.000) = $ 1.200.000 por ciclo. La inversión de Fase 1 se recupera en ≈ 4 ciclos (≈ 6 meses de producción continua).

---

## 9. Proveedores recomendados

### IoT y electrónica

| Proveedor | Ubicación | Qué comprar | Ventaja |
|-----------|----------|------------|---------|
| **MercadoLibre Colombia** | Nacional | ESP32, sensores, módulos | Envío rápido, garantía |
| **AliExpress** | China (importado) | MH-Z19B, SHT31, BH1750 en cantidad | 40–60 % más económico si se piden varios |
| **Micro-Ingeniería** | Medellín | Componentes electrónicos | Stock local, asesoría técnica |
| **Electronika** | Medellín (El Centro) | Componentes básicos, cables, conectores | Precio bajo, pago en efectivo |
| **Diotrón** | Bogotá / online | Módulos ESP32, sensores | Buena variedad |

### Hardware de laboratorio

| Proveedor | Qué comprar |
|-----------|------------|
| **Homecenter** | Estanterías, herramientas, impermeabilizantes |
| **Mercado de San Alejo / usados ML** | Nevera para cápsula Mini, ollas grandes |
| **Makro / Almacenes Éxito** | Ollas, básculas, deshidratador |
| **Agromédico / Agrosavia** | Balanzas de precisión, termómetros |

### Insumos de cultivo

| Proveedor | Ubicación | Qué comprar |
|-----------|----------|------------|
| **Aserraderos zona industrial Guarne/Marinilla** | Local | Aserrín de maderas duras |
| **Fincas arroceras Llanos** | Importado región | Paja de arroz (buscar proveedor Villavicencio o Tolima) |
| **Mercado campesino Guarne/El Carmen** | Local | Paja de trigo, salvado, cal |
| **Fungifarm Colombia** | Bogotá / online | Cepas certificadas, semilla de grano |
| **Setas Colombia** | Medellín / online | Cepas y semilla de grano regional |
| **Importadora de plásticos** | Medellín | Bolsas PP 0,003" por mayor |

### Piezas constructivas

| Proveedor | Qué comprar |
|-----------|------------|
| **Madecor / El Pino Maderas** | Melamina y madera para cápsulas |
| **Ferroplast / Ferplas** | Láminas PVC, cortinas, mangueras |
| **Cerrajería Centro Guarne** | Bisagras, manijas, ángulos aluminio |

---

## Notas de compra

**Qué comprar primero (Fase 0):**
1. Termohigrómetro datalogger — necesario antes de cualquier otra inversión
2. Medidor CO₂ — para la línea de base ambiental

**Qué pedir con anticipación (4–6 semanas antes de Fase 1):**
- MH-Z19B por AliExpress (15–30 días de envío)
- Raspberry Pi 4 (stock limitado en Colombia — buscar con tiempo)
- Filtro HEPA H14 para flujo laminar DIY

**Qué comprar local y en el momento:**
- Paja, aserrín, cal, salvado → frescos y por cantidad
- Guantes, alcohol, mascarillas → cada ciclo según consumo real
- Nevera usada → buscar en marketplace 1–2 semanas antes de construir

**Advertencia de precios:**
Los precios electrónicos varían ±20 % con la tasa de cambio. Verificar en MercadoLibre la semana de la compra. Para pedidos de AliExpress, confirmar que el envío a Colombia esté disponible para cada producto.

---

*Bichongos · docs/bom-precios-cop.md · v1.0 · 2026-06-30*
