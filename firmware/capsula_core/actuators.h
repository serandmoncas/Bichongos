#pragma once
#include <Arduino.h>

// Índices de canal (matchean el array interno)
#define CH_HUMIDIF   0
#define CH_EXTRACTOR 1
#define CH_HEATER    2
#define CH_LED       3

struct ActuatorState {
  bool humidificador;
  bool extractor;
  bool calefactor;
  bool led;
};

void         initActuators();
void         setActuator(int channel, bool on);
void         setAllActuators(ActuatorState state);
void         emergencyShutdown();    // apaga todo antes de OTA
ActuatorState getCurrentActuatorState();
