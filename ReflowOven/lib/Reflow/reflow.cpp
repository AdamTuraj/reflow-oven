#include "reflow.h"

void drawReflowMenu()
{
  lcd.clear();
  printScreen(0, 0, "Reflow Menu");
  printScreen(0, 1, "Temp: ");
  lcd.print(getTemperature(), 1);
  lcd.print((char)223);
  drawMenuArrows();
}

const char *reflowMenuSections[] = {"Preheat", "Soak", "Reflow", "Cool down", "Cool down"};

void enterReflowMenu()
{
  boolean inMenu = true;
  uint16_t(*reflowProfile)[2] = getReflowProfile();

  printScreen(0, 0, "Press any button");
  printScreen(0, 1, "to start reflow");

  while (digitalRead(BUTTON_UP_PIN) == HIGH && digitalRead(BUTTON_DOWN_PIN) == HIGH && digitalRead(BUTTON_SELECT_PIN) == HIGH)
  {
    delay(10);
  }

  printScreen(0, 0, "Starting reflow");
  printScreen(0, 1, "Button to abort");

  while (inMenu)
  {
    for (uint8_t i = 0; i < 5; i++)
    {
      unsigned long startSectionTime = millis();

      setHeaterTemperature(reflowProfile[i][0]);

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

      tone(BUZZER_PIN, NOTE_SECTION_DONE, 100);
      lcd.clear();
      printScreen(0, 0, reflowMenuSections[i]);

      while ((millis() - startSectionTime) / 1000 < reflowProfile[i][1])
      {
        if (readButton() && startSectionTime + 1000 < millis())
        {
          lcd.clear();
          printScreen(0, 0, "Reflow aborted");
          abortHeater();

          tone(BUZZER_PIN, NOTE_CLICK, 2500);

          delay(5000);
          return;
        }

        if (getTemperature() > 300)
        {
          Serial.println("Temperature too high, aborting");
          lcd.clear();
          printScreen(0, 0, "Temperature too high, aborting");
          abortHeater();

          tone(BUZZER_PIN, NOTE_CLICK, 2500);

          delay(5000);

          return;
        }
        else if (getTemperature() < 0)
        {
          Serial.println("Temperature is out of range, are you sure it is connected");
          lcd.clear();
          printScreen(0, 0, "Probe");
          printScreen(0, 1, "disconnected");
          abortHeater();

          tone(BUZZER_PIN, NOTE_CLICK, 2500);

          delay(5000);

          return;
        }
        updateHeater();

        printScreen(0, 1, (millis() - startSectionTime) / 1000);
        lcd.print("s/");
        lcd.print(reflowProfile[i][1]);
        lcd.print("s");
        printScreen(9, 1, "|");
        lcd.print(reflowProfile[i][0]);
        lcd.print((char)223);

        printScreen(9, 0, "|");
        lcd.print(getTemperature(), 1);
        lcd.print((char)223);
        lcd.print("/");
      }
    }

    abortHeater();
    inMenu = false;
    tone(BUZZER_PIN, NOTE_SECTION_DONE, 1000);

    lcd.clear();

    while (getTemperature() > 50)
    {
      if (getPreviousTemperature() >= 100.00 && getTemperature() < 100.00) // Prevents the temperature from constantly flashing from clearing the screen
      {
        printScreen(8, 1, "         "); // Clears the previous temperature reading
      }

      printScreen(0, 0, "Cooling down");
      printScreen(0, 1, "Temp: ");
      lcd.print(getTemperature(), 1);
      lcd.print((char)223);

      delay(1000);
    }

    tone(BUZZER_PIN, NOTE_SECTION_DONE, 1000);

    printScreen(0, 0, "Reflow complete");
    printScreen(0, 1, "Remove boards");

    delay(20000);
  }
}