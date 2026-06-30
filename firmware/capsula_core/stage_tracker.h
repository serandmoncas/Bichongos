#pragma once
#include <Arduino.h>
#include <Preferences.h>  // ESP32 NVS (Non-Volatile Storage)

// Persiste en flash la fecha de inicio de cada etapa.
// Sobrevive reinicios del ESP32 sin necesidad de RTC externo.
// La hora viene de NTP — requiere WiFi en algún momento para sincronizar.

struct StageInfo {
  char    stage[24];
  time_t  startTime;   // epoch UTC cuando comenzó esta etapa
  int     dayElapsed;  // días transcurridos desde startTime
};

void      stageTrackerInit();
void      stageTrackerSetStage(const char* stage);
StageInfo stageTrackerGet();
bool      stageTrackerShouldAlert(int duracionDias);
void      stageTrackerClear();
