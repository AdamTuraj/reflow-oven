#include "test.h"

void drawTestMenu()
{
  lcd.clear();
  printScreen(0, 0, "Test Menu");
  printScreen(0, 1, "Temp: ");
  lcd.print(getTemperature(), 1);
  lcd.print((char)223);
  drawMenuArrows();
}

void enterTestMenu()
{
  lcd.clear();
  printScreen(0, 0, "Press any button");
  printScreen(0, 1, "to begin.");

  waitForButtonPress(BUTTON_UP_PIN, BUTTON_DOWN_PIN, BUTTON_SELECT_PIN);

  Serial.println("Starting test...");
  lcd.clear();

  printScreen(0, 0, "Click button if");
  printScreen(0, 1, "all is visible.");

  delay(3000);

  const char fullLine[16] = {(char)255, (char)255, (char)255, (char)255, (char)255, (char)255, (char)255, (char)255,
                             (char)255, (char)255, (char)255, (char)255, (char)255, (char)255, (char)255, (char)255};
  lcd.clear();

  printScreen(0, 0, fullLine);
  printScreen(0, 1, fullLine);

  waitForButtonPress(BUTTON_UP_PIN, BUTTON_DOWN_PIN, BUTTON_SELECT_PIN);

  lcd.clear();
  printScreen(0, 0, "Testing heaters");
  printScreen(0, 1, "Clk btn to abort");

  // TODO: Implement heater test
}

void waitForButtonPress(uint8_t button_up, uint8_t button_down, uint8_t button_select)
{
  while (digitalRead(button_up) == HIGH && digitalRead(button_down) == HIGH && digitalRead(button_select) == HIGH)
  {
    delay(10);
  }
}