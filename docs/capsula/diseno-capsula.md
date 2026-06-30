# Diseño de la Cápsula de Cultivo — Bichongos

> Especificaciones técnicas para construir la cápsula estándar y sus variantes. El mismo diseño es replicable en cualquier sede.

---

## Principio de diseño

Una cápsula Bichongos es una **cámara hermética, aislada térmicamente, con control activo de temperatura, humedad, CO₂ y luz**, operada por un nodo ESP32 que sigue un perfil de parámetros intercambiable por especie.

El objetivo es que **el clima exterior sea irrelevante** — una cápsula en Barranquilla (35 °C) o en Bogotá (13 °C) produce las mismas condiciones internas si recibe el mismo perfil JSON.

---

## Tipos de cápsula

### Tipo 1 — Mini (nevera modificada)

**Uso:** I+D, prueba de cepas nuevas, experimentos de parámetros.

| Especificación | Valor |
|---------------|-------|
| Base | Nevera doméstica 150–200 L |
| Capacidad | 10–20 bolsas |
| Aislamiento | Ya incorporado en la nevera |
| Sistema de frío | Compresor original de la nevera (controlado por ESP32 vía relé) |
| Sistema de calor | Resistencia cerámica 100 W |
| Ventilación | Tubo de 40 mm con extractor PC 12V y filtro HEPA |
| Humidificación | Humidificador ultrasónico 1 L por tubo de entrada |
| Costo estimado | $150–300 USD (nevera usada + electrónica) |

**Ventaja:** construcción mínima. Ideal para comenzar.

---

### Tipo 2 — Estándar (caja construida)

**Uso:** producción individual por especie.

#### Materiales de construcción

| Componente | Material | Dimensiones |
|-----------|---------|------------|
| Estructura | Madera contrachapada 18 mm | 60 × 60 × 120 cm (interior útil) |
| Aislamiento interior | Espuma de poliuretano 3–5 cm (spray o planchas) | — |
| Recubrimiento interior | Pintura epoxi blanca o lámina PVC 2 mm | — |
| Puerta | Ventana de vidrio acrílico con junta de silicón | 30 × 40 cm |

#### Sistemas activos

| Sistema | Componente | Especificación |
|---------|-----------|---------------|
| Calefacción | Resistencia cerámica PTC | 200–500 W (según especie) |
| Refrigeración | Módulo Peltier TEC1-12706 + disipador | Para Enoki y cepas frías |
| Humidificación | Humidificador ultrasónico 5 L | Controlado por ESP32 via relé |
| FAE (intercambio de aire) | Extractor PC 120 mm + filtro MERV-11 | Controlado por ESP32 via relé |
| Iluminación | Tira LED 6500K (luz blanca fría) | 12–24 V, intensidad regulable |

> **Nota sobre refrigeración:** para la mayoría de las especies (orellana, shiitake, melena, reishi), no se necesita refrigeración activa. El módulo Peltier es necesario solo para Enoki o en sedes con clima cálido (>25 °C constante).

#### Costo estimado (sin electrónica IoT)

| Item | Costo (USD) |
|------|------------|
| Madera + tornillos | 40–60 |
| Aislamiento | 20–30 |
| Recubrimiento interior | 15–25 |
| Calefactor cerámica | 15–25 |
| Humidificador | 40–60 |
| Extractor + filtro | 20–35 |
| LED strip + fuente | 15–25 |
| Silicón, herrajes, bisagras | 15–20 |
| **Total construcción** | **~180–280 USD** |

---

### Tipo 3 — Rack con cortina (mayor escala)

**Uso:** producción principal en la sede piloto.

- Estantería metálica 5 niveles (90 × 45 × 180 cm).
- Cortinas de PVC transparente en los 4 lados (ancladas con velcro o perfiles de aluminio).
- Sistema de nebulización por línea de goteo + atomizadores en la parte superior.
- 1 nodo ESP32 por rack con sensores en el nivel central (representativo de todos los niveles).
- Capacidad: 80–120 bolsas por rack.
- Costo: $200–400 USD por rack (incluyendo cortinas y electrónica).

---

## Esquema electrónico del nodo ESP32

```
                    ┌─────────────────────────────────┐
                    │         ESP32 DevKit V1          │
                    │                                  │
     SHT31 ─────── │ GPIO 21 (SDA) / 22 (SCL)  [I2C] │
     MH-Z19B ───── │ GPIO 16 (RX)  / 17 (TX)  [UART]│
     BH1750 ─────── │ GPIO 21 (SDA) / 22 (SCL)  [I2C] │ (misma línea I2C)
     DS18B20 ─────── │ GPIO 4                [1-Wire] │
                    │                                  │
     Relé CH1 ───── │ GPIO 26 → Humidificador          │
     Relé CH2 ───── │ GPIO 27 → Extractor FAE          │
     Relé CH3 ───── │ GPIO 14 → Calefactor             │
     Relé CH4 ───── │ GPIO 12 → LED / Luz              │
                    │                                  │
     WiFi ────────  │ (interno)                        │
     Fuente 5V ──── │ VIN / GND                       │
                    └─────────────────────────────────┘
```

---

## Firmware — Lógica de control

El firmware del ESP32 implementa:

1. **Carga de perfil:** lee el perfil JSON activo (almacenado en SPIFFS o descargado de Firebase).
2. **Lectura de sensores:** cada 30 segundos.
3. **Control PID simple:** compara valores medidos con el perfil y activa/desactiva relés.
4. **Protecciones:**
   - Tiempo mínimo entre encendidos del relé (protección de actuadores mecánicos).
   - Alarma si sensor no responde (posible fallo de hardware).
   - Modo seguro: si pierde WiFi, sigue funcionando con los últimos parámetros.
5. **Publicación MQTT:** publica todos los valores al broker local y a Firebase.
6. **Alertas:** publica a topic de alertas si hay valor fuera de rango crítico.

---

## Lista de materiales completa por nodo IoT

| Componente | Cantidad | Link de referencia |
|------------|----------|-------------------|
| ESP32 DevKit V1 | 1 | AliExpress / MercadoLibre |
| Sensor SHT31 (I2C) | 1 | AliExpress |
| Sensor MH-Z19B (CO₂ NDIR) | 1 | AliExpress ($20–25 USD) |
| Sensor BH1750 (luz I2C) | 1 | AliExpress |
| Sensor DS18B20 | 1 | AliExpress |
| Módulo relé 4 canales 5V | 1 | AliExpress / MercadoLibre |
| Fuente de alimentación 5V 2A | 1 | AliExpress |
| Cable Dupont 40 pines | 1 paquete | AliExpress |
| Caja IP65 (15×10×7 cm) | 1 | AliExpress |
| Portafusibles + fusible 2A | 1 | — |

**Costo total por nodo: ~$65–80 USD**

---

## Guía de instalación rápida

1. Montar el ESP32 en la caja IP65 con soporte de tornillo.
2. Conectar sensores según el esquema electrónico.
3. Conectar módulo de relés a los actuadores de la cápsula.
4. Cargar el firmware desde el IDE de Arduino.
5. Configurar las credenciales WiFi y la dirección del broker MQTT en `config.h`.
6. Verificar que aparece en el dashboard de Grafana y que los valores son coherentes.
7. Cargar el perfil JSON de la especie a cultivar.

---

## Guía de mantenimiento

| Tarea | Frecuencia |
|-------|-----------|
| Limpiar filtros del extractor FAE | Cada 2 semanas |
| Calibrar sensor MH-Z19B (auto-calibración) | Cada 6 meses |
| Verificar humidificador (limpieza de mineral) | Cada 2 semanas |
| Backup de datos en Firebase | Automático (continuo) |
| Revisar conexiones eléctricas | Cada 3 meses |
| Actualizar firmware OTA | Según actualizaciones del repositorio |

---

*Bichongos · docs/capsula/diseno-capsula.md · Actualizado: 2026-06-30*
