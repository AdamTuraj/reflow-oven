#include "heater.h"

double Setpoint, Input, Output;

PID myPID(&Input, &Output, &Setpoint, 0, 0, 0, DIRECT);

unsigned long windowStartTime;

void setupHeater()
{
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, WINDOW_TIME);
  windowStartTime = millis();

  pinMode(HEATER_TOP_PIN, OUTPUT);
  pinMode(HEATER_BOTTOM_PIN, OUTPUT);
}

void updateHeater()
{
  Input = getTemperature();

  myPID.Compute();

  if (millis() - windowStartTime > WINDOW_TIME)
  {
    windowStartTime += WINDOW_TIME;
  }

  if ((millis() - windowStartTime) < Output)
  {
    digitalWrite(HEATER_TOP_PIN, HIGH);
    digitalWrite(HEATER_BOTTOM_PIN, HIGH);
  }
  else
  {
    digitalWrite(HEATER_TOP_PIN, LOW);
    digitalWrite(HEATER_BOTTOM_PIN, LOW);
  }
}

void abortHeater()
{
  digitalWrite(HEATER_TOP_PIN, LOW);
  digitalWrite(HEATER_BOTTOM_PIN, LOW);
}

void setHeaterTemperature(double temperature)
{
  Setpoint = temperature;
}

void setHeaterTunings(double kp, double ki, double kd)
{
  myPID.SetTunings(kp, ki, kd);
}