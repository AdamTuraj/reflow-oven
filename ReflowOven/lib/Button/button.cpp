#include "button.h"

boolean waitingForRise = false;
uint8_t buttonRise = 0;
unsigned long pressTimed = millis();

uint8_t readButton()
{
  uint8_t result = 0;

  if (digitalRead(BUTTON_UP_PIN) == LOW && waitingForRise == false)
  {
    waitingForRise = true;
    buttonRise = 0;
    pressTimed = millis();
    Serial.println("Button Pressed");
  }
  if (digitalRead(BUTTON_DOWN_PIN) == LOW && waitingForRise == false)
  {
    waitingForRise = true;
    buttonRise = 1;
    pressTimed = millis();
  }
  if (digitalRead(BUTTON_SELECT_PIN) == LOW && waitingForRise == false)
  {
    waitingForRise = true;
    buttonRise = 2;
    pressTimed = millis();
  }

  if (digitalRead(BUTTON_UP_PIN) == HIGH && waitingForRise == true && buttonRise == 0)
  {
    if (millis() - pressTimed > 50)
    {
      tone(BUZZER_PIN, NOTE_CLICK, 50);

      waitingForRise = false;

      result = 1;
    }
    else
    {
      waitingForRise = false;
    }
  }
  if (digitalRead(BUTTON_DOWN_PIN) == HIGH && waitingForRise == true && buttonRise == 1)
  {
    if (millis() - pressTimed > 50)
    {
      tone(BUZZER_PIN, NOTE_CLICK, 50);

      waitingForRise = false;

      result = 2;
    }
    else
    {
      waitingForRise = false;
    }
  }
  if (digitalRead(BUTTON_SELECT_PIN) == HIGH && waitingForRise == true && buttonRise == 2)
  {
    if (millis() - pressTimed > 50)
    {
      tone(BUZZER_PIN, NOTE_CLICK, 50);

      waitingForRise = false;

      result = 3;
    }
    else
    {
      waitingForRise = false;
    }
  }

  return result;
}