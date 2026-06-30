#pragma once
#include <Arduino.h>

struct SensorData {
  float tempAire;      // °C  — SHT31
  float humedad;       // %   — SHT31
  int   co2Ppm;        // ppm — MH-Z19B
  float luzLux;        // lux — BH1750
  float tempSustrato;  // °C  — DS18B20

  // Error flags: true = lectura fallida, valor = -99 / -1
  bool  errorSHT31;
  bool  errorMHZ19;
  bool  errorBH1750;
  bool  errorDS18B20;
};

bool       initSensors();
SensorData readAllSensors();
