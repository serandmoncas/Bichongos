# KPIs y Criterios de Éxito — Bichongos

> Define qué significa "funcionar bien" en cada dimensión del proyecto. Un sistema sin umbrales claros no puede mejorarse sistemáticamente.

**Versión:** 1.0 · **Fecha:** 2026-06-30

---

## Índice

1. [KPIs de Producción Biológica](#1-kpis-de-producción-biológica)
2. [KPIs del Sistema IoT](#2-kpis-del-sistema-iot)
3. [KPIs Financieros](#3-kpis-financieros)
4. [KPIs de Calidad del Producto](#4-kpis-de-calidad-del-producto)
5. [Semáforo de Decisión](#5-semáforo-de-decisión)
6. [Criterios de Avance por Especie](#6-criterios-de-avance-por-especie)
7. [Plantilla de Reporte Semanal](#7-plantilla-de-reporte-semanal)
8. [Plantilla de Reporte Mensual](#8-plantilla-de-reporte-mensual)

---

## 1. KPIs de Producción Biológica

### 1.1 Eficiencia Biológica (BE%)

**Definición:** Porcentaje de hongo fresco cosechado en relación al peso seco del sustrato.

```
BE% = (kg cosechados frescos / kg sustrato seco) × 100
```

**Cómo medir:** pesar el sustrato seco antes de preparar + pesar toda la cosecha acumulada de todas las oleadas del mismo bloque.

| Especie | 🟢 Excelente | 🟡 Aceptable | 🔴 Revisar proceso |
|---------|------------|------------|-----------------|
| Orellana | ≥ 100 % | 70–99 % | < 70 % |
| Shiitake | ≥ 80 % | 50–79 % | < 50 % |
| Portobello | ≥ 70 % | 45–69 % | < 45 % |
| Melena de León | ≥ 60 % | 40–59 % | < 40 % |
| Enoki | ≥ 80 % | 55–79 % | < 55 % |
| Reishi | ≥ 30 % | 15–29 % | < 15 % |
| Cordyceps | ≥ 40 % | 25–39 % | < 25 % |
| Maitake | ≥ 40 % | 25–39 % | < 25 % |
| Cola de Pavo | ≥ 50 % | 30–49 % | < 30 % |

> **Nota:** Reishi tiene BE% bajo porque se cosecha en seco y su valor está en los compuestos activos, no en el volumen fresco.

---

### 1.2 Tasa de Contaminación

**Definición:** Porcentaje de bloques que presentan contaminación visible antes de fructificar.

```
Tasa de contaminación = (bloques contaminados / bloques inoculados) × 100
```

**Cuándo registrar:** al día 14 post-inoculación (si el micelio no colonizó > 70 % del bloque y hay color verde/naranja/negro → contaminado).

| Umbral | Valor | Acción |
|--------|-------|--------|
| 🟢 Proceso controlado | < 5 % | Mantener rutinas actuales |
| 🟡 Revisar un paso | 5–15 % | Auditar zona de inoculación, FC del sustrato, tiempo de esterilización |
| 🔴 Parar y auditar | > 15 % | Detener inoculaciones hasta identificar la fuente; revisar todos los pasos del SOP |

---

### 1.3 Tiempo de Ciclo

**Definición:** Días desde la inoculación hasta el inicio de la primera cosecha.

| Especie | 🟢 Dentro del rango | 🟡 Lento (revisar temp/HR) | 🔴 Problema grave |
|---------|-------------------|--------------------------|------------------|
| Orellana | 14–25 días | 26–35 días | > 35 días |
| Shiitake | 60–90 días | 91–110 días | > 110 días |
| Melena de León | 20–30 días | 31–40 días | > 40 días |
| Enoki | 25–35 días | 36–45 días | > 45 días |
| Reishi | 60–120 días | 121–150 días | > 150 días |
| Cordyceps | 45–60 días | 61–75 días | > 75 días |

---

### 1.4 Número de Oleadas por Bloque

**Definición:** Cuántas cosechas produce un mismo bloque antes de agotarse o contaminarse.

| Especie | Oleadas esperadas | Mínimo aceptable |
|---------|-----------------|-----------------|
| Orellana | 3–5 | 2 |
| Shiitake | 3–4 + re-inducción | 2 |
| Melena de León | 2–3 | 2 |
| Enoki | 2–3 | 2 |
| Reishi | 1 (cosecha única continua) | — |
| Cordyceps | 1–2 | 1 |

---

## 2. KPIs del Sistema IoT

### 2.1 Disponibilidad del Sistema (Uptime)

**Definición:** Porcentaje del tiempo que el sistema está recibiendo datos de sensores correctamente.

```
Uptime = (minutos con datos válidos / minutos totales del período) × 100
```

| Umbral | Valor | Acción |
|--------|-------|--------|
| 🟢 Operacional | ≥ 98 % | Normal |
| 🟡 Degradado | 95–97 % | Revisar conectividad WiFi, broker MQTT, alimentación |
| 🔴 Crítico | < 95 % | Intervención inmediata — cultivos sin monitoreo están en riesgo |

**Cómo medir:** consultar en InfluxDB el número de registros en el período vs. los esperados (1 registro cada 30 s = 2880 registros por día por cápsula).

---

### 2.2 Latencia de Alertas

**Definición:** Tiempo desde que un sensor supera un umbral crítico hasta que el operario recibe la notificación en Telegram.

| Umbral | Valor | Significado |
|--------|-------|------------|
| 🟢 Inmediato | < 2 minutos | Normal |
| 🟡 Demorado | 2–10 minutos | Revisar flujo Node-RED y conexión a Telegram |
| 🔴 Sin alerta | > 10 minutos | Sistema de alertas no funciona — riesgo operativo |

**Cómo medir:** simular una condición fuera de rango manualmente (desconectar sensor o cambiar umbral temporalmente) y medir el tiempo hasta recibir la notificación.

---

### 2.3 Integridad de Datos

**Definición:** Porcentaje de lecturas de sensores dentro de rangos físicamente plausibles (descarta errores de hardware o drift).

| Sensor | Rango plausible | Si está fuera → |
|--------|----------------|----------------|
| SHT31 Temperatura | 0–45 °C | Sensor desconectado o dañado |
| SHT31 Humedad | 0–100 % HR | Sensor dañado |
| MH-Z19B CO₂ | 400–5000 ppm | Sensor sin calibrar o dañado |
| BH1750 Luz | 0–65535 lux | Desconectado |
| DS18B20 Sustrato | 0–40 °C | Desconectado |

**Umbral mínimo:** < 1 % de lecturas fuera de rango físico en un período de 24 h.

---

### 2.4 Cobertura de Perfiles Activos

**Definición:** Porcentaje de cápsulas con un perfil JSON válido asignado y activo.

| Umbral | Valor |
|--------|-------|
| 🟢 Correcto | 100 % de cápsulas con perfil válido |
| 🔴 Error | Cualquier cápsula sin perfil → actuadores en modo apagado por defecto |

---

## 3. KPIs Financieros

### 3.1 Costo de Producción por Kg

**Definición:** Suma de todos los costos directos dividida entre el total cosechado en kg frescos.

```
Costo/kg = (sustrato + semilla + energía + consumibles + mano de obra) / kg cosechados
```

**Referencia inicial (Orellana):**

| Componente | Costo estimado (COP) |
|-----------|-------------------|
| Sustrato (paja) — 1 kg seco | $ 800 |
| Semilla de grano — 200 g | $ 2.000 |
| Energía (humidificador + extractor) | $ 500 |
| Bolsa PP + insumos | $ 600 |
| **Total por bloque (1 kg sustrato seco)** | **$ 3.900** |
| Rendimiento esperado (BE 100 %) | 1 kg fresco |
| **Costo mínimo/kg** | **$ 3.900** |

| Umbral | Valor Orellana | Acción |
|--------|--------------|--------|
| 🟢 Rentable | < $ 6.000/kg | Margen positivo a precio mercado |
| 🟡 Ajustar | $ 6.000–$ 9.000/kg | Revisar desperdicio y BE% |
| 🔴 No rentable | > $ 9.000/kg | El precio de mercado no cubre costos |

> Actualizar esta tabla con costos reales después del primer lote.

---

### 3.2 Precio de Venta Promedio Ponderado

**Definición:** Precio promedio recibido por kg, ponderado por canal y categoría.

```
Precio promedio = Σ(kg canal × precio canal) / kg totales vendidos
```

**Referencia de precios en Antioquia (2026):**

| Especie | Plaza de mercado | Restaurante | Tienda naturista |
|---------|-----------------|------------|-----------------|
| Orellana fresca | $ 12.000–$ 16.000/kg | $ 18.000–$ 25.000/kg | — |
| Shiitake fresco | $ 20.000–$ 28.000/kg | $ 30.000–$ 40.000/kg | — |
| Melena de León fresca | $ 35.000–$ 50.000/kg | $ 60.000–$ 80.000/kg | — |
| Reishi seco | — | — | $ 80.000–$ 120.000/kg |
| Cordyceps seco | — | — | $ 150.000–$ 300.000/kg |

> Verificar y actualizar con precios reales antes del primer lote (tarea COM-02).

---

### 3.3 Margen Bruto por Lote

**Definición:** Rentabilidad directa de un lote después de descontar costos directos.

```
Margen bruto (%) = ((ingresos - costos directos) / ingresos) × 100
```

| Umbral | Valor | Acción |
|--------|-------|--------|
| 🟢 Saludable | ≥ 40 % | Escalar producción |
| 🟡 Ajustar | 20–39 % | Optimizar costos o subir precio/canal |
| 🔴 Insostenible | < 20 % | No escalar hasta resolver |

---

### 3.4 Retorno de Inversión (ROI) del Hardware por Cápsula

**Definición:** Cuántos meses hasta recuperar el costo del nodo IoT con la producción de esa cápsula.

```
Meses para ROI = Costo del nodo / Margen bruto mensual por cápsula
```

**Referencia:** nodo IoT completo (ESP32 + sensores + relés) ≈ $ 300.000–$ 400.000 COP.

| Umbral | Meses | Viabilidad |
|--------|-------|-----------|
| 🟢 Excelente | < 4 meses | Muy rentable |
| 🟡 Aceptable | 4–8 meses | Escalar con cautela |
| 🔴 Revisar | > 8 meses | El hardware no se justifica para esa especie/cápsula |

---

## 4. KPIs de Calidad del Producto

### 4.1 Porcentaje Categoría A

**Definición:** Porcentaje del peso cosechado que clasifica como Categoría A (tamaño uniforme, sin daños, apto para restaurante premium).

| Umbral | Valor | Significado |
|--------|-------|------------|
| 🟢 Alta calidad | ≥ 70 % cat A | Parámetros de cosecha correctos |
| 🟡 Calidad media | 50–69 % cat A | Revisar momento de cosecha o HR durante fructificación |
| 🔴 Baja calidad | < 50 % cat A | Problema de parámetros — la mayoría va a precio rebajado |

---

### 4.2 Vida Útil en Fresco

**Definición:** Días que el producto mantiene calidad comercial a 2–4 °C.

| Especie | 🟢 Correcto | 🔴 Revisar (cosecha tardía o mal manejo) |
|---------|------------|----------------------------------------|
| Orellana | ≥ 5 días | < 3 días |
| Shiitake | ≥ 10 días | < 6 días |
| Melena de León | ≥ 7 días | < 4 días |

---

### 4.3 Tasa de Devoluciones

**Definición:** Porcentaje de ventas que resultan en queja o devolución por calidad.

| Umbral | Valor | Acción |
|--------|-------|--------|
| 🟢 Excelente | 0 % | Mantener proceso |
| 🟡 Atención | 1–3 % | Revisar protocolo de empaque y cadena de frío |
| 🔴 Problema | > 3 % | Investigar causa raíz antes de siguiente entrega |

---

## 5. Semáforo de Decisión

Tabla de referencia rápida para decidir si se puede avanzar a la siguiente especie o fase.

| Criterio | Verde ✅ — Avanzar | Amarillo ⚠️ — Esperar | Rojo 🛑 — Resolver primero |
|---------|-------------------|----------------------|--------------------------|
| BE% orellana | ≥ 100 % | 70–99 % | < 70 % |
| Tasa contaminación | < 5 % | 5–15 % | > 15 % |
| Uptime IoT | ≥ 98 % | 95–97 % | < 95 % |
| Margen bruto | ≥ 40 % | 20–39 % | < 20 % |
| Primer cliente real | Contrato o pedido repetido | Venta puntual | Sin ventas |
| Banco de cepas | ≥ 1 cepa preservada de la especie | En proceso | Sin cepas propias |

**Regla de avance:** todos los criterios relevantes deben estar en Verde para iniciar producción de la siguiente especie de dificultad superior.

---

## 6. Criterios de Avance por Especie

### Nivel 1 → Nivel 2 (Orellana → Shiitake / Melena de León)

Antes de inocular el primer lote de nivel 2, verificar:

- [ ] ≥ 3 lotes de orellana completados con registro completo
- [ ] BE% promedio ≥ 80 % en los últimos 2 lotes
- [ ] Tasa de contaminación < 5 % en los últimos 3 lotes
- [ ] Sistema IoT estable ≥ 30 días sin intervención manual
- [ ] Al menos 1 cliente recurrente con pedido confirmado
- [ ] Cepa de orellana preservada en banco propio (agar inclinado o LC a 4 °C)

### Nivel 2 → Nivel 3 (Shiitake → Reishi / Enoki / Maitake)

- [ ] ≥ 2 lotes de nivel 2 exitosos con inducción documentada
- [ ] BE% shiitake ≥ 60 % o melena de león ≥ 50 %
- [ ] Cápsula con control de CO₂ validada (melena) o cápsula de frío (enoki)
- [ ] Dashboard Grafana con histórico ≥ 60 días por especie
- [ ] Protocolo de esterilización validado (> 95 % de lotes sin contaminación bacteriana)

### Nivel 3 → Nivel 4 (Reishi → Cordyceps / Cola de Pavo)

- [ ] Cultivo líquido dominado (≥ 3 lotes de LC sin contaminación)
- [ ] Banco de cepas con ≥ 3 especies preservadas
- [ ] Sistema OTA funcionando (actualizaciones remotas de firmware)
- [ ] Módulo financiero activo con seguimiento de costos por lote
- [ ] Acceso a autoclave de ≥ 50 L validado con cinta indicadora

---

## 7. Plantilla de Reporte Semanal

Llenar cada lunes para el período anterior (lunes–domingo).

```
SEMANA: ___________ al ___________
Responsable: ___________

PRODUCCIÓN
  Lotes activos: ___________
  Lotes inoculados esta semana: ___
  Lotes cosechados esta semana: ___
  Lotes contaminados: ___  (tasa: ___ %)
  Kg cosechados: ___ kg
  BE% promedio lotes cerrados: ___ %

VENTAS
  Kg vendidos: ___ kg
  Ingresos: $ ___________
  Canal principal: [ ] Restaurante  [ ] Plaza  [ ] Tienda  [ ] Directo

SISTEMA IoT
  Cápsulas activas: ___
  Alertas disparadas: ___
  Alertas resueltas: ___
  Uptime estimado: ___ %
  Incidencias: ___________

OBSERVACIONES
  ___________________________________________
  ___________________________________________

ACCIONES PARA PRÓXIMA SEMANA
  1. ___________________________________________
  2. ___________________________________________
```

---

## 8. Plantilla de Reporte Mensual

Llenar el primer lunes de cada mes para el mes anterior.

```
MES: ___________  AÑO: ___________

PRODUCCIÓN
  Total lotes inoculados: ___
  Total lotes cosechados: ___
  Total lotes contaminados: ___ (tasa: ___ %)
  Total kg cosechados: ___ kg
  BE% promedio global: ___ %
  BE% por especie:
    Orellana: ___ %
    Shiitake: ___ %
    Otra: ___ %

FINANZAS
  Ingresos totales: $ ___________
  Costos directos (sustrato + semilla + energía): $ ___________
  Margen bruto: $ ___________  (___ %)
  Costo promedio/kg: $ ___________
  Precio promedio/kg: $ ___________

CALIDAD
  % Categoría A: ___ %
  Devoluciones: ___  (___ %)
  Clientes atendidos: ___
  Clientes recurrentes: ___

SISTEMA IoT
  Uptime promedio: ___ %
  Total alertas: ___
  Tiempo promedio resolución de alertas: ___ min
  Incidencias hardware: ___________

SEMÁFORO GLOBAL DEL MES
  BE% orellana: [ ] 🟢  [ ] 🟡  [ ] 🔴
  Tasa contaminación: [ ] 🟢  [ ] 🟡  [ ] 🔴
  Uptime IoT: [ ] 🟢  [ ] 🟡  [ ] 🔴
  Margen bruto: [ ] 🟢  [ ] 🟡  [ ] 🔴
  Ventas/clientes: [ ] 🟢  [ ] 🟡  [ ] 🔴

DECISIONES DEL MES
  ¿Avanzar a nueva especie?: [ ] Sí  [ ] No  [ ] Pendiente
  ¿Escalar producción?: [ ] Sí  [ ] No  [ ] Pendiente
  Acción prioritaria próximo mes: ___________________________________________
```

---

## Cómo usar este documento

1. **Antes del primer lote:** definir quién llena los reportes y con qué frecuencia.
2. **Después de cada lote:** registrar BE%, contaminación, días de ciclo.
3. **Cada semana:** llenar el reporte semanal (15 min máximo).
4. **Cada mes:** revisar el semáforo global y tomar decisión de avance o ajuste.
5. **Cuando un KPI llegue a rojo:** no avanzar a nueva especie ni escalar — resolver primero.

> Los umbrales de este documento son puntos de partida basados en literatura y proyecciones. Ajustar con datos reales después de los primeros 3 lotes de cada especie.

---

*Bichongos · docs/kpis-criterios-exito.md · v1.0 · 2026-06-30*
