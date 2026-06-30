# Canvas de Modelos de Negocio — Bichongos

> Tres perspectivas complementarias del modelo de negocio: Osterwalder para la arquitectura completa, Value Proposition Canvas para el ajuste producto-mercado, y Lean Canvas para la validación startup.

**Versión:** 1.0 · **Fecha:** 2026-06-30

---

## 1. Business Model Canvas — Alexander Osterwalder

```
╔══════════════════╦══════════════════╦══════════════════╦══════════════════╗
║  SOCIOS CLAVE    ║ ACTIVIDADES CLAVE║ PROPUESTA        ║ RELACIONES CON   ║
║                  ║                  ║ DE VALOR         ║ CLIENTES         ║
║ • Fungifarm /    ║ • Cultivo y      ║                  ║                  ║
║   Setas Colombia ║   mantenimiento  ║ "Hongos premium  ║ • Restaurantes:  ║
║   (cepas         ║   de cápsulas    ║  con trazabilidad║   contrato de    ║
║   certificadas)  ║                  ║  IoT completa,   ║   suministro     ║
║                  ║ • Control de     ║  disponibles     ║   semanal        ║
║ • Restaurantes   ║   calidad y      ║  todo el año,    ║                  ║
║   ancla          ║   trazabilidad   ║  producidos      ║ • Naturistas:    ║
║   (contratos     ║   por lote       ║  localmente en   ║   pedido         ║
║   de volumen)    ║                  ║  Guarne."        ║   recurrente     ║
║                  ║ • Desarrollo de  ║                  ║   WhatsApp       ║
║ • Proveedores    ║   nuevas especies ║ Por segmento:   ║                  ║
║   de insumos     ║   y productos    ║ → Restaurante:   ║ • Consumidor     ║
║   (paja, bolsas, ║                  ║   calidad consis.║   directo:       ║
║   aserrín)       ║ • Ventas y       ║   + trazabilidad ║   comunidad      ║
║                  ║   distribución   ║ → Naturista:     ║   educativa      ║
║ • Técnico        ║                  ║   extractos       ║   (IG, talleres) ║
║   electrónico    ║ • Mantenimiento  ║   certificados   ║                  ║
║   local          ║   del sistema    ║ → Consumidor:    ║ • Franquiciado:  ║
║   (IoT)          ║   IoT            ║   salud local    ║   soporte        ║
║                  ║                  ║   + fresco       ║   técnico y      ║
║ • Distribuidores ║ • I+D en nuevas  ║ → Franquiciado:  ║   acompañamiento ║
║   naturistas     ║   cepas y        ║   sistema llave  ║   operativo      ║
║                  ║   formatos       ║   en mano        ║                  ║
╠══════════════════╩══════════════════╣                  ╠══════════════════╣
║  RECURSOS CLAVE                     ║                  ║ SEGMENTOS DE     ║
║                                     ║                  ║ CLIENTES         ║
║ Físicos:                            ║                  ║                  ║
║ • Cápsulas IoT (ESP32 + sensores)   ║                  ║ S1 — Restaurante ║
║ • Invernadero 7×14 m Guarne         ║                  ║ gourmet Medellín/║
║ • Equipamiento de laboratorio       ║                  ║ Rionegro         ║
║ • Banco de cepas certificadas       ║                  ║ (Tamaño: ~200    ║
║                                     ║                  ║  restaurantes)   ║
║ Intelectuales:                      ╚══════════════════╣                  ║
║ • Perfiles JSON por especie (git)   ║ CANALES          ║ S2 — Tienda      ║
║ • Know-how micológico + IoT         ║                  ║ naturista /      ║
║ • Marca Bichongos + trazabilidad    ║ Awareness:       ║ suplementos      ║
║ • Sistema de replicación de sede    ║ • Instagram/     ║ (naturistas,     ║
║                                     ║   TikTok         ║  farmacias       ║
║ Humanos:                            ║   educativo      ║  naturales)      ║
║ • Micólogo fundador                 ║ • Mercado        ║                  ║
║ • Técnico IoT                       ║   campesino      ║ S3 — Consumidor  ║
║ • Operario de producción            ║                  ║ directo (salud   ║
║                                     ║ Consideración:   ║ consciente,      ║
║ Financieros:                        ║ • WhatsApp       ║ veganos,         ║
║ • Capital inicial ~$4.2M COP        ║   Business       ║ deportistas)     ║
║ • Flujo de caja de orellana         ║ • Visita al      ║                  ║
║   desde mes 2                       ║   invernadero    ║ S4 — Franquiciado║
║                                     ║                  ║ potencial        ║
║                                     ║ Compra:          ║ (emprendedor que ║
║                                     ║ • Pedido directo ║ quiere replicar  ║
║                                     ║   WhatsApp       ║ el modelo en     ║
║                                     ║ • Web App (F2)   ║ otra ciudad)     ║
║                                     ║                  ║                  ║
║                                     ║ Posventa:        ║                  ║
║                                     ║ • QR trazabilidad║                  ║
║                                     ║ • Recetas y      ║                  ║
║                                     ║   contenido      ║                  ║
╠═════════════════════════════════════╩══════════════════╩══════════════════╣
║  ESTRUCTURA DE COSTOS                    ║  FUENTES DE INGRESO            ║
║                                          ║                                ║
║  COSTOS VARIABLES (por kg producido):    ║  I1 — Hongos frescos por kg   ║
║  • Sustrato (paja/aserrín): $800–1.200/kg║       Precio: $14k–80k COP/kg  ║
║  • Semilla de grano: $4.000–5.000/kg     ║       Modelo: precio spot /    ║
║    producido (al escalar con banco propio)║       contrato semanal         ║
║  • Bolsas PP + filtros + clips: $500/kg  ║                                ║
║  • Consumibles bioseguridad: $300/kg     ║  I2 — Hongos secos / polvo    ║
║  • Energía (electricidad): $150/kg       ║       Precio: $80k–300k COP/kg ║
║                                          ║       Modelo: precio spot      ║
║  COSTOS FIJOS MENSUALES:                 ║                                ║
║  • Servicios públicos base: $120.000     ║  I3 — Extractos dobles        ║
║  • Conexión a internet: $80.000          ║       (reishi, cordyceps,      ║
║  • Insumos mantenimiento IoT: $50.000    ║       melena) 100 ml           ║
║  • Mano de obra operativa: $1.500.000    ║       Precio: $40k–90k COP     ║
║                                          ║       Modelo: venta directa /  ║
║  INVERSIÓN (amortización):               ║       consignación             ║
║  • Hardware cápsulas: ~$260k/nodo        ║                                ║
║    Amortización: 36 meses                ║  I4 — Cápsulas de suplementos ║
║  • Equipamiento laboratorio: $1.4M       ║       (Fase 3+)                ║
║    Amortización: 60 meses                ║       Precio: $35k–60k / 60u   ║
║                                          ║                                ║
║  ECONOMÍAS DE ESCALA:                    ║  I5 — Kits de cultivo hogar   ║
║  Al escalar a 10+ cápsulas:              ║       Precio: $80k–150k COP    ║
║  • Compra de insumos por volumen −30 %   ║       Modelo: venta única      ║
║  • Banco de cepas propio −80 % en semilla║                                ║
║  • Mano de obra diluida por cápsula      ║  I6 — Franquicia / licencia   ║
║  • Energía solar (Fase 3): −40 % consumo ║       del sistema (Fase 4+)    ║
╚══════════════════════════════════════════╩════════════════════════════════╝
```

### Desglose de los 9 bloques

#### Segmentos de clientes — detalle

| Segmento | Descripción | Tamaño estimado | Precio objetivo | Prioridad |
|---------|-------------|----------------|----------------|----------|
| **S1 — Restaurante gourmet** | Chefs que buscan producto premium, consistente, con historia del cultivo | ~200 en Medellín/Rionegro | $18k–25k/kg fresco | 🔴 Fase 1 |
| **S2 — Tienda naturista** | Buscan productos funcionales locales con historia verificable | ~80 tiendas Antioquia | $50k–120k/kg seco | 🔴 Fase 2 |
| **S3 — Consumidor directo** | Salud consciente, veganos, deportistas, interés en micoterapia | Creciente, sin cuantificar | $16k–30k/kg fresco | 🟡 Fase 1 paralelo |
| **S4 — Franquiciado potencial** | Emprendedor que quiere montar su propio laboratorio replicando el sistema | Nacional, difuso | $15M–50M COP setup | 🟢 Fase 4 |

#### Fuentes de ingreso — modelo de precios

| Fuente | Producto | Precio COP | Modelo | Margen estimado |
|--------|---------|-----------|--------|----------------|
| I1 | Orellana fresca (cat A, restaurante) | $18.000–$25.000/kg | Suscripción semanal | 65–72 % |
| I1 | Orellana fresca (cat B, plaza) | $12.000–$15.000/kg | Spot | 45–55 % |
| I1 | Melena de León fresca | $50.000–$80.000/kg | Spot / contrato | 70–80 % |
| I1 | Shiitake fresco | $25.000–$35.000/kg | Contrato semanal | 60–70 % |
| I2 | Reishi seco trozo | $80.000–$120.000/kg | Consignación / directo | 75–85 % |
| I2 | Cordyceps seco | $150.000–$300.000/kg | Directo / naturista | 80–90 % |
| I3 | Extracto doble reishi 100 ml | $45.000–$65.000 | Venta directa | 70–80 % |
| I4 | Cápsulas suplemento 60 u | $40.000–$60.000 | Naturistas / web | 75 % |
| I5 | Kit cultivo hogar | $100.000–$150.000 | Venta única | 60 % |
| I6 | Licencia sistema cápsula | $15M–$30M COP | Pago único + royalty | > 90 % |

---

## 2. Value Proposition Canvas

### Segmento 1 — Restaurante Gourmet

```
┌─────────────────────────────────┐   ┌──────────────────────────────────┐
│        PERFIL DEL CLIENTE       │   │          MAPA DE VALOR           │
├─────────────────────────────────┤   ├──────────────────────────────────┤
│                                 │   │                                  │
│  TRABAJOS (Jobs to be done)     │   │  PRODUCTOS Y SERVICIOS           │
│  ─────────────────────────────  │   │  ─────────────────────────────   │
│  • Conseguir ingredientes       │   │  • Hongos frescos entregados     │
│    premium de forma confiable   │   │    semanalmente con orden fija   │
│    y consistente                │   │  • Variedad amplia (6+ especies) │
│  • Construir propuesta          │   │    en una sola relación          │
│    gastronómica diferencial     │   │  • QR de trazabilidad por lote   │
│    ("farm-to-table")            │   │    para mostrar en menú          │
│  • Reducir tiempo de gestión    │   │  • Garantía de reposición en     │
│    de proveedores               │   │    24 h si hay inconformidad     │
│                                 │   │                                  │
│  DOLORES (Pains)                │   │  ALIVIADORES DE DOLOR            │
│  ─────────────────────────────  │   │  ─────────────────────────────   │
│  • Proveedores irregulares      │ ◄►│  • Contrato de suministro con    │
│    ("a veces hay, a veces no")  │   │    volumen y frecuencia fijos    │
│  • Calidad variable entre       │   │  • Parámetros IoT verificables   │
│    entregas                     │   │    garantizan misma calidad      │
│  • Hongos importados o de       │   │    en cada entrega               │
│    Bogotá llegan maltratados    │   │  • Producción local → entrega    │
│  • Solo 1–2 especies            │   │    en < 12 h desde cosecha       │
│    disponibles localmente       │   │  • Catálogo de 6+ especies       │
│  • No pueden contar la          │   │    de un solo proveedor          │
│    historia del producto        │   │  • Historia verificable del      │
│    al comensal                  │   │    cultivo para carta / redes    │
│                                 │   │                                  │
│  GANANCIAS (Gains)              │   │  CREADORES DE GANANCIAS          │
│  ─────────────────────────────  │   │  ─────────────────────────────   │
│  • Diferenciarse de la          │   │  • Contenido de marketing listo  │
│    competencia                  │   │    (fotos del proceso IoT,       │
│  • Fidelidad del comensal       │   │    historial de cultivo)         │
│    gracias a propuesta única    │   │  • Factura electrónica y         │
│  • Historia que contar          │   │    trazabilidad para clientes    │
│    ("cultivado en Guarne        │   │    que exigen certificados       │
│    con control IoT")            │   │  • Propuesta "de la cápsula      │
│  • Proveedor que responda       │   │    al plato" con QR              │
│    rápido                       │   │  • WhatsApp directo con el       │
│                                 │   │    productor — respuesta < 2 h   │
└─────────────────────────────────┘   └──────────────────────────────────┘

                    FIT: ✅ ALTO
  Los mayores dolores (irregularidad, calidad variable, una sola especie)
  son exactamente los que el sistema de cápsulas IoT resuelve por diseño.
```

---

### Segmento 2 — Consumidor de Suplementos Naturales

```
┌─────────────────────────────────┐   ┌──────────────────────────────────┐
│        PERFIL DEL CLIENTE       │   │          MAPA DE VALOR           │
├─────────────────────────────────┤   ├──────────────────────────────────┤
│                                 │   │                                  │
│  TRABAJOS (Jobs to be done)     │   │  PRODUCTOS Y SERVICIOS           │
│  ─────────────────────────────  │   │  ─────────────────────────────   │
│  • Mejorar salud de forma       │   │  • Extractos dobles de reishi,   │
│    natural y sostenida          │   │    cordyceps, melena de león     │
│  • Encontrar suplementos        │   │  • Polvo de hongos para batidos  │
│    colombianos de calidad       │   │  • Cápsulas de suplemento 60 u   │
│    (desconfía de los            │   │  • Certificación de proceso +    │
│    importados sin historia)     │   │    historial IoT del lote        │
│  • Saber qué consume y de       │   │                                  │
│    dónde viene exactamente      │   │  ALIVIADORES DE DOLOR            │
│                                 │   │  ─────────────────────────────   │
│  DOLORES (Pains)                │   │  • QR en cada producto muestra   │
│  ─────────────────────────────  │   │    el historial completo del     │
│  • Productos importados sin     │ ◄►│    cultivo (temp, HR, CO₂ reales)│
│    trazabilidad ni garantía     │   │  • Producción en Colombia sin    │
│  • No sabe si el hongo fue      │   │    intermediarios de importación │
│    cultivado con pesticidas     │   │  • Proceso sin pesticidas         │
│  • Precios muy altos en tienda  │   │    verificable en el historial   │
│  • Productos sin dosificación   │   │  • Venta directa del productor   │
│    clara ni asesoría            │   │    → precio justo sin markup     │
│  • No sabe cómo usarlos         │   │    de intermediario              │
│                                 │   │                                  │
│  GANANCIAS (Gains)              │   │  CREADORES DE GANANCIAS          │
│  ─────────────────────────────  │   │  ─────────────────────────────   │
│  • Sentirse parte de algo       │   │  • Comunidad educativa en        │
│    local y sostenible           │   │    Instagram y talleres          │
│  • Poder recomendar el          │   │    ("aprende a usar los hongos") │
│    producto con confianza       │   │  • Suscripción mensual con       │
│  • Recibir orientación          │   │    descuento y envío a domicilio │
│    sobre uso y dosis            │   │  • Contenido de recetas y        │
│                                 │   │    protocolos de uso             │
│                                 │   │  • Identidad "apoyo a productor  │
│                                 │   │    local colombiano"             │
└─────────────────────────────────┘   └──────────────────────────────────┘

                    FIT: ✅ ALTO
  La trazabilidad IoT es el diferenciador más poderoso en este segmento:
  ningún importador puede mostrar el historial real de cultivo de cada lote.
```

---

## 3. Lean Canvas — Ash Maurya

```
╔══════════════════════╦══════════════════════╦══════════════════════╗
║     PROBLEMA         ║     SOLUCIÓN         ║  PROPUESTA DE VALOR  ║
║                      ║                      ║  ÚNICA (UVP)         ║
║  Top 3 problemas     ║  Top 3 features      ║                      ║
║  del mercado:        ║  del producto:       ║  "El único hongo     ║
║                      ║                      ║  cultivado en        ║
║  1. Los hongos       ║  1. Cápsulas IoT     ║  Colombia que        ║
║  premium llegan      ║  con control de      ║  trae el historial   ║
║  irregulares o       ║  temp, HR, CO₂ y     ║  real de su cultivo  ║
║  maltratados desde   ║  luz por especie     ║  en un QR —          ║
║  Bogotá o importados ║  — producción        ║  producido a 30 min  ║
║                      ║  consistente         ║  de tu cocina."      ║
║  2. No hay           ║                      ║                      ║
║  trazabilidad real   ║  2. Perfil JSON      ║                      ║
║  en suplementos de   ║  por especie +       ║                      ║
║  hongos en Colombia  ║  QR de trazabilidad  ║                      ║
║  (importados sin     ║  descargable para    ║                      ║
║  historia)           ║  cada lote vendido   ║                      ║
║                      ║                      ║                      ║
║  3. El sistema de    ║  3. Sistema de       ║                      ║
║  producción de hongos ║  replicación        ║                      ║
║  en Colombia no      ║  ("playbook de       ║                      ║
║  escala ni se        ║  nueva sede") para   ║                      ║
║  replica fácilmente  ║  franquiciados       ║                      ║
╠══════════════════════╬══════════════════════╬══════════════════════╣
║ SEGMENTOS DE         ║  CANALES             ║ VENTAJA INJUSTA      ║
║ CLIENTES             ║                      ║ (Unfair Advantage)   ║
║                      ║  Awareness:          ║                      ║
║  Early adopters:     ║  • Instagram/TikTok  ║  1. El sistema IoT   ║
║                      ║    con proceso de    ║  con perfiles JSON   ║
║  • Chef de           ║    cultivo en vivo   ║  es open-source y    ║
║    restaurante que   ║  • Visita presencial ║  versionado en git — ║
║    ya compra hongos  ║    al invernadero    ║  la competencia no   ║
║    importados y      ║    (genera confianza)║  tiene este nivel de ║
║    está insatisfecho ║                      ║  datos por lote      ║
║    con la calidad    ║  Conversión:         ║                      ║
║                      ║  • WhatsApp Business ║  2. Ubicación:       ║
║  • Consumidor que    ║    con pedido directo║  Guarne a 30 min     ║
║    ya toma hongos    ║  • Mercado campesino ║  de Medellín —       ║
║    medicinales       ║    Guarne / Rionegro ║  frescura imposible  ║
║    importados y      ║                      ║  de igualar con      ║
║    quiere una        ║  Retención:          ║  producto importado  ║
║    alternativa local ║  • Suscripción       ║                      ║
║                      ║    semanal fija      ║  3. Replicabilidad:  ║
║  Segmentos futuros:  ║  • Contenido         ║  el "playbook de     ║
║  S2 tienda naturista ║    educativo IG      ║  sede" convierte el  ║
║  S4 franquiciados    ║  • QR en producto    ║  know-how en activo  ║
║                      ║    → landing página  ║  vendible            ║
╠══════════════════════╩══════════════════════╩══════════════════════╣
║  FLUJOS DE INGRESOS                ║  ESTRUCTURA DE COSTOS           ║
║                                    ║                                 ║
║  Corto plazo (Fase 1):             ║  Costos de adquisición          ║
║  • Venta de orellana fresca        ║  de clientes (CAC):             ║
║    Precio: $14k–$25k COP/kg        ║  • Mercado campesino: $0        ║
║    Frecuencia: semanal             ║  • Instagram orgánico: $0       ║
║    Margen: ~55–65 %                ║  • Visita a restaurante: $0     ║
║                                    ║                                 ║
║  Mediano plazo (Fase 2–3):         ║  Costos variables:              ║
║  • Melena de León, shiitake        ║  • Sustrato + semilla: $5k/kg   ║
║    Precio: $25k–$80k COP/kg        ║  • Empaque + distribución:$1k/kg║
║  • Extractos reishi/cordyceps      ║  • Energía: $150/kg             ║
║    Precio: $45k–$90k/frasco        ║                                 ║
║                                    ║  Costos fijos mensuales:        ║
║  Largo plazo (Fase 4+):            ║  • MO operativa: $1.500.000     ║
║  • Licencia de franquicia          ║  • Servicios públicos: $200.000 ║
║    Precio: $15M–$30M COP           ║  • Mantenimiento IoT: $100.000  ║
║    + royalty mensual               ║                                 ║
║  • Cápsulas de suplementos         ║  Punto de equilibrio mensual:   ║
║    Precio: $40k–$60k / 60 u        ║  • 120 kg/mes a $15k/kg        ║
║                                    ║    = $1.800.000 en ingresos     ║
╠════════════════════════════════════╩═════════════════════════════════╣
║  MÉTRICAS CLAVE (KPIs de tracción)                                  ║
║                                                                      ║
║  Producción:              Clientes:              Financiero:         ║
║  • BE% por especie        • Nº clientes activos  • Ingreso mensual   ║
║  • Tasa contaminación     • Tasa retención 90d   • Costo/kg prod.    ║
║  • Kg/mes producidos      • NPS de restaurantes  • Margen bruto      ║
║  • Ciclos completados     • Pedidos recurrentes  • Meses para ROI    ║
╚══════════════════════════════════════════════════════════════════════╝
```

---

## 4. Insights clave — comparación de los tres canvas

### Tensiones identificadas

| Tensión | Descripción | Cómo resolverla |
|---------|-------------|----------------|
| **Volumen vs. calidad** | El BMC muestra que S1 (restaurantes) necesita volumen constante, pero en Fase 1 la producción es limitada. Vender a demasiados clientes antes de escalar destruye la propuesta de valor. | Máximo 2–3 restaurantes ancla en Fase 1. Crecer en capacidad antes de ampliar cartera. |
| **B2B vs. D2C** | El BMC y el Lean Canvas revelan que el B2B (restaurantes) da volumen pero el D2C (consumidor) da margen. Gestionar los dos canales en paralelo con equipo pequeño es difícil. | En Fase 1: solo B2B. En Fase 2: añadir D2C con suscripción semanal ya que el sistema de pedidos es repetible. |
| **Hongos frescos vs. extractos** | El VPC del segmento naturista muestra que los extractos tienen mayor margen y más defensibilidad de marca, pero requieren Fase 3 de producción. El riesgo es intentar hacer las dos cosas demasiado rápido. | Desarrollar extractos solo cuando la producción de gourmet sea estable y rentable (criterio: 3 meses seguidos de margen > 40 %). |
| **Producto vs. plataforma** | La franquicia (I6) es la fuente de ingreso más escalable del BMC, pero la infraestructura (sistema IoT, perfiles JSON, playbook) aún no está validada en producción. Vender el sistema antes de probarlo es un riesgo reputacional alto. | Solo ofrecer franquicia después de 12 meses de operación continua documentada con datos reales. |

### Oportunidades no obvias

1. **El QR de trazabilidad es un canal de marketing gratuito** — cada hongo vendido en un restaurante lleva el QR al comensal, que puede seguir a Bichongos en Instagram o hacer su próximo pedido directo. El BMC no lo mapea explícitamente como canal, pero el Lean Canvas lo captura como ventaja injusta.

2. **El mercado campesino es el canal de validación más rápido y barato** — permite vender sin contrato, obtener feedback directo, y construir base de clientes D2C antes de tener una web app. Costo de adquisición: $0.

3. **La visita al invernadero es el cierre de ventas más efectivo para restaurantes** — ver las cápsulas con los datos en tiempo real en Grafana convierte la propuesta de valor en algo tangible. El VPC lo mapea como "creador de ganancia" pero debería ser el primer paso del proceso de ventas.

4. **El banco de cepas propio es la ventaja injusta más subestimada** — cuando Bichongos tenga sus propias cepas preservadas, el costo de semilla cae un 80 % y la dependencia de proveedores externos desaparece. Es el activo que más impacta el margen a largo plazo.

### Prioridad estratégica por fase

| Fase | Foco del modelo de negocio |
|------|---------------------------|
| **0 — Pre-lanzamiento** | Validar el canal: contactar 3 restaurantes, confirmar precio y frecuencia de compra antes de invertir en hardware |
| **1 — Piloto** | Un cliente ancla. Máxima calidad. Documentar todo. Construir el caso de éxito. |
| **2 — Escala gourmet** | 3–5 restaurantes + canal directo (WhatsApp). Primera producción de shiitake y melena. |
| **3 — Diversificación** | Extractos + tiendas naturistas. Primer producto de valor agregado. |
| **4 — Plataforma** | Franquicia del sistema. El know-how se convierte en el producto principal. |

---

*Bichongos · docs/negocio/canvas-modelos.md · v1.0 · 2026-06-30*
