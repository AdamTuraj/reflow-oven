#include "temphold.h"

unsigned long lastScreenRefresh = millis();

void drawTempHoldMenu()
{
  lcd.clear();
  printScreen(0, 0, "Temp Hold Menu");
  printScreen(0, 1, "Temp: ");
  lcd.print(getTemperature(), 1);
  lcd.print((char)223);
  drawMenuArrows();
}

void enterTempHoldMenu()
{
  uint16_t holdTemp = 0;

  lcd.clear();
  printScreen(0, 0, "What tmp to hold");
  printScreen(0, 1, "Temp: ");
  lcd.print(holdTemp);

  while (true)
  {
    uint8_t button = readButton();

    if (button == 1)
    {
      holdTemp += 5;
    }
    else if (button == 2)
    {
      holdTemp -= 5;
    }
    else if (button == 3)
    {
      break;
    }

    printScreen(6, 1, holdTemp);
  }

  lcd.clear();
  printScreen(0, 0, "Holding: ");
  lcd.print(holdTemp);
  lcd.print((char)223);

  printScreen(0, 1, "Press to exit");
  delay(5000);

  printScreen(0, 1, "                ");

  setHeaterTemperature(holdTemp);

  setHeaterTunings(PID_KP_HOLD, PID_KI_HOLD, PID_KI_HOLD);

  while (true)
  {
    updateHeater();

    if (readButton())
    {
      break;
    }

    if (lastScreenRefresh + 1000 < millis())
    {
      float prevTemp = getPreviousTemperature();
      float temp = getTemperature();

      if (prevTemp >= 100.00 && temp < 100.00) // Prevents the temperature from constantly flashing from clearing the screen
      {
        printScreen(0, 1, "               "); // Clears the previous temperature reading
      }

      printScreen(0, 1, "Temp: ");
      lcd.print(temp, 1);
      lcd.print((char)223);

      lastScreenRefresh = millis();
    }
  }

  abortHeater();
}