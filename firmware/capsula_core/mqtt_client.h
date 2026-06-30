#pragma once
#include <Arduino.h>
#include <PubSubClient.h>
#include "sensors.h"
#include "actuators.h"
#include "profile.h"

// Callback para comandos recibidos desde el broker
typedef void (*ProfileSetCallback)(const char* newProfile, const char* newStage);
typedef void (*OtaTriggerCallback)();

void mqttInit(WiFiClient& wifiClient,
              ProfileSetCallback onProfileSet,
              OtaTriggerCallback onOtaTrigger);
bool mqttConnect();
void mqttLoop();

void mqttPublishSensors(const SensorData& s,
                        const ActuatorState& a,
                        const Profile& p);
void mqttPublishAlert(const char* tipo,
                      float valorActual,
                      float umbral,
                      const char* accion);
void mqttPublishStatus(const ActuatorState& a, const Profile& p);

bool mqttIsConnected();
