#ifndef HEATER_H
#define HEATER_H

#include <Arduino.h> // I don't know why but it kept erroring without this

#include <PID_v1.h>

#include "config.h"
#include "thermocouple.h"

#define WINDOW_TIME 1000

void setupHeater();
void updateHeater();
void abortHeater();

void setHeaterTemperature(double temperature);
void setHeaterTunings(double kp, double ki, double kd);

#endif // HEATER_H