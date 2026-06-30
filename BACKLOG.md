# BACKLOG — Bichongos

> Registro de todas las funcionalidades, tareas y mejoras del proyecto. Organizado por épica y fase. Prioridad: 🔴 Alta · 🟡 Media · 🟢 Baja

**Última actualización:** 2026-06-30
**Estado del proyecto:** Fase 0 completada (documentación base). Pre-implementación en curso.

---

## Estado General

| Épica | Total tareas | Completadas | En progreso | Pendientes |
|-------|-------------|------------|-------------|-----------|
| E1 — Infraestructura Física | 16 | 0 | 0 | 16 |
| E2 — IoT / Firmware | 20 | 14 | 0 | 6 |
| E3 — Gateway & Dashboard Local | 10 | 8 | 0 | 2 |
| E4 — Nube & Alertas | 6 | 0 | 0 | 6 |
| E5 — Web App | 14 | 0 | 0 | 14 |
| E6 — App Móvil | 6 | 0 | 0 | 6 |
| E7 — Módulo Financiero | 8 | 0 | 0 | 8 |
| E8 — Multi-sede | 6 | 0 | 0 | 6 |
| E9 — Producción / Cultivo | 20 | 0 | 0 | 20 |
| E10 — Documentación | 22 | 17 | 0 | 5 |
| E11 — Validación Comercial | 6 | 0 | 0 | 6 |
| E12 — Marco Legal & Calidad | 5 | 0 | 0 | 5 |
| E13 — Seguridad IoT | 6 | 6 | 0 | 0 |
| E14 — Plan de Negocio | 4 | 4 | 0 | 0 |
| **Total** | **149** | **49** | **0** | **100** |

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
| F1-11 | Construir cápsula con sistema de frío para Enoki | 🟢 | 3 | 🔲 |
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
| IOT-14 | Firmware: contador de días por etapa y notificación de fin de etapa | 🟡 | 2 | 🔲 |
| IOT-15 | Firmware: OTA updates (actualización remota del firmware) | 🟢 | 2 | ✅ |
| IOT-16 | Firmware: soporte de múltiples perfiles (cambio de etapa remoto vía MQTT) | 🟢 | 2 | ✅ |
| IOT-17 | Crear `config.h.example` con template de credenciales WiFi/MQTT | 🔴 | 1 | ✅ |
| IOT-18 | Probar firmware en cápsula Mini con orellana (primer ciclo real) | 🔴 | 1 | 🔲 |
| IOT-19 | Definir y documentar protocolo de calibración de sensores (SHT31, MH-Z19B) | 🔴 | 1 | 🔲 |
| IOT-20 | Escribir spec del modo seguro: comportamiento del ESP32 sin WiFi y sin MQTT | 🔴 | 1 | ✅ |

---

## ÉPICA 3 — Gateway & Dashboard Local (Raspberry Pi)

> Instalación y configuración del gateway central.

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
| GW-09 | Configurar UPS y script de shutdown seguro | 🟡 | 1 | 🔲 |
| GW-10 | Documentar flujos Node-RED y exportar `node-red-flows.json` | 🟡 | 1 | 🔲 |

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
| CUL-01 | Adquirir cepa de Orellana (P. ostreatus) certificada | 🔴 | 1 | 🔲 |
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
| DOC-18 | docs/protocolos/SOP-agar.md — trabajo en agar | 🟡 | 2 | 🔲 |
| DOC-19 | docs/protocolos/SOP-banco-cepas.md — preservación de cepas | 🟡 | 2 | 🔲 |
| DOC-20 | Playbook nueva sede (guía de replicación) | 🟢 | 4 | 🔲 |
| DOC-21 | Documento de KPIs y criterios de éxito del sistema (tasa contaminación, BE%, SLA) | 🔴 | 0 | ✅ |
| DOC-22 | Registro de línea de base ambiental del invernadero (7 días de medición real) | 🔴 | 0 | ✅ |

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

1. **Firmware no existe** — los perfiles JSON están creados pero el código Arduino que los lee no existe. Es el primer bloqueador real.
2. **Gateway no configurado** — sin el RPi configurado no hay dashboard, no hay histórico, no hay alertas.
3. **Primera cápsula no construida** — todo el sistema es teórico hasta que haya hardware físico funcionando.

### 🟡 Importantes (próximas iteraciones)

4. **Banco de cepas no establecido** — depender de cepas externas crea riesgo de cadena de suministro. Hay que preservar cepas propias desde el primer lote exitoso.
5. **No hay primer cliente definido** — la proyección financiera supone ventas desde el primer ciclo. Hay que validar el canal de venta antes de escalar producción.
6. **El perfil JSON de Enoki tiene `co2_min`** — el firmware debe soportar tanto límite máximo como mínimo de CO₂ (para Enoki se necesita CO₂ ALTO de forma intencional — lógica invertida).

### 🟢 Mejoras futuras

7. **Sistema de log de oleadas** — el sistema actual no rastrea el número de oleadas por bloque. Agregar `oleada` al modelo de datos del lote.
8. **Comparación de cepas** — dos perfiles de la misma especie con parámetros distintos en cápsulas distintas. El historial de Grafana permitirá comparar rendimiento.
9. **Alertas de fin de etapa** — el firmware debería notificar automáticamente cuando los `duracion_dias` del perfil se cumplen, indicando que hay que cambiar de etapa o cosechar.
10. **Integración con báscula digital** — registro automático de peso de cosecha via Bluetooth/USB al sistema de trazabilidad.

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
- [ ] **F1-13** Levantar BOM real con precios COP (cotizar sensores, ESP32, relés en Medellín)
- [ ] **F1-16** Medir línea de base ambiental del invernadero durante 7 días (termómetro + higrómetro manual)
- [ ] **F1-14** Crear diagrama eléctrico de la primera cápsula

---

## Sprint 1 — Construcción e instalación inicial

> Después de completar Sprint 0. Estimado: 4–6 semanas.

- [ ] **F1-01** Sellar pisos del invernadero
- [ ] **F1-05** Construir cápsula Mini con nevera usada
- [ ] **F1-15** Diseñar plan de red WiFi (IPs estáticas, cobertura)
- [ ] **IOT-01** Configurar IDE Arduino + primera prueba de sensor SHT31
- [ ] **IOT-19** Protocolo de calibración de sensores antes del primer despliegue
- [ ] **IOT-20** Escribir spec del modo seguro del ESP32
- [ ] **GW-01** Instalar Raspberry Pi OS
- [ ] **GW-02** Instalar y configurar Mosquitto
- [ ] **SEC-01** Configurar autenticación MQTT desde el inicio
- [ ] **SEC-03** Definir reglas de seguridad Firebase antes de conectar
- [ ] **CUL-01** Conseguir cepa de Orellana certificada
- [ ] **LEG-04** Protocolo de gestión de lotes contaminados

---

*Bichongos · BACKLOG.md · Actualizado: 2026-06-30 · v2.1*
