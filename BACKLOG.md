# BACKLOG — Bichongos

> Registro de todas las funcionalidades, tareas y mejoras del proyecto. Organizado por épica y fase. Prioridad: 🔴 Alta · 🟡 Media · 🟢 Baja

**Última actualización:** 2026-07-23
**Estado del proyecto:** Firmware (`firmware/capsula_core/`) y gateway (`gateway/`) implementados y compilando (ver `CLAUDE.md`). Infraestructura física (Fase 1) sigue pendiente — no hay cápsula construida todavía.

---

## Estado General

| Épica | Total tareas | Completadas | En progreso | Pendientes |
|-------|-------------|------------|-------------|-----------|
| E1 — Infraestructura Física | 16 | 3 | 0 | 13 |
| E2 — IoT / Firmware | 20 | 18 | 0 | 2 |
| E3 — Gateway & Dashboard Local | 11 | 10 | 0 | 1 |
| E4 — Nube & Alertas | 6 | 0 | 0 | 6 |
| E5 — Web App | 14 | 0 | 0 | 14 |
| E6 — App Móvil | 6 | 0 | 0 | 6 |
| E7 — Módulo Financiero | 8 | 0 | 0 | 8 |
| E8 — Multi-sede | 6 | 0 | 0 | 6 |
| E9 — Producción / Cultivo | 23 | 0 | 0 | 23 |
| E10 — Documentación | 28 | 27 | 0 | 1 |
| E11 — Validación Comercial | 6 | 0 | 0 | 6 |
| E12 — Marco Legal & Calidad | 5 | 0 | 0 | 5 |
| E13 — Seguridad IoT | 6 | 6 | 0 | 0 |
| E14 — Plan de Negocio | 4 | 4 | 0 | 0 |
| E15 — Consultoría Clientes | 18 | 3 | 0 | 15 |
| **Total** | **177** | **71** | **0** | **106** |

> Conteo recalculado programáticamente contando los checkmarks reales de cada tabla, no a mano —
> la tabla anterior tenía errores aritméticos genuinos (no solo desactualización): E1 decía 0
> completadas cuando F1-13/14/15 ya estaban ✅, E10 no incluía las 3 fichas de especie documentadas
> sin fila de backlog (ver DOC-25 a DOC-27).

---

## ÉPICA 1 — Infraestructura Física

> Construcción y adecuación del invernadero piloto en Guarne.

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| F1-01 | Sellar piso con pintura epoxi (zonas B, C, D, E, F) | 🔴 | 1 | 🔲 |
| F1-02 | Instalar divisiones de PVC entre zonas | 🔴 | 1 | 🔲 |
| F1-03 | Instalar circuito eléctrico 220V para autoclave | 🔴 | 1 | 🔲 |
| F1-04 | Instalar protección GFCI en zonas húmedas | 🔴 | 1 | 🔲 |
| F1-05 | Construir primera cápsula Mini (nevera modificada) para I+D | 🔴 | 1 | 🔲 |
| F1-06 | Construir 3 cápsulas Rack para producción de orellana | 🔴 | 1 | 🔲 |
| F1-07 | Montar campana de flujo laminar DIY (zona D) | 🔴 | 1 | 🔲 |
| F1-08 | Instalar extractor + filtro HEPA en zona B | 🟡 | 1 | 🔲 |
| F1-09 | Instalar deshidratador en zona C | 🟡 | 1 | 🔲 |
| F1-10 | Construir cápsula Estándar para Shiitake | 🟡 | 2 | 🔲 |
| F1-11 | Construir cápsula Enoki (Tipo 1 Mini — nevera modificada, reutiliza el compresor) | 🟢 | 3 | 🔲 |
| F1-12 | Construir cápsula con calefacción para Reishi / Cordyceps | 🟢 | 3 | 🔲 |
| F1-13 | Levantar BOM real con precios en COP (cotizar Medellín + AliExpress) | 🔴 | 0 | ✅ |
| F1-14 | Crear diagrama eléctrico de la primera cápsula (Fritzing o KiCad) | 🔴 | 1 | ✅ |
| F1-15 | Diseñar plan de red WiFi del invernadero (cobertura, IPs estáticas por nodo) | 🟡 | 1 | ✅ |
| F1-16 | Medir línea de base ambiental real del invernadero (temp/HR/CO₂ durante 7 días) | 🔴 | 0 | 🔲 |

---

## ÉPICA 2 — IoT / Firmware ESP32

> Firmware base y lógica de control parametrizada por perfil JSON.

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| IOT-01 | Configurar IDE Arduino + librerías (PubSubClient, ArduinoJson, Wire) | 🔴 | 1 | 🔲 |
| IOT-02 | Firmware: lectura de sensor SHT31 (temp + humedad) | 🔴 | 1 | ✅ |
| IOT-03 | Firmware: control de relés (humidificador, extractor, calefactor, LED) | 🔴 | 1 | ✅ |
| IOT-04 | Firmware: lógica de control por umbrales (ON/OFF simple) | 🔴 | 1 | ✅ |
| IOT-05 | Firmware: carga de perfil JSON desde SPIFFS | 🔴 | 1 | ✅ |
| IOT-06 | Firmware: publicación de datos vía MQTT | 🔴 | 1 | ✅ |
| IOT-07 | Firmware: lectura de sensor MH-Z19B (CO₂) | 🔴 | 1 | ✅ |
| IOT-08 | Firmware: lectura de sensor BH1750 (luz) | 🟡 | 1 | ✅ |
| IOT-09 | Firmware: lectura de sensor DS18B20 (temp sustrato) | 🟡 | 1 | ✅ |
| IOT-10 | Firmware: modo seguro (continúa operando si pierde WiFi) | 🔴 | 1 | ✅ |
| IOT-11 | Firmware: alertas MQTT si sensor fuera de rango crítico | 🔴 | 1 | ✅ |
| IOT-12 | Firmware: protección de relés (tiempo mínimo entre encendidos) | 🔴 | 1 | ✅ |
| IOT-13 | Firmware: timer de iluminación (ciclo luz/oscuridad por perfil) | 🟡 | 1 | ✅ |
| IOT-14 | Firmware: contador de días por etapa y notificación de fin de etapa | 🟡 | 2 | ✅ |
| IOT-15 | Firmware: OTA updates (actualización remota del firmware) | 🟢 | 2 | ✅ |
| IOT-16 | Firmware: soporte de múltiples perfiles (cambio de etapa remoto vía MQTT) | 🟢 | 2 | ✅ |
| IOT-17 | Crear `config.h.example` con template de credenciales WiFi/MQTT | 🔴 | 1 | ✅ |
| IOT-18 | Probar firmware en cápsula Mini con orellana (primer ciclo real) | 🔴 | 1 | 🔲 |
| IOT-19 | Definir y documentar protocolo de calibración de sensores (SHT31, MH-Z19B) | 🔴 | 1 | ✅ |
| IOT-20 | Escribir spec del modo seguro: comportamiento del ESP32 sin WiFi y sin MQTT | 🔴 | 1 | ✅ |

---

## ÉPICA 3 — Gateway & Dashboard Local (Raspberry Pi)

> Instalación y configuración del gateway central.

> **Nota (2026-07-23):** GW-01 a GW-10 están ✅ porque el software/scripts están escritos y
> revisados (`gateway/scripts/`, `gateway/mosquitto/`), no porque ya corran en un Raspberry Pi
> físico real — el hardware existe pero no se ha puesto en funcionamiento todavía (ver GW-11).

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| GW-01 | Instalar Raspberry Pi OS + configuración inicial | 🔴 | 1 | ✅ |
| GW-02 | Instalar y configurar Mosquitto (broker MQTT) | 🔴 | 1 | ✅ |
| GW-03 | Instalar Node-RED + flujos básicos de control | 🔴 | 1 | ✅ |
| GW-04 | Node-RED: leer MQTT y persistir en InfluxDB | 🔴 | 1 | ✅ |
| GW-05 | Instalar InfluxDB (base de datos de serie temporal) | 🔴 | 1 | ✅ |
| GW-06 | Instalar Grafana + dashboard inicial (temp, HR, CO₂ por cápsula) | 🔴 | 1 | ✅ |
| GW-07 | Node-RED: lógica de alertas (si no hay datos en 5 min → alerta) | 🟡 | 1 | ✅ |
| GW-08 | Configurar backup automático a Firebase | 🟡 | 1 | ✅ |
| GW-09 | Configurar UPS y script de shutdown seguro | 🟡 | 1 | ✅ |
| GW-10 | Documentar flujos Node-RED y exportar `node-red-flows.json` | 🟡 | 1 | ✅ |
| GW-11 | Desplegar el gateway en el Raspberry Pi físico real (correr `gateway/scripts/setup.sh`, configurar Mosquitto/Node-RED/InfluxDB/Grafana en vivo) | 🔴 | 1 | 🔲 |

---

## ÉPICA 4 — Nube & Alertas

> Integración con Firebase y Telegram para acceso remoto y notificaciones.

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| CLD-01 | Crear proyecto Firebase y configurar Realtime Database | 🔴 | 1 | 🔲 |
| CLD-02 | Script Python/Node en RPi para sincronizar InfluxDB → Firebase | 🔴 | 1 | 🔲 |
| CLD-03 | Crear Telegram Bot (BotFather) | 🔴 | 1 | 🔲 |
| CLD-04 | Integrar Telegram Bot con Node-RED (alertas automáticas) | 🔴 | 1 | 🔲 |
| CLD-05 | Definir tipos de alerta: crítica (inmediata) vs. informativa (resumen diario) | 🟡 | 1 | 🔲 |
| CLD-06 | Dashboard Firebase público/privado para acceso web básico | 🟢 | 2 | 🔲 |

---

## ÉPICA 5 — Web App (Panel de Gestión)

> Aplicación web para gestión de lotes, cápsulas, cosechas y trazabilidad.

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| WEB-01 | Definir stack: Next.js + Firebase + Tailwind CSS | 🔴 | 2 | 🔲 |
| WEB-02 | Diseño de base de datos (esquema de lotes, cápsulas, cosechas) | 🔴 | 2 | 🔲 |
| WEB-03 | Diseño de wireframes (panel principal, detalle de cápsula, lote) | 🔴 | 2 | 🔲 |
| WEB-04 | Autenticación: login con email/Google | 🔴 | 2 | 🔲 |
| WEB-05 | Vista de cápsulas: estado en tiempo real (temperatura, HR, CO₂) | 🔴 | 2 | 🔲 |
| WEB-06 | CRUD de lotes: crear, editar, marcar cosecha | 🔴 | 2 | 🔲 |
| WEB-07 | Historial de parámetros: gráficas de sensor por cápsula/período | 🔴 | 2 | 🔲 |
| WEB-08 | Gestión de perfiles JSON: ver, editar, asignar a cápsula | 🟡 | 2 | 🔲 |
| WEB-09 | Registro de cosechas: peso, categoría, precio, destino | 🟡 | 2 | 🔲 |
| WEB-10 | Trazabilidad por lote: QR code que muestra historial completo | 🟡 | 3 | 🔲 |
| WEB-11 | Wiki integrada: fichas de especie y protocolos desde el panel | 🟢 | 3 | 🔲 |
| WEB-12 | API REST: endpoints para que el firmware ESP32 pueda consultar perfiles | 🟡 | 2 | 🔲 |
| WEB-13 | Despliegue en Vercel (o Railway) con dominio propio | 🟡 | 2 | 🔲 |
| WEB-14 | Tests básicos: validación de formularios, autenticación | 🟢 | 2 | 🔲 |

---

## ÉPICA 6 — App Móvil

> Aplicación móvil para monitoreo y alertas desde el celular.

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| MOB-01 | Definir plataforma: React Native o Flutter | 🟡 | 3 | 🔲 |
| MOB-02 | Dashboard: temperatura, HR, CO₂ de todas las cápsulas | 🟡 | 3 | 🔲 |
| MOB-03 | Push notifications: alertas críticas del sistema | 🟡 | 3 | 🔲 |
| MOB-04 | Control remoto: cambiar perfil activo de una cápsula | 🟢 | 3 | 🔲 |
| MOB-05 | Scanner QR: escanear lote para ver historial | 🟢 | 3 | 🔲 |
| MOB-06 | Publicación en Play Store / App Store | 🟢 | 4 | 🔲 |

---

## ÉPICA 7 — Módulo Financiero

> Seguimiento de costos, ingresos y rentabilidad por especie y lote.

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| FIN-01 | Definir modelo de datos financiero (costo por lote, ingreso por cosecha) | 🟡 | 3 | 🔲 |
| FIN-02 | Registro de costos de producción por lote (sustrato, semilla, energía) | 🟡 | 3 | 🔲 |
| FIN-03 | Registro de ingresos por cosecha (peso × precio × canal) | 🟡 | 3 | 🔲 |
| FIN-04 | Cálculo automático de margen por lote | 🟡 | 3 | 🔲 |
| FIN-05 | Reporte de rentabilidad por especie (comparar cápsulas) | 🟢 | 4 | 🔲 |
| FIN-06 | Reporte de ROI por cápsula (amortización del hardware) | 🟢 | 4 | 🔲 |
| FIN-07 | Proyección de ingresos basada en lotes en curso | 🟢 | 4 | 🔲 |
| FIN-08 | Exportar reportes a CSV / PDF | 🟢 | 4 | 🔲 |

---

## ÉPICA 8 — Multi-sede

> Replicación del sistema en nuevas ubicaciones.

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| MS-01 | Documentar "playbook de nueva sede" (guía de instalación completa) | 🟡 | 4 | 🔲 |
| MS-02 | Empaquetar "kit de nueva sede": hardware lista + configuración | 🟡 | 4 | 🔲 |
| MS-03 | Dashboard consolidado: ver todas las sedes en una sola pantalla | 🟡 | 4 | 🔲 |
| MS-04 | Firebase multi-tenant: separar datos por sede | 🟡 | 4 | 🔲 |
| MS-05 | OTA updates masivo: actualizar firmware de todos los ESP32 de todas las sedes | 🟢 | 5 | 🔲 |
| MS-06 | Reporte comparativo entre sedes (misma especie, distintas condiciones) | 🟢 | 5 | 🔲 |

---

## ÉPICA 9 — Producción / Cultivo

> Hitos de producción real — cultivos exitosos por especie.

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| CUL-01 | Adquirir cepa de Orellana (P. ostreatus) certificada — **en camino, entrega estimada semana del 2026-07-27** | 🔴 | 1 | 🔲 |
| CUL-02 | Primer lote de orellana: pasteurización + inoculación (registro completo) | 🔴 | 1 | 🔲 |
| CUL-03 | Primera cosecha orellana + cálculo de BE% | 🔴 | 1 | 🔲 |
| CUL-04 | Primer cliente: restaurante o plaza de mercado | 🔴 | 1 | 🔲 |
| CUL-05 | Adquirir cepa Shiitake certificada | 🟡 | 2 | 🔲 |
| CUL-06 | Primer lote Shiitake (esterilización + bloque compactado) | 🟡 | 2 | 🔲 |
| CUL-07 | Primera inducción Shiitake (choque de frío o inmersión) | 🟡 | 2 | 🔲 |
| CUL-08 | Adquirir cepa Melena de León | 🟡 | 2 | 🔲 |
| CUL-09 | Primer lote Melena de León (control estricto de CO₂) | 🟡 | 2 | 🔲 |
| CUL-10 | Adquirir cepa Reishi | 🟢 | 3 | 🔲 |
| CUL-11 | Primer lote Reishi (etapa antler → cap) | 🟢 | 3 | 🔲 |
| CUL-12 | Primer extracto doble de Reishi (agua + alcohol) | 🟢 | 3 | 🔲 |
| CUL-13 | Adquirir cepa Cordyceps militaris | 🟢 | 3 | 🔲 |
| CUL-14 | Preparar primer cultivo líquido de Cordyceps | 🟢 | 3 | 🔲 |
| CUL-15 | Primer lote Cordyceps (sustrato arroz + ciclo luz/oscuridad) | 🟢 | 3 | 🔲 |
| CUL-16 | Primer lote Enoki (cápsula de frío activo) | 🟢 | 3 | 🔲 |
| CUL-17 | Adquirir cepa Maitake + inicio lote (incubación larga) | 🟢 | 3 | 🔲 |
| CUL-18 | Establecer banco de cepas (agar inclinado + frío) | 🟡 | 2 | 🔲 |
| CUL-19 | Primera clonación de tejido frutal en agar | 🟡 | 2 | 🔲 |
| CUL-20 | Primer aislamiento monoespórico | 🟢 | 4 | 🔲 |
| CUL-21 | Crear perfil JSON y doc técnico para Eryngii (King Oyster / Ostra Rey) — pedido por cliente 1-jul | 🔴 | 1 | 🔲 |
| CUL-22 | Crear perfil JSON para Chaga (doc técnico ya existe: docs/especies/N4-chaga.md) | 🟡 | 2 | 🔲 |
| CUL-23 | Crear perfil JSON para Trufas (doc técnico ya existe: docs/especies/N4-trufas.md) | 🟢 | 3 | 🔲 |

---

## ÉPICA 10 — Documentación

> Documentación técnica del proyecto.

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| DOC-01 | README.md — visión del proyecto | 🔴 | 0 | ✅ |
| DOC-02 | docs/capsula/diseno-capsula.md | 🔴 | 0 | ✅ |
| DOC-03 | docs/especies/N1-orellana.md | 🔴 | 0 | ✅ |
| DOC-04 | docs/especies/N2-shiitake.md | 🔴 | 0 | ✅ |
| DOC-05 | docs/especies/N2-portobello.md | 🟡 | 0 | ✅ |
| DOC-06 | docs/especies/N2-melena-de-leon.md | 🔴 | 0 | ✅ |
| DOC-07 | docs/especies/N3-enoki.md | 🟡 | 0 | ✅ |
| DOC-08 | docs/especies/N3-reishi.md | 🟡 | 0 | ✅ |
| DOC-09 | docs/especies/N3-maitake.md | 🟢 | 0 | ✅ |
| DOC-10 | docs/especies/N3-cola-de-pavo.md | 🟢 | 0 | ✅ |
| DOC-11 | docs/especies/N4-cordyceps.md | 🟡 | 0 | ✅ |
| DOC-12 | docs/roadmap-equipo.md | 🔴 | 0 | ✅ |
| DOC-13 | docs/protocolos/ — SOPs completos | 🔴 | 1 | ✅ |
| DOC-14 | firmware/profiles/ — perfiles JSON por especie | 🔴 | 0 | ✅ |
| DOC-15 | CLAUDE.md — actualizar con estructura real | 🟡 | 0 | ✅ |
| DOC-16 | gateway/README.md — guía de instalación RPi | 🟡 | 1 | ✅ |
| DOC-17 | firmware/capsula_core/README.md — guía de firmware | 🔴 | 1 | ✅ |
| DOC-18 | docs/protocolos/SOP-agar.md — trabajo en agar | 🟡 | 2 | ✅ |
| DOC-19 | docs/protocolos/SOP-banco-cepas.md — preservación de cepas | 🟡 | 2 | ✅ |
| DOC-20 | Playbook nueva sede (guía de replicación) | 🟢 | 4 | 🔲 |
| DOC-21 | Documento de KPIs y criterios de éxito del sistema (tasa contaminación, BE%, SLA) | 🔴 | 0 | ✅ |
| DOC-22 | Registro de línea de base ambiental del invernadero (7 días de medición real) | 🔴 | 0 | ✅ |
| DOC-23 | Propuesta de consultoría para clientes externos (docs/negocio/propuesta-consultoria.md) | 🔴 | 0 | ✅ |
| DOC-24 | Diseño de espacio para primer cliente — La Jobiteka (docs/negocio/diseno-espacio-jobiteka.md) | 🔴 | 1 | ✅ |
| DOC-25 | docs/especies/N4-psilocybe.md | 🔴 | 0 | ✅ |
| DOC-26 | docs/especies/N4-chaga.md (documentada, sin perfil JSON — ver CUL-22) | 🟡 | 0 | ✅ |
| DOC-27 | docs/especies/N4-trufas.md (documentada, sin perfil JSON — ver CUL-23) | 🟢 | 0 | ✅ |
| DOC-28 | docs/capsula/SOP-primer-despliegue.md — guía secuencial gateway + cápsula + firmware + primera prueba | 🔴 | 1 | ✅ |

---

## ÉPICA 11 — Validación Comercial

> Validar mercado, precios y canales de venta antes de escalar producción.

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| COM-01 | Identificar y contactar 3–5 restaurantes/distribuidores en Medellín y Rionegro | 🔴 | 0 | 🔲 |
| COM-02 | Validar precio de compra real y volumen mínimo por canal (restaurante, plaza, tienda) | 🔴 | 0 | 🔲 |
| COM-03 | Mapear competidores locales (quién vende hongos en Antioquia, a qué precio) | 🟡 | 0 | 🔲 |
| COM-04 | Definir propuesta de valor diferencial (trazabilidad IoT, calidad constante, delivery) | 🟡 | 0 | 🔲 |
| COM-05 | Realizar primera venta piloto de orellana antes de escalar (validar cadena completa) | 🔴 | 1 | 🔲 |
| COM-06 | Abrir canal digital de ventas (WhatsApp Business, perfil de proveedor en Instagram) | 🟢 | 1 | 🔲 |

---

## ÉPICA 12 — Marco Legal & Calidad

> Cumplimiento regulatorio y estándares de calidad para producción y venta.

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| LEG-01 | Verificar requisitos INVIMA / Secretaría de Salud para venta de hongos comestibles en Colombia | 🔴 | 0 | 🔲 |
| LEG-02 | Registrar actividad como productor agrícola o microempresa (RUT, Cámara de Comercio) | 🔴 | 0 | 🔲 |
| LEG-03 | Definir KPIs mínimos aceptables: tasa de contaminación, BE% por especie, SLA del IoT | 🔴 | 0 | 🔲 |
| LEG-04 | Crear protocolo de gestión de lotes contaminados (cuarentena, descarte, trazabilidad) | 🔴 | 1 | 🔲 |
| LEG-05 | Crear ficha técnica de producto por especie (nutrición, alérgenos, conservación, precio) | 🟡 | 1 | 🔲 |

---

## ÉPICA 13 — Seguridad IoT

> Proteger el sistema contra accesos no autorizados, datos falsos y fallos en cascada.

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| SEC-01 | Configurar autenticación MQTT en Mosquitto (usuario/contraseña por ESP32) | 🔴 | 1 | ✅ |
| SEC-02 | Habilitar TLS en el broker MQTT (cifrar datos en tránsito) | 🟡 | 1 | ✅ |
| SEC-03 | Definir y aplicar reglas de seguridad en Firebase Realtime Database | 🔴 | 1 | ✅ |
| SEC-04 | Documentar política de acceso: quién lee datos, quién puede cambiar perfiles de cápsulas | 🟡 | 1 | ✅ |
| SEC-05 | Configurar red WiFi segmentada (VLAN o red separada para dispositivos IoT) | 🟢 | 1 | ✅ |
| SEC-06 | Definir plan de respuesta a incidentes IoT (ESP32 con datos anómalos, actuador bloqueado) | 🟡 | 2 | ✅ |

---

## ÉPICA 14 — Plan de Negocio

> Documentación estratégica, modelos de negocio y proyecciones financieras.

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| BIZ-01 | Crear plan de negocio completo (mercado, operaciones, equipo, riesgos, hoja de ruta) | 🔴 | 0 | ✅ |
| BIZ-02 | Business Model Canvas (Osterwalder) + Value Proposition Canvas + Lean Canvas | 🔴 | 0 | ✅ |
| BIZ-03 | Modelo financiero a 5 años (P&L, flujo de caja, break-even, escenarios) | 🔴 | 0 | ✅ |
| BIZ-04 | Diagrama de flujo del sistema completo (datos, control, alertas, ciclo de lote) | 🟡 | 0 | ✅ |

---

## Mejoras Identificadas en el Análisis

### 🔴 Críticas (bloquean avance)

1. **Primera cápsula no construida** — todo el sistema de control es teórico hasta que haya
   hardware físico funcionando (F1-05). Firmware y gateway (software) ya están implementados y
   compilando, pero nunca se han probado en un ESP32 real.
2. **Cepa de Orellana no adquirida** (CUL-01) — sin cepa certificada no puede arrancar el primer
   lote real, aunque el resto del sistema esté listo.

### 🟡 Importantes (próximas iteraciones)

3. **Banco de cepas no establecido** — depender de cepas externas crea riesgo de cadena de suministro. Hay que preservar cepas propias desde el primer lote exitoso.
4. **No hay primer cliente de producto definido** (distinto del cliente de consultoría, ver Épica 15) — la proyección financiera supone ventas desde el primer ciclo. Hay que validar el canal de venta antes de escalar producción.

### 🟢 Mejoras futuras

5. **Sistema de log de oleadas** — el sistema actual no rastrea el número de oleadas por bloque. Agregar `oleada` al modelo de datos del lote.
6. **Comparación de cepas** — dos perfiles de la misma especie con parámetros distintos en cápsulas distintas. El historial de Grafana permitirá comparar rendimiento.

---

## ÉPICA 15 — Consultoría Clientes

> Servicio de consultoría para terceros que quieren montar laboratorios de hongos. Primer cliente: La Jobiteka (Juan, Guarne).

| ID | Tarea | Prioridad | Fase | Estado |
|----|-------|-----------|------|--------|
| CON-01 | Propuesta de consultoría formal (4 componentes, honorarios, forma de pago) | 🔴 | 0 | ✅ |
| CON-02 | Diseño de espacio provisional — La Jobiteka 7×14 m | 🔴 | 0 | ✅ |
| CON-03 | Agenda y talking points para reunión con cliente | 🔴 | 0 | ✅ |
| CON-04 | Cerrar acuerdo con La Jobiteka (definir Modelo A o B, escenario, fecha de inicio) | 🔴 | 1 | 🔲 |
| CON-05 | Realizar visita de diagnóstico presencial (Componente 1) | 🔴 | 1 | 🔲 |
| CON-06 | Entregar diseño técnico final del espacio (plano + cronograma) | 🔴 | 1 | 🔲 |
| CON-07 | Acompañamiento de adecuación — La Jobiteka (Componente 2) | 🟡 | 1 | 🔲 |
| CON-08 | Capacitación con primer lote + entrega de manuales (Componentes 3 y 4) | 🟡 | 1 | 🔲 |
| CON-09 | Acta reunión 1-jul-2026 enviada a Daniela (docs/reuniones/2026-07-01-reunion-cliente.md) | 🔴 | 1 | 🔲 |
| CON-10 | Visita física al invernadero + revisión de espacio (acordada al final de reunión 1-jul) | 🔴 | 1 | 🔲 |
| CON-11 | Agendar cata en Mamá Santa con Edward (chef) — ramen, orellana tempura, portobello | 🔴 | 1 | 🔲 |
| CON-12 | Propuesta económica detallada Fase 1 (definir tras visita al invernadero) | 🔴 | 1 | 🔲 |
| CON-13 | Contactar Plural (Iván Montoya) — restaurante universitario, potencial cliente institucional | 🟡 | 1 | 🔲 |
| CON-14 | Contactar Lolita de AFID | 🟡 | 1 | 🔲 |
| CON-15 | Contactar restaurante vía Forme (a través del contacto que tiene Juan) | 🟡 | 1 | 🔲 |
| CON-16 | Documentar concepto cápsula-pecera para restaurante (cápsula visible en sala del restaurante) | 🟡 | 2 | 🔲 |
| CON-17 | Documentar mini cápsula de escritorio como producto retail | 🟡 | 2 | 🔲 |
| CON-18 | Diseñar formato de taller de siembra como evento pago (~$200.000/persona) | 🟢 | 2 | 🔲 |

---

## Sprint 0 — Pre-implementación (antes de tocar hardware o código)

> Validaciones y diseños que reducen riesgo antes de invertir en hardware o desarrollo.
> Estimado: 2–3 semanas.

- [ ] **COM-01** Contactar 3 restaurantes/distribuidores en Medellín y Rionegro
- [ ] **COM-02** Validar precio y volumen mínimo de compra (llamadas o visita presencial)
- [ ] **COM-03** Mapear competidores: quién vende hongos en Antioquia y a qué precio
- [ ] **LEG-01** Verificar requisitos INVIMA para venta de hongos comestibles
- [ ] **LEG-02** Registrar actividad económica (RUT / Cámara de Comercio)
- [ ] **LEG-03** Definir KPIs mínimos del sistema (tasa contaminación, BE%, SLA IoT)
- [ ] **F1-16** Medir línea de base ambiental del invernadero durante 7 días (termómetro + higrómetro manual)

> F1-13 (BOM) y F1-14 (diagrama eléctrico) ya están ✅ completadas — quitadas de esta lista.

---

## Sprint 1 — Construcción e instalación inicial

> Después de completar Sprint 0. Estimado: 4–6 semanas.

- [ ] **F1-01** Sellar pisos del invernadero
- [ ] **F1-05** Construir cápsula Mini con nevera usada
- [ ] **IOT-01** Configurar IDE Arduino + primera prueba de sensor SHT31 (nota: el firmware ya
      compila vía PlatformIO — ver `firmware/capsula_core/platformio.ini` — este paso ahora es
      solo cargarlo a un ESP32 físico)
- [ ] **CUL-01** Conseguir cepa de Orellana certificada
- [ ] **LEG-04** Protocolo de gestión de lotes contaminados

> F1-15, IOT-19, IOT-20, GW-01, GW-02, SEC-01 y SEC-03 ya están ✅ completadas — quitadas de esta
> lista. El firmware y el gateway (software) están implementados; lo que falta de este sprint es
> la infraestructura física y desplegar/probar en hardware real.

---

*Bichongos · BACKLOG.md · Actualizado: 2026-07-23 · v2.2*
