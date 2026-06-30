#include "actuators.h"
#include "config.h"

// Los módulos de relé opto-aislados son activos en LOW
// (JD-VCC desconectado del VCC — ver diagrama eléctrico)
#define RELAY_ON  LOW
#define RELAY_OFF HIGH

static const int RELAY_PINS[4] = {
  PIN_RELAY_HUMIDIF,
  PIN_RELAY_EXTRACTOR,
  PIN_RELAY_HEATER,
  PIN_RELAY_LED
};

static ActuatorState currentState       = {false, false, false, false};
static unsigned long lastChangeMs[4]    = {0, 0, 0, 0};

// Protección: mínimo 30 s entre cambios de estado de un mismo relé
// Evita ciclos rápidos que dañan actuadores y solenoides
static const unsigned long MIN_SWITCH_MS = 30000UL;

void initActuators() {
  for (int i = 0; i < 4; i++) {
    pinMode(RELAY_PINS[i], OUTPUT);
    digitalWrite(RELAY_PINS[i], RELAY_OFF);
  }
  Serial.println("[ACT] Todos los relés → OFF");
}

void setActuator(int ch, bool on) {
  if (ch < 0 || ch > 3) return;

  unsigned long now = millis();
  if ((now - lastChangeMs[ch]) < MIN_SWITCH_MS) return;

  bool* state;
  switch (ch) {
    case CH_HUMIDIF:   state = &currentState.humidificador; break;
    case CH_EXTRACTOR: state = &currentState.extractor;     break;
    case CH_HEATER:    state = &currentState.calefactor;    break;
    case CH_LED:       state = &currentState.led;           break;
    default:           return;
  }

  if (*state == on) return; // sin cambio

  *state = on;
  digitalWrite(RELAY_PINS[ch], on ? RELAY_ON : RELAY_OFF);
  lastChangeMs[ch] = now;

  const char* nombres[] = {"Humidif.", "Extractor", "Calefactor", "LED"};
  Serial.printf("[ACT] %-10s → %s\n", nombres[ch], on ? "ON" : "OFF");
}

void setAllActuators(ActuatorState s) {
  setActuator(CH_HUMIDIF,   s.humidificador);
  setActuator(CH_EXTRACTOR, s.extractor);
  setActuator(CH_HEATER,    s.calefactor);
  setActuator(CH_LED,       s.led);
}

void emergencyShutdown() {
  // Bypass del intervalo mínimo: apagado de seguridad (ej. antes de OTA)
  for (int i = 0; i < 4; i++) {
    digitalWrite(RELAY_PINS[i], RELAY_OFF);
  }
  currentState     = {false, false, false, false};
  Serial.println("[ACT] SHUTDOWN DE EMERGENCIA — todos los relés OFF");
}

ActuatorState getCurrentActuatorState() {
  return currentState;
}
