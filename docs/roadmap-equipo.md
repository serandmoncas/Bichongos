# Roadmap de Habilidades del Equipo — Bichongos

> Guía progresiva de conocimientos y habilidades para cultivar todas las especies del proyecto, de menor a mayor dificultad. Cada etapa agrega capacidades nuevas sobre las anteriores.

---

## Mapa de competencias

El equipo necesita dominar tres áreas en paralelo:

| Área | ¿Qué cubre? |
|------|------------|
| **Micología** | Biología fúngica, técnicas de cultivo, identificación de cepas y contaminantes |
| **IoT / Electrónica** | Montaje de cápsulas, sensores, firmware ESP32, automatización |
| **Operaciones de lab** | Esterilización, manejo de sustratos, cosecha, postcosecha, trazabilidad |

---

## Etapa 0 — Fundamentos (Mes 1–2)

**Objetivo:** sentar las bases antes de cultivar. Sin estas habilidades, todo lo demás falla.

### Micología básica

- [ ] Entender el ciclo de vida de un hongo: micelio → primordio → cuerpo fructífero → espora
- [ ] Diferencia entre saprofito, micorrícico y parásito
- [ ] Qué es una cepa y cómo se preserva (en agar, en grano, en frío)
- [ ] Contaminantes más comunes: Trichoderma, Neurospora, bacterias — cómo identificarlos
- [ ] Concepto de eficiencia biológica (BE %)

### IoT / Electrónica básica

- [ ] Instalar y usar el IDE de Arduino
- [ ] Conectar un ESP32 a la computadora y subir un "Hello World"
- [ ] Leer un sensor DHT22 o SHT31 con el ESP32
- [ ] Entender qué es MQTT y cómo funciona el modelo publicar/suscribir
- [ ] Instalar Mosquitto en Raspberry Pi y publicar el primer mensaje

### Operaciones de laboratorio

- [ ] Protocolo de limpieza y desinfección de superficies
- [ ] Uso correcto de alcohol isopropílico, hipoclorito y luz UV
- [ ] Flujo de tráfico en el laboratorio: sucio → limpio (nunca al revés)
- [ ] Cómo usar guantes y mascarilla sin contaminar el proceso
- [ ] Registro básico de lotes: fecha, cepa, sustrato, cantidad

**Recursos:**
- Libro: *The Mushroom Cultivator* — Stamets & Chilton (capítulos 1–3)
- Video: "Mushroom Growing Basics" — MushroomMan Stevie (YouTube)
- Práctica: observar y registrar el crecimiento de micelio en distintos sustratos

---

## Etapa 1 — Principiante: Orellana (Mes 2–5)

**Objetivo:** dominar el ciclo completo de la especie más forgiving del proyecto.

### Micología — Orellana

- [ ] Características de Pleurotus ostreatus, P. djamor y P. citrinopileatus
- [ ] Parámetros ideales: temperatura, humedad, CO₂, luz (ver [ficha técnica](especies/N1-orellana.md))
- [ ] Sustratos compatibles: paja de arroz, café, aserrín, tusa de maíz
- [ ] Reconocer la colonización sana vs. contaminada
- [ ] Identificar el momento óptimo de cosecha (bordes del sombrero aún enrollados hacia abajo)
- [ ] Manejo de oleadas: cuándo remojar el bloque para inducir la 2.ª fructificación

### IoT — Primera cápsula

- [ ] Montar la primera cápsula estándar (rack + cortina PVC)
- [ ] Cablear ESP32 con SHT31 y módulo relé
- [ ] Programar firmware básico: leer sensor → controlar relé según umbral
- [ ] Configurar Node-RED: flujo simple de control de humedad
- [ ] Ver datos en Grafana: primer dashboard con temperatura y humedad en tiempo real
- [ ] Recibir primera alerta por Telegram cuando la humedad baje del límite

### Operaciones

- [ ] Pasteurización de paja en caliente (80 °C × 1.5 h)
- [ ] Inoculación en bolsa con semilla de grano
- [ ] Cálculo de la receta: relación sustrato seco / agua / semilla
- [ ] Registro completo de lote: datos de entrada, parámetros monitoreados, peso en cosecha
- [ ] Calcular BE% del primer lote

**Hito:** producir y cosechar el primer lote de orellana con datos registrados en Grafana.

---

## Etapa 2 — Intermedio: Shiitake, Melena de León, Portobello (Mes 5–12)

**Objetivo:** agregar especies con sustratos y técnicas más exigentes. Dominar el trabajo en agar.

### Micología — Nivel 2

- [ ] Diferencias de sustrato entre orellana (paja), shiitake (aserrín de madera dura) y portobello (compost)
- [ ] Técnica de bloque compactado para shiitake (no bolsa suelta)
- [ ] Choque de inducción: frío o inmersión en agua fría para shiitake
- [ ] Capa de casing para portobello/crimini: qué es, cómo aplicarla, por qué importa
- [ ] Por qué la melena de León produce "dientes" en vez de pompones (exceso de CO₂) y cómo evitarlo
- [ ] Cultivo básico en agar: preparar MEA (Malt Extract Agar), esterilizar, verter en placas, inocular
- [ ] Cómo clonar tejido frutal en agar

### IoT — Sistema multi-cápsula

- [ ] Configurar perfil JSON por especie y etapa
- [ ] Node-RED: cargar perfil y adaptar umbrales automáticamente
- [ ] Gestionar múltiples cápsulas desde un mismo gateway
- [ ] Configurar Firebase: sincronización de datos en nube
- [ ] Bot de Telegram: alertas diferenciadas por cápsula y tipo de evento
- [ ] Dashboard Grafana: múltiples paneles por cápsula

### Operaciones

- [ ] Esterilización en olla a presión (121 °C × 2.5 h): grano para semilla, aserrín suplementado
- [ ] Preparar semilla de grano (maíz, trigo, centeno)
- [ ] Compostaje en dos fases para Agaricus (pasteurización fase I + acondicionamiento fase II)
- [ ] Manejo de deshidratador: curvas de temperatura para hongos gourmet (50–60 °C, < 8 % humedad)
- [ ] Empaque al vacío y etiquetado para venta

**Hito:** producir simultáneamente tres especies distintas en cápsulas independientes con perfiles JSON separados.

---

## Etapa 3 — Avanzado: Enoki, Reishi, Maitake, Cola de Pavo (Mes 12–20)

**Objetivo:** dominar cápsulas con climatización activa y especies de ciclos largos.

### Micología — Nivel 3

- [ ] Enoki: por qué necesita frío (7–12 °C) y CO₂ elevado. Fisiología del tallo largo
- [ ] Reishi: ciclo largo, doble etapa de fructificación (antler → cap), cosecha del esporocarpo
- [ ] Maitake: reconocer el ritmo de colonización ultra-lento, paciencia y registro largo plazo
- [ ] Cola de Pavo: diferencia entre cuerpo fructífero para extracto vs. consumo fresco
- [ ] Cultivo en agar avanzado: aislar contaminantes, reconocer sectores de la placa
- [ ] Cultivo líquido (LC): preparar caldo de miel o extracto de malta, inocular, agitar, usar como semilla

### IoT — Climatización activa

- [ ] Integrar mini split inverter al sistema de control (relé + sensor de temperatura en la cápsula)
- [ ] Control PID básico en Node-RED: evitar ciclos rápidos de encendido/apagado
- [ ] Cápsula de frío para Enoki: aislamiento térmico adicional, gestión del condensado
- [ ] Cápsula de calor para Reishi: calefactor + control de temperatura ±1 °C
- [ ] Logs de largo plazo en InfluxDB: análisis de 16 semanas de datos para maitake
- [ ] Alertas por ausencia de datos (sensor caído o ESP32 sin conexión)

### Operaciones

- [ ] Procesamiento de Reishi: secado, molido, extracción dual (agua + alcohol)
- [ ] Procesamiento de Cola de Pavo: decocción, tintura, encapsulado
- [ ] Control de calidad: pruebas de humedad residual en producto seco (< 10 %)
- [ ] Diseño de empaque y etiquetado para suplementos (requisitos INVIMA)

**Hito:** primera cápsula de Reishi cosechada y procesada en polvo para venta. Primera cápsula de Enoki con sistema de frío activo funcionando.

---

## Etapa 4 — Experto: Cordyceps, Psilocybe, Nuevas Sedes (Mes 20+)

**Objetivo:** dominar las especies más técnicas y replicar el modelo en una segunda sede.

### Micología — Nivel 4

- [ ] Cordyceps militaris: ciclo de inducción con luz, manejo de sustrato de arroz o pupas, cosecha del estroma
- [ ] Psilocybe: protocolo completo bajo marco legal de investigación; registro riguroso; aislamiento de zona
- [ ] Aislamiento monoespórico: crear una cepa nueva desde impresión de esporas en agar
- [ ] Banco de cepas: preservación en agar inclinado, en grano sellado y en glycerol a -80 °C
- [ ] Análisis de rendimiento: comparar cepas diferentes de la misma especie

### IoT — Multi-sede

- [ ] Diseño de arquitectura multi-gateway: varios RPi reportando a un mismo Firebase
- [ ] Dashboard consolidado: ver todas las sedes en una sola interfaz
- [ ] Empaquetado del "kit de nueva sede": hardware + firmware + guía de instalación
- [ ] OTA (Over The Air) updates: actualizar firmware de todos los ESP32 remotamente
- [ ] API REST: integrar el sistema IoT con la web app de gestión de lotes

### Operaciones

- [ ] Replicar la adecuación del espacio en una nueva ubicación usando el playbook documentado
- [ ] Formar a nuevo personal siguiendo este roadmap desde la Etapa 0
- [ ] Auditoría de trazabilidad: verificar que cada lote tiene registro completo de parámetros

**Hito:** segunda sede operando con las mismas cápsulas y perfiles JSON que la sede piloto.

---

## Tabla de resumen de habilidades

| Habilidad | Etapa | Área |
|-----------|-------|------|
| Higiene de laboratorio | 0 | Operaciones |
| Ciclo de vida fúngico | 0 | Micología |
| ESP32 + sensor SHT31 | 0 | IoT |
| MQTT + Mosquitto | 0 | IoT |
| Pasteurización de paja | 1 | Operaciones |
| Inoculación en bolsa | 1 | Micología |
| Primera cápsula + Node-RED | 1 | IoT |
| Dashboard Grafana | 1 | IoT |
| Esterilización en autoclave | 2 | Operaciones |
| Semilla de grano | 2 | Operaciones |
| Cultivo en agar | 2 | Micología |
| Multi-cápsula + perfiles JSON | 2 | IoT |
| Firebase + Telegram | 2 | IoT |
| Cultivo líquido | 3 | Micología |
| Climatización activa (frío / calor) | 3 | IoT |
| Control PID básico | 3 | IoT |
| Procesamiento de extractos | 3 | Operaciones |
| Aislamiento monoespórico | 4 | Micología |
| Banco de cepas | 4 | Micología |
| Multi-sede IoT | 4 | IoT |
| OTA firmware updates | 4 | IoT |
| Formación de nuevo personal | 4 | Operaciones |

---

## Recursos de aprendizaje recomendados

| Recurso | Tipo | Etapas |
|---------|------|--------|
| *The Mushroom Cultivator* — Stamets & Chilton | Libro | 0–2 |
| *Growing Gourmet and Medicinal Mushrooms* — Stamets | Libro | 0–4 |
| *Organic Mushroom Farming* — Cotter | Libro | 1–3 |
| Shroomery.org — foros técnicos | Web | 1–4 |
| r/MushroomGrowing | Comunidad | 1–3 |
| ESP32 Arduino Core Docs | Documentación | 0–4 |
| Node-RED Docs | Documentación | 1–3 |
| "Agar Work Masterclass" — Mycology Simplified (YouTube) | Video | 2 |
| "Liquid Culture Guide" — MushroomMan Stevie (YouTube) | Video | 3 |

---

*Bichongos · docs/roadmap-equipo.md · Actualizado: 2026-06-30*
