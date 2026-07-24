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

# Revisa tanto lo staged (--cached) como las modificaciones sin stagear de
# archivos ya trackeados: "git commit -a"/"git commit <pathspec>" auto-staggean
# esos cambios justo al momento del commit, despues de que este hook ya corrio
# contra el index. Sin cubrir tambien el diff sin stagear, un secreto pegado en
# un archivo trackeado y commiteado con -a pasaria sin ser detectado.
all_changed_files=$( { git diff --cached --name-only; git diff --name-only; } | sort -u || true)

blocked_reason=""

while IFS= read -r f; do
  [[ -z "$f" ]] && continue
  if [[ "$f" =~ $forbidden_names ]]; then
    blocked_reason="archivo de credenciales '$f' esta en el commit (deberia estar en .gitignore)"
    break
  fi
done <<< "$all_changed_files"

if [[ -z "$blocked_reason" ]]; then
  diff_content=$( { git diff --cached -- . ":(exclude)*.example"; git diff -- . ":(exclude)*.example"; } || true)

  if echo "$diff_content" | grep -Eq '^\+.*[0-9]{8,10}:[A-Za-z0-9_-]{35}'; then
    blocked_reason="posible token de Telegram bot detectado en el diff"
  elif echo "$diff_content" | grep -Eq '^\+.*-----BEGIN (RSA |EC |OPENSSH )?PRIVATE KEY-----'; then
    blocked_reason="bloque de llave privada detectado en el diff"
  elif echo "$diff_content" | grep -Eq '^\+.*#define[[:space:]]+(WIFI_PASSWORD|MQTT_PASS|OTA_PASSWORD)[[:space:]]+"[^"]{4,}"'; then
    blocked_reason="posible credencial hardcodeada (WIFI_PASSWORD/MQTT_PASS/OTA_PASSWORD) detectada en el diff"
  fi
fi

if [[ -n "$blocked_reason" ]]; then
  jq -n --arg msg "Commit bloqueado: $blocked_reason. Revisa los cambios (staged y sin stagear) antes de commitear." \
    '{hookSpecificOutput: {permissionDecision: "deny"}, systemMessage: $msg}'
fi

exit 0
