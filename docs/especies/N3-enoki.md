# Enoki — Flammulina velutipes

**Nivel de dificultad:** ⭐⭐⭐ (Avanzado)
**Categoría:** Gourmet
**Tiempo total de cultivo:** 8–10 semanas

---

## Perfil de la cápsula

| Parámetro | Incubación | Fructificación |
|-----------|-----------|---------------|
| Temperatura | 22–25 °C | **7–12 °C** ← requiere frío activo |
| Humedad relativa | 70–80 % | 85–90 % |
| CO₂ | sin límite | **> 2.000 ppm** ← alto intencional |
| Luz | 0 h | **mínima** (< 100 lux) |
| Duración | 21–30 días | 14–21 días |

> **Lógica invertida:** el Enoki comercial (tallo largo, sombrero pequeño) se produce de forma opuesta al resto de especies — necesita frío, CO₂ alto y poca luz. La cápsula de Enoki es la única del proyecto que requiere refrigeración activa y sello parcial para acumular CO₂.

### Archivo de perfil JSON

```json
{
  "especie": "Flammulina velutipes",
  "nombre_comun": "Enoki",
  "etapas": {
    "incubacion": {
      "temp_min": 22, "temp_max": 25,
      "humedad_min": 70, "humedad_max": 80,
      "co2_max": 9999,
      "luz_horas": 0,
      "duracion_dias": 25
    },
    "fructificacion": {
      "temp_min": 7, "temp_max": 12,
      "humedad_min": 85, "humedad_max": 90,
      "co2_min": 2000,
      "co2_max": 4000,
      "luz_max_lux": 100,
      "luz_horas": 4,
      "duracion_dias": 18
    }
  }
}
```

---

## Diseño especial de la cápsula para Enoki

Enoki **no usa la cápsula Tipo 2 Estándar** de madera — se construye sobre una **cápsula Tipo 1
Mini (nevera doméstica modificada, 150–200 L)**, igual que las cápsulas de I+D (ver
`docs/capsula/diseno-capsula.md`). El compresor real de la nevera ya está dimensionado para ese
volumen y cubre el delta-T necesario (ambiente de Guarne 14–17 °C → objetivo 7–12 °C) sin
sobredimensionar como haría un mini-split, ni quedar corto como un módulo Peltier sin calcular.

1. **Aislamiento térmico:** ya incorporado en la nevera; si se necesita margen extra en sedes más
   cálidas, agregar espuma de poliestireno en la puerta/junta, no reemplazar el sistema de frío.
2. **Sistema de frío:** compresor original de la nevera, controlado por el ESP32 vía relé (con
   protección de tiempo mínimo entre encendidos para proteger el compresor — igual que el resto
   de cápsulas Tipo 1).
3. **Ventilación reducida:** el extractor FAE solo opera en pulsos cortos para mantener CO₂ > 2.000 ppm. Si el CO₂ sube mucho (> 5.000 ppm), el extractor corre 30 segundos.
4. **Oscurecimiento:** cubrir el interior con material opaco. Los 4 h de luz son tenue (< 100 lux) para guiar el crecimiento vertical.

---

## Sustrato

### Receta base

| Ingrediente | % |
|------------|---|
| Aserrín de maderas duras | 70 % |
| Salvado de trigo | 20 % |
| Cáscara de arroz (para aireación) | 10 % |
| Agua (hasta FC 60 %) | — |

**pH objetivo:** 6,0–6,5

---

## Protocolo de cultivo

### 1–3. Preparación, inoculación e incubación

- Igual que shiitake: esterilizar en autoclave, inocular con 15 % de semilla de grano, incubar a 22–25 °C.
- La incubación es en condiciones normales — el frío solo se activa para la fructificación.

### 4. Inducción a fructificación

1. Cuando el bloque esté 100 % colonizado, transferir a la **cápsula de frío**.
2. Bajar temperatura a 7–10 °C.
3. Mantener humedad 85–90 % con nebulizador de ciclos cortos.
4. Reducir FAE para acumular CO₂ > 2.000 ppm.
5. Primordios pequeños aparecen en 7–10 días.

### 5. Guía de crecimiento

- Los tallos crecen hacia arriba buscando la poca luz disponible.
- Para tallos más uniformes: colocar un tubo de cartón o papel sobre el bloque como "chimenea" de 10–15 cm. El Enoki crece dentro del tubo, produciendo los manojos característicos.
- Cosechar cuando los tallos miden 10–15 cm y el sombrero aún es pequeño (< 1 cm de diámetro).

---

## Guía de problemas comunes

| Síntoma | Causa | Solución |
|---------|-------|---------|
| Sombreros grandes y tallos cortos | Temperatura demasiado alta o CO₂ bajo | Bajar temp a 8 °C, reducir FAE |
| Sin primordios | Bloque no suficientemente colonizado | Esperar o verificar calidad de semilla |
| Condensación excesiva | Diferencial de temperatura alto | Ajustar aislamiento de la cápsula |
| Micelio naranja (Neurospora) | Contaminación — cuarentena | Revisar protocolo de esterilización |

---

## Mercado y precios

El Enoki cultivado es difícil de conseguir fresco en Colombia — precio premium.

| Canal | Precio (COP/kg) |
|-------|----------------|
| Restaurantes asiáticos / fusión | 30.000–50.000 |
| Tiendas especializadas | 25.000–40.000 |
| Importado (referencia) | 40.000–70.000 |

---

## Referencias

- Stamets, P. (1993). *Growing Gourmet and Medicinal Mushrooms*, cap. Flammulina.
- Chang, S.T. & Miles, P.G. (2004). *Mushrooms: Cultivation, Nutritional Value, Medicinal Effect, and Environmental Impact*.
