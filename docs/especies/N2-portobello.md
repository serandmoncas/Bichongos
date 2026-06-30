# Portobello / Crimini / Paris — Agaricus bisporus

**Nivel de dificultad:** ⭐⭐ (Intermedio)
**Categoría:** Gourmet
**Tiempo total de cultivo:** 10–14 semanas

---

## Perfil de la cápsula

| Parámetro | Incubación (fase I) | Acondicionamiento (fase II) | Fructificación |
|-----------|--------------------|-----------------------------|---------------|
| Temperatura | 22–25 °C | 45–60 °C (pasteurización) → 25 °C | 16–20 °C |
| Humedad relativa | 70–80 % | — | 85–90 % |
| CO₂ máximo | sin límite | sin límite | **800 ppm** (el más bajo del proyecto) |
| Luz | 0 h | 0 h | 12 h/día |
| Duración | 14–21 días | 7 días | 7–10 días por oleada |

> **Particularidad:** Agaricus bisporus es el único del proyecto que requiere compostaje en dos fases y una **capa de casing** (turba + cal) sobre el sustrato para iniciar la fructificación.

### Archivo de perfil JSON

```json
{
  "especie": "Agaricus bisporus",
  "nombre_comun": "Portobello / Crimini / Paris",
  "etapas": {
    "incubacion": {
      "temp_min": 22, "temp_max": 25,
      "humedad_min": 70, "humedad_max": 80,
      "co2_max": 9999,
      "luz_horas": 0,
      "duracion_dias": 18
    },
    "fructificacion": {
      "temp_min": 16, "temp_max": 20,
      "humedad_min": 85, "humedad_max": 90,
      "co2_max": 800,
      "luz_horas": 12,
      "duracion_dias": 8,
      "casing_requerido": true
    }
  }
}
```

---

## Sustrato — Compost en dos fases

### Fase I — Compostaje

| Ingrediente | % |
|------------|---|
| Paja de trigo | 60 % |
| Estiércol de caballo (o pollinaza) | 30 % |
| Yeso agrícola | 5 % |
| Urea / sulfato de amonio | 5 % |

- Humedecer hasta 70–75 % de humedad.
- Voltear cada 2–3 días durante 14–21 días (proceso aeróbico, temperatura interna 65–75 °C).

### Fase II — Pasteurización y acondicionamiento

- Pasteurizar el compost a 57–60 °C durante 6–8 h en la cápsula o cámara.
- Bajar temperatura a 25 °C y mantener 5–7 días para que los microorganismos benéficos colonicen.

### Capa de casing

| Ingrediente | Proporción |
|------------|-----------|
| Turba (peat moss) | 70 % |
| Cal dolomita | 30 % |
| Agua | Hasta pH 7,0–7,5 |

- Aplicar 2–3 cm sobre el sustrato colonizado antes de iniciar fructificación.

---

## Protocolo de cultivo

1. Preparar compost (Fase I + Fase II).
2. Inocular con semilla de Agaricus (spawn de grano o semilla de caso de madera).
3. Incubar hasta colonización completa del compost.
4. Aplicar capa de casing uniformemente.
5. Esperar 7–10 días, bajar temperatura a 16–18 °C, aumentar HR a 85–90 %.
6. Primordios aparecen en 7–14 días desde el casing.
7. Cosechar cuando el velo parcial aún está intacto (Paris/Crimini) o roto (Portobello).

---

## Diferencia entre variedades

| Variedad | Estado de cosecha | Tamaño sombrero | Precio relativo |
|----------|-----------------|----------------|----------------|
| **Paris** | Velo cerrado, botón | 2–4 cm | 1× |
| **Crimini** | Velo cerrado o semiabierto | 4–8 cm | 1.2× |
| **Portobello** | Velo abierto, láminas visibles | 10–15 cm | 1.5× |

---

## Guía de problemas comunes

| Síntoma | Causa | Solución |
|---------|-------|---------|
| Sin primordios tras el casing | pH del casing incorrecto o temp alta | Verificar pH 7.0–7.5, bajar temp a 16 °C |
| Manchas marrones en sombrero | Bacterias (Pseudomonas) | Mejorar higiene del agua, reducir agua libre |
| CO₂ alto, tallos alargados | FAE insuficiente | Aumentar extractor, verificar sello de cápsula |

---

## Mercado y precios

| Variedad | Precio mayorista (COP/kg) | Precio restaurantes |
|----------|--------------------------|---------------------|
| Paris (botón blanco) | 8.000–12.000 | 12.000–18.000 |
| Crimini | 10.000–15.000 | 15.000–22.000 |
| Portobello | 15.000–25.000 | 22.000–35.000 |

---

## Referencias

- Stamets, P. (1993). *Growing Gourmet and Medicinal Mushrooms*, cap. Agaricus bisporus.
- Oei, P. (2003). *Mushroom Cultivation*, cap. 6: Agaricus cultivation.
