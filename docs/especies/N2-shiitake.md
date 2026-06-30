# Shiitake — Lentinula edodes

**Nivel de dificultad:** ⭐⭐ (Intermedio)
**Categoría:** Gourmet
**Tiempo total de cultivo:** 8–16 semanas

---

## Perfil de la cápsula

### Parámetros por etapa

| Parámetro | Incubación | Maduración (browning) | Fructificación |
|-----------|-----------|----------------------|---------------|
| Temperatura | 20–25 °C | 18–22 °C | 15–22 °C |
| Humedad relativa | 70–80 % | 65–70 % | 85–95 % |
| CO₂ máximo | sin límite activo | sin límite activo | 1.000 ppm |
| Luz | 0 h | 0 h | 12 h/día, indirecta |
| Duración estimada | 50–70 días | 7–14 días | 7–14 días por oleada |

> **Etapa de maduración (browning):** única en shiitake. Después de la colonización blanca, el bloque debe "marronarse" — el micelio forma una corteza café oscuro (primordia skin) que es señal de madurez para fructificar. Esta fase requiere menor humedad para inducir el endurecimiento.

### Archivo de perfil JSON

```json
{
  "especie": "Lentinula edodes",
  "nombre_comun": "Shiitake",
  "etapas": {
    "incubacion": {
      "temp_min": 20, "temp_max": 25,
      "humedad_min": 70, "humedad_max": 80,
      "co2_max": 9999,
      "luz_horas": 0,
      "duracion_dias": 60
    },
    "maduracion_browning": {
      "temp_min": 18, "temp_max": 22,
      "humedad_min": 65, "humedad_max": 70,
      "co2_max": 9999,
      "luz_horas": 0,
      "duracion_dias": 10
    },
    "fructificacion": {
      "temp_min": 15, "temp_max": 22,
      "humedad_min": 85, "humedad_max": 95,
      "co2_max": 1000,
      "luz_horas": 12,
      "duracion_dias": 10,
      "choque_frio": true,
      "temp_choque": 10,
      "duracion_choque_horas": 12,
      "inmersion_agua": true,
      "duracion_inmersion_horas": 8
    }
  }
}
```

---

## Sustrato

### Receta base (por bloque de 1,5 kg seco)

| Ingrediente | Cantidad (seco) | % |
|------------|----------------|---|
| Aserrín de maderas duras (roble, eucalipto, nogal) | 1.200 g | 80 % |
| Salvado de trigo | 200 g | 13 % |
| Harina de avena | 75 g | 5 % |
| Yeso agrícola (CaSO₄) | 30 g | 2 % |
| Agua (hasta FC 55–60 %) | ~2 L | — |

**pH objetivo:** 5,5–6,5. El shiitake prefiere sustratos ligeramente ácidos.

> **Importante:** a diferencia de la orellana, el shiitake se cultiva en **bloque compactado**, no en bolsa suelta. La densidad del bloque (0,5–0,6 g/cm³) afecta directamente la calidad del hongo.

### Maderas compatibles en Colombia

- **Eucalipto** (abundante, excelente sustrato)
- **Roble colombiano / encenillo** (Weinmannia spp.)
- **Nogal cafetero** (Cordia alliodora)
- Evitar maderas resinosas (pino, ciprés) — los terpenos inhiben el micelio.

---

## Protocolo de cultivo

### 1. Preparación del bloque

1. Mezclar todos los ingredientes secos.
2. Agregar agua gradualmente hasta FC 55–60 % (al apretar, caen máximo 2–3 gotas).
3. Llenar bolsas de polipropileno compactando bien (sin burbujas de aire).
4. Esterilizar en autoclave o olla a presión: 121 °C × 2,5 h.
5. Enfriar a temperatura ambiente en zona limpia antes de inocular.

### 2. Inoculación

1. Zona de inoculación desinfectada con UV + alcohol 70 %.
2. Inocular con semilla de grano a 10–15 % (150–200 g por bloque de 1,5 kg seco).
3. Sellar la bolsa. Marcar la fecha.

### 3. Incubación (50–70 días)

- Perfil `shiitake-incubacion.json` activo.
- Oscuridad total. El micelio blanco debe cubrir progresivamente todo el bloque.
- Temperatura crítica: mantener 22–24 °C. Por debajo de 18 °C la colonización se detiene.
- En Guarne: puede necesitar calefactor activo durante la noche.

### 4. Maduración / Browning (7–14 días)

- Cuando el bloque está 100 % colonizado (blanco), cambiar al perfil `shiitake-browning.json`.
- Reducir humedad al 65–70 % para endurecer la corteza.
- El bloque pasa de blanco brillante a café oscuro — es lo esperado.
- No intentar fructificar antes de que aparezca esta corteza café.

### 5. Inducción a fructificación

Hay dos métodos — usar el que corresponda a las condiciones de la cápsula:

**Método A — Choque de frío (recomendado):**
1. Bajar la temperatura de la cápsula a 10 °C durante 12 h.
2. Volver a 18–22 °C y mantener HR >85 %.
3. Primordios en 3–7 días.

**Método B — Inmersión en agua fría:**
1. Sacar el bloque de la bolsa y sumergir en agua fría (10–15 °C) durante 6–12 h.
2. Devolver a la cápsula con perfil de fructificación activo.

### 6. Cosecha

- Cosechar cuando el sombrero tiene 5–10 cm y el velo parcial (membrana entre sombrero y tallo) aún no se ha roto completamente.
- Torcer suavemente en la base.

---

## Eficiencia biológica esperada

| Oleada | BE% típico |
|--------|-----------|
| Primera | 40–60 % |
| Segunda | 20–35 % |
| **Total** | **60–95 %** |

El shiitake tiene menor BE que la orellana pero precio de mercado 2.5–3× mayor.

---

## Guía de problemas comunes

| Síntoma | Causa probable | Solución |
|---------|---------------|---------|
| Micelio no cubre el bloque después de 80 días | Temperatura baja (<18 °C) o inoculante débil | Aumentar calefacción, revisar calidad de semilla |
| El bloque no se marronea | Humedad muy alta o temperatura muy baja | Reducir HR a 65 % y mantener 20 °C |
| Primordios no aparecen tras el choque | Choque insuficiente o bloque inmaduro | Repetir inmersión en agua más fría |
| Sombrero con manchas amarillas | Golpe de calor o agua estancada | Mejorar ventilación, revisar drenaje de la cápsula |
| Micelio verde (Trichoderma) | Contaminación — cuarentena | Remover bloque, registrar lote |

---

## Postcosecha

- **Fresco:** refrigerar a 2–4 °C. Vida útil: 10–15 días (mayor que orellana).
- **Deshidratado:** 55–60 °C hasta < 8 % humedad. El shiitake seco tiene demanda premium.
- **Polvo:** base para salsas, caldos y suplementos.

---

## Mercado y precios

| Canal | Precio fresco (COP/kg) | Precio seco (COP/kg) |
|-------|----------------------|---------------------|
| Mayorista | 25.000–35.000 | 120.000–200.000 |
| Restaurantes | 35.000–50.000 | — |
| Directo / CSA | 40.000–60.000 | 180.000–280.000 |

---

## Referencias

- Stamets, P. (1993). *Growing Gourmet and Medicinal Mushrooms*, cap. Lentinula edodes.
- Przybylowicz, P. & Donoghue, J. (1990). *Shiitake Growers Handbook*. Kendall/Hunt.
- [Shroomery — Shiitake cultivation](https://www.shroomery.org)
