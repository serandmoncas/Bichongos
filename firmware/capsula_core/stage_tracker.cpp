#include "stage_tracker.h"
#include <time.h>

static Preferences prefs;
static const char* NVS_NS = "bichongos";

void stageTrackerInit() {
  prefs.begin(NVS_NS, false);
  Serial.printf("[STAGE] Etapa en NVS: %s  inicio: %lld\n",
                prefs.getString("stage", "none").c_str(),
                (long long)prefs.getLong64("startTime", 0));
}

void stageTrackerSetStage(const char* stage) {
  time_t now = time(nullptr);
  if (now < 1700000000L) {
    // NTP no sincronizado todavía — guardar 0 y actualizar al primer sync
    now = 0;
    Serial.println("[STAGE] WARN: NTP no sincronizado, startTime = 0");
  }
  prefs.putString("stage", stage);
  prefs.putLong64("startTime", (long long)now);
  Serial.printf("[STAGE] Nueva etapa: %s  inicio: %lld\n", stage, (long long)now);
}

StageInfo stageTrackerGet() {
  StageInfo info = {};
  String s = prefs.getString("stage", "");
  strlcpy(info.stage, s.c_str(), sizeof(info.stage));
  info.startTime = (time_t)prefs.getLong64("startTime", 0);

  time_t now = time(nullptr);
  if (info.startTime > 0 && now > info.startTime) {
    info.dayElapsed = (int)((now - info.startTime) / 86400L);
  } else {
    info.dayElapsed = 0;
  }
  return info;
}

bool stageTrackerShouldAlert(int duracionDias) {
  StageInfo info = stageTrackerGet();
  // Alertar el día exacto Y los 2 días siguientes (en caso de no recibir el primer aviso)
  return (info.dayElapsed >= duracionDias && info.dayElapsed <= duracionDias + 2);
}

void stageTrackerClear() {
  prefs.clear();
  Serial.println("[STAGE] NVS limpiado");
}
