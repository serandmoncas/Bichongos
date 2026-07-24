# Eryngii — Pleurotus eryngii (King Oyster / Ostra Rey)

**Nivel de dificultad:** ⭐⭐ (Intermedio)
**Categoría:** Gourmet
**Tiempo total de cultivo:** 5–6 semanas

> Pedido por el cliente La Jobiteka en la reunión del 2026-07-01 (ver CON-11 y CUL-21 en `BACKLOG.md`).

---

## Perfil de la cápsula

### Parámetros por etapa

| Parámetro | Incubación | Inducción | Fructificación |
|-----------|-----------|-----------|-----------------|
| Temperatura | 22–26 °C | **10–15 °C** (choque 24 h a 12 °C) | **10–16 °C** |
| Humedad relativa | 85–95 % | 90–95 % | 85–90 % |
| CO₂ máximo | sin límite activo | 800 ppm | 900 ppm |
| Luz | 0 h | 10 h/día (dispara primordios) | 10 h/día, indirecta |
| Duración estimada | ~25 días | ~2 días | 10–14 días |

> **Fructifica en frío:** a diferencia del resto de especies gourmet del proyecto (que fructifican
> 15–22 °C), Eryngii necesita 10–16 °C para producir tallos gruesos y sombreros bien formados —
> comparte cápsula fría con Enoki (Tipo 1 Mini, ver `docs/capsula/diseno-capsula.md`), no la
> cápsula Estándar del resto de especies N2.

> **Sensibilidad al CO₂:** exceso de CO₂ en fructificación produce tallos largos y delgados con
> sombreros pequeños — comercialmente indeseable (el valor de Eryngii está justamente en el tallo
> grueso tipo "King Oyster"). Sensibilidad similar a melena de león, aunque menos extrema.

### Archivo de perfil JSON

```json
{
  "especie": "Pleurotus eryngii",
  "nombre_comun": "Eryngii (King Oyster / Ostra Rey)",
  "etapas": {
    "incubacion": {
      "temp_min": 22, "temp_max": 26,
      "humedad_min": 85, "humedad_max": 95,
      "co2_max": 9999,
      "luz_horas": 0,
      "duracion_dias": 25
    },
    "induccion": {
      "temp_min": 10, "temp_max": 15,
      "humedad_min": 90, "humedad_max": 95,
      "co2_max": 800,
      "luz_horas": 10,
      "duracion_dias": 2,
      "choque_frio": true,
      "temp_choque": 12,
      "duracion_choque_horas": 24
    },
    "fructificacion": {
      "temp_min": 10, "temp_max": 16,
      "humedad_min": 85, "humedad_max": 90,
      "co2_max": 900,
      "luz_horas": 10,
      "duracion_dias": 12
    }
  }
}
```

---

## Sustrato

### Receta base (por bloque de 1,2 kg seco)

| Ingrediente | Cantidad (seco) | % |
|------------|----------------|---|
| Aserrín de maderas duras (roble, eucalipto, nogal) | 900 g | 75 % |
| Salvado de trigo | 240 g | 20 % |
| Yeso agrícola (CaSO₄) | 36 g | 3 % |
| Cal hidratada | 24 g | 2 % |
| Agua (hasta FC 60–65 %) | ~1,8 L | — |

**pH objetivo:** 6,0–7,0 (más neutro que shiitake).

> **Poda de primordios:** a diferencia de la orellana (donde se dejan crecer todos los racimos),
> en Eryngii se recomienda dejar solo 2–3 primordios por punto de fructificación y remover el
> resto a mano — esto concentra el crecimiento en tallos gruesos en vez de muchos tallos delgados.

---

## Protocolo de cultivo

### 1. Preparación e inoculación

1. Mezclar ingredientes secos, hidratar hasta FC 60–65 %.
2. Compactar en bolsas de polipropileno (bloque, igual que shiitake — no bolsa suelta como orellana).
3. Esterilizar en autoclave/olla a presión: 121 °C × 2 h.
4. Enfriar en zona limpia e inocular con semilla de grano al 10–15 %.

### 2. Incubación (~25 días)

- Perfil `incubacion` activo. Oscuridad total.
- Colonización más lenta que orellana regular — no apresurar el paso a inducción antes de que el bloque esté 100 % blanco.

### 3. Inducción (choque de frío, 24 h a 10–13 °C)

- Bajar la cápsula a la etapa `induccion`: 24 h de choque frío + introducir luz indirecta (10 h/día) + aumentar FAE.
- Este choque es más largo que el de shiitake (12 h) — Eryngii necesita más tiempo frío para formar primordios gruesos en vez de muchos brotes delgados.

### 4. Fructificación (10–14 días)

- Mantener 10–16 °C, HR 85–90 %, ventilación activa para controlar CO₂ (< 900 ppm).
- Podar a 2–3 primordios por punto de fructificación en cuanto sean visibles.
- Cosechar cuando el sombrero esté convexo y aún no plano, con el tallo firme (2,5–4 cm de diámetro).

---

## Eficiencia biológica esperada

| Oleada | BE% típico |
|--------|-----------|
| Primera | 30–50 % |
| Segunda | 15–25 % |
| **Total** | **45–70 %** |

BE% menor que orellana (por la poda de primordios), pero el tallo grueso tiene precio de mercado significativamente mayor.

---

## Guía de problemas comunes

| Síntoma | Causa probable | Solución |
|---------|---------------|---------|
| Tallos largos y delgados, sombrero pequeño | CO₂ demasiado alto en fructificación | Aumentar ciclos de FAE, verificar que `co2_max` de la etapa se respete |
| No aparecen primordios tras el choque | Choque de frío insuficiente (< 24h) o bloque inmaduro | Repetir choque completo de 24h a 10–13 °C |
| Muchos primordios delgados en vez de pocos gruesos | Falta de poda manual | Podar a 2–3 primordios por punto apenas sean visibles |
| Sombrero deforme o decolorado | Poca luz o ventilación insuficiente | Confirmar 10h/día de luz indirecta y FAE activo |

---

## Postcosecha

- **Fresco:** refrigerar a 2–4 °C. Vida útil: 10–14 días (tallo grueso se conserva mejor que orellana).
- **Uso culinario:** el tallo se puede cortar en rodajas y cocinar como sustituto de vieira/escalope — es el atractivo comercial principal frente a otras orellanas.

---

## Mercado y precios

| Canal | Precio fresco (COP/kg) |
|-------|----------------------|
| Mayorista | 30.000–40.000 |
| Restaurantes | 40.000–60.000 |
| Directo / gourmet | 45.000–65.000 |

> Precio superior a shiitake en Colombia por ser menos común localmente — verificar con mercado real antes de fijar precio (ver COM-02 en `BACKLOG.md`).

---

## Referencias

- Stamets, P. (1993). *Growing Gourmet and Medicinal Mushrooms*, cap. Pleurotus eryngii.
- Royse, D.J. et al. — cultivation notes on King Oyster substrate formulations and cold-shock induction.
- [Shroomery — King Oyster cultivation](https://www.shroomery.org)
