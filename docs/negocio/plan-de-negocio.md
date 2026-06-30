# Plan de Negocio — Bichongos

> Laboratorio de cultivo de hongos de alta especialidad con control IoT en Guarne, Antioquia, Colombia.

**Versión:** 1.0 · **Fecha:** 2026-06-30
**Autor:** Sergio Monsalve · **Contacto:** angecanar@gmail.com

---

## Índice

1. [Resumen Ejecutivo](#1-resumen-ejecutivo)
2. [Descripción del Negocio](#2-descripción-del-negocio)
3. [Análisis de Mercado](#3-análisis-de-mercado)
4. [Producto y Servicio](#4-producto-y-servicio)
5. [Estrategia de Marketing y Ventas](#5-estrategia-de-marketing-y-ventas)
6. [Plan de Operaciones](#6-plan-de-operaciones)
7. [Equipo](#7-equipo)
8. [Plan Financiero](#8-plan-financiero-resumen)
9. [Análisis de Riesgos](#9-análisis-de-riesgos)
10. [Hoja de Ruta](#10-hoja-de-ruta)

---

## 1. Resumen Ejecutivo

**Bichongos** es un laboratorio de cultivo de hongos gourmet y funcionales ubicado en Guarne, Antioquia, Colombia. Opera mediante un sistema de **cápsulas de cultivo controladas por IoT**: cámaras herméticas con sensores de temperatura, humedad, CO₂ y luz, gobernadas por un microcontrolador ESP32 que sigue un perfil paramétrico por especie. Este diseño hace que la producción sea **independiente del clima exterior**, replicable en cualquier geografía y trazable desde el sustrato hasta la venta.

**El problema que resuelve:** los restaurantes y consumidores de Antioquia dependen de hongos importados (champignon de Bogotá, shiitake de China) con baja frescura, alta variabilidad de calidad y sin trazabilidad. Las variedades funcionales premium (melena de león, cordyceps, reishi) son prácticamente imposibles de conseguir frescas en el mercado local.

**La solución:** producción local, continua, con registro IoT de cada lote y entrega directa. El cliente recibe hongos cosechados en menos de 24 horas, con QR que muestra el historial completo del cultivo.

**Propuesta de valor en una línea:**
> *"Hongos premium de Antioquia, cultivados con precisión IoT, entregados en 24 horas con trazabilidad completa desde el sustrato."*

### Resumen financiero

| Indicador | Valor |
|-----------|-------|
| Inversión total Fase 1 | $ 4.200.000 COP |
| Ingresos proyectados Año 1 | $ 12.800.000 COP |
| Ingresos proyectados Año 3 | $ 68.000.000 COP |
| Punto de equilibrio operacional | Mes 8 |
| Payback de inversión Fase 1 | 6 meses |
| Margen bruto objetivo (Año 2) | 55–65 % |

---

## 2. Descripción del Negocio

### 2.1 Identidad

| Campo | Detalle |
|-------|---------|
| Nombre | Bichongos |
| Tipo de empresa | Microempresa / Persona natural (inicio), SAS (Fase 2) |
| Ubicación | Guarne, Antioquia, Colombia |
| Altitud | 2.150 msnm — temperatura natural 14–17 °C |
| Área operativa | 50 m² útiles en invernadero 7×14 m |
| Fundador | Sergio Monsalve |

### 2.2 Historia y contexto

El negocio nace de la intersección de tres factores:
1. **Disponibilidad geográfica:** Guarne tiene temperatura natural ideal para orellana y shiitake sin calefacción activa, reduciendo costos energéticos.
2. **Brecha de mercado:** el mercado antioqueño de hongos especiales es incipiente — la demanda de restaurantes gourmet supera la oferta local.
3. **Ventaja tecnológica:** el sistema de cápsulas IoT permite producción controlada y replicable que un cultivador tradicional no puede igualar.

### 2.3 Concepto diferenciador: la cápsula

Cada especie habita en una cápsula propia con microclima exacto a su perfil. El ESP32 lee sensores cada 30 segundos y activa humidificador, extractor FAE, calefactor y LED según los umbrales del perfil JSON activo. Los datos viajan por MQTT al gateway (Raspberry Pi 4) y se almacenan en InfluxDB para visualización en Grafana y acceso remoto vía Firebase.

```
Sustrato + cepa  →  Cápsula controlada  →  Hongo premium  →  Cliente
    (entrada)       (proceso IoT)           (salida)         (valor)
```

La trazabilidad completa de cada lote es el activo diferenciador más difícil de imitar por un competidor artesanal.

---

## 3. Análisis de Mercado

### 3.1 Mercado objetivo — Colombia

| Segmento | Tamaño estimado | Tendencia |
|---------|----------------|----------|
| Restaurantes gourmet Medellín/Rionegro | 200–400 establecimientos | ↑ Crecimiento 8 %/año |
| Tiendas naturistas Antioquia | 300–500 puntos de venta | ↑ Crecimiento 12 %/año |
| Consumidores de suplementos naturales | Mercado nacional en expansión | ↑↑ Post-pandemia |
| Hoteles boutique y resorts Antioquia | 80–120 propiedades | ↑ Turismo gastronómico |
| Mercado de extractos funcionales | Incipiente, alto potencial | ↑↑ |

**Mercado total direccionable (TAM) estimado Antioquia:**
- Hongos frescos gourmet: ~$8.000.000.000 COP/año
- Productos funcionales (polvo, extracto): ~$3.000.000.000 COP/año
- **TAM combinado: ~$11.000.000.000 COP/año**

**Mercado servible (SAM) — radio 60 km de Guarne:**
- Estimado $2.000.000.000 COP/año

**Mercado objetivo (SOM) — meta a 3 años:**
- $68.000.000 COP/año (3.4 % del SAM)

### 3.2 Análisis de competidores

| Competidor | Tipo | Fortaleza | Debilidad | Cómo nos diferenciamos |
|-----------|------|----------|----------|----------------------|
| Importadores de Bogotá | Distribuidor | Volumen, precio | Frescura 3–7 días, sin trazabilidad | Frescura < 24 h, trazabilidad IoT |
| Cultivadores artesanales locales | Productor | Precio bajo | Sin control de parámetros, inconsistencia | Calidad constante, variedades premium |
| Importaciones de China (shiitake seco) | Distribuidor | Precio | Sin frescura, calidad variable | Producto fresco local |
| Grandes productores (Bogotá) | Productor | Escala | Especies básicas, sin servicio premium | Especies exóticas, trazabilidad |

**Posicionamiento:** nicho premium — calidad, frescura, trazabilidad y variedades únicas en el mercado local. No competimos en precio con el champignon de plaza.

### 3.3 Tendencias del mercado

- **Gastronomía de producto local:** el movimiento "de la granja al plato" genera demanda de proveedores certificables con historia del producto.
- **Salud funcional:** crecimiento del 15–20 % anual en Colombia de productos naturales con respaldo científico. Reishi, melena de león y cordyceps tienen comunidades activas en redes.
- **Micología recreativa:** comunidad en expansión (grupos de forrajeo, cultivo en casa) que valora la trazabilidad y la variedad.
- **Trazabilidad alimentaria:** restaurantes upscale empiezan a exigir proveedores que puedan documentar el origen del ingrediente — el QR de Bichongos es una respuesta directa.

---

## 4. Producto y Servicio

### 4.1 Portafolio de productos

**Línea 1 — Hongos frescos gourmet (Fases 1–2)**

| Producto | Presentación | Canal | Precio COP |
|---------|-------------|-------|-----------|
| Orellana fresca | Bandeja 300 g / bolsa 1 kg | Restaurante, plaza | $14.000–$20.000/kg |
| Shiitake fresco | Bandeja 200 g / bolsa 500 g | Restaurante | $25.000–$35.000/kg |
| Melena de León fresca | Unidad 200–400 g | Restaurante premium | $50.000–$70.000/kg |
| Enoki fresco | Paquete 100 g | Restaurante asiático, naturista | $30.000–$45.000/kg |
| Portobello fresco | Unidad 150–300 g | Supermercado, restaurante | $22.000–$30.000/kg |

**Línea 2 — Hongos secos y polvo (Fase 2–3)**

| Producto | Presentación | Canal | Precio COP |
|---------|-------------|-------|-----------|
| Orellana seca | Bolsa 50 g | Tienda naturista, e-commerce | $18.000/und |
| Shiitake seco | Bolsa 50 g | Tienda naturista | $22.000/und |
| Reishi seco en trozo | Bolsa 50 g | Tienda naturista | $35.000/und |
| Polvo de Melena de León | Frasco 60 g | Naturista, online | $55.000/und |
| Polvo de Reishi | Frasco 60 g | Naturista, online | $48.000/und |

**Línea 3 — Extractos dobles (Fase 3)**

| Producto | Presentación | Canal | Precio COP |
|---------|-------------|-------|-----------|
| Extracto Reishi (agua+alcohol) | Frasco 60 ml | Naturista, online | $85.000/und |
| Extracto Melena de León | Frasco 60 ml | Naturista, online | $95.000/und |
| Extracto Cordyceps | Frasco 60 ml | Naturista, online | $120.000/und |
| Blend "Inmunidad" (3 extractos) | Frasco 60 ml | Online, farmacia natural | $140.000/und |

**Línea 4 — Servicios (Fase 4)**

| Servicio | Descripción | Precio COP |
|---------|-------------|-----------|
| Kit de cultivo doméstico | Bloque inoculado listo para fructificar | $35.000–$55.000/kit |
| Licencia de sistema de cápsulas | Manual + soporte para nueva sede | A definir |
| Consultoría de cultivo | Visita técnica + setup IoT | $200.000/sesión |

### 4.2 Ciclo de calidad

```
Cepa certificada
     │
     ▼
Sustrato preparado (SOP documentado)
     │
     ▼
Inoculación en zona limpia (flujo laminar)
     │
     ▼
Cápsula con parámetros IoT monitoreados 24/7
     │
     ▼
Cosecha en punto óptimo (indicadores visuales + días de perfil)
     │
     ▼
Clasificación A/B/C + registro de peso y BE%
     │
     ▼
Empaque con QR de trazabilidad
     │
     ▼
Entrega < 24 h de cosechado
```

---

## 5. Estrategia de Marketing y Ventas

### 5.1 Propuesta de posicionamiento

**Para restaurantes:**
> "El ingrediente que le cuenta su historia. Hongos de Guarne cosechados esta mañana, con registro IoT de cada día de cultivo. Tu cliente lo escanea en la mesa."

**Para consumidores de suplementos:**
> "Extractos con identidad: sabes de dónde vino, cómo creció y cuándo se procesó. Sin intermediarios, desde el laboratorio a tu puerta."

### 5.2 Estrategia de entrada al mercado (Fase 1)

**Mes 1–3: Validación con clientes ancla**

1. Identificar 3 restaurantes en Medellín/Rionegro/Guarne dispuestos a probar producto.
2. Entregar muestras gratuitas de la primera cosecha de orellana (2–3 kg).
3. Solicitar feedback estructurado: calidad, frescura, presentación, precio justo.
4. Convertir al menos 1 en cliente regular antes de escalar.

**Mes 4–6: Primer canal regular**

- 1 restaurante con pedido semanal de 5–10 kg de orellana.
- Presencia en 1 plaza de mercado campesino (Guarne o Marinilla, sábados).
- Instagram activo con contenido del proceso (detrás de cámaras del laboratorio IoT).

**Mes 7–12: Ampliación**

- 3–5 restaurantes activos.
- Canal naturista: 2–3 tiendas con producto seco y polvo.
- WhatsApp Business con catálogo y pedidos.

### 5.3 Canales de venta por fase

| Canal | Fase 1 | Fase 2 | Fase 3 |
|-------|--------|--------|--------|
| Venta directa a restaurantes | ✅ Primario | ✅ Primario | ✅ |
| Plaza de mercado campesino | ✅ | ✅ | ✅ |
| WhatsApp Business | ✅ | ✅ | ✅ |
| Tiendas naturistas | ❌ | ✅ | ✅ |
| Instagram / e-commerce | ❌ | ✅ | ✅ |
| Web app con pedidos | ❌ | ✅ | ✅ |
| Domicilios / delivery | ❌ | ❌ | ✅ |
| Exportación (Ecuador, Perú) | ❌ | ❌ | Explorar |

### 5.4 Estrategia de contenido

El sistema IoT es el mejor argumento de marketing. Publicar:
- **Timelapse de colonización** de micelio (muy viral en comunidades de cultivo)
- **Dashboard en vivo** de temperatura y CO₂ dentro de las cápsulas
- **"De la cápsula al plato"**: historia completa de un hongo en un restaurante específico
- **Educación:** propiedades medicinales de cada especie con citas científicas
- **Proceso:** transparencia total de cómo se produce sin pesticidas ni químicos

---

## 6. Plan de Operaciones

### 6.1 Layout del invernadero

```
┌─────────────────────────────────────────────┐
│     7 × 14 m — Área útil 50 m²             │
│                                             │
│  [A] Bodega    [B] Prep.   [C] Postcosecha │
│  sustrato      sustrato    y secado         │
│                                             │
│  [D] Inoculación  [E] Incubación           │
│  (zona limpia)    (cápsulas)               │
│                                             │
│  [F] Fructificación                        │
│  (cápsulas)                                │
└─────────────────────────────────────────────┘
```

### 6.2 Capacidad de producción por fase

| Fase | Cápsulas | Producción mensual estimada | Ingresos mensuales |
|------|---------|---------------------------|-------------------|
| 1 (mes 1–6) | 1 rack orellana | 13 kg orellana | $208.000 |
| 1b (mes 4–6) | 1 rack + cápsula mini | 17 kg | $272.000 |
| 2 (mes 7–12) | 4 racks orellana + 1 cápsula shiitake | 56 kg mix | $952.000 |
| 3 (mes 13–24) | 6 racks + 3 cápsulas especiales | 90 kg + extractos | $2.800.000 |
| 4 (mes 25–36) | Escala completa + spawn propio | 150 kg + línea funcional | $5.500.000 |

### 6.3 Proceso de producción semanal

**Semana típica en Fase 2 (4 racks activos):**

| Día | Actividad | Tiempo |
|-----|-----------|--------|
| Lunes | Revisar Grafana, inspección visual de cápsulas | 1 h |
| Lunes | Preparar sustrato (pasteurización) si hay lote nuevo | 3 h |
| Martes | Inoculación de nuevos bloques | 2 h |
| Martes | Cosecha si hay oleadas listas, registrar peso | 1–2 h |
| Miércoles | Clasificar, empacar, etiquetas + QR | 1 h |
| Miércoles | Entrega a restaurantes | 2 h |
| Jueves | Limpieza de cápsulas, mantenimiento | 1 h |
| Viernes | Registro de datos en sistema, reporte semanal | 1 h |
| Sábado | Plaza de mercado (opcional) | 4 h |
| **Total** | | **16–18 h/semana** |

Con 1 persona a tiempo parcial + fundador: viable en Fase 1–2.

### 6.4 Control de calidad

- **Trazabilidad IoT:** cada lote tiene ID único con historial de parámetros.
- **Registro manual:** planillas de inoculación, cosecha y venta (ver SOPs).
- **KPIs semanales:** BE%, tasa de contaminación, % categoría A.
- **Umbrales de alerta:** ver `docs/kpis-criterios-exito.md`.

### 6.5 Proveedores críticos

| Insumo | Proveedor actual | Proveedor alternativo | Riesgo |
|--------|-----------------|----------------------|--------|
| Cepas certificadas | Fungifarm Colombia | Setas Colombia | Medio — tener banco propio desde mes 4 |
| ESP32 + sensores | MercadoLibre / AliExpress | Micro-Ingeniería Medellín | Bajo |
| Sustrato (paja) | Mercado campesino local | Fincas arroceras región | Bajo |
| Bolsas PP | Importadora plásticos Medellín | ML | Bajo |

---

## 7. Equipo

### 7.1 Fundador

**Sergio Monsalve** — Guarne, Antioquia

Roles en el negocio:
- Dirección general y estrategia
- Diseño y mantenimiento del sistema IoT
- Cultivo y control de calidad
- Ventas y relaciones con clientes

### 7.2 Estructura de equipo por fase

| Fase | Equipo | Costo mensual |
|------|--------|--------------|
| Fase 1 (mes 1–6) | Fundador únicamente | $0 salario (reinversión) |
| Fase 1b (mes 7–12) | Fundador + 1 ayudante part-time | $600.000/mes |
| Fase 2 (año 2) | Fundador + 1 operario tiempo completo | $1.600.000/mes |
| Fase 3 (año 3) | + 1 persona ventas/distribución | $2.800.000/mes |
| Fase 4 (año 4) | Equipo completo 5 personas | $6.000.000/mes |

### 7.3 Habilidades críticas a desarrollar

Ver `docs/roadmap-equipo.md` para el plan completo de formación técnica.

**Habilidades prioritarias Fase 1:**
- Técnica de inoculación estéril (tasa contaminación < 5%)
- Interpretación de Grafana (lectura de dashboards IoT)
- Manejo de herramientas Arduino IDE (ajuste de firmware)
- Ventas directas B2B (negociación con restaurantes)

---

## 8. Plan Financiero (Resumen)

> Ver `docs/negocio/modelo-financiero.md` para el detalle completo.

### 8.1 Inversión requerida

| Fase | Inversión | Fuente |
|------|----------|--------|
| Fase 0 (medición) | $335.000 | Capital propio |
| Fase 1 (piloto) | $3.857.480 | Capital propio |
| Fase 2 (escala) | $6.473.390 | Utilidades Fase 1 |
| Fase 3 (funcionales) | $8.500.000 | Utilidades + crédito Bancóldex |
| Fase 4 (expansión) | $25.000.000 | Inversionista ángel o Fondo Emprender |

### 8.2 Proyección de ingresos

| Año | Ingresos COP | Margen bruto | Utilidad neta |
|-----|-------------|-------------|--------------|
| Año 1 | $12.800.000 | 42 % | -$8.200.000 (inversión) |
| Año 2 | $38.400.000 | 55 % | $8.600.000 |
| Año 3 | $68.000.000 | 62 % | $22.400.000 |
| Año 4 | $115.000.000 | 65 % | $45.000.000 |
| Año 5 | $180.000.000 | 67 % | $78.000.000 |

### 8.3 Punto de equilibrio

- **Break-even operacional:** mes 8 (primer mes sin pérdida operacional)
- **Recuperación de inversión Fase 1:** mes 12–14
- **Producción mínima para cubrir costos fijos (Año 1):** 12 kg/mes de orellana a $16.000/kg

---

## 9. Análisis de Riesgos

### 9.1 Matriz de riesgos

| Riesgo | Probabilidad | Impacto | Nivel | Mitigación |
|--------|-------------|---------|-------|-----------|
| Contaminación masiva (> 30 % lotes) | Media | Alto | 🔴 | Protocolo SOP estricto; cuarentena inmediata |
| Demanda menor a proyectada | Media | Alto | 🔴 | Validar cliente ancla antes de escalar |
| Falla del sistema IoT (RPi o MQTT) | Baja | Alto | 🟡 | Modo seguro firmware; UPS; backup RPi |
| Corte de energía prolongado | Baja | Alto | 🟡 | UPS 600VA; avisos Telegram; plantas de emergencia |
| Proveedor de cepas deja de operar | Baja | Medio | 🟡 | Banco de cepas propio desde mes 4 |
| Precio de mercado cae > 20 % | Baja | Medio | 🟡 | Diversificar hacia línea seca/extractos |
| Competidor local entra al mercado | Media | Medio | 🟡 | Ventaja IoT y trazabilidad difícil de replicar rápido |
| Cambio regulatorio (INVIMA) | Baja | Bajo | 🟢 | Cumplir requisitos desde el inicio |
| Devaluación del peso (insumos importados) | Alta | Bajo | 🟢 | Comprar sensores en volumen; priorizar insumos locales |

### 9.2 Plan de contingencia principal

**Escenario: contaminación alta en los primeros meses**

1. Parar toda inoculación nueva inmediatamente.
2. Auditar cada paso del SOP de inoculación (zona D, FC del sustrato, temperatura de inoculación).
3. Hacer prueba de esterilidad: preparar 5 bloques sin semilla y verificar 7 días.
4. Si hay contaminación en bloques sin semilla: el problema está en la esterilización.
5. Si no hay contaminación: el problema está en la semilla o en la técnica de inoculación.
6. No reiniciar producción hasta tener la causa raíz identificada.
7. Comunicar proactivamente a clientes el retraso con fecha realista de reactivación.

---

## 10. Hoja de Ruta

### Fase 0 — Pre-implementación (Julio 2026)
- [ ] Medir línea de base ambiental del invernadero (7 días)
- [ ] Contactar 3 restaurantes y validar precio/demanda
- [ ] Levantar BOM real con cotizaciones
- [ ] Registrar actividad económica (RUT/Cámara de Comercio)
- [ ] Verificar requisitos INVIMA para venta de hongos

### Fase 1 — Piloto (Agosto–Diciembre 2026)
- [ ] Construir cápsula Mini y rack orellana
- [ ] Instalar gateway Raspberry Pi + Mosquitto + Grafana
- [ ] Flashear firmware ESP32 y validar sensores
- [ ] Primer lote de orellana (registro completo)
- [ ] Primera cosecha + primera venta
- [ ] Establecer banco de cepas propio

### Fase 2 — Escala N1 (Enero–Junio 2027)
- [ ] 3 racks adicionales de orellana
- [ ] 1 cápsula estándar para shiitake
- [ ] Canal naturista con producto seco
- [ ] Web app básica con catálogo y pedidos
- [ ] 5 clientes regulares activos

### Fase 3 — Especies funcionales (Julio 2027–Junio 2028)
- [ ] Cápsulas de reishi, melena de león, cordyceps
- [ ] Línea de extractos dobles
- [ ] Deshidratador industrial
- [ ] Presencia en tiendas naturistas de Medellín

### Fase 4 — Expansión (2029+)
- [ ] Segunda sede o modelo de franquicia
- [ ] Exportación a Ecuador / Perú (hongos secos y extractos)
- [ ] Web app completa con trazabilidad pública por QR
- [ ] Alianza con cadena de tiendas naturistas o supermercados

---

## Anexos

- `docs/negocio/canvas-modelos.md` — Business Model Canvas, Value Proposition Canvas, Lean Canvas
- `docs/negocio/modelo-financiero.md` — Proyecciones financieras detalladas a 5 años
- `docs/kpis-criterios-exito.md` — Métricas de éxito operativo
- `docs/bom-precios-cop.md` — Lista de materiales con precios
- `BACKLOG.md` — 145 tareas del proyecto organizadas por épica

---

*Bichongos · docs/negocio/plan-de-negocio.md · v1.0 · 2026-06-30*
