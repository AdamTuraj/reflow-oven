#include "debug.h"

// Preheat, Soak, Reflow, Cool down, Cool down
// (Temp, Time)
uint16_t testReflowProfile[5][2] = {{150, 180}, {200, 180}, {225, 90}, {183, 30}, {0, 30}};

void runTest()
{
  while (Serial.available() == 0)
  {
    Serial.println(getTemperature());
    delay(100);
  }

  Serial.println("Running profile");

  setupHeater();

  unsigned long previousMeasureTime = millis();
  float previousTemperature = getTemperature();
  float tempChangePerSecond = 0;

  unsigned long startTime = millis();

  for (uint8_t i = 0; i < 5; i++)
  {
    unsigned long startSectionTime = millis();

    setHeaterTemperature(testReflowProfile[i][0]);

    // Preheat
    if (i == 0)
    {
      setHeaterTunings(PID_KP_PREHEAT, PID_KI_PREHEAT, PID_KD_PREHEAT);
    }
    // Soak
    else if (i == 1)
    {
      setHeaterTunings(PID_KP_SOAK, PID_KI_SOAK, PID_KD_SOAK);
    }
    // Reflow
    else if (i == 2)
    {
      setHeaterTunings(PID_KP_REFLOW, PID_KI_REFLOW, PID_KD_REFLOW);
    }

    while ((millis() - startSectionTime) / 1000 < testReflowProfile[i][1])
    {
      if (getTemperature() > 300)
      {
        Serial.println("Temperature too high, aborting");
        lcd.clear();
        printScreen(0, 0, "Temperature too high, aborting");
        abortHeater();

        return;
      }
      else if (getTemperature() < 0)
      {
        Serial.println("Temperature is out of range, are you sure it is connected");
        lcd.clear();
        printScreen(0, 0, "Probe");
        printScreen(0, 1, "disconnected");
        abortHeater();

        return;
      }
      updateHeater();
      Serial.print(getTemperature());
      Serial.print(",");
      Serial.print(testReflowProfile[i][0]);
      Serial.print(",");
      Serial.print(millis() - startTime);
      Serial.print(",");
      Serial.println(tempChangePerSecond);

      if (millis() - previousMeasureTime > 1000)
      {
        float currentTemperature = getTemperature();
        tempChangePerSecond = (currentTemperature - previousTemperature) / ((millis() - previousMeasureTime) / 1000);
        previousTemperature = currentTemperature;
        previousMeasureTime = millis();
      }
    }
  }
  abortHeater();
  Serial.println("Done");
}