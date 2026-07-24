# Harness Engineering para Bichongos — Diseño

**Fecha:** 2026-07-23
**Estado:** Aprobado, pendiente de implementación

## Contexto

La auditoría del proyecto (agente `claude-automation-recommender`) encontró que el repo no tiene
ningún skill, hook ni subagente propio (`.claude/` solo tiene un `settings.local.json` de permisos
vacío). Recomendó 4 piezas concretas, priorizadas por costo/beneficio y por dependencias entre
ellas (la skill de nueva especie reutiliza el validador de esquema). El usuario aprobó las 4, en
ese orden, con decisiones de diseño para cada una (ver más abajo).

Esto es la pieza "harness engineering" del pedido original de revisión de proyecto + guía de
Jorge + harness engineering — las otras dos piezas (adopción más amplia de la guía SDD, fixes de
documentación/negocio) se abordan por separado.

## Alcance

### 1. Hook anti-credenciales (`PreToolUse` sobre `Bash`)

**Por qué:** `.gitignore` ya excluye `config.h`, `secrets.h`, `.env`, `mosquitto_passwd`, pero es
una sola capa — un `git add -f` accidental o un archivo renombrado la salta. Defensa en
profundidad barata.

**Archivo:** `.claude/hooks/block-credential-commit.sh` (bash), registrado en
`.claude/settings.json`:

```json
{
  "PreToolUse": [
    {
      "matcher": "Bash",
      "hooks": [
        {
          "type": "command",
          "command": "bash $CLAUDE_PROJECT_DIR/.claude/hooks/block-credential-commit.sh",
          "timeout": 10
        }
      ]
    }
  ]
}
```

**Lógica del script:**
1. Leer JSON de stdin, extraer `.tool_input.command` con `jq`.
2. Si el comando no matchea `git[[:space:]]+commit` (regex bash), salir 0 sin hacer nada — no
   interferir con ningún otro comando Bash.
3. Si es un commit:
   - Listar archivos staged: `git -C "$CLAUDE_PROJECT_DIR" diff --cached --name-only`.
   - Bloquear si algún nombre matchea: `(^|/)config\.h$`, `(^|/)secrets\.h$`, `(^|/)\.env$`,
     `(^|/)mosquitto_passwd$`.
   - Revisar el contenido staged **excluyendo `*.example`** (esos archivos existen justamente
     para tener placeholders y sí deben commitearse):
     `git -C "$CLAUDE_PROJECT_DIR" diff --cached -- . ":(exclude)*.example"`.
   - Sobre ese diff (solo líneas agregadas, prefijo `+`), bloquear si aparece:
     - Token de Telegram: `[0-9]{8,10}:[A-Za-z0-9_-]{35}`
     - Cabecera de llave privada: `-----BEGIN (RSA |EC |OPENSSH )?PRIVATE KEY-----`
     - Asignación de credencial con valor no-vacío:
       `#define[[:space:]]+(WIFI_PASSWORD|MQTT_PASS|OTA_PASSWORD)[[:space:]]+"[^"]{4,}"`
4. Si algo matcheó: imprimir a stdout
   `{"hookSpecificOutput": {"permissionDecision": "deny"}, "systemMessage": "<qué patrón/archivo
   matcheó, SIN incluir el valor real>"}` y salir 0 (el bloqueo lo decide el campo
   `permissionDecision`, no el código de salida).
5. Si no matcheó nada: salir 0 sin imprimir nada.

**No debe:** bloquear commits que no toquen archivos sensibles, ni imprimir el secreto real en el
mensaje (solo el nombre del patrón/archivo).

### 2. Validador de esquema de perfiles (`PostToolUse` sobre `Edit|Write`)

**Por qué:** ya hay deriva real de esquema — 5 de 10 perfiles no tienen `choque_frio`, campos como
`co2_min`/`luz_max_lux`/`refrigeracion_activa`/`fae_modo` son exclusivos de 1-2 especies sin
ningún validador, y el firmware carga estos JSON directo a runtime sin chequeo.

**Archivo:** `.claude/hooks/validate-species-profile.py` (Python 3, sin dependencias externas),
registrado en `.claude/settings.json`:

```json
{
  "PostToolUse": [
    {
      "matcher": "Edit|Write",
      "hooks": [
        {
          "type": "command",
          "command": "python3 $CLAUDE_PROJECT_DIR/.claude/hooks/validate-species-profile.py",
          "timeout": 10
        }
      ]
    }
  ]
}
```

**Lógica del script:**
1. Leer JSON de stdin, extraer `.tool_input.file_path`.
2. Si la ruta no matchea `firmware/profiles/*.json` NI `firmware/capsula_core/data/profiles/*.json`,
   salir 0 sin hacer nada.
3. Si matchea: leer el archivo del disco (ya editado), `json.load()`. Si falla el parseo, error y
   salir 2.
4. Validar **top-level obligatorio** (presente en los 10 perfiles reales hoy):
   `id` (str), `especie` (str), `nombre_comun` (str), `categoria` (str), `nivel_dificultad` (str),
   `etapa_actual` (str), `etapas` (dict no vacío), `alertas` (dict), `notas` (str),
   `version_perfil` (presente, cualquier tipo simple).
5. **Top-level opcional** (solo psilocybe hoy, pero válido para cualquier especie restringida):
   `zona_restringida` (bool), `marco_legal` (str), `requiere_autorizacion` (bool).
6. Para cada etapa dentro de `etapas`, **obligatorio**: `temp_min`/`temp_max`/`humedad_min`/
   `humedad_max` (número), `co2_max` (int), `duracion_dias` (int). Chequeo de sensatez:
   `temp_min < temp_max` y `humedad_min < humedad_max` (si no, error, no solo warning).
7. Por etapa, **opcional pero tipado si aparece** (lista completa derivada de los 10 perfiles
   reales — ver tabla abajo): `co2_min` (int), `luz_horas` (int), `luz_inicio`/`luz_fin` (str
   `HH:MM`), `calefaccion_activa` (bool), `refrigeracion_activa` (bool), `luz_max_lux` (int),
   `oscuridad_total` (bool), `ciclo_luz_estricto` (bool), `luz_tipo` (str), `choque_frio` (bool),
   `duracion_choque_horas` (número), `temp_choque` (número), `induccion_inmersion` (bool),
   `duracion_inmersion_horas` (número), `casing_requerido` (bool), `casing_ph_min`/`casing_ph_max`
   (número), `fae_modo` (str).
8. `alertas`: obligatorio `temp_critica_max`/`temp_critica_min`/`humedad_critica_min` (número),
   `co2_critico_max` (int); opcional `co2_critico_min` (int).
9. Si hay errores: imprimirlos todos juntos (no solo el primero) a stderr, salir 2 (PostToolUse no
   puede deshacer la edición ya aplicada, pero exit 2 le da el feedback a Claude para corregir en
   el mismo turno). Si no hay errores: salir 0 sin imprimir nada.

**No debe:** exigir un campo que hoy no existe en ningún perfil real (eso rompería los 10 archivos
existentes en el primer `pio run`-equivalente de validación); ser un esquema "por especie" —
un único esquema con opcionales tipados, según lo decidido.

### 3. Subagente `firmware-iot-reviewer` (invocación bajo demanda)

**Por qué:** el firmware fue generado en buena parte por IA y ya se encontraron bugs reales
marcados como "completos" sin verificación (watchdog ausente, alertas no evaluadas, etc.) — hace
falta una checklist dedicada a la que Claude (o el usuario) pueda recurrir explícitamente al
terminar cambios de firmware, en vez de depender de una revisión de código genérica.

**Archivo:** `.claude/agents/firmware-iot-reviewer.md`, frontmatter con `name`, `description`
(explicando cuándo aplica: cambios en `firmware/capsula_core/`), `tools` (Read, Grep, Glob, Bash —
para poder correr `pio run` si está disponible).

**Checklist que debe aplicar** (derivada directamente de los hallazgos reales de la auditoría de
este proyecto, no genérica):
- Watchdog de hardware presente y alimentado antes de cualquier `return` temprano en `loop()`.
- Ninguna espera bloqueante larga dentro de `loop()` (conexión WiFi/MQTT deben ser no-bloqueantes
  o tener timeout corto).
- Fallo de sensor tiene manejo explícito con estado seguro (no silencioso).
- Reconexión WiFi/MQTT tiene límite de reintentos o backoff, no bucle agresivo.
- Actuadores en conflicto (calefactor + enfriamiento, o similar) tienen arbitraje explícito, no
  solo un "apagar todo".
- Cualquier dato recibido por red (MQTT) usado para construir una ruta de archivo o comando está
  sanitizado (regex whitelist, no blacklist).
- Cada umbral definido en `alertas` de un perfil JSON tiene su chequeo correspondiente en
  `checkAlerts()` — o el que sea el equivalente en el archivo que se esté revisando.
- Buffers de tamaño fijo (`char buf[N]`) no usan funciones que puedan escanear más allá del
  tamaño real de los datos recibidos (ej. `strlcpy`/`strcpy` sobre payloads de red).
- Reporta hallazgos con el mismo formato de severidad (Crítico/Importante/Menor) que usan los
  demás agentes de revisión del proyecto.

### 4. Skill `/nueva-especie` (interactiva)

**Por qué:** cerrar el gap que ya ocurrió con chaga y trufas (doc sin perfil JSON ni entrada en
backlog) generando los 3 artefactos siempre juntos y consistentes.

**Archivo:** `.claude/skills/nueva-especie/SKILL.md`.

**Flujo:**
1. Pregunta (conversación normal o `AskUserQuestion`): nombre común y científico, nivel de
   dificultad (N1-N4), categoría (gourmet/funcional/restringida), y por cada etapa de cultivo que
   aplique: `temp_min/max`, `humedad_min/max`, `co2_max`, `duracion_dias`, más cualquier campo
   especial que el usuario mencione (frío, luz, inmersión, etc. — mapeados a los nombres de campo
   ya establecidos en la tabla del punto 2, no inventar nombres nuevos).
2. Si la especie es restringida legalmente (ej. psilocibina), preguntar explícitamente y agregar
   `zona_restringida`/`marco_legal`/`requiere_autorizacion`.
3. Escribe `docs/especies/N{nivel}-{slug}.md` siguiendo la misma estructura que los docs
   existentes (leer 1-2 ejemplos de `docs/especies/` antes de escribir, para igualar formato).
4. Escribe el JSON en **dos ubicaciones idénticas** (para no repetir el gap de sincronización que
   ya existía entre `firmware/profiles/` y `firmware/capsula_core/data/profiles/` antes de la
   rama de fixes de firmware): `firmware/profiles/N{nivel}-{slug}.json` Y
   `firmware/capsula_core/data/profiles/N{nivel}-{slug}.json` (mismo contenido byte a byte).
5. Agrega una fila nueva a la épica correspondiente en `BACKLOG.md` (leer el archivo primero para
   usar el siguiente ID disponible en la épica de Documentación o Producción/Cultivo, según
   corresponda, y no romper la numeración existente).
6. El validador del punto 2 corre automáticamente vía el hook `PostToolUse` al escribir los JSON —
   la skill no necesita re-implementar la validación, solo debe leer el resultado del hook si
   falla y corregir antes de terminar.

## Fuera de alcance

- No se automatiza la fila de BACKLOG.md más allá de agregarla — no se recalculan los totales de
  la tabla "Estado General" (eso es un problema aparte, ya identificado en la auditoría de
  documentación, con su propio arreglo pendiente).
- No se valida el contenido de `docs/especies/*.md` contra el JSON (solo se generan juntos por la
  skill; una validación cruzada doc↔JSON automática queda fuera de este alcance, podría ser un
  hook futuro).
- Los hooks no cubren `gateway/.env` más allá del chequeo de nombre de archivo ya existente en la
  lista — no se agregan patrones de contenido específicos de Firebase/Telegram del lado del
  gateway en esta ronda (se puede extender después con la misma estructura).

## Verificación

- Hook 1: probar manualmente con `echo '<json de prueba>' | bash .claude/hooks/block-credential-commit.sh`
  simulando un `tool_input.command` de `git commit`, con archivos staged de prueba (uno limpio,
  uno con nombre prohibido, uno con contenido sospechoso) — confirmar que solo bloquea los 2
  últimos casos.
- Hook 2: correr el script directamente contra cada uno de los 10 `firmware/profiles/*.json`
  reales (deben pasar todos, son la base de la validación) y contra al menos un JSON
  deliberadamente roto (falta un campo obligatorio, o un tipo incorrecto) para confirmar que sí
  falla.
- Subagente: no tiene test automatizado — se verifica leyendo el archivo generado y confirmando
  que el formato de frontmatter es válido (`name`, `description`, `tools`) y que la checklist
  cubre los 9 puntos de esta spec.
- Skill: no tiene test automatizado tampoco — se verifica con una corrida real interactiva
  generando una especie de prueba (ej. "Pleurotus eryngii", que ya está pendiente en BACKLOG como
  CUL-21) y confirmando que los 3 artefactos quedan consistentes y que el hook de validación no
  reporta errores sobre el JSON generado.
- Ninguno de estos 4 componentes tiene test unitario formal (no hay framework de test en este
  repo, igual que en el firmware) — la verificación es funcional/manual, igual que se documentó
  para los fixes de firmware.

## Riesgos abiertos

- Los hooks se cargan al iniciar la sesión de Claude Code — cambios no toman efecto hasta
  reiniciar. Esto debe advertirse al usuario tras implementar.
- El hook anti-credenciales usa regex sobre el diff en texto plano — no es infalible contra
  ofuscación deliberada, pero cubre el caso real (error humano), que es el que motivó el hallazgo.
- `.claude/settings.json` (no `.local.json`) se commitea al repo — los hooks aplican para
  cualquiera que clone el proyecto y use Claude Code, lo cual es la intención (no es config
  personal de un solo desarrollador).
