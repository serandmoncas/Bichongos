# Modelo Financiero — Bichongos

> Proyecciones a 5 años para el sistema de cápsulas de cultivo IoT en Guarne, Antioquia.
> Moneda: COP (pesos colombianos). Todos los valores son nominales sin ajuste inflacionario.

**Versión:** 1.0 · **Fecha:** 2026-06-30

> ⚠️ **Este modelo es una proyección basada en supuestos técnicos y precios de referencia. Validar con datos reales del primer lote antes de tomar decisiones de inversión.**

---

## Índice

1. [Supuestos del modelo](#1-supuestos-del-modelo)
2. [Plan de producción — primeros 24 meses](#2-plan-de-producción--primeros-24-meses)
3. [Proyección de ingresos a 5 años](#3-proyección-de-ingresos-a-5-años)
4. [Estructura de costos](#4-estructura-de-costos)
5. [Estado de Resultados (P&L)](#5-estado-de-resultados-pl)
6. [Flujo de caja](#6-flujo-de-caja)
7. [Punto de equilibrio](#7-punto-de-equilibrio)
8. [Indicadores financieros clave](#8-indicadores-financieros-clave)
9. [Escenarios](#9-escenarios)
10. [Hoja de ruta de reinversión](#10-hoja-de-ruta-de-reinversión)

---

## 1. Supuestos del modelo

### 1.1 Producción

| Supuesto | Valor | Justificación |
|---------|-------|--------------|
| Ciclo orellana (incubación + fructificación + descanso) | 45 días | 18 días incubación + 20 días fructificación + 7 días descanso |
| Ciclos por rack por año | 8 | 365 / 45 = 8.1 → conservador en 8 |
| BE% orellana (escenario base) | 100 % | Rango reportado 80–150 %; promedio principiante conservador |
| Producción por rack por ciclo | 80 kg frescos | 80 bolsas × 1 kg sustrato × BE% 100 % |
| Producción por rack por año | 640 kg | 8 ciclos × 80 kg |
| Promedio mensual por rack | 53 kg | 640 / 12 |
| Tasa de contaminación asumida | 5 % | Pérdida aplicada desde mes 1 |
| Producción neta por rack/año | 608 kg | 640 × (1 - 5 %) |
| Ciclo melena de león | 37 días | 20 incubación + 10 fructificación + 7 descanso |
| Ciclos melena por cápsula/año | 8 | — |
| Producción neta melena/año | 68 kg | 15 bloques × 60 % BE × 8 ciclos × (1 - 5 %) |
| Ciclo reishi | 97 días | 60 incubación + 30 fructificación + 7 descanso |
| Ciclos reishi/año | 3 | — |
| Producción reishi seco/año | 14.25 kg | 5 kg/ciclo × 3 ciclos × (1 - 5 %) |
| Ciclo cordyceps | 67 días | 45 incubación + 15 fructificación + 7 descanso |
| Ciclos cordyceps/año | 5 | — |
| Producción cordyceps seco/año | 9.5 kg | 2 kg/ciclo × 5 ciclos × (1 - 5 %) |

### 1.2 Precios de venta

| Producto | Canal | Precio COP/kg | Mix de canales asumido |
|---------|-------|--------------|----------------------|
| Orellana fresca | Plaza / directo | $ 14.000 | 40 % |
| Orellana fresca | Restaurante | $ 20.000 | 60 % |
| **Orellana — precio promedio ponderado** | | **$ 17.600** | |
| Melena de León fresca | Restaurante premium | $ 65.000 | 80 % |
| Melena de León fresca | Tienda naturista | $ 50.000 | 20 % |
| **Melena — precio promedio ponderado** | | **$ 62.000** | |
| Reishi seco | Tienda naturista | $ 100.000 | 100 % |
| Cordyceps seco | Tienda naturista / online | $ 200.000 | 100 % |
| Extracto doble (reishi/cordyceps) | Premium | $ 350.000/kg eq. | Desde año 3 |
| Suplementos en polvo | Online / naturista | $ 280.000/kg eq. | Desde año 4 |

> Precios validados con referencia BOM (`docs/bom-precios-cop.md`). **Verificar con cotizaciones reales (tarea COM-02).**

### 1.3 Costos variables por ciclo

| Insumo | Con spawn comprado (meses 1–7) | Con spawn propio (mes 8+) |
|--------|-------------------------------|--------------------------|
| Paja / sustrato | $ 64.000 | $ 64.000 |
| Semilla de grano (12 kg) | $ 420.000 | $ 80.000 (producción propia) |
| Salvado de trigo | $ 21.600 | $ 21.600 |
| Bolsas PP + filtros + clips | $ 53.000 | $ 53.000 |
| **Total por ciclo (80 bolsas)** | **$ 558.600** | **$ 218.600** |
| **Costo por kg producido** | **$ 6.983** | **$ 2.733** |

### 1.4 Costos fijos mensuales

| Costo | Fase 1 (mes 1–6) | Fase 2 (mes 7–18) | Fase 3 (mes 19+) |
|-------|-----------------|------------------|-----------------|
| Energía eléctrica | $ 120.000 | $ 200.000 | $ 350.000 |
| Internet + datos | $ 80.000 | $ 80.000 | $ 80.000 |
| Limpieza y bioseguridad | $ 80.000 | $ 80.000 | $ 100.000 |
| Salario dueño (retiro) | $ 0 | $ 800.000 | $ 1.500.000 |
| Ayudante part-time | $ 0 | $ 600.000 | $ 900.000 |
| Mantenimiento IoT | $ 50.000 | $ 80.000 | $ 120.000 |
| Servicios digitales | $ 30.000 | $ 50.000 | $ 80.000 |
| **Total mensual** | **$ 360.000** | **$ 1.890.000** | **$ 3.130.000** |
| **Total anual** | **$ 2.160.000** | **$ 22.680.000** | **$ 37.560.000** |

### 1.5 Inversiones por fase

| Fase | Mes de inversión | Monto COP | Detalle |
|------|-----------------|-----------|---------|
| Fase 0 — Medición base | Mes 0 | $ 335.000 | Termohigrómetro + medidor CO₂ |
| Fase 1 — Piloto | Mes 1 | $ 3.857.480 | 1 rack + gateway RPi + laboratorio |
| Fase 2 — Escala N1 | Mes 7 | $ 6.473.390 | 3 racks adicionales + 1 cápsula estándar |
| Fase 3 — Funcionales | Mes 19 | $ 8.500.000 | 2 cápsulas funcionales + equipo extractos |
| Fase 4 — Segunda sede | Mes 37 | $ 25.000.000 | Replicación completa del sistema |
| **Total inversión acumulada año 5** | | **$ 44.165.870** | |

### 1.6 Depreciación (línea recta, 5 años)

| Inversión | Monto | Dep. anual |
|-----------|-------|-----------|
| Fase 1 | $ 3.857.480 | $ 771.496 |
| Fase 2 | $ 6.473.390 | $ 1.294.678 |
| Fase 3 | $ 8.500.000 | $ 1.700.000 |
| Fase 4 | $ 25.000.000 | $ 5.000.000 |

---

## 2. Plan de producción — primeros 24 meses

> La producción de orellana es cíclica (1 cosecha cada 45 días por rack). La tabla muestra el **promedio mensual** para facilitar la lectura. Las cosechas reales ocurren cada 6–7 semanas por rack.

| Mes | Racks activos | Cápsulas activas | kg orellana | kg melena | Ingresos orellana | Ingresos melena | **Total mes** |
|-----|:------------:|:---------------:|:-----------:|:---------:|:-----------------:|:---------------:|:-------------:|
| 1 | 1 | 0 | 0 | 0 | $ 0 | $ 0 | **$ 0** |
| 2 | 1 | 0 | 53 | 0 | $ 933.600 | $ 0 | **$ 933.600** |
| 3 | 1 | 0 | 53 | 0 | $ 933.600 | $ 0 | **$ 933.600** |
| 4 | 1 | 0 | 53 | 0 | $ 933.600 | $ 0 | **$ 933.600** |
| 5 | 1 | 0 | 53 | 0 | $ 933.600 | $ 0 | **$ 933.600** |
| 6 | 1 | 0 | 53 | 0 | $ 933.600 | $ 0 | **$ 933.600** |
| **Subtotal H1** | | | **265** | **0** | **$ 4.668.000** | **$ 0** | **$ 4.668.000** |
| 7 | 4 | 0 | 53 | 0 | $ 933.600 | $ 0 | **$ 933.600** |
| 8 | 4 | 1 | 200 | 6 | $ 3.520.000 | $ 372.000 | **$ 3.892.000** |
| 9 | 4 | 1 | 200 | 6 | $ 3.520.000 | $ 372.000 | **$ 3.892.000** |
| 10 | 4 | 1 | 200 | 6 | $ 3.520.000 | $ 372.000 | **$ 3.892.000** |
| 11 | 4 | 1 | 200 | 6 | $ 3.520.000 | $ 372.000 | **$ 3.892.000** |
| 12 | 4 | 1 | 200 | 6 | $ 3.520.000 | $ 372.000 | **$ 3.892.000** |
| **Subtotal H2** | | | **1.053** | **30** | **$ 18.533.600** | **$ 1.860.000** | **$ 20.393.600** |
| **Total Año 1** | | | **1.318** | **30** | **$ 23.201.600** | **$ 1.860.000** | **$ 25.061.600** |

| Mes | Racks activos | kg orellana | kg melena | kg reishi | kg cordyceps | **Total mes** |
|-----|:------------:|:-----------:|:---------:|:---------:|:------------:|:-------------:|
| 13 | 4 | 213 | 6 | 0 | 0 | **$ 4.122.800** |
| 14 | 4 | 213 | 6 | 0 | 0 | **$ 4.122.800** |
| 15 | 4 | 213 | 6 | 0 | 0 | **$ 4.122.800** |
| 16 | 4 | 213 | 6 | 0 | 0 | **$ 4.122.800** |
| 17 | 4 | 213 | 6 | 0 | 0 | **$ 4.122.800** |
| 18 | 4 | 213 | 6 | 0 | 0 | **$ 4.122.800** |
| **Subtotal H3 (Año 2 - 1er sem)** | | **1.278** | **36** | **0** | **0** | **$ 24.736.800** |
| 19 | 4 | 213 | 6 | 1.2 | 0.8 | **$ 4.682.800** |
| 20 | 4 | 213 | 6 | 1.2 | 0.8 | **$ 4.682.800** |
| 21 | 4 | 213 | 6 | 1.2 | 0.8 | **$ 4.682.800** |
| 22 | 4 | 213 | 6 | 1.2 | 0.8 | **$ 4.682.800** |
| 23 | 4 | 213 | 6 | 1.2 | 0.8 | **$ 4.682.800** |
| 24 | 4 | 213 | 6 | 1.2 | 0.8 | **$ 4.682.800** |
| **Subtotal H4 (Año 2 - 2do sem)** | | **1.278** | **36** | **7.2** | **4.8** | **$ 28.096.800** |
| **Total Año 2** | | **2.556** | **72** | **7.2** | **4.8** | **$ 52.833.600** |

> **Notas:**
> - Mes 1: sin ingresos — rack en proceso de construcción e inoculación
> - Mes 7: 3 racks adicionales instalados, primer ciclo en incubación, sin cosecha aún
> - Mes 8: spawn propio disponible (costo variable cae 61 %); primeros 4 racks produciendo
> - Mes 19: inician cápsulas funcionales (reishi + cordyceps) con Inversión Fase 3

---

## 3. Proyección de ingresos a 5 años

### 3.1 Producción anual por línea

| Línea de producto | Año 1 | Año 2 | Año 3 | Año 4 | Año 5 |
|------------------|:-----:|:-----:|:-----:|:-----:|:-----:|
| Orellana (kg) | 1.318 | 2.556 | 2.556 | 5.120 | 7.680 |
| Melena de León (kg) | 30 | 72 | 72 | 144 | 216 |
| Reishi seco (kg) | 0 | 7 | 14 | 28 | 42 |
| Cordyceps seco (kg) | 0 | 5 | 10 | 19 | 28 |
| Extractos (kg eq.) | 0 | 0 | 20 | 50 | 100 |
| Suplementos polvo (kg eq.) | 0 | 0 | 0 | 30 | 80 |
| Kits cultivo hogar (u) | 0 | 0 | 20 | 50 | 100 |

### 3.2 Ingresos anuales por línea (COP)

| Línea de producto | Precio/kg | Año 1 | Año 2 | Año 3 | Año 4 | Año 5 |
|------------------|:---------:|------:|------:|------:|------:|------:|
| Orellana fresca | $ 17.600 | $ 23.201.600 | $ 44.985.600 | $ 44.985.600 | $ 90.112.000 | $ 135.168.000 |
| Melena de León | $ 62.000 | $ 1.860.000 | $ 4.464.000 | $ 4.464.000 | $ 8.928.000 | $ 13.392.000 |
| Reishi seco | $ 100.000 | $ 0 | $ 700.000 | $ 1.400.000 | $ 2.800.000 | $ 4.200.000 |
| Cordyceps seco | $ 200.000 | $ 0 | $ 1.000.000 | $ 2.000.000 | $ 3.800.000 | $ 5.600.000 |
| Extractos premium | $ 350.000 | $ 0 | $ 0 | $ 7.000.000 | $ 17.500.000 | $ 35.000.000 |
| Suplementos polvo | $ 280.000 | $ 0 | $ 0 | $ 0 | $ 8.400.000 | $ 22.400.000 |
| Kits cultivo hogar | $ 120.000/u | $ 0 | $ 0 | $ 2.400.000 | $ 6.000.000 | $ 12.000.000 |
| **TOTAL INGRESOS** | | **$ 25.061.600** | **$ 51.149.600** | **$ 62.249.600** | **$ 137.540.000** | **$ 227.760.000** |
| Crecimiento YoY | | — | +104 % | +22 % | +121 % | +66 % |
| **Ingresos acumulados** | | **$ 25.061.600** | **$ 76.211.200** | **$ 138.460.800** | **$ 276.000.800** | **$ 503.760.800** |

> El salto de Año 3 → Año 4 (+121%) corresponde a la inversión en segunda sede (Fase 4, mes 37) y consolidación de línea de extractos.

---

## 4. Estructura de costos

### 4.1 Costos variables anuales (COP)

| Costo variable | Año 1 | Año 2 | Año 3 | Año 4 | Año 5 |
|---------------|------:|------:|------:|------:|------:|
| Sustrato y paja | $ 1.024.000 | $ 1.843.200 | $ 1.843.200 | $ 3.686.400 | $ 5.529.600 |
| Semilla de grano | $ 2.016.000 | $ 576.000 | $ 576.000 | $ 1.152.000 | $ 1.728.000 |
| Suplementos sustrato | $ 518.400 | $ 933.120 | $ 933.120 | $ 1.866.240 | $ 2.799.360 |
| Empaque (bolsas, filtros) | $ 612.000 | $ 1.101.600 | $ 1.101.600 | $ 2.203.200 | $ 3.304.800 |
| Empaque postcosecha | $ 384.000 | $ 768.000 | $ 936.000 | $ 2.116.800 | $ 3.499.200 |
| Insumos funcionales (reishi, cordyceps) | $ 0 | $ 350.000 | $ 700.000 | $ 1.400.000 | $ 2.100.000 |
| Insumos extractos y cápsulas | $ 0 | $ 0 | $ 1.400.000 | $ 3.500.000 | $ 7.000.000 |
| **Total costos variables** | **$ 4.554.400** | **$ 5.571.920** | **$ 7.489.920** | **$ 15.924.640** | **$ 25.960.960** |

### 4.2 Costos fijos anuales (COP)

| Costo fijo | Año 1 | Año 2 | Año 3 | Año 4 | Año 5 |
|-----------|------:|------:|------:|------:|------:|
| Energía eléctrica | $ 1.920.000 | $ 2.400.000 | $ 4.200.000 | $ 6.000.000 | $ 8.400.000 |
| Internet y datos | $ 960.000 | $ 960.000 | $ 960.000 | $ 960.000 | $ 1.920.000 |
| Limpieza y bioseguridad | $ 960.000 | $ 1.200.000 | $ 1.200.000 | $ 2.400.000 | $ 3.600.000 |
| Salario dueño | $ 4.800.000 | $ 18.000.000 | $ 24.000.000 | $ 36.000.000 | $ 48.000.000 |
| Ayudante(s) part/full time | $ 3.600.000 | $ 10.800.000 | $ 14.400.000 | $ 28.800.000 | $ 43.200.000 |
| Mantenimiento IoT | $ 780.000 | $ 960.000 | $ 1.440.000 | $ 1.920.000 | $ 2.880.000 |
| Servicios digitales | $ 480.000 | $ 600.000 | $ 960.000 | $ 1.200.000 | $ 1.800.000 |
| Marketing y ventas | $ 300.000 | $ 1.200.000 | $ 2.400.000 | $ 4.800.000 | $ 7.200.000 |
| Contador / asesor | $ 600.000 | $ 1.200.000 | $ 1.800.000 | $ 2.400.000 | $ 3.600.000 |
| Seguros y otros | $ 0 | $ 600.000 | $ 600.000 | $ 1.200.000 | $ 2.400.000 |
| **Total costos fijos** | **$ 14.400.000** | **$ 37.920.000** | **$ 51.960.000** | **$ 85.680.000** | **$ 123.000.000** |

### 4.3 Depreciación anual (COP)

| Fase depreciada | Año 1 | Año 2 | Año 3 | Año 4 | Año 5 |
|----------------|------:|------:|------:|------:|------:|
| Fase 1 | $ 771.496 | $ 771.496 | $ 771.496 | $ 771.496 | $ 771.496 |
| Fase 2 | $ 647.339 | $ 1.294.678 | $ 1.294.678 | $ 1.294.678 | $ 1.294.678 |
| Fase 3 | $ 0 | $ 850.000 | $ 1.700.000 | $ 1.700.000 | $ 1.700.000 |
| Fase 4 | $ 0 | $ 0 | $ 0 | $ 2.500.000 | $ 5.000.000 |
| **Total depreciación** | **$ 1.418.835** | **$ 2.916.174** | **$ 3.766.174** | **$ 6.266.174** | **$ 8.766.174** |

---

## 5. Estado de Resultados (P&L)

*(Cifras en COP)*

| Concepto | Año 1 | Año 2 | Año 3 | Año 4 | Año 5 |
|---------|------:|------:|------:|------:|------:|
| **Ingresos totales** | **25.061.600** | **51.149.600** | **62.249.600** | **137.540.000** | **227.760.000** |
| Costo de ventas (variable) | (4.554.400) | (5.571.920) | (7.489.920) | (15.924.640) | (25.960.960) |
| **Utilidad bruta** | **20.507.200** | **45.577.680** | **54.759.680** | **121.615.360** | **201.799.040** |
| Margen bruto | 81,8 % | 89,1 % | 88,0 % | 88,4 % | 88,6 % |
| Gastos operacionales (fijos) | (14.400.000) | (37.920.000) | (51.960.000) | (85.680.000) | (123.000.000) |
| **EBITDA** | **6.107.200** | **7.657.680** | **2.799.680** | **35.935.360** | **78.799.040** |
| Margen EBITDA | 24,4 % | 15,0 % | 4,5 % | 26,1 % | 34,6 % |
| Depreciación | (1.418.835) | (2.916.174) | (3.766.174) | (6.266.174) | (8.766.174) |
| **EBIT** | **4.688.365** | **4.741.506** | **(966.494)** | **29.669.186** | **70.032.866** |
| Impuesto renta estimado (15 % efectivo) | (703.255) | (711.226) | 0 | (4.450.378) | (10.504.930) |
| **Utilidad neta** | **3.985.110** | **4.030.280** | **(966.494)** | **25.218.808** | **59.527.936** |
| Margen neto | 15,9 % | 7,9 % | −1,6 % | 18,3 % | 26,1 % |

> **Año 3 con pérdida neta:** la inversión de Fase 3 ($8.5M, mes 19) genera alta depreciación en el año. La operación sigue generando caja positiva (EBITDA $2.8M). Ajustar con préstamo o reinversión de utilidades acumuladas.

---

## 6. Flujo de caja

### 6.1 Flujo mensual — primeros 18 meses

*(Cifras en COP)*

| Mes | Saldo inicial | Ingresos | Inversión | Costos op. | Saldo final | Estado |
|-----|:------------:|--------:|--------:|----------:|:----------:|:------:|
| 0 | $ 10.000.000 | $ 0 | ($ 335.000) | $ 0 | **$ 9.665.000** | Capital semilla |
| 1 | $ 9.665.000 | $ 0 | ($ 3.857.480) | ($ 558.600) | **$ 5.248.920** | Inversión + 1er ciclo |
| 2 | $ 5.248.920 | $ 933.600 | $ 0 | ($ 360.000) | **$ 5.822.520** | ✅ 1er cosecha |
| 3 | $ 5.822.520 | $ 933.600 | $ 0 | ($ 360.000) | **$ 6.396.120** | |
| 4 | $ 6.396.120 | $ 933.600 | $ 0 | ($ 360.000) | **$ 6.969.720** | |
| 5 | $ 6.969.720 | $ 933.600 | $ 0 | ($ 360.000) | **$ 7.543.320** | |
| 6 | $ 7.543.320 | $ 933.600 | $ 0 | ($ 360.000) | **$ 8.116.920** | |
| 7 | $ 8.116.920 | $ 933.600 | ($ 6.473.390) | ($ 558.600) | **$ 2.018.530** | Inversión Fase 2 |
| 8 | $ 2.018.530 | $ 3.892.000 | $ 0 | ($ 1.890.000) | **$ 4.020.530** | ✅ 4 racks activos |
| 9 | $ 4.020.530 | $ 3.892.000 | $ 0 | ($ 1.890.000) | **$ 6.022.530** | |
| 10 | $ 6.022.530 | $ 3.892.000 | $ 0 | ($ 1.890.000) | **$ 8.024.530** | |
| 11 | $ 8.024.530 | $ 3.892.000 | $ 0 | ($ 1.890.000) | **$ 10.026.530** | |
| 12 | $ 10.026.530 | $ 3.892.000 | $ 0 | ($ 1.890.000) | **$ 12.028.530** | Capital recuperado |
| 13 | $ 12.028.530 | $ 4.122.800 | $ 0 | ($ 2.200.000) | **$ 13.951.330** | |
| 14 | $ 13.951.330 | $ 4.122.800 | $ 0 | ($ 2.200.000) | **$ 15.874.130** | |
| 15 | $ 15.874.130 | $ 4.122.800 | $ 0 | ($ 2.200.000) | **$ 17.796.930** | |
| 16 | $ 17.796.930 | $ 4.122.800 | $ 0 | ($ 2.200.000) | **$ 19.719.730** | |
| 17 | $ 19.719.730 | $ 4.122.800 | $ 0 | ($ 2.200.000) | **$ 21.642.530** | |
| 18 | $ 21.642.530 | $ 4.122.800 | $ 0 | ($ 2.200.000) | **$ 23.565.330** | |

> **Capital semilla recomendado:** $10.000.000 COP (~$2.380 USD) para cubrir inversiones de Fase 0 y 1 más el primer ciclo sin ingresos.

### 6.2 Flujo de caja anual

| Año | Saldo inicial | EBITDA | Inversión | Saldo final |
|-----|:------------:|-------:|----------:|:-----------:|
| Año 1 | $ 10.000.000 | $ 6.107.200 | ($ 10.665.870) | **$ 5.441.330** |
| Año 2 | $ 5.441.330 | $ 7.657.680 | ($ 8.500.000) | **$ 4.599.010** |
| Año 3 | $ 4.599.010 | $ 2.799.680 | $ 0 | **$ 7.398.690** |
| Año 4 | $ 7.398.690 | $ 35.935.360 | ($ 25.000.000) | **$ 18.334.050** |
| Año 5 | $ 18.334.050 | $ 78.799.040 | $ 0 | **$ 97.133.090** |

> La caja nunca cae a negativo gracias al capital semilla de $10M. Los momentos críticos son el mes 7 (inversión Fase 2: saldo mínimo $2M) y el mes 19 (inversión Fase 3: cubierta por utilidades acumuladas).

---

## 7. Punto de equilibrio

### 7.1 Break-even operacional mensual

Calculado para Fase 2 (mes 7+, 4 racks activos, spawn propio):

```
Costos fijos mensuales:          $ 1.890.000
Precio promedio orellana:        $ 17.600 / kg
Costo variable por kg:           $ 2.733 / kg
Margen de contribución por kg:   $ 14.867 / kg

Break-even en kg:
  $ 1.890.000 / $ 14.867 = 127 kg / mes

Break-even en ingresos:
  127 kg × $ 17.600 = $ 2.235.200 / mes
```

### 7.2 Capacidad instalada vs. break-even

| Período | Racks activos | Producción mensual | Break-even mensual | ¿Cubre? |
|---------|:------------:|:-----------------:|:-----------------:|:-------:|
| Mes 1–6 | 1 | 53 kg | 24 kg (costos Fase 1) | ✅ Desde mes 2 |
| Mes 7 | 1 (3 en setup) | 53 kg | 127 kg (costos Fase 2) | ❌ Déficit temporal |
| Mes 8–12 | 4 | 213 kg | 127 kg | ✅ Cubre con 67 % de capacidad |
| Año 2+ | 4 | 213 kg | 127 kg | ✅ Margen de seguridad 68 % |

### 7.3 Mes en que se alcanza el break-even

| Tipo de break-even | Mes |
|-------------------|:---:|
| Break-even operacional mensual (flujo positivo) | **Mes 2** (Fase 1) |
| Break-even post inversión Fase 2 (recuperar el mes de caída) | **Mes 8** |
| Break-even de inversión total acumulada | **Mes 22–24** |

---

## 8. Indicadores financieros clave

### 8.1 ROI por fase

| Inversión | Monto | Utilidad generada (en 5 años) | ROI |
|-----------|------:|------------------------------:|:---:|
| Fase 1 | $ 3.857.480 | $ 25.061.600 (Año 1 revenues) | 549 % |
| Fase 2 | $ 6.473.390 | $ 51.149.600 (Año 2 revenues) | 690 % |
| Fase 3 | $ 8.500.000 | $ 9.000.000 (extractos Año 3-5) | 6 % en Año 3, escala a 500%+ en Año 5 |
| Fase 4 | $ 25.000.000 | $ 165.000.000 (revenues adicionales Año 5) | 560 % |

> El ROI de Fase 1 parece alto porque los ingresos son brutos, no utilidades netas. El ROI sobre utilidad neta de Fase 1 es del orden del 100 % en el primer año completo.

### 8.2 Período de recuperación (Payback)

| Inversión | Payback |
|-----------|:-------:|
| Fase 1 ($3.857.480) | **5–6 meses** desde primera cosecha |
| Inversión total Fase 1 + 2 ($10.330.870) | **18–20 meses** |
| Inversión total acumulada Fase 1+2+3 ($18.830.870) | **26–30 meses** |

### 8.3 Margen bruto por producto

| Producto | Precio/kg | Costo variable/kg | Margen bruto |
|---------|:---------:|:-----------------:|:------------:|
| Orellana (spawn propio) | $ 17.600 | $ 2.733 | **84,5 %** |
| Orellana (spawn comprado) | $ 17.600 | $ 6.983 | **60,3 %** |
| Melena de León | $ 62.000 | $ 8.500 (est.) | **86,3 %** |
| Reishi seco | $ 100.000 | $ 12.000 (est.) | **88,0 %** |
| Cordyceps seco | $ 200.000 | $ 35.000 (est.) | **82,5 %** |
| Extracto doble | $ 350.000 | $ 80.000 (est.) | **77,1 %** |

### 8.4 Ingreso y costo por kg producido

| Métrica | Orellana Año 1 | Orellana Año 2+ |
|---------|:--------------:|:---------------:|
| Ingresos por kg | $ 17.600 | $ 17.600 |
| Costo variable por kg | $ 5.183 (mix spawn) | $ 2.733 (spawn propio) |
| Contribución por kg | $ 12.417 | $ 14.867 |
| Costos fijos asignados/kg | $ 10.927 | $ 7.426 (más kg diluyen fijos) |
| **Utilidad neta por kg** | **$ 1.490** | **$ 7.441** |

---

## 9. Escenarios

### 9.1 Variables de escenario

| Variable | Pesimista | Base | Optimista |
|---------|:---------:|:----:|:---------:|
| BE% orellana | 70 % | 100 % | 130 % |
| Precio de venta (vs. base) | −20 % | Base | +20 % |
| Tasa de contaminación | 15 % | 5 % | 2 % |
| Ciclos por año por rack | 6 | 8 | 9 |

### 9.2 Producción en cada escenario (Año 2, 4 racks)

| Escenario | Kg/rack/ciclo | Ciclos/año | Kg/rack/año | Total 4 racks |
|-----------|:------------:|:----------:|:-----------:|:-------------:|
| Pesimista | 56 | 6 | 336 | 1.344 kg |
| Base | 76 | 8 | 608 | 2.432 kg |
| Optimista | 101 | 9 | 909 | 3.636 kg |

### 9.3 Ingresos Año 2 en cada escenario

| Concepto | Pesimista | Base | Optimista |
|---------|----------:|-----:|----------:|
| Precio prom. orellana | $ 14.080/kg | $ 17.600/kg | $ 21.120/kg |
| Producción orellana | 1.344 kg | 2.432 kg | 3.636 kg |
| Ingresos orellana | $ 18.923.520 | $ 42.803.200 | $ 76.792.320 |
| Ingresos melena | $ 2.976.000 | $ 4.464.000 | $ 5.952.000 |
| **Total ingresos** | **$ 21.899.520** | **$ 47.267.200** | **$ 82.744.320** |
| EBITDA estimado | $ (2.500.000) | $ 7.657.680 | $ 29.844.320 |
| **¿Viable?** | ⚠️ Pérdida | ✅ Rentable | ✅ Muy rentable |

### 9.4 Análisis de sensibilidad — Año 2 EBITDA

```
                    Precio de venta
                 -20 %    Base    +20 %
BE% 70 %    $ -8.7M   $ -2.5M   $ +3.7M
BE% 100 %   $ -0.5M   $ +7.7M   $ +15.8M
BE% 130 %   $ +7.7M   $ +17.9M  $ +28.1M
```

> El modelo es más sensible al BE% que al precio. Optimizar el proceso de inoculación y las condiciones ambientales tiene mayor impacto que subir precios.

---

## 10. Hoja de ruta de reinversión

```
AÑO 1 — Estabilización
────────────────────────
Utilidad neta disponible: ~$4.000.000 COP

Prioridades de reinversión:
  1. Fondo de emergencia: $2.000.000 (reserva 3 meses de costos fijos)
  2. Banco de cepas (agar, LC, frío): $500.000
  3. Kit de spawn propio (multiplicación grano): $800.000
  4. Material de marketing inicial: $700.000
  Retiro personal: $0 (ya incluido en costos fijos mes 7+)


AÑO 2 — Consolidación
───────────────────────
Utilidad neta disponible: ~$4.000.000 COP (después de inversión Fase 3)

Prioridades:
  1. Certificación INVIMA / registro sanitario: $1.500.000
  2. Equipo de postcosecha (selladora vacío, display frío): $1.200.000
  3. Presencia digital (web + Instagram ads): $800.000
  4. Reserva para expansión: $500.000


AÑO 3 — Diversificación
─────────────────────────
EBITDA disponible: ~$2.800.000 (año de inversión Fase 3)

Prioridades:
  1. Desarrollo línea de extractos dobles: $1.500.000
  2. Alianza con distribuidor naturista regional: $500.000
  3. Curso/taller de cultivo para generar ingresos laterales: $300.000
  4. Reserva Fase 4: $500.000


AÑO 4 — Escala
────────────────
EBITDA disponible: ~$10.000.000 (después de inversión Fase 4)

Prioridades:
  1. Contratar operario full-time segunda sede: incluido en Fase 4
  2. Sistema ERP/contabilidad formal: $2.000.000
  3. Registro de marca Bichongos: $800.000
  4. Fondo de franquicia (documentar playbook): $2.000.000
  5. Retiro personal dueño: aumentar a $3.000.000/mes


AÑO 5 — Expansión
──────────────────
Caja proyectada final Año 5: $97.133.090 COP (~$23.000 USD)

Opciones estratégicas:
  A. Tercera sede propia (nueva ciudad): inversión ~$30M
  B. Modelo franquicia (licenciar sistema + capacitación): $0 inversión, ingresos por regalías
  C. Línea de suplementos certificados (INVIMA medicamentos naturales): $15M + 18 meses
  D. Combinación A+C: la más agresiva pero viable con la caja acumulada
```

---

## Nota metodológica

Este modelo asume:
- **Precios estables:** no incorpora inflación ni presión de competidores. Verificar anualmente.
- **Demanda ilimitada:** se asume que toda la producción se vende. Validar canales antes de escalar (tarea COM-01 a COM-05).
- **Sin financiación externa:** el modelo es 100 % capital propio + reinversión. Con crédito de fomento (Finagro, Bancoldex microempresa) la curva de crecimiento puede acelerarse significativamente.
- **Impuesto estimado al 15 % efectivo:** Colombia tiene tasas formales del 35 % para empresas, pero microempresas en régimen SIMPLE tributan entre 1.8 % y 5.4 % sobre ingresos brutos. Consultar con contador antes del primer período fiscal.
- **Los costos de spawn propio asumen producción exitosa desde el mes 8.** Si el banco de cepas tarda más, mantener el costo de spawn comprado hasta que se valide.

---

*Bichongos · docs/negocio/modelo-financiero.md · v1.0 · 2026-06-30*
