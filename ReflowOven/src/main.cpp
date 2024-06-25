#include "main.h"

// Global Variables
uint8_t menu = 0;
boolean inMenu = true;

unsigned long lastTempUpdate = millis();

void setup()
{
  delay(100);

  // Setup the serial port
  Serial.begin(115200);

  // Setup the inputs and outputs
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP);

  pinMode(LED_HOT_PIN, OUTPUT);

  // Setup the peripherals
  setup_thermocouple();
  setup_lcd();
  setupHeater();
  Serial.println("Setup complete");

  // print the splash screen
  printScreen(0, 0, "Reflow Oven v1.0");
  printScreen(1, 1, "Made by Adam T");

  delay(500);

  // Play the startup tone
  tone(BUZZER_PIN, NOTE_STARTUP, 200);
  delay(2000);

  if (DEBUG)
  {
    runTest();
  }

  // Draw the main menu
  drawMainMenu();
}

void (*menus[NUMBER_OF_MENUS])() = {drawMainMenu, drawReflowMenu, drawTempHoldMenu, drawTestMenu, drawProfileMenu};
// void (*enterMenus[NUMBER_OF_MENUS])() = {enterMainMenu, enterReflowMenu, enterBakeMenu, enterTestMenu, enterProfileMenu};
void (*enterMenus[NUMBER_OF_MENUS])() = {nullptr, enterReflowMenu, enterTempHoldMenu, enterTestMenu, enterProfileMenu};

void loop()
{
  if (inMenu)
  {
    if (lastTempUpdate + 1000 < millis())
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

      lastTempUpdate = millis();
    }

    uint8_t button = readButton();

    if (button == 1)
    {
      if (menu > 0)
      {
        menu--;
      }
      else if (menu == 0)
      {
        menu = NUMBER_OF_MENUS - 1;
      }
      menus[menu]();
    }
    else if (button == 2)
    {
      if (menu < NUMBER_OF_MENUS - 1)
      {
        menu++;
      }
      else
      {
        menu = 0;
      }
      menus[menu]();
    }
    else if (button == 3)
    {
      if (menu == 0)
      {
        return;
      }

      inMenu = false;
      lcd.clear();
      enterMenus[menu]();

      drawMainMenu();
      inMenu = true;
      menu = 0;
    }
  }

  delay(50);
}

void drawMainMenu()
{
  lcd.clear();

  float temp = getTemperature();

  printScreen(0, 0, "Main Menu");
  printScreen(0, 1, "Temp: ");
  lcd.print(temp, 1);
  lcd.print((char)223);

  printByte(15, 0, 0);
  printByte(15, 1, 1);
}