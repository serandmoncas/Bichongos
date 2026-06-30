# Orellana — Pleurotus ostreatus / djamor / citrinopileatus

**Nivel de dificultad:** ⭐ (Principiante)
**Categoría:** Gourmet
**Tiempo total de cultivo:** 4–6 semanas

---

## Perfil de la cápsula

### Parámetros por etapa

| Parámetro | Incubación | Fructificación |
|-----------|-----------|---------------|
| Temperatura | 20–24 °C | 14–20 °C |
| Humedad relativa | 70–80 % | 85–95 % |
| CO₂ máximo | sin límite activo | 1.000 ppm |
| Luz | 0 h (oscuridad) | 12 h/día, indirecta |
| Duración estimada | 14–21 días | 7–14 días por oleada |

### Archivo de perfil JSON

```json
{
  "especie": "Pleurotus ostreatus",
  "nombre_comun": "Orellana",
  "etapas": {
    "incubacion": {
      "temp_min": 20, "temp_max": 24,
      "humedad_min": 70, "humedad_max": 80,
      "co2_max": 9999,
      "luz_horas": 0,
      "duracion_dias": 18
    },
    "fructificacion": {
      "temp_min": 14, "temp_max": 20,
      "humedad_min": 85, "humedad_max": 95,
      "co2_max": 1000,
      "luz_horas": 12,
      "duracion_dias": 10,
      "choque_frio": false
    }
  }
}
```

> **Nota Guarne:** la temperatura natural (14–17 °C) coincide con el rango de fructificación. No se requiere climatización activa para esta especie en la sede piloto.

---

## Sustrato

### Receta base (por bolsa de 1 kg seco)

| Ingrediente | Cantidad | % |
|------------|----------|---|
| Paja de arroz o trigo | 850 g (seco) | 85 % |
| Salvado de trigo | 100 g | 10 % |
| Cal hidratada | 50 g | 5 % |
| Agua (hasta FC 60–65 %) | ~1,5 L | — |

**Prueba de campo (Field Capacity):** apretar un puñado de sustrato húmedo — deben caer solo 1–2 gotas. Si cae un chorro continuo, está demasiado húmedo.

**pH objetivo:** 6,0–7,0 (la cal ayuda a alcanzar este rango y reduce competidores).

### Sustratos alternativos

- Bagazo de caña de azúcar (abundante en Antioquia)
- Pulpa de café (subproducto local, excelente resultado)
- Tusa de maíz triturada + paja (50/50)
- Aserrín de maderas blandas (mezclar con paja para mejorar estructura)

---

## Protocolo de cultivo

### 1. Preparación del sustrato

1. Picar la paja en trozos de 5–10 cm.
2. Hidratar en agua con cal (5 g/L) durante 12–18 h en frío, o pasteurizar a 80 °C × 1.5 h.
3. Escurrir hasta Field Capacity (FC 60–65 %).
4. Enfriar a temperatura ambiente antes de inocular.

### 2. Inoculación

1. Desinfectar la zona de inoculación con alcohol 70 % y luz UV 30 min antes.
2. Mezclar sustrato + semilla de grano a razón de 15–20 % (150–200 g semilla por kg sustrato seco).
3. Empacar en bolsa de polipropileno y sellar con micro-pore o filtro de disco.
4. Etiquetar: fecha, cepa, lote.

### 3. Incubación

- Cargar la bolsa en la **cápsula de incubación** con perfil `orellana-incubacion.json`.
- Mantener oscuridad total.
- Revisar diariamente: micelio blanco y esponjoso = normal; verde, negro, naranja o amarillo = contaminación → cuarentena inmediata.
- Tiempo esperado: 14–21 días para colonización completa (micelio cubre toda la bolsa).

### 4. Inducción a fructificación

No requiere choque de frío. La simple reducción de temperatura y el aumento de humedad son suficientes:
1. Trasladar a la **cápsula de fructificación** con perfil `orellana-fructificacion.json`.
2. Hacer cortes en la bolsa (ventanas de 5–8 cm) en los puntos donde emergerán los primordios.
3. Inicio de primordios: 3–7 días después del corte.

### 5. Cosecha

- Cosechar cuando el sombrero tiene 5–15 cm de diámetro y los bordes aún están enrollados hacia abajo.
- Torcer y jalar en la base (no cortar con cuchillo — reduce riesgo de bacterias).
- No dejar hongos viejos en la bolsa — liberan esporas que contaminan la cápsula.

### 6. Oleadas

- Después de la primera cosecha: limpiar residuos, remojar el bloque 4–6 h en agua fría.
- Devolver a la cápsula. Segunda oleada en 10–14 días.
- Con buen manejo: 3 oleadas por bolsa antes de que el sustrato se agote.

---

## Eficiencia biológica esperada

| Oleada | BE% típico |
|--------|-----------|
| Primera | 60–80 % |
| Segunda | 30–50 % |
| Tercera | 10–20 % |
| **Total** | **100–150 %** |

*BE% = (peso húmedo cosechado / peso seco del sustrato) × 100*

---

## Guía de problemas comunes

| Síntoma | Causa probable | Solución |
|---------|---------------|---------|
| Primordios no aparecen | Humedad insuficiente, CO₂ alto o temp muy alta | Verificar parámetros en dashboard, remojar bloque |
| Sombrero pequeño y tallo largo | CO₂ elevado (>1.500 ppm) | Revisar extractor FAE, limpiar filtro |
| Bordes ondulados / deformes | Temperatura irregular | Revisar calefactor o posición del termómetro |
| Coloración amarilla en micelio | Estrés por calor o bacterias incipientes | Bajar temperatura, evaluar contaminación |
| Micelio verde (Trichoderma) | Contaminación — cuarentena | Remover bolsa, registrar lote, revisar técnica |

---

## Postcosecha y conservación

- **Fresco:** refrigerar a 2–4 °C. Vida útil: 5–10 días.
- **Deshidratado:** 50–55 °C en deshidratador hasta < 8 % humedad. Vida útil: 12–18 meses.
- **Polvo:** moler deshidratado. Uso en restaurantes y cocina.

---

## Mercado y precios

| Canal | Precio (COP/kg) | Observaciones |
|-------|----------------|--------------|
| Mayorista / plazas | 10.000–12.000 | Volumen, pago rápido |
| Restaurantes | 14.000–20.000 | Requiere entrega constante |
| Cajas CSA / directo | 18.000–25.000 | Mayor margen, fidelización |
| Deshidratada | 80.000–120.000 | Por kg de producto seco |

**Variedad más vendida en Colombia:** orellana gris (P. ostreatus). La rosada (P. djamor) tiene precio premium pero menor vida de anaquel.

---

## Referencias específicas

- Stamets, P. (1993). *Growing Gourmet and Medicinal Mushrooms*, cap. Pleurotus.
- Oei, P. (2003). *Mushroom Cultivation*, cap. 5: Pleurotus cultivation.
- [Shroomery — Pleurotus cultivation forum](https://www.shroomery.org/forums/postlist.php/Board/14)
