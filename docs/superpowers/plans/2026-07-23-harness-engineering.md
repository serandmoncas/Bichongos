# Harness Engineering para Bichongos — Plan de Implementación

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Construir las 4 piezas de "harness engineering" aprobadas para Bichongos: un hook que bloquea commits con credenciales, un hook que valida el esquema de los perfiles JSON de especies, un subagente de revisión de firmware IoT, y una skill interactiva para dar de alta una especie nueva de forma consistente (doc + JSON + backlog).

**Architecture:** Todo vive en `.claude/` del repo (no es un plugin distribuible, es config de proyecto). Los hooks van en `.claude/settings.json` (commiteado, aplica a cualquiera que use Claude Code en este repo) con scripts en `.claude/hooks/`. El subagente y la skill son archivos markdown independientes en `.claude/agents/` y `.claude/skills/`.

**Tech Stack:** Bash + `jq` (hook 1), Python 3 sin dependencias externas (hook 2), markdown con frontmatter YAML (agente y skill).

Spec de referencia: `docs/superpowers/specs/2026-07-23-harness-engineering-design.md`

## Global Constraints

- **No hay framework de test en este repo** (igual que en el firmware) — la verificación de cada tarea es funcional/manual: invocar el script del hook directamente con `echo '<json>' | bash/python3 script`, no un test runner.
- **Los hooks se cargan al iniciar sesión de Claude Code** — un cambio en `.claude/settings.json` o en los scripts de `.claude/hooks/` no tiene efecto hasta reiniciar la sesión. Esto no bloquea la verificación (se puede invocar el script directamente), pero avísalo al usuario al terminar.
- **`.claude/settings.json` no existe todavía** — la Tarea 1 lo crea; la Tarea 2 lo modifica (debe fusionar, no sobrescribir, la clave que agregó la Tarea 1).
- Todo mensaje/comentario en español, consistente con el resto del repo.
- Los scripts de hooks nunca deben imprimir el valor real de un secreto detectado — solo el nombre del patrón/archivo que lo disparó.
- Verificación de cada tarea debe dejar el working tree limpio (`git status` sin cambios residuales de prueba) al terminar — cualquier archivo/staged-change de prueba se limpia antes del commit de la tarea.

---

### Task 1: Hook anti-credenciales (`PreToolUse` sobre `Bash`)

**Files:**
- Create: `.claude/settings.json`
- Create: `.claude/hooks/block-credential-commit.sh`

**Interfaces:**
- Produce: `.claude/settings.json` con la clave top-level `"PreToolUse"` — la Tarea 2 debe agregarle una clave `"PostToolUse"` hermana, sin tocar `"PreToolUse"`.

- [ ] **Step 1: Crear el script `.claude/hooks/block-credential-commit.sh`**

```bash
#!/usr/bin/env bash
set -euo pipefail

input=$(cat)
command=$(echo "$input" | jq -r '.tool_input.command // empty')

if [[ -z "$command" ]]; then
  exit 0
fi

if [[ ! "$command" =~ git[[:space:]]+commit ]]; then
  exit 0
fi

cd "$CLAUDE_PROJECT_DIR"

forbidden_names='(^|/)config\.h$|(^|/)secrets\.h$|(^|/)\.env$|(^|/)mosquitto_passwd$'
staged_files=$(git diff --cached --name-only || true)

blocked_reason=""

while IFS= read -r f; do
  [[ -z "$f" ]] && continue
  if [[ "$f" =~ $forbidden_names ]]; then
    blocked_reason="archivo de credenciales '$f' esta en el commit (deberia estar en .gitignore)"
    break
  fi
done <<< "$staged_files"

if [[ -z "$blocked_reason" ]]; then
  diff_content=$(git diff --cached -- . ":(exclude)*.example" || true)

  if echo "$diff_content" | grep -Eq '^\+.*[0-9]{8,10}:[A-Za-z0-9_-]{35}'; then
    blocked_reason="posible token de Telegram bot detectado en el diff"
  elif echo "$diff_content" | grep -Eq '^\+.*-----BEGIN (RSA |EC |OPENSSH )?PRIVATE KEY-----'; then
    blocked_reason="bloque de llave privada detectado en el diff"
  elif echo "$diff_content" | grep -Eq '^\+.*#define[[:space:]]+(WIFI_PASSWORD|MQTT_PASS|OTA_PASSWORD)[[:space:]]+"[^"]{4,}"'; then
    blocked_reason="posible credencial hardcodeada (WIFI_PASSWORD/MQTT_PASS/OTA_PASSWORD) detectada en el diff"
  fi
fi

if [[ -n "$blocked_reason" ]]; then
  jq -n --arg msg "Commit bloqueado: $blocked_reason. Revisa el diff staged antes de commitear." \
    '{hookSpecificOutput: {permissionDecision: "deny"}, systemMessage: $msg}'
fi

exit 0
```

- [ ] **Step 2: Hacerlo ejecutable**

```bash
chmod +x .claude/hooks/block-credential-commit.sh
```

- [ ] **Step 3: Crear `.claude/settings.json`**

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

- [ ] **Step 4: Verificar el caso "no bloquea" (comando que no es git commit)**

```bash
echo '{"tool_input": {"command": "ls -la"}}' | bash .claude/hooks/block-credential-commit.sh; echo "exit=$?"
```

Esperado: sin salida, `exit=0`.

- [ ] **Step 5: Verificar el caso "bloquea por nombre de archivo prohibido"**

```bash
touch /tmp/bichongos-hook-test-config.h
cp /tmp/bichongos-hook-test-config.h firmware/capsula_core/config.h.hooktest
git add firmware/capsula_core/config.h.hooktest
# Simular que el archivo se llama config.h para la prueba del patron de nombre:
git mv firmware/capsula_core/config.h.hooktest firmware/capsula_core/config.h.testonly 2>/dev/null || true
```

Nota: como `config.h` real ya está gitignored y no se puede stagear, esta prueba usa un nombre de
archivo alterno para validar la lógica del patrón sin depender del `.gitignore` real. Ajusta así:

```bash
echo "test" > /tmp/secrets.h
git add /tmp/secrets.h 2>/dev/null || cp /tmp/secrets.h ./secrets.h && git add secrets.h
echo '{"tool_input": {"command": "git commit -m test"}}' | bash .claude/hooks/block-credential-commit.sh; echo "exit=$?"
```

Esperado: imprime JSON con `"permissionDecision":"deny"` y `systemMessage` mencionando
`secrets.h`, `exit=0` (el bloqueo es por el campo `permissionDecision`, no por el código de
salida).

Limpieza inmediata:

```bash
git reset secrets.h
rm -f secrets.h /tmp/secrets.h
```

- [ ] **Step 6: Verificar el caso "bloquea por contenido sospechoso"**

```bash
echo '#define OTA_PASSWORD  "esto-es-un-secreto-real"' > /tmp/fake_secret.h
cp /tmp/fake_secret.h ./fake_secret_test.h
git add fake_secret_test.h
echo '{"tool_input": {"command": "git commit -m test"}}' | bash .claude/hooks/block-credential-commit.sh; echo "exit=$?"
```

Esperado: imprime JSON con `"permissionDecision":"deny"` y `systemMessage` mencionando
"credencial hardcodeada".

Limpieza inmediata:

```bash
git reset fake_secret_test.h
rm -f fake_secret_test.h /tmp/fake_secret.h
```

- [ ] **Step 7: Verificar que `git status` quedó limpio**

```bash
git status --short
```

Esperado: sin salida (nada pendiente de las pruebas).

- [ ] **Step 8: Commit**

```bash
git add .claude/settings.json .claude/hooks/block-credential-commit.sh
git commit -m "harness: agregar hook anti-credenciales en commits (PreToolUse)

Defensa en profundidad mas alla de .gitignore: bloquea git commit si
detecta nombres de archivo de credenciales conocidos o patrones de
secretos (tokens Telegram, llaves privadas, defines hardcodeados) en
el diff staged. Los archivos *.example quedan excluidos del chequeo
de contenido a proposito."
```

---

### Task 2: Validador de esquema de perfiles (`PostToolUse` sobre `Edit|Write`)

**Files:**
- Create: `.claude/hooks/validate-species-profile.py`
- Modify: `.claude/settings.json`

**Interfaces:**
- Consume: la clave `"PreToolUse"` ya presente en `.claude/settings.json` (Tarea 1) — debe quedar intacta.
- Produce: `.claude/settings.json` con `"PostToolUse"` agregado como clave hermana.

- [ ] **Step 1: Crear el script `.claude/hooks/validate-species-profile.py`**

```python
#!/usr/bin/env python3
import json
import re
import sys


def eprint(*args):
    print(*args, file=sys.stderr)


def type_ok(value, types):
    base_types = types if isinstance(types, tuple) else (types,)
    if base_types == (bool,):
        return isinstance(value, bool)
    # bool es subclase de int en Python; un booleano nunca debe pasar
    # como valido para un campo numerico o de texto.
    if isinstance(value, bool):
        return False
    return isinstance(value, base_types)


def main():
    try:
        payload = json.load(sys.stdin)
    except Exception:
        return 0

    file_path = payload.get("tool_input", {}).get("file_path", "")
    if not file_path:
        return 0

    normalized = file_path.replace("\\", "/")
    is_profile = bool(
        re.search(r"firmware/profiles/[^/]+\.json$", normalized)
        or re.search(r"firmware/capsula_core/data/profiles/[^/]+\.json$", normalized)
    )
    if not is_profile:
        return 0

    try:
        with open(file_path, "r", encoding="utf-8") as f:
            data = json.load(f)
    except Exception as e:
        eprint(f"[validate-species-profile] ERROR: no se pudo parsear {file_path}: {e}")
        return 2

    errors = []

    def require(d, key, types, where):
        if key not in d:
            errors.append(f"{where}: falta el campo obligatorio '{key}'")
            return None
        if not type_ok(d[key], types):
            errors.append(f"{where}: '{key}' deberia ser {types}, es {type(d[key]).__name__}")
        return d.get(key)

    def check_optional(d, key, types, where):
        if key in d and not type_ok(d[key], types):
            errors.append(f"{where}: '{key}' (opcional) deberia ser {types}, es {type(d[key]).__name__}")

    require(data, "id", str, "top-level")
    require(data, "especie", str, "top-level")
    require(data, "nombre_comun", str, "top-level")
    require(data, "categoria", str, "top-level")
    require(data, "nivel_dificultad", int, "top-level")
    require(data, "etapa_actual", str, "top-level")
    etapas = require(data, "etapas", dict, "top-level")
    alertas = require(data, "alertas", dict, "top-level")
    require(data, "notas", str, "top-level")
    if "version_perfil" not in data:
        errors.append("top-level: falta el campo obligatorio 'version_perfil'")

    check_optional(data, "zona_restringida", bool, "top-level")
    check_optional(data, "marco_legal", str, "top-level")
    check_optional(data, "requiere_autorizacion", bool, "top-level")

    if isinstance(etapas, dict):
        if len(etapas) == 0:
            errors.append("'etapas' no puede estar vacio")
        for stage_name, stage in etapas.items():
            where = f"etapas.{stage_name}"
            if not isinstance(stage, dict):
                errors.append(f"{where}: debe ser un objeto")
                continue

            tmin = require(stage, "temp_min", (int, float), where)
            tmax = require(stage, "temp_max", (int, float), where)
            hmin = require(stage, "humedad_min", (int, float), where)
            hmax = require(stage, "humedad_max", (int, float), where)
            require(stage, "co2_max", int, where)
            require(stage, "duracion_dias", int, where)

            if isinstance(tmin, (int, float)) and isinstance(tmax, (int, float)) and not isinstance(tmin, bool) and not isinstance(tmax, bool) and tmin >= tmax:
                errors.append(f"{where}: temp_min ({tmin}) debe ser menor que temp_max ({tmax})")
            if isinstance(hmin, (int, float)) and isinstance(hmax, (int, float)) and not isinstance(hmin, bool) and not isinstance(hmax, bool) and hmin >= hmax:
                errors.append(f"{where}: humedad_min ({hmin}) debe ser menor que humedad_max ({hmax})")

            check_optional(stage, "co2_min", int, where)
            check_optional(stage, "luz_horas", int, where)
            check_optional(stage, "luz_inicio", str, where)
            check_optional(stage, "luz_fin", str, where)
            check_optional(stage, "calefaccion_activa", bool, where)
            check_optional(stage, "refrigeracion_activa", bool, where)
            check_optional(stage, "luz_max_lux", int, where)
            check_optional(stage, "oscuridad_total", bool, where)
            check_optional(stage, "ciclo_luz_estricto", bool, where)
            check_optional(stage, "luz_tipo", str, where)
            check_optional(stage, "choque_frio", bool, where)
            check_optional(stage, "duracion_choque_horas", (int, float), where)
            check_optional(stage, "temp_choque", (int, float), where)
            check_optional(stage, "induccion_inmersion", bool, where)
            check_optional(stage, "duracion_inmersion_horas", (int, float), where)
            check_optional(stage, "casing_requerido", bool, where)
            check_optional(stage, "casing_ph_min", (int, float), where)
            check_optional(stage, "casing_ph_max", (int, float), where)
            check_optional(stage, "fae_modo", str, where)

            for key in ("luz_inicio", "luz_fin"):
                if key in stage and isinstance(stage[key], str) and not re.match(r"^\d{2}:\d{2}$", stage[key]):
                    errors.append(f"{where}: '{key}' debe tener formato HH:MM, es '{stage[key]}'")

    if isinstance(alertas, dict):
        require(alertas, "temp_critica_max", (int, float), "alertas")
        require(alertas, "temp_critica_min", (int, float), "alertas")
        require(alertas, "humedad_critica_min", (int, float), "alertas")
        require(alertas, "co2_critico_max", int, "alertas")
        check_optional(alertas, "co2_critico_min", int, "alertas")

    if errors:
        eprint(f"[validate-species-profile] {file_path} tiene {len(errors)} problema(s):")
        for e in errors:
            eprint(f"  - {e}")
        return 2

    return 0


if __name__ == "__main__":
    sys.exit(main())
```

- [ ] **Step 2: Hacerlo ejecutable**

```bash
chmod +x .claude/hooks/validate-species-profile.py
```

- [ ] **Step 3: Agregar `PostToolUse` a `.claude/settings.json` (fusionar, no sobrescribir `PreToolUse`)**

El archivo debe quedar así (agrega la clave `PostToolUse` como hermana de `PreToolUse`, que ya
existe de la Tarea 1):

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
  ],
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

- [ ] **Step 4: Verificar contra los 10 perfiles reales (todos deben pasar)**

```bash
for f in firmware/profiles/*.json; do
  echo "== $f =="
  echo "{\"tool_input\": {\"file_path\": \"$f\"}}" | python3 .claude/hooks/validate-species-profile.py
  echo "exit=$?"
done
```

Esperado: `exit=0` y sin salida en stderr para los 10 archivos.

- [ ] **Step 5: Verificar que detecta un perfil roto**

```bash
python3 -c "
import json
d = json.load(open('firmware/profiles/N1-orellana.json'))
del d['etapas']['incubacion']['temp_max']
d['co2_critico_min_bad'] = 'no aplica aqui'
json.dump(d, open('firmware/profiles/_test-broken.json', 'w'))
"
echo '{"tool_input": {"file_path": "firmware/profiles/_test-broken.json"}}' | python3 .claude/hooks/validate-species-profile.py; echo "exit=$?"
```

Esperado: `exit=2`, con al menos un error mencionando `temp_max`.

Limpieza inmediata:

```bash
rm -f firmware/profiles/_test-broken.json
```

- [ ] **Step 6: Verificar que ignora archivos que no son perfiles**

```bash
echo '{"tool_input": {"file_path": "docs/especies/N1-orellana.md"}}' | python3 .claude/hooks/validate-species-profile.py; echo "exit=$?"
```

Esperado: sin salida, `exit=0`.

- [ ] **Step 7: Verificar que `git status` quedó limpio**

```bash
git status --short
```

Esperado: sin salida.

- [ ] **Step 8: Commit**

```bash
git add .claude/settings.json .claude/hooks/validate-species-profile.py
git commit -m "harness: agregar validador de esquema de perfiles JSON (PostToolUse)

Valida firmware/profiles/*.json y firmware/capsula_core/data/profiles/*.json
al editarlos: campos obligatorios del nucleo comun, tipos correctos de
los campos opcionales especificos por especie (co2_min, luz_max_lux,
calefaccion_activa, etc.), y rangos min<max sensatos. El esquema se
derivo de los 10 perfiles reales existentes, no se inventaron campos."
```

---

### Task 3: Subagente `firmware-iot-reviewer`

**Files:**
- Create: `.claude/agents/firmware-iot-reviewer.md`

**Interfaces:**
- Ninguna — es un archivo de definición de agente independiente, invocado bajo demanda (no engancha con hooks ni con otras tareas).

- [ ] **Step 1: Crear `.claude/agents/firmware-iot-reviewer.md`**

```markdown
---
name: firmware-iot-reviewer
description: Use this agent to review changes to Bichongos' ESP32 firmware (firmware/capsula_core/) for IoT-specific correctness and safety — watchdog coverage, non-blocking control loop, sensor failure handling, reconnection limits, actuator conflict arbitration, network-input sanitization, and alert-threshold completeness against the active species JSON profile. Invoke after implementing or modifying firmware code, before considering the change done.

<example>
Context: User just added a new MQTT command handler to capsula_core.ino
user: "Ya agregué el manejo de un nuevo comando MQTT, revísalo"
assistant: "Voy a usar el agente firmware-iot-reviewer para revisar el cambio con la checklist de seguridad IoT de este proyecto."
<commentary>
Cambio de firmware terminado — el agente aplica una checklist derivada de bugs reales ya encontrados en este mismo firmware, no una revisión de código genérica.
</commentary>
</example>

<example>
Context: User modified computeControl() actuator logic for a new species
user: "Cambié la lógica de control de actuadores para la nueva especie"
assistant: "Uso firmware-iot-reviewer para confirmar que no hay conflictos de actuadores sin arbitrar y que las alertas siguen cubiertas."
<commentary>
Lógica de control tocada — el agente verifica específicamente arbitraje de conflictos y cobertura de alertas, los dos tipos de bug que ya aparecieron en la auditoría de este firmware (ej. co2_critico_min sin evaluar, extractor apagado incondicionalmente).
</commentary>
</example>
tools: Read, Grep, Glob, Bash
---

Eres un revisor senior de sistemas embebidos, especializado en firmware ESP32/Arduino, revisando
código del proyecto Bichongos (laboratorio de cultivo de hongos con IoT).

Este firmware fue generado en buena parte con asistencia de IA. La evidencia de la industria (y de
este mismo proyecto) es que ese código necesita MÁS escrutinio, no menos: llega rápido al 80% que
funciona en demo, pero omite el 20% difícil — manejo de fallos, límites, seguridad — que es
justamente el que un review superficial no detecta.

## Checklist obligatoria

Para cada cambio en `firmware/capsula_core/`, verifica explícitamente cada uno de estos puntos y
repórtalos aunque el resultado sea "OK, sin problema":

1. **Watchdog de hardware**: ¿sigue presente `esp_task_wdt_reset()` al inicio de `loop()`, antes
   de cualquier `return` temprano (ej. rutas de OTA pendiente)? Si el cambio agregó un nuevo
   `return` temprano en `loop()`, ¿quedó antes o después del reset del watchdog?
2. **Sin bloqueos largos en `loop()`**: ninguna espera de WiFi/MQTT/sensor debe ser un `delay()`
   largo o un bucle sin timeout dentro del loop principal.
3. **Fallo de sensor con estado seguro explícito**: si un sensor puede fallar (`errorSHT31`,
   `errorMHZ19`, `errorDS18B20`, etc.), ¿el código que lo usa comprueba el flag de error antes de
   actuar sobre el valor, en vez de usar un valor por defecto silenciosamente?
4. **Límite de reintentos/backoff en reconexión**: WiFi y MQTT deben reintentar con un intervalo
   (no un bucle agresivo sin espera).
5. **Arbitraje explícito de actuadores en conflicto**: si dos actuadores no deben estar activos a
   la vez (ej. calefactor + extractor), ¿la resolución del conflicto está explícita y documentada,
   en vez de un "apagar todo" que pueda esconder un caso real de la especie (ej. Enoki necesita
   frío + CO2 alto a la vez)?
6. **Sanitización de input de red usado para rutas/comandos**: cualquier dato recibido por MQTT
   que se use para construir una ruta de archivo (ej. `/profiles/<id>.json`) debe validarse contra
   una whitelist de caracteres (`[A-Za-z0-9_-]`), nunca una blacklist.
7. **Cobertura de alertas**: por cada umbral definido en la sección `alertas` de un perfil JSON
   (`temp_critica_max/min`, `humedad_critica_min`, `co2_critico_max`, `co2_critico_min` si
   aplica), confirma que existe un chequeo correspondiente en `checkAlerts()` (o el equivalente).
   Un umbral en el JSON sin su chequeo en el firmware es un hallazgo, no un detalle menor.
8. **Buffers de tamaño fijo**: cualquier copia de datos recibidos por red a un `char buf[N]` debe
   usar una longitud explícita acotada (ej. `memcpy` + terminador manual), nunca una función que
   escanee el origen buscando un terminador que la red no garantiza (ej. `strlcpy`/`strcpy` sobre
   payloads MQTT crudos).
9. **Consistencia con `firmware/capsula_core/platformio.ini`**: si el cambio usa una API de una
   librería de ESP32 (ej. `esp_task_wdt`), confirma que la firma usada coincide con la versión de
   `platform`/librerías realmente fijada en `platformio.ini` — estas APIs cambian de firma entre
   versiones del core.

## Cómo revisar

1. Lee el diff o los archivos modificados en `firmware/capsula_core/`.
2. Si `firmware/capsula_core/platformio.ini` existe, intenta correr `pio run -e esp32dev` desde
   `firmware/capsula_core/` para confirmar que compila de verdad — no reportes "compila" sin
   haberlo corrido.
3. Aplica los 9 puntos de la checklist uno por uno.

## Formato de salida

Reporta hallazgos por severidad, igual que los demás agentes de revisión de este proyecto:

### Crítico
### Importante
### Menor

Para cada hallazgo: archivo:línea, qué está mal, por qué importa, cómo arreglarlo si no es obvio.
Si un punto de la checklist está bien cubierto, dilo explícitamente — no omitas los puntos que
pasan.
```

- [ ] **Step 2: Verificar que el frontmatter es YAML válido**

```bash
python3 -c "
import yaml
with open('.claude/agents/firmware-iot-reviewer.md') as f:
    content = f.read()
frontmatter = content.split('---')[1]
data = yaml.safe_load(frontmatter)
assert 'name' in data and data['name'] == 'firmware-iot-reviewer'
assert 'description' in data
assert 'tools' in data
print('frontmatter OK:', list(data.keys()))
"
```

Esperado: `frontmatter OK: ['name', 'description', 'tools']` (o similar, sin error).

- [ ] **Step 3: Commit**

```bash
git add .claude/agents/firmware-iot-reviewer.md
git commit -m "harness: agregar subagente firmware-iot-reviewer

Checklist de 9 puntos derivada directamente de los bugs reales
encontrados en la auditoria de este firmware (watchdog, arbitraje de
actuadores, cobertura de alertas, sanitizacion de input de red, etc.),
no una checklist generica. Invocacion bajo demanda."
```

---

### Task 4: Skill `/nueva-especie`

**Files:**
- Create: `.claude/skills/nueva-especie/SKILL.md`

**Interfaces:**
- Consume: el validador de la Tarea 2 (corre automáticamente vía el hook `PostToolUse` cuando la
  skill escribe un JSON de perfil — la skill no reimplementa la validación).

- [ ] **Step 1: Crear `.claude/skills/nueva-especie/SKILL.md`**

```markdown
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
```

- [ ] **Step 2: Verificar que el frontmatter es YAML válido**

```bash
python3 -c "
import yaml
with open('.claude/skills/nueva-especie/SKILL.md') as f:
    content = f.read()
frontmatter = content.split('---')[1]
data = yaml.safe_load(frontmatter)
assert data['name'] == 'nueva-especie'
assert 'description' in data
print('frontmatter OK:', list(data.keys()))
"
```

Esperado: `frontmatter OK: ['name', 'description']` sin error.

- [ ] **Step 3: Commit**

```bash
git add .claude/skills/nueva-especie/SKILL.md
git commit -m "harness: agregar skill /nueva-especie

Genera doc + JSON (en las dos ubicaciones que deben sincronizarse) +
fila de BACKLOG en un solo flujo interactivo, para evitar el gap que
ya ocurrio con chaga y trufas (doc sin perfil ni entrada en backlog).
Reutiliza el hook de validacion de esquema de la Tarea 2 en vez de
reimplementar la validacion."
```

---

## Verificación final del plan

Tras las 4 tareas, confirmar que Claude Code reconoce todo (requiere reiniciar la sesión, ya que
los hooks/skills/agentes se cargan al inicio):

```bash
ls .claude/hooks/ .claude/agents/ .claude/skills/nueva-especie/
cat .claude/settings.json
```

Esperado: `block-credential-commit.sh`, `validate-species-profile.py` en `.claude/hooks/`;
`firmware-iot-reviewer.md` en `.claude/agents/`; `SKILL.md` en `.claude/skills/nueva-especie/`;
`.claude/settings.json` con las claves `PreToolUse` y `PostToolUse` presentes.

**Pendiente explícito, no cubierto por este plan:** una prueba end-to-end real de la skill
`/nueva-especie` generando una especie real (ej. Pleurotus eryngii, ya pendiente como CUL-21 en
BACKLOG.md) queda para cuando el usuario la use por primera vez — no se ejecuta como parte de este
plan porque crearía artefactos de proyecto reales (una especie nueva) que no fueron pedidos en
este alcance.
