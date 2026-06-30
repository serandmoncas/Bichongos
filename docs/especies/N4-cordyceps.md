# Cordyceps — Cordyceps militaris

**Nivel de dificultad:** ⭐⭐⭐⭐ (Experto)
**Categoría:** Funcional / Medicinal
**Tiempo total de cultivo:** 8–12 semanas

---

## Perfil de la cápsula

| Parámetro | Incubación | Fructificación (estroma) |
|-----------|-----------|------------------------|
| Temperatura | 22–26 °C | 22–24 °C |
| Humedad relativa | 70–80 % | 80–90 % |
| CO₂ máximo | sin límite | 1.500 ppm |
| Luz | **0 h** (oscuridad total) | **Ciclo 12/12 h** — luz blanca fría |
| Duración | 14–21 días | 45–60 días |

> **Diferencia con todas las demás especies:** el Cordyceps militaris fructifica mejor cuando la etapa de colonización es en **oscuridad total**, y la fructificación requiere un **ciclo estricto de luz/oscuridad** como señal de cambio de estación. La luz actúa como reloj biológico para inducir la formación del estroma.

### Archivo de perfil JSON

```json
{
  "especie": "Cordyceps militaris",
  "nombre_comun": "Cordyceps",
  "etapas": {
    "incubacion": {
      "temp_min": 22, "temp_max": 26,
      "humedad_min": 70, "humedad_max": 80,
      "co2_max": 9999,
      "luz_horas": 0,
      "duracion_dias": 18
    },
    "fructificacion": {
      "temp_min": 22, "temp_max": 24,
      "humedad_min": 80, "humedad_max": 90,
      "co2_max": 1500,
      "luz_horas": 12,
      "luz_tipo": "blanca_fria_6500K",
      "luz_inicio": "08:00",
      "luz_fin": "20:00",
      "duracion_dias": 55
    }
  }
}
```

---

## Sustrato

### Opción A — Arroz integral (más accesible)

| Ingrediente | Cantidad |
|------------|----------|
| Arroz integral | 100 g por frasco |
| Agua | 80–90 ml por frasco |
| Peptona o levadura nutricional | 2 g |

- Mezclar arroz + agua en frascos de vidrio de boca ancha (500 ml).
- Cubrir con tapa con filtro de algodón y papel aluminio.
- Esterilizar en autoclave: 121 °C × 1,5 h.
- Enfriar y luego inocular con cultivo líquido de Cordyceps.

### Opción B — Pupas de gusano de seda (resultado superior)

- Las pupas de gusano de seda son el sustrato natural del Cordyceps.
- Esterilizar las pupas antes de inocular.
- El estroma crece directamente del cuerpo de la pupa — presentación estética y precio premium.
- Mayor dificultad operativa: requiere conseguir pupas frescas o congeladas de proveedores de seda.

---

## Protocolo de cultivo

### 1. Inoculación

- El Cordyceps **no se inocula con semilla de grano** — se usa **cultivo líquido (LC)** o micelio líquido.
- Preparar el LC con anterioridad (ver docs/protocolos/cultivo-liquido.md).
- Inocular 5–10 ml de LC por frasco bajo condiciones estériles (flujo laminar o glove box).

### 2. Incubación (oscuridad total)

- Mantener en oscuridad completa a 22–26 °C durante 14–21 días.
- El micelio coloniza el arroz uniformemente (color blanco denso).
- **No exposición a luz** durante esta etapa — interrumpe el ciclo de señalización.

### 3. Inducción y fructificación

1. Cuando el sustrato esté 100 % colonizado, iniciar ciclo de luz 12/12 h.
2. Los primeros estróbilos (dedos naranjas) aparecen en 7–14 días.
3. Mantener el ciclo de luz estricto durante toda la fructificación (45–60 días).
4. La humedad debe estar entre 80–90 % pero sin agua libre sobre el sustrato.

### 4. Cosecha

- Cosechar cuando los estróbilos tienen 5–10 cm y antes de que liberen esporas (superficie cambia de lisa a granulada).
- Cortar con tijeras desinfectadas en la base.
- El sustrato puede producir una segunda tanda si se mantienen las condiciones.

---

## Procesamiento

El Cordyceps se consume casi exclusivamente en forma seca o en extracto:

1. **Seco:** deshidratar a 45–50 °C (temperatura baja para preservar compuestos activos).
2. **Polvo:** moler y encapsular.
3. **Extracción dual:** agua (cordycepina, adenosina) + alcohol (otros compuestos).

---

## Compuestos activos

| Compuesto | Propiedad estudiada |
|----------|-------------------|
| Cordycepina (3'-deoxyadenosina) | Adaptogénico, antifatiga, antitumoral |
| Adenosina | Vasodilatación, regulación cardiovascular |
| Beta-glucanos | Inmunomodulación |

---

## Mercado y precios

El Cordyceps militaris cultivado es el sustituto viable del C. sinensis salvaje (el más caro del mundo — >$20.000 USD/kg). El cultivado tiene perfil similar a menor precio.

| Formato | Precio Colombia (COP) |
|---------|----------------------|
| Seco (estróbilos) | 200.000–400.000/kg |
| Polvo | 300.000–500.000/kg |
| Cápsulas 60 u | 80.000–150.000 |
| Extracto tintura 60 ml | 60.000–120.000 |

---

## Errores comunes

| Error | Consecuencia | Solución |
|-------|-------------|---------|
| Luz durante la incubación | Sin fructificación | Oscuridad total hasta colonización completa |
| Ciclo de luz irregular | Fructificación deforme o nula | Usar temporizador digital con batería de respaldo |
| Sustrato muy húmedo | Bacterias | Reducir agua al 80–85 g por 100 g de arroz |
| Inocular con semilla de grano (no LC) | Colonización muy lenta | Siempre usar cultivo líquido para Cordyceps |

---

## Referencias

- Holliday, J.C. & Cleaver, M. (2008). Medicinal value of the caterpillar fungi species of the genus Cordyceps. *Evidence-Based Complementary and Alternative Medicine*, 5(3).
- [Sporeworks — Cordyceps militaris cultivation guide](https://sporeworks.com)
