#include "sensors.h"
#include "config.h"
#include <Wire.h>
#include <Adafruit_SHT31.h>
#include <BH1750.h>
#include <MHZ19.h>
#include <OneWire.h>
#include <DallasTemperature.h>

static Adafruit_SHT31   sht31;
static BH1750            bh1750;
static MHZ19             mhz19;
static HardwareSerial    mhzSerial(2);  // UART2
static OneWire           oneWire(PIN_DS18B20);
static DallasTemperature ds18b20(&oneWire);

static bool sht31Ok    = false;
static bool bh1750Ok   = false;

bool initSensors() {
  Wire.begin(PIN_SDA, PIN_SCL);

  sht31Ok = sht31.begin(0x44);
  if (!sht31Ok) Serial.println("[SENSOR] ERROR: SHT31 no encontrado en 0x44");
  else           Serial.println("[SENSOR] SHT31 OK");

  bh1750Ok = bh1750.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &Wire);
  if (!bh1750Ok) Serial.println("[SENSOR] ERROR: BH1750 no encontrado en 0x23");
  else            Serial.println("[SENSOR] BH1750 OK");

  // MH-Z19B: necesita 5V en VCC; TX/RX a nivel lógico 3.3V es compatible
  mhzSerial.begin(9600, SERIAL_8N1, PIN_MHZ19_RX, PIN_MHZ19_TX);
  mhz19.begin(mhzSerial);
  mhz19.autoCalibration(false);  // desactivar calibración automática en cultivo
  Serial.println("[SENSOR] MH-Z19B inicializado (UART2)");

  ds18b20.begin();
  Serial.printf("[SENSOR] DS18B20: %d sensor(es) en GPIO%d\n",
                ds18b20.getDeviceCount(), PIN_DS18B20);

  return sht31Ok && bh1750Ok;
}

SensorData readAllSensors() {
  SensorData d = {};

  // ── SHT31 ────────────────────────────────────────────────────────────────
  d.tempAire = sht31.readTemperature();
  d.humedad  = sht31.readHumidity();
  d.errorSHT31 = isnan(d.tempAire) || isnan(d.humedad);
  if (d.errorSHT31) { d.tempAire = -99; d.humedad = -99; }

  // ── BH1750 ───────────────────────────────────────────────────────────────
  d.luzLux     = bh1750.readLightLevel();
  d.errorBH1750 = (d.luzLux < 0);
  if (d.errorBH1750) d.luzLux = -1;

  // ── MH-Z19B ──────────────────────────────────────────────────────────────
  d.co2Ppm   = mhz19.getCO2();
  d.errorMHZ19 = (d.co2Ppm <= 0);
  if (d.errorMHZ19) d.co2Ppm = -1;

  // ── DS18B20 ──────────────────────────────────────────────────────────────
  ds18b20.requestTemperatures();
  d.tempSustrato = ds18b20.getTempCByIndex(0);
  d.errorDS18B20 = (d.tempSustrato == DEVICE_DISCONNECTED_C);
  if (d.errorDS18B20) d.tempSustrato = -99;

  return d;
}
