# Reishi — Ganoderma lucidum

**Nivel de dificultad:** ⭐⭐⭐ (Avanzado)
**Categoría:** Funcional / Medicinal
**Tiempo total de cultivo:** 12–20 semanas

---

## Perfil de la cápsula

| Parámetro | Incubación | Antler (cuernos) | Fructificación (cap) |
|-----------|-----------|-----------------|---------------------|
| Temperatura | 25–28 °C | 25–28 °C | **25–30 °C** ← calefacción activa |
| Humedad relativa | 70–80 % | 95–100 % | 85–95 % |
| CO₂ | sin límite | **> 3.000 ppm** | **< 700 ppm** |
| Luz | 0 h | mínima | 12 h/día |
| Duración | 30–45 días | 14–21 días | 30–60 días |

> **Especie tropical:** Ganoderma lucidum requiere temperaturas de 25–30 °C durante todo el ciclo. En Guarne (14–17 °C exterior), la cápsula de Reishi necesita calefacción activa continua. Es el mayor consumo energético del proyecto.

> **Dos etapas de fructificación distintas:** primero forma "antler" (cuernos alargados) con CO₂ alto, luego el "cap" (sombrero en forma de riñón) con CO₂ bajo. Esta transición es deliberada y controlada por el perfil IoT.

### Archivo de perfil JSON

```json
{
  "especie": "Ganoderma lucidum",
  "nombre_comun": "Reishi",
  "etapas": {
    "incubacion": {
      "temp_min": 25, "temp_max": 28,
      "humedad_min": 70, "humedad_max": 80,
      "co2_max": 9999,
      "luz_horas": 0,
      "duracion_dias": 40
    },
    "antler": {
      "temp_min": 25, "temp_max": 28,
      "humedad_min": 95, "humedad_max": 100,
      "co2_min": 3000,
      "luz_horas": 0,
      "duracion_dias": 18
    },
    "fructificacion_cap": {
      "temp_min": 25, "temp_max": 30,
      "humedad_min": 85, "humedad_max": 95,
      "co2_max": 700,
      "luz_horas": 12,
      "duracion_dias": 45
    }
  }
}
```

---

## Sustrato

### Receta base (por bloque de 2 kg seco)

| Ingrediente | % |
|------------|---|
| Aserrín de roble o eucalipto | 80 % |
| Salvado de trigo | 15 % |
| Harina de soya desengrasada | 5 % |
| Agua (hasta FC 55–60 %) | — |

**pH objetivo:** 5,5–6,0 (ligeramente ácido, típico de madera dura descompuesta).

> El Reishi crece naturalmente sobre muñones de roble, encino y otras maderas duras. El sustrato debe ser de madera dura exclusivamente — no paja, no maíz.

---

## Protocolo de cultivo

### 1–3. Preparación, inoculación e incubación

1. Esterilizar bloque de aserrín en autoclave: 121 °C × 3 h (más tiempo que otros por la densidad).
2. Inocular con semilla de grano al 10–15 %.
3. Incubar a 26–28 °C. **Crítico:** mantener la temperatura — sin calefacción la colonización se detiene o se contamina.
4. Tiempo de colonización: 30–45 días (lento comparado con orellana).

### 4. Etapa Antler (formación de cuernos)

1. Al completarse la colonización, aumentar HR al 95–100 % y acumular CO₂ > 3.000 ppm (reducir FAE).
2. El micelio forma "cuernos" o "antlers" — estructuras alargadas de color rojo brillante.
3. Esta etapa puede mantenerse o transitarse al cap.

### 5. Transición al Cap

1. Abrir el FAE para bajar CO₂ < 700 ppm.
2. Activar luz 12 h/día.
3. El cuerno se aplana y forma el sombrero en forma de riñón (cap) con borde blanco brillante.
4. El cap madura durante 30–60 días hasta que el borde blanco desaparece.

### 6. Cosecha

- **Momento óptimo:** cuando el borde blanco del cap ha desaparecido completamente y la superficie es café-rojo brillante uniforme.
- Si aparece polvo dorado en la cápsula: son esporas — el Reishi está maduro o sobremadurado.
- Cortar el esporocarpo en la base con cuchillo desinfectado.

---

## Procesamiento post-cosecha

El Reishi no se consume fresco — es demasiado duro y amargo. Todo el valor está en el extracto.

### Opciones de procesamiento

1. **Reishi seco en rodajas:** secar a 55–60 °C hasta < 8 % humedad. Para decocción en agua.
2. **Polvo:** moler el seco en polvo fino. Base para cápsulas y tés.
3. **Extracto acuoso:** hervir 1 h en agua, concentrar, secar en spray-drier (o reducir con calor).
4. **Extracto dual (agua + alcohol):** extracción secuencial para capturar tanto polisacáridos (agua) como triterpenos (alcohol).

---

## Compuestos activos clave

| Compuesto | Tipo | Propiedad asociada |
|----------|------|-------------------|
| Beta-glucanos | Polisacárido | Inmunomodulación |
| Ganodérico ácido | Triterpenoide | Adaptogénico, hepatoprotector |
| Germanio orgánico | Mineral | Oxigenación celular |

---

## Mercado y precios

| Formato | Precio (COP/kg o unidad) |
|---------|------------------------|
| Seco en rodajas | 80.000–120.000 COP/kg |
| Polvo | 150.000–250.000 COP/kg |
| Extracto tintura (60 ml) | 40.000–80.000 COP/frasco |
| Cápsulas 500 mg (60 u) | 60.000–120.000 COP |

---

## Guía de problemas comunes

| Síntoma | Causa | Solución |
|---------|-------|---------|
| Colonización muy lenta | Temperatura baja (<24 °C) | Reforzar calefacción, verificar termostato |
| Antlers deformados | Fluctuaciones de temperatura o humedad | Estabilizar control IoT, aislar mejor la cápsula |
| Borde blanco que no desaparece | Poca luz o FAE insuficiente | Verificar ciclo de luz, bajar CO₂ |
| Esporas excesivas en cápsula | Cosecha tardía | Cosechar cuando borde blanco recién desaparece |

---

## Referencias

- Stamets, P. (1993). *Growing Gourmet and Medicinal Mushrooms*, cap. Ganoderma.
- Wasser, S.P. (2002). Medicinal mushrooms as a source of antitumor polysaccharides. *Applied Microbiology and Biotechnology*.
- [Fungi Perfecti — Reishi](https://www.fungi.com)
