# Propuesta de Consultoría — Laboratorio de Hongos

**Para:** Juan y equipo (La Jobiteka)
**De:** Bichongos — Sergio Monsalve
**Fecha:** Julio 2026
**Versión:** 1.1 (ajustada post-reunión 30 jun)

---

## El proyecto

Diseño, montaje y puesta en marcha de un laboratorio de cultivo de hongos gourmet y funcionales en invernadero de 7×14 m en Guarne, Antioquia. Punto de partida con orellana y escalamiento progresivo hacia especies de mayor valor.

---

## Componentes de la propuesta

### Componente 1 — Diagnóstico y diseño técnico
**Valor: $3.500.000 COP · Duración: 1–2 semanas**

Incluye:
- Visita técnica al espacio (diagnóstico de una sola jornada)
- Levantamiento de información: condiciones ambientales, acceso a agua/energía, restricciones constructivas
- Definición de capacidad de producción realista según el espacio
- Diseño de distribución de áreas (plano con zonas modulares)
- Diseño del flujo operativo: sustrato → pasteurización → inoculación → incubación → fructificación → postcosecha
- Selección de equipos y materiales constructivos recomendados
- Diseño de ventilación y control ambiental por zona
- Plan de bioseguridad básico
- Cronograma de implementación detallado
- **Entregable:** documento técnico completo + planos de distribución

> *Nota: este componente puede hacerse en una sola visita dado el contexto que ya conocemos del espacio y del proyecto.*

---

### Componente 2 — Acompañamiento de adecuación
**Valor: $3.500.000 COP · Duración: 1–3 meses (ejecución por el cliente)**

Incluye:
- Entrega de toda la información técnica necesaria para que el equipo ejecute la adecuación
- Revisión de avances por fotos/video (remoto)
- Resolución de dudas durante la construcción
- Visita de verificación al finalizar la adecuación
- Aprobación para arrancar el primer lote

> *El equipo de La Jobiteka ejecuta la obra. Nosotros no somos constructores — somos el criterio técnico que dice qué sí y qué no.*

---

### Componente 3 — Capacitación con primer lote
**Valor: $8.000.000 COP · Duración: 2 meses**

Capacitación haciendo — el aprendizaje ocurre ejecutando el primer ciclo real de orellana:

**Mes 1:**
- Selección y preparación del sustrato (paja u otros)
- Pasteurización (métodos disponibles según el equipo existente)
- Inoculación en zona limpia (técnica estéril básica)
- Registro de lote, identificación, trazabilidad
- Primer lote en incubación + monitoreo IoT

**Mes 2:**
- Inducción a fructificación
- Manejo de condiciones en cápsula durante fructificación
- Primera cosecha + clasificación + empaque
- Cálculo de eficiencia biológica (BE%)
- Análisis del ciclo: qué salió bien, qué ajustar

**Modalidades posibles:**
- Individual: solo el equipo de La Jobiteka
- Grupal: con Alejo, Edward u otros → distribuye costo, enriquece la experiencia

---

### Componente 4 — Manuales y protocolos operativos
**Valor: $2.000.000 COP · Entrega al finalizar el Componente 3**

Incluye:
- SOP de pasteurización adaptado al equipo del espacio
- SOP de inoculación
- SOP de postcosecha y clasificación
- Protocolos de limpieza y bioseguridad
- Formatos de registro de lote (papel + digital)
- Perfil JSON de orellana cargado en el sistema IoT
- Dashboard Grafana configurado con los parámetros del espacio

---

## Resumen de honorarios

| Componente | Valor | Tiempo estimado |
|-----------|-------|----------------|
| 1. Diagnóstico y diseño técnico | $3.500.000 | Semana 1–2 |
| 2. Acompañamiento de adecuación | $3.500.000 | Meses 1–3 |
| 3. Capacitación con primer lote | $8.000.000 | Meses 4–5 |
| 4. Manuales y protocolos | $2.000.000 | Al finalizar mes 5 |
| **Total honorarios** | **$17.000.000** | **~5–6 meses** |

**Forma de pago sugerida:**
- 30% al inicio del proyecto ($5.100.000)
- 30% al finalizar la adecuación y antes de arrancar capacitación ($5.100.000)
- 40% al entregar manuales y primer lote completado ($6.800.000)

---

## Opción: administración del cultivo (mensual, opcional)

Si el equipo de La Jobiteka desea acompañamiento continuo después del primer lote:

| Plan | Descripción | Valor mensual |
|------|-------------|--------------|
| Básico | 2 visitas al mes + soporte remoto | $2.800.000 |
| Intermedio | 1 visita semanal + soporte remoto | $4.200.000 |
| Integral | Acompañamiento permanente | $5.800.000 |

---

## Presupuesto de inversión estimado para La Jobiteka

> *Estos valores son estimados. Se entregarán cotizaciones reales en el Componente 1.*

### Adecuación del espacio (una vez)

| Ítem | Estimado COP |
|------|-------------|
| Divisiones y acabados zona limpia | $3.000.000–$6.000.000 |
| Instalación eléctrica y puntos de agua | $2.000.000–$4.000.000 |
| Piso epóxico zonas húmedas | $1.500.000–$3.000.000 |
| Campana de flujo laminar DIY | $800.000–$1.500.000 |
| **Subtotal adecuación** | **$7.300.000–$14.500.000** |

### Equipos de producción (una vez)

| Ítem | Escenario mínimo | Escenario completo |
|------|-----------------|-------------------|
| Cápsulas de fructificación (racks) | $2.400.000 (3 racks) | $8.000.000 (10 racks) |
| Nodo IoT por cápsula (ESP32 + sensores) | $800.000 (por nodo) | Escala con cápsulas |
| Gateway Raspberry Pi | $780.000 | $780.000 |
| Olla a presión / autoclave | $400.000 | $2.500.000 (autoclave) |
| Deshidratador | $350.000 | $1.500.000 |
| Elementos de laboratorio | $500.000 | $1.000.000 |
| **Subtotal equipos** | **~$5.200.000** | **~$14.000.000** |

### Insumos primer ciclo (100 bloques orellana)

| Ítem | Valor |
|------|-------|
| Sustrato (paja, salvado, cal) | $280.000 |
| Semilla orellana certificada | $420.000 |
| Bolsas PP + filtros | $110.000 |
| Desinfectantes y EPP | $98.000 |
| **Subtotal insumos** | **$908.000** |

### Resumen inversión total

| Escenario | Inversión cliente | + Honorarios Bichongos | Total |
|---------|-----------------|----------------------|-------|
| **Mínimo** (arrancar, validar) | $13.400.000 | $17.000.000 | **$30.400.000** |
| **Intermedio** (producción real desde el inicio) | $29.400.000 | $17.000.000 | **$46.400.000** |
| **Completo** (escala con inversión externa) | $65.000.000+ | $17.000.000 | **$82.000.000+** |

---

## Dos modelos de relación posibles

### Modelo A — Consultoría pura
La Jobiteka es el dueño 100% del negocio. Bichongos cobra honorarios por los servicios descritos arriba. Sin participación en las utilidades del cultivo.

**Ventaja:** relación simple y clara.
**Para quién:** si La Jobiteka ya tiene capital propio y quiere controlar el negocio.

### Modelo B — Sociedad con participación accionaria
Bichongos entra como socio tecnológico con participación en la empresa nueva que se crea. En lugar de cobrar todos los honorarios, parte del valor aportado (conocimiento, sistema IoT, perfiles, documentación) se convierte en acciones.

Esquema posible:
- La Jobiteka: X%
- Bichongos: Y%
- Inversionista externo: Z% (aporta el capital de infraestructura)

**Ventaja:** Bichongos tiene incentivo a que el negocio funcione bien; La Jobiteka reduce el costo inicial de honorarios; el inversionista entra con capital real.
**Para quién:** si La Jobiteka no tiene todo el capital y quiere crecer más rápido con un tercer socio.

> En el Modelo B, los honorarios de consultoría se reducen o eliminan a cambio de la participación pactada.

---

## Cronograma propuesto

```
Semana 1–2   │ Componente 1 — Diagnóstico y diseño
Semana 3     │ Entrega de planos y documento técnico
Mes 1–3      │ Componente 2 — Adecuación (ejecutada por La Jobiteka)
Mes 3        │ Verificación técnica del espacio terminado
Mes 4        │ Inicio capacitación — preparación sustrato e inoculación
Mes 4–5      │ Primer lote en incubación con monitoreo IoT
Mes 5        │ Primera cosecha + evaluación BE%
Mes 5        │ Entrega de manuales (Componente 4)
Mes 6+       │ Segunda producción autónoma del equipo
             │ (opcional: administración mensual Bichongos)
```

---

## Preguntas abiertas para definir en reunión

- [ ] ¿Escenario mínimo (validar) o escenario completo (inversión grande desde el inicio)?
- [ ] ¿Modelo A (consultoría pura) o Modelo B (sociedad + inversionista externo)?
- [ ] ¿Capacitación individual o grupal (con Alejo, Edward, otros)?
- [ ] ¿Quién va a operar el cultivo día a día? ¿Persona contratada o alguien del equipo?
- [ ] ¿Tienen presupuesto propio para la inversión o necesitan un tercero?
- [ ] ¿Cuál es el objetivo principal: producción para venta, aprendizaje, o proyecto demostrativo?
- [ ] ¿Tienen ya clientes o canales de venta identificados?

---

*Bichongos · docs/negocio/propuesta-consultoria.md · v1.1 · 2026-06-30*
