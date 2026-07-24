# Diseño de Espacio — Sede Guarne (Bichongos)

**Espacio disponible:** Invernadero 7×14 m = 98 m²
**Área útil interna (zona cerrada):** 6×12 m = 72 m² (recomendado)
**Ubicación:** Guarne, Antioquia
**Versión:** 0.1 (borrador pre-diagnóstico)

> *Este diseño es provisional. El diseño final se entrega como parte del Componente 1 de la propuesta de consultoría con La Jobiteka.*
>
> *Nota (2026-07-24): este invernadero es la sede física de Bichongos (Épica 1 de `BACKLOG.md`), no un sitio aparte de un cliente. Juan (La Jobiteka), socio de Songo Sorhongo, está ejecutando la obra civil como parte del acuerdo de consultoría — ver `docs/negocio/propuesta-consultoria.md` y `docs/reuniones/`. El archivo se renombró de `diseno-espacio-jobiteka.md` para reflejar esto.*

---

## Distribución propuesta de zonas

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                        INVERNADERO 7 × 14 m                                 │
│                                                                               │
│  ┌──────────────────┬───────────────────┬───────────────────┐               │
│  │  SUSTRATO +       │   BODEGA +         │   POSTCOSECHA +   │               │
│  │  PASTEURIZACIÓN   │   INSUMOS          │   SECADO          │               │
│  │   ~10–12 m²       │   ~10 m²           │   ~10 m²          │  ZONA         │
│  │                   │                    │                   │  HÚMEDA /     │
│  │  [fogón]          │  [estantería]      │  [deshidratador]  │  PRODUCCIÓN   │
│  │  [olla/canecas]   │  [sustratos]       │  [mesa clasif.]   │               │
│  ├──────────────────┴───────────────────┬┴───────────────────┤               │
│  │                                       │                    │               │
│  │     FRUCTIFICACIÓN                    │   INCUBACIÓN       │  ZONA         │
│  │        ~16–18 m²                      │    ~12 m²          │  CONTROLADA   │
│  │                                       │                    │               │
│  │  [racks con bloques]                  │  [estantería]      │  (cápsulas    │
│  │  [humidificador]                      │  [oscuridad]       │   IoT aquí)   │
│  │  [extractor + ionizador]              │  [temp. pasiva]    │               │
│  │  [nodo IoT]                           │  [nodo IoT]        │               │
│  ├───────────────────────────────────────┴────────────────────┤               │
│  │                  INOCULACIÓN / ZONA LIMPIA                  │               │
│  │                          ~5 m²                              │  ZONA         │
│  │   [campana flujo laminar / mínimo: mesa + lámpara UV]       │  ASÉPTICA     │
│  │   [acceso restringido — solo personal capacitado]           │               │
│  └─────────────────────────────────────────────────────────────┘               │
│                                                                               │
│  ← Acceso principal (puerta de servicio) ·  Zona de descarga y materiales →  │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

## Zonas detalladas

### 1. Zona de sustrato y pasteurización (~10–12 m²)
**Función:** preparar y pasteurizar el sustrato antes de inoculación.

Equipos mínimos:
- Fogón (ya tienen)
- 2 canecas metálicas de 200 L (ya tienen)
- Mesa de trabajo (acero inox o madera resistente)
- Punto de agua
- Piso fácil de lavar (baldosa, cemento sellado, o similar)

Alternativa con más capacidad:
- Tolvadora horizontal o pasteurizador de bolsas
- Autoclave pequeña para inoculación con cámaras de flujo laminar

> *Prioridad: que el piso y las paredes sean lavables. Esta zona se ensucia regularmente.*

### 2. Zona de inoculación / zona limpia (~5 m²)
**Función:** inocular los sustratos pasteurizados con semilla. La zona más crítica de bioseguridad.

Equipos mínimos:
- Mesa limpia (desinfección con alcohol 70%)
- Lámpara UV germicida (30–60 min antes de trabajar)
- EPP: guantes, tapabocas, bata

Inversión adicional cuando escalen:
- Campana de flujo laminar DIY (~$800.000–$1.500.000)
- Cabina HEPA filtrada

> *Paredes y piso lavables. Debe poder quedar oscura para el uso de la UV. Ventanas con cortinas o selladas.*

### 3. Zona de incubación (~12 m²)
**Función:** mantener los bloques inoculados a temperatura controlada durante la colonización micelial (21–24 °C para orellana).

Equipos mínimos:
- Estanterías metálicas (3–4 niveles)
- Termómetro de ambiente manual (inicio)
- Oscuridad completa (bloquear luz)
- Ventilación pasiva mínima

Con IoT (recomendado):
- Nodo ESP32 + SHT31 (temperatura y humedad)
- Relay para ventilador de renovación de aire
- Dashboard Grafana con alertas Telegram

Capacidad estimada:
- 3 estanterías 120×40 cm × 4 niveles = ~192 bloques simultáneos
- Rotación cada 21–28 días (orellana)

### 4. Zona de fructificación (~16–18 m²)
**Función:** condiciones para el crecimiento de los cuerpos frutales. La zona más visible y húmeda del laboratorio.

Equipos mínimos:
- 3–5 racks de fructificación
- Humidificador ultrasónico (tipo niebla)
- Extractor de aire con filtro anti-polvo
- Iluminación LED (fotoperíodo 12/12 para algunas especies)
- Termómetro + higrómetro manual (inicio)

Con IoT (recomendado):
- Nodo ESP32 + SHT31 + BH1750 + MH-Z19B
- Control automático de humidificador, extractor y LED
- Perfiles JSON por especie cargados en SPIFFS

Condiciones objetivo (orellana):
- Temperatura: 14–20 °C
- Humedad relativa: 85–95%
- CO₂: < 1.000 ppm
- Luz: 12h/día, 200–500 lux

### 5. Zona de postcosecha y secado (~10 m²)
**Función:** clasificar, empacar y/o deshidratar la cosecha.

Equipos mínimos:
- Mesa de trabajo
- Báscula de cocina (±1 g)
- Bolsas/empaques para distribución
- Etiquetadora o rotulador manual

Opcional según canales de venta:
- Deshidratador ($350.000–$1.500.000)
- Selladora al vacío ($200.000–$800.000)
- Cámara fría de 1 puerta (para fresco)

### 6. Bodega e insumos (~10 m²)
**Función:** almacén de materias primas (paja, salvado, bolsas) y productos de limpieza.

- Estanterías
- Lugar fresco y seco
- Separado de la zona húmeda de producción
- Acceso de carga sin pasar por zona limpia (si el diseño lo permite)

---

## Flujo de materiales

```
                    ENTRADA INSUMOS (paja, salvado, semilla)
                              ↓
              ┌───────────────────────────────┐
              │   SUSTRATO + PASTEURIZACIÓN   │
              └───────────────┬───────────────┘
                              ↓ (sustrato enfriado, ~12 h)
              ┌───────────────────────────────┐
              │       INOCULACIÓN             │ ← semilla certificada
              └───────────────┬───────────────┘
                              ↓ (bloques sellados)
              ┌───────────────────────────────┐
              │         INCUBACIÓN            │ (21–28 días)
              └───────────────┬───────────────┘
                              ↓ (micelio visible ≥ 80%)
              ┌───────────────────────────────┐
              │       FRUCTIFICACIÓN          │ (10–14 días)
              └───────────────┬───────────────┘
                              ↓
              ┌───────────────────────────────┐
              │    POSTCOSECHA / EMPAQUE      │ → distribución fresca
              │    SECADO (opcional)          │ → distribución seca
              └───────────────────────────────┘
```

---

## Consideraciones de obra

### Zona limpia (inoculación)
- Paredes: pintura epóxica o azulejo hasta 1,5 m de altura
- Piso: baldosa antideslizante o epóxico
- Sellado de grietas y juntas
- Puerta con cierre hermético (no necesita ser de laboratorio — solo sin huecos)

### Zona húmeda (fructificación)
- Piso con drenaje o pendiente hacia desagüe
- Paredes lavables hasta al menos 2 m
- Ventana de extracción + filtro anti-polvo

### Eléctrica
- Un circuito independiente para el área de producción (recomendado)
- Mínimo 4 tomas en fructificación: humidificador, extractor, LED, IoT gateway
- Protección GFCI (diferencial) en zonas húmedas

### Agua
- Un punto de agua cerca de pasteurización
- Otro punto cerca de inoculación (para lavado de manos)
- No se necesita agua potable en fructificación (solo el humidificador)

---

## Opciones de tamaño del área cerrada

| Opción | Área | Comentario |
|--------|------|-----------|
| 5×10 m = 50 m² | Mínima | Zona limpia muy ajustada; no ideal |
| 5×12 m = 60 m² | Viable | Funciona con diseño eficiente |
| **6×12 m = 72 m²** | **Recomendado** | Permite crecer sin remodelar |
| 6×14 m = 84 m² | Óptimo | Solo si el invernadero lo permite |

> *Recomendación: 6×12 m. Con 72 m² se pueden acomodar todas las zonas cómodamente y escalar a 10 racks de fructificación sin obra adicional.*

---

## Capacidad productiva estimada (escenario mínimo)

| Variable | Valor |
|---------|-------|
| Bloques por lote inicial | 50–100 |
| Peso sustrato por bloque | 1 kg (paja) |
| BE% orellana (realista) | 80–100% |
| Rendimiento por bloque | 800–1.000 g fresco |
| Producción por lote | 40–100 kg |
| Precio restaurante | $18.000–$22.000/kg |
| Ingreso por lote | $720.000–$2.200.000 |
| Lotes por mes (escalonado, 3×) | 3 |
| **Ingreso mensual estimado** | **$2.1M–$6.6M** |

---

*Bichongos · docs/negocio/diseno-espacio-jobiteka.md · v0.1 · 2026-06-30*
*Sujeto a actualización tras diagnóstico técnico presencial (Componente 1)*
