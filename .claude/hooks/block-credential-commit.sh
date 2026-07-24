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
