# Psilocybe spp.

**Nivel de dificultad:** ⭐⭐⭐⭐ (Experto — con consideraciones legales y éticas)
**Categoría:** Medicinal / Investigación
**Tiempo total de cultivo:** 4–8 semanas

---

## Marco legal en Colombia

**Esta sección es informativa. El cultivo debe realizarse dentro del marco legal vigente.**

| Aspecto | Estado legal |
|---------|-------------|
| Posesión personal (dosis) | No penalizado — Ley 30/1986, art. 2; Sentencia C-491/12 CC |
| Cultivo comercial | Penalizado bajo la Ley 30/1986 |
| Uso terapéutico asistido | En proceso de regulación — seguir decretos del MinSalud |
| Investigación científica | Posible bajo protocolo con aval de comité de ética |

**Estrategia recomendada para Bichongos:**
- Cultivo experimental bajo protocolo documentado para investigación.
- Zona de acceso restringido, con registro de entradas y salidas.
- Preparación para un marco regulatorio que probablemente avanzará en los próximos 5–10 años (siguiendo el modelo de Canadá, Jamaica, Países Bajos y estados de EE.UU.).
- Mantener documentación de todo: propósito, cantidad, disposición final.

---

## Perfil de la cápsula

| Parámetro | Incubación | Fructificación |
|-----------|-----------|---------------|
| Temperatura | 25–28 °C | 22–26 °C |
| Humedad relativa | 70–80 % | 90–95 % |
| CO₂ máximo | sin límite | 1.500 ppm |
| Luz | 0 h | 12 h/día, indirecta |
| Duración | 14–21 días | 10–14 días por oleada |

### Archivo de perfil JSON

```json
{
  "especie": "Psilocybe cubensis",
  "nombre_comun": "Psilocybe",
  "zona_restringida": true,
  "requiere_autorizacion": true,
  "etapas": {
    "incubacion": {
      "temp_min": 25, "temp_max": 28,
      "humedad_min": 70, "humedad_max": 80,
      "co2_max": 9999,
      "luz_horas": 0,
      "duracion_dias": 18
    },
    "fructificacion": {
      "temp_min": 22, "temp_max": 26,
      "humedad_min": 90, "humedad_max": 95,
      "co2_max": 1500,
      "luz_horas": 12,
      "duracion_dias": 12
    }
  }
}
```

> **Nota para Guarne:** la temperatura de incubación (25–28 °C) requiere calefacción activa en la sede piloto.

---

## Especies del género

| Especie | Temperatura | Origen | Disponibilidad de cepas |
|---------|------------|--------|------------------------|
| P. cubensis | 22–28 °C (tropical) | América tropical | Alta — la más cultivada globalmente |
| P. semilanceata | 10–18 °C (fría) | Europa / zonas templadas | Difícil — no se cultiva bien en sustrato |
| P. azurescens | 8–16 °C (muy fría) | Costa noroeste EE.UU. | Difícil — madera, exterior |
| P. cyanescens | 10–18 °C | Europa, EE.UU. | Intermedia |
| P. mexicana | 20–25 °C | México | Moderada |

**Para Colombia:** P. cubensis es la especie más adaptada al clima (requiere calor) y la que tiene mayor documentación técnica de cultivo.

---

## Técnicas de cultivo

### Técnica PF Tek (más sencilla — ideal para experimentación)

- Sustrato: mezcla de harina de arroz integral + vermiculita + agua (en frascos de vidrio).
- Esterilizar: 90 min en baño de vapor (no requiere autoclave).
- Inocular con jeringa de esporas.
- Incubar a 26–28 °C durante 14–21 días.
- Fructificar en contenedor con sustrato de bulk (coco + vermiculita).
- Las oleadas de producción son múltiples (3–5 por sustrato).

### Técnica Bulk (mayor volumen)

- Bulk substrate: fibra de coco (coir), perlita, turba, harina de trigo tostada.
- Spawn run en grano de trigo o arroz.
- Casing opcional (turba + cal) para mejor distribución de primordios.
- Producción por metro cuadrado de superficie: 100–300 g por oleada.

---

## Compuestos activos

| Compuesto | Mecanismo |
|----------|-----------|
| Psilocibina | Profármaco — se convierte en psilocina in vivo |
| Psilocina | Agonista parcial de receptores 5-HT2A |
| Baeocistina | Compuesto secundario, efecto menos estudiado |
| Norbaeocistina | Compuesto secundario |

### Contenido típico en P. cubensis

- Psilocibina: 0,5–1,0 % del peso seco
- Psilocina: 0,1–0,3 % del peso seco

---

## Consideraciones de seguridad en el laboratorio

- **Zona segregada:** la cápsula de Psilocybe debe estar en área de acceso controlado con registro de entradas.
- **Etiquetado claro:** todos los recipientes con etiqueta de contenido, fecha, cantidad, responsable.
- **Registro de lote:** cantidad producida, disposición final, quién tuvo acceso.
- **Spore prints / jeringa de esporas:** almacenar en frío, etiquetadas, fuera del alcance de personal no autorizado.

---

## Investigación clínica de referencia

La evidencia científica sobre uso terapéutico asistido con psilocibina ha crecido significativamente desde 2016:

- Carhart-Harris, R. et al. (2021). Trial of psilocybin versus escitalopram for depression. *New England Journal of Medicine*.
- Davis, A.K. et al. (2021). Effects of psilocybin-assisted therapy on major depressive disorder. *JAMA Psychiatry*.
- [Johns Hopkins Center for Psychedelic and Consciousness Research](https://hopkinspsychedelic.org)
- [MAPS — Multidisciplinary Association for Psychedelic Studies](https://maps.org)

---

## Seguimiento legal Colombia

- MinSalud Colombia — Resolución sobre uso medicinal de sustancias psicoactivas (en desarrollo).
- [Fundación CAMBIA — política de drogas Colombia](https://cambiapoliticadedrogas.org)
