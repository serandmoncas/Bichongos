# Línea de Base Ambiental — Invernadero Guarne

> Protocolo para medir las condiciones reales del invernadero **antes** de instalar cualquier cápsula o sistema IoT. Sin estos datos, los perfiles JSON y los umbrales de control son suposiciones, no hechos.

**Versión:** 1.0 · **Fecha de creación:** 2026-06-30
**Estado:** 🔲 Pendiente de ejecución (tarea DOC-22 en BACKLOG.md)

---

## Por qué medir antes de construir

Guarne está a 2.150 msnm con temperatura promedio de 14–17 °C, pero eso es el promedio anual. Lo que importa para el cultivo es:

- **La variación diurna:** ¿cuánto sube la temperatura al mediodía dentro del invernadero con efecto invernadero?
- **La variación nocturna:** ¿baja lo suficiente para inducir fructificación natural en orellana sin choque de frío activo?
- **La humedad real dentro:** el invernadero puede ser más seco que el exterior si hay ventilación, o más húmedo si está sellado.
- **El CO₂ de base:** en una estructura cerrada sin ventilación puede superar 1.000 ppm solo por respiración humana y microbiana del sustrato.
- **Los puntos fríos y calientes:** la temperatura no es uniforme — junto a la cubierta puede ser 5 °C más alta que en el centro.

Con estos datos se puede saber:
- Qué especies pueden fructificar **sin climatización activa** en Guarne
- Dónde ubicar físicamente cada cápsula dentro del invernadero
- Cuánta carga térmica deben manejar los actuadores (dimensionar calefactores, extractores)
- Qué valores poner como referencia de "ambiente normal" para detectar anomalías del sensor

---

## Equipos necesarios

| Equipo | Uso | Costo referencia |
|--------|-----|-----------------|
| Termohigrómetro digital con datalogger | Temp + HR cada 30 min automático | $ 80.000–$ 150.000 COP |
| Termómetro infrarrojo | Verificar puntos específicos (superficies) | $ 40.000–$ 80.000 COP |
| Medidor de CO₂ portátil (NDIR) | CO₂ en ppm en distintos puntos | $ 150.000–$ 300.000 COP |
| Luxómetro | Luz en lux por zona | $ 50.000–$ 100.000 COP |
| Anemómetro o cinta de humo | Detectar corrientes de aire | $ 30.000–$ 60.000 COP |
| Cuaderno de campo o planilla impresa | Registro manual | $ 0 |

> Si no hay datalogger disponible, tomar lecturas manuales cada 2 horas durante 7 días. Es más trabajo pero igualmente válido.

---

## Puntos de medición

Definir y marcar físicamente **al menos 6 puntos** dentro del invernadero antes de empezar:

```
Plano esquemático del invernadero (7 × 14 m):

  Norte
  ┌─────────────────────────────────┐
  │  [P1]          [P2]      [P3]  │ ← Zona superior (junto a cubierta)
  │                                │
  │  Zona E       Zona F           │
  │  (incub.)     (fructif.)       │
  │                                │
  │  [P4]          [P5]      [P6]  │ ← Zona inferior (cerca del suelo)
  │                                │
  │  Zona D    Zona B    Zona C    │
  │  (inocul.) (prep.)   (secado)  │
  └─────────────────────────────────┘
  Sur

P1 — Esquina noroeste, 1,5 m de altura
P2 — Centro del invernadero, 1,5 m de altura
P3 — Esquina noreste, 1,5 m de altura
P4 — Junto a la cubierta sur, 0,5 m del suelo
P5 — Zona de inoculación (Zona D), 1,0 m de altura
P6 — Zona de fructificación prevista (Zona F), 1,0 m de altura
```

Ajustar la ubicación de los puntos según el plano real del invernadero.

---

## Protocolo de medición

### Duración mínima

**7 días consecutivos** para capturar la variación diurna completa. Idealmente 14 días para incluir variación entre semanas (días laborales vs. fin de semana cuando nadie entra).

### Frecuencia de registro

| Método | Frecuencia |
|--------|-----------|
| Datalogger automático | Cada 30 minutos (recomendado) |
| Registro manual | Cada 2 horas (06:00, 08:00, 10:00, 12:00, 14:00, 16:00, 18:00, 20:00) |

### Variables a registrar en cada punto

| Variable | Unidad | Instrumento |
|---------|--------|------------|
| Temperatura del aire | °C | Termohigrómetro |
| Humedad relativa | % HR | Termohigrómetro |
| CO₂ | ppm | Medidor NDIR |
| Luz | lux | Luxómetro |
| Temperatura de superficie (piso, paredes) | °C | Infrarrojo |

### Condiciones a registrar en cada lectura

Anotar junto a cada lectura:

- [ ] Cielo: soleado / nublado / lluvia
- [ ] Puertas/ventanas: abiertas / cerradas
- [ ] Personas dentro: sí / no
- [ ] Hora del día

---

## Planillas de registro

### Planilla diaria (una por día, por punto de medición)

```
PUNTO: ___  FECHA: ___________  DÍA: ___________

Hora   | Temp (°C) | HR (%) | CO₂ (ppm) | Luz (lux) | Cielo    | Puertas
-------|-----------|--------|-----------|-----------|----------|---------
06:00  |           |        |           |           |          |
08:00  |           |        |           |           |          |
10:00  |           |        |           |           |          |
12:00  |           |        |           |           |          |
14:00  |           |        |           |           |          |
16:00  |           |        |           |           |          |
18:00  |           |        |           |           |          |
20:00  |           |        |           |           |          |
-------|-----------|--------|-----------|-----------|----------|---------
Mín:   |           |        |           |           |
Máx:   |           |        |           |           |
Prom:  |           |        |           |           |

Observaciones del día:
_______________________________________________
```

### Planilla de resumen semanal (consolidado de los 7 días)

```
SEMANA: ___________ al ___________

          │ TEMP (°C)        │ HR (%)           │ CO₂ (ppm)
Punto     │ Mín  Máx  Prom  │ Mín  Máx  Prom  │ Mín  Máx  Prom
----------|------------------|------------------|------------------
P1        │      │     │     │      │     │     │      │     │
P2        │      │     │     │      │     │     │      │     │
P3        │      │     │     │      │     │     │      │     │
P4        │      │     │     │      │     │     │      │     │
P5        │      │     │     │      │     │     │      │     │
P6        │      │     │     │      │     │     │      │     │
----------|------------------|------------------|------------------
GLOBAL    │      │     │     │      │     │     │      │     │

          │ LUZ (lux)
Punto     │ Mín  Máx  Prom
----------|-------------------
P1        │      │     │
P2        │      │     │
P6        │      │     │

Temp. de superficie:
  Piso zona E (incubación): ___ °C
  Pared norte: ___ °C
  Cubierta interior (mediodía): ___ °C
```

---

## Cómo analizar los resultados

### Paso 1 — Completar la tabla de condiciones reales

Una vez terminado el período de medición, consolidar en esta tabla:

```
CONDICIONES REALES DEL INVERNADERO (llenar con datos medidos)
Período medido: ___________ al ___________

Variable          │ Noche (00–06h) │ Mañana (06–12h) │ Tarde (12–18h) │ Noche (18–24h)
------------------|----------------|-----------------|----------------|----------------
Temp. mín diaria  │                │                 │                │
Temp. máx diaria  │                │                 │                │
Temp. promedio    │                │                 │                │
HR promedio       │                │                 │                │
CO₂ promedio      │                │                 │                │
Luz promedio      │                │                 │                │
```

### Paso 2 — Comparar contra requerimientos de cada especie

Completar la siguiente tabla con los datos medidos y marcar si se necesita climatización activa:

| Especie | Parámetro | Requerimiento perfil | Condición real | ¿Necesita control activo? |
|---------|-----------|---------------------|---------------|--------------------------|
| **Orellana** | Temp. incubación | 20–24 °C | ___ °C | ¿Sí/No? |
| | Temp. fructificación | 14–20 °C | ___ °C | ¿Sí/No? |
| | HR fructificación | 85–95 % | ___ % | ¿Sí/No? |
| | CO₂ fructificación | < 1.000 ppm | ___ ppm | ¿Sí/No? |
| **Shiitake** | Temp. incubación | 22–26 °C | ___ °C | ¿Sí/No? |
| | Temp. fructificación | 15–21 °C | ___ °C | ¿Sí/No? |
| | HR fructificación | 80–90 % | ___ % | ¿Sí/No? |
| **Melena de León** | Temp. incubación | 21–24 °C | ___ °C | ¿Sí/No? |
| | CO₂ fructificación | < 700 ppm | ___ ppm | ¿Sí/No? |
| | HR fructificación | 90–95 % | ___ % | ¿Sí/No? |
| **Enoki** | Temp. fructificación | 7–12 °C | ___ °C | ¿Sí/No? (frío activo) |
| | CO₂ fructificación | > 2.000 ppm | ___ ppm | ¿Sí/No? (acumular CO₂) |
| **Reishi** | Temp. todas etapas | 25–30 °C | ___ °C | **Siempre sí** |
| | HR fructificación | 85–95 % | ___ % | ¿Sí/No? |
| **Cordyceps** | Temp. incubación | 22–25 °C | ___ °C | ¿Sí/No? |
| | Luz fructificación | 12/12 h ciclo | ___ lux/h | ¿Sí/No? |

### Paso 3 — Identificar puntos críticos del espacio

Con el mapa de temperaturas por punto (P1–P6), responder:

1. **¿Dónde está el punto más cálido?** → ubicar allí las cápsulas de Reishi y Cordyceps (necesitan calor)
2. **¿Dónde está el punto más frío?** → ubicar allí las cápsulas de Enoki (o donde se instale el sistema de frío)
3. **¿Hay estratificación vertical?** (diferencia P1/P3 vs. P4/P6) → si hay > 3 °C de diferencia, los hongos a nivel del suelo y a 1,5 m vivirán en microclimas distintos
4. **¿Hay corrientes de aire frío?** → las corrientes directas sobre las cápsulas generan estrés hídrico y contaminación por polvo

---

## Interpretación esperada para Guarne

Basado en las condiciones conocidas de la zona (2.150 msnm, 14–17 °C promedio), se anticipa:

| Especie | Hipótesis pre-medición | Confirmar con datos |
|---------|----------------------|-------------------|
| Orellana | Puede fructificar sin calefacción (temp. natural suficiente) | Verificar que temp. nocturna baje a 14–18 °C |
| Shiitake | Puede incubar sin calefacción; fructificación natural posible | Verificar temp. diurna ≤ 22 °C en verano |
| Melena de León | HR posiblemente insuficiente sin humidificador | Verificar HR < 80 % en días secos |
| Enoki | Necesita frío activo casi seguro (Guarne no baja a 7–12 °C) | Confirmar que temp. no baja a 7 °C ni de noche |
| Reishi | Definitivamente necesita calefacción activa en Guarne | Confirmar que nunca alcanza 25 °C naturalmente |
| Cordyceps | Temperatura probablemente correcta; luz necesita control | Verificar luminosidad natural y ciclo de luz |

> Estas son hipótesis — los datos reales pueden sorprender. Un invernadero de plástico puede crear efecto de invernadero y subir la temperatura interna 8–12 °C sobre la exterior en días soleados.

---

## Resultado esperado del documento

Al terminar las mediciones, este documento debe tener completadas:

- [ ] Tabla de condiciones reales por punto y período del día
- [ ] Tabla de comparación especie vs. condición real
- [ ] Mapa de calor del invernadero (temperatura por zona)
- [ ] Lista de especies que pueden producirse con climatización mínima
- [ ] Lista de especies que necesitan climatización activa y de qué tipo
- [ ] Recomendación de ubicación de cada cápsula dentro del invernadero
- [ ] Ajuste de los perfiles JSON si los valores de referencia difieren de la literatura

---

## Impacto en los perfiles JSON

Si los datos medidos difieren de los valores del perfil, actualizar los campos relevantes en `firmware/profiles/`. Ejemplo:

```json
// Antes (valores de literatura)
"fructificacion": {
  "temp_min": 14,
  "temp_max": 20
}

// Después (ajustado a condición real de Guarne)
"fructificacion": {
  "temp_min": 14,
  "temp_max": 20,
  "_nota_local": "En Guarne, temp. promedio nocturna 13-15°C — no se necesita calefacción para orellana"
}
```

---

*Bichongos · docs/linea-base-ambiental.md · v1.0 · 2026-06-30*
