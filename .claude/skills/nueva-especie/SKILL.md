---
name: nueva-especie
description: Genera en un solo paso la documentación técnica, el perfil JSON de cultivo, y la entrada en BACKLOG.md para una especie nueva de hongo en Bichongos. Usar cuando el usuario pida documentar una especie nueva, agregar un perfil de cultivo, o registrar una especie en el backlog de producción.
---

# Nueva especie — Bichongos

Genera de forma consistente los 3 artefactos que una especie nueva necesita en este proyecto,
evitando el gap que ya ocurrió antes (chaga y trufas tenían ficha en `docs/especies/` pero nunca
tuvieron perfil JSON ni entrada en `BACKLOG.md`).

## Proceso

1. **Recolectar datos** (conversación normal o `AskUserQuestion`, una pregunta a la vez):
   - Nombre común y nombre científico.
   - Nivel de dificultad: N1 (fácil) a N4 (avanzado/restringido).
   - Categoría: gourmet, funcional/medicinal, o restringida (investigación).
   - Por cada etapa de cultivo que aplique (típicamente `incubacion` y `fructificacion`, a veces
     una etapa intermedia como `induccion`): `temp_min`/`temp_max`, `humedad_min`/`humedad_max`,
     `co2_max`, `duracion_dias`.
   - Casos especiales si el usuario los menciona (frío, luz, inmersión, etc.) — mapear siempre a
     los nombres de campo ya establecidos en el proyecto, nunca inventar nombres nuevos:
     `co2_min`, `luz_horas`, `luz_inicio`/`luz_fin` (formato `"HH:MM"`), `calefaccion_activa`,
     `refrigeracion_activa`, `luz_max_lux`, `oscuridad_total`, `ciclo_luz_estricto`, `luz_tipo`,
     `choque_frio`, `duracion_choque_horas`, `temp_choque`, `induccion_inmersion`,
     `duracion_inmersion_horas`, `casing_requerido`, `casing_ph_min`/`casing_ph_max`, `fae_modo`.
   - Umbrales de alerta: `temp_critica_max`/`temp_critica_min`, `humedad_critica_min`,
     `co2_critico_max`, y `co2_critico_min` si la especie tiene lógica de CO2 mínimo (como Enoki).
   - Si la especie tiene restricción legal (ej. psilocibina): preguntar explícitamente y agregar
     `zona_restringida: true`, `marco_legal`, `requiere_autorizacion: true`.

2. **Leer 1-2 ejemplos existentes** en `docs/especies/` y `firmware/profiles/` antes de escribir,
   para igualar el formato y el nivel de detalle exactos (tablas, secciones, tono).

3. **Escribir la ficha técnica**: `docs/especies/N{nivel}-{slug}.md` (slug en minúsculas, guiones,
   sin tildes — ej. `N3-lions-mane.md`), siguiendo la misma estructura que los docs existentes.

4. **Escribir el perfil JSON en las DOS ubicaciones**, contenido idéntico byte a byte:
   - `firmware/profiles/N{nivel}-{slug}.json`
   - `firmware/capsula_core/data/profiles/N{nivel}-{slug}.json`

   (Estas dos carpetas deben mantenerse en sync — la primera es la fuente, la segunda es lo que se
   sube a SPIFFS. Escribir ambas siempre evita que se repita la deriva que existía antes.)

5. **Verificar el resultado del hook de validación** (`PostToolUse` sobre el `Write` del JSON). Si
   reporta errores, corregir el JSON antes de continuar — no ignorar el hook.

6. **Agregar una fila a `BACKLOG.md`**: leer el archivo primero para identificar el siguiente ID
   disponible en la épica de Documentación (`DOC-NN`) para la ficha, y en la épica de
   Producción/Cultivo (`CUL-NN`) para el perfil de cultivo, respetando la numeración y el formato
   de tabla existentes. No recalcular ni tocar los totales de la tabla "Estado General" — eso es
   un problema aparte, ya identificado, con su propio arreglo pendiente.

7. **Resumen final al usuario**: listar los 3 (o 4, contando las dos copias del JSON) archivos
   creados/modificados y confirmar que el hook de validación no reportó errores.

## Qué NO hacer

- No inventar nombres de campo nuevos fuera de la lista del paso 1 — si la especie necesita algo
  genuinamente nuevo, preguntar al usuario cómo llamarlo y proponer agregarlo también al validador
  de esquema (`.claude/hooks/validate-species-profile.py`) en un paso aparte, no silenciosamente.
- No escribir el JSON en una sola de las dos ubicaciones.
- No saltarse la fila de BACKLOG.md aunque parezca un detalle menor — es la causa raíz del gap que
  esta skill existe para evitar.
