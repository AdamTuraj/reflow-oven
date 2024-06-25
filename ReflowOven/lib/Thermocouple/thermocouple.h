#ifndef THERMOCOUPLE_H
#define THERMOCOUPLE_H

// Includes
#include <Adafruit_MAX31856.h>

#include "config.h"

// Thermocouple Section
extern Adafruit_MAX31856 thermocouple;

void setup_thermocouple();
float getTemperature();
float getPreviousTemperature();

#endif // THERMOCOUPLE_H