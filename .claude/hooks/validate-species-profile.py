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
