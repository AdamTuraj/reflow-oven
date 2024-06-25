#include "thermocouple.h"

float previousTemp = 0.00;

Adafruit_MAX31856 thermocouple = Adafruit_MAX31856(THERMOCOUPLE_CS, THERMOCOUPLE_SDI, THERMOCOUPLE_SDO, THERMOCOUPLE_CLK);

void setup_thermocouple()
{
  thermocouple.begin();

  thermocouple.setThermocoupleType(THERMOCOUPLE_TYPE); // Set the type of thermocouple
  thermocouple.setConversionMode(MAX31856_CONTINUOUS); // Set the conversion mode. We want it to continuously sample the temperature

  thermocouple.setColdJunctionFaultThreshholds(0, THERMOCOUPLE_IC_THRESHHOLD_HIGH); // Set the temp range of the IC
  thermocouple.setTempFaultThreshholds(0, THERMOCOUPLE_HOT_THRESHHOLD_HIGH);        // Set the temp range of the thermocouple
}

float getTemperature()
{
  previousTemp = thermocouple.readThermocoupleTemperature();

  if (previousTemp > 50.00)
  {
    digitalWrite(LED_HOT_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_HOT_PIN, LOW);
  }

  return previousTemp;
}

float getPreviousTemperature()
{
  return previousTemp;
}
