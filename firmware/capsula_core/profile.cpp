#include "profile.h"
#include "config.h"
#include <SPIFFS.h>

static bool parseStage(JsonObject stage, StageParams& out) {
  out.tempMin     = stage["temp_min"]    | 15.0f;
  out.tempMax     = stage["temp_max"]    | 25.0f;
  out.humedadMin  = stage["humedad_min"] | 70.0f;
  out.humedadMax  = stage["humedad_max"] | 95.0f;
  out.co2Max      = stage["co2_max"]     | 9999;
  out.co2Min      = stage["co2_min"]     | 0;
  out.luzHoras    = stage["luz_horas"]   | 0;
  out.duracionDias = stage["duracion_dias"] | 14;

  // Parsear "07:00" → hora y minuto
  const char* inicio = stage["luz_inicio"] | "07:00";
  const char* fin    = stage["luz_fin"]    | "19:00";
  out.luzInicioH = atoi(inicio);
  out.luzInicioM = atoi(inicio + 3);
  out.luzFinH    = atoi(fin);
  out.luzFinM    = atoi(fin + 3);

  return true;
}

bool loadProfile(const char* path, Profile& out) {
  if (!SPIFFS.begin(true)) {
    Serial.println("[PROFILE] ERROR: SPIFFS no montado");
    out.loaded = false;
    return false;
  }

  File f = SPIFFS.open(path, "r");
  if (!f) {
    Serial.printf("[PROFILE] ERROR: no existe %s\n", path);
    out.loaded = false;
    return false;
  }

  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, f);
  f.close();

  if (err) {
    Serial.printf("[PROFILE] ERROR JSON: %s\n", err.c_str());
    out.loaded = false;
    return false;
  }

  strlcpy(out.id,          doc["id"]           | "desconocido", sizeof(out.id));
  strlcpy(out.especie,     doc["especie"]       | "desconocida", sizeof(out.especie));
  strlcpy(out.etapaActual, doc["etapa_actual"]  | "incubacion",  sizeof(out.etapaActual));

  out.alertas.tempCriticaMax   = doc["alertas"]["temp_critica_max"]    | 30.0f;
  out.alertas.tempCriticaMin   = doc["alertas"]["temp_critica_min"]    | 8.0f;
  out.alertas.humedadCriticaMin = doc["alertas"]["humedad_critica_min"] | 60.0f;
  out.alertas.co2CriticoMax    = doc["alertas"]["co2_critico_max"]     | 5000;

  JsonObject stageObj = doc["etapas"][out.etapaActual];
  if (!parseStage(stageObj, out.etapa)) {
    Serial.printf("[PROFILE] ERROR: etapa '%s' no encontrada\n", out.etapaActual);
    out.loaded = false;
    return false;
  }

  out.loaded = true;
  printProfile(out);
  return true;
}

bool setStage(Profile& p, const char* stage, JsonDocument& doc) {
  JsonObject stageObj = doc["etapas"][stage];
  if (stageObj.isNull()) {
    Serial.printf("[PROFILE] ERROR: etapa '%s' no existe en perfil\n", stage);
    return false;
  }
  strlcpy(p.etapaActual, stage, sizeof(p.etapaActual));
  return parseStage(stageObj, p.etapa);
}

bool reloadProfileStage(const char* stage, Profile& out) {
  // Lee el perfil completo desde SPIFFS y cambia a la etapa indicada
  if (!SPIFFS.begin(false)) return false;
  File f = SPIFFS.open(PROFILE_PATH, "r");
  if (!f) return false;
  JsonDocument doc;
  if (deserializeJson(doc, f)) { f.close(); return false; }
  f.close();
  return setStage(out, stage, doc);
}

void printProfile(const Profile& p) {
  Serial.printf("[PROFILE] ID: %s | Especie: %s | Etapa: %s\n",
                p.id, p.especie, p.etapaActual);
  Serial.printf("[PROFILE] Temp: %.0f–%.0f°C | HR: %.0f–%.0f%% | CO2 max: %d ppm | Luz: %dh\n",
                p.etapa.tempMin, p.etapa.tempMax,
                p.etapa.humedadMin, p.etapa.humedadMax,
                p.etapa.co2Max, p.etapa.luzHoras);
}
