#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

struct StageParams {
  float tempMin;
  float tempMax;
  float humedadMin;
  float humedadMax;
  int   co2Max;
  int   co2Min;       // solo Enoki (lógica invertida); 0 = no aplica
  int   luzHoras;
  int   luzInicioH;   // hora de inicio de luz (24h)
  int   luzInicioM;
  int   luzFinH;
  int   luzFinM;
  int   duracionDias;
};

struct AlertThresholds {
  float tempCriticaMax;
  float tempCriticaMin;
  float humedadCriticaMin;
  int   co2CriticoMax;
};

struct Profile {
  char          id[32];
  char          especie[64];
  char          etapaActual[24];
  StageParams   etapa;
  AlertThresholds alertas;
  bool          loaded;
};

bool    loadProfile(const char* path, Profile& out);
bool    setStage(Profile& p, const char* stage, JsonDocument& doc);
bool    reloadProfileStage(const char* stage, Profile& out);
void    printProfile(const Profile& p);
