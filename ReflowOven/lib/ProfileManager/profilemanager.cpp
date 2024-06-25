#include "profilemanager.h"

uint16_t defaultReflowProfile[5][2] = {{150, 60}, {217, 60}, {240, 40}, {240, 10}, {75, 10}};

boolean inManager = false;
boolean selectPressed = false;

uint8_t selectedVar = 0;

void drawProfileMenu()
{
  lcd.clear();
  printScreen(0, 0, "Manage Profile");
  printScreen(0, 1, "Temp: ");
  lcd.print(getTemperature(), 1);
  lcd.print((char)223);
  drawMenuArrows();
}

void enterProfileMenu()
{
  lcd.clear();

  uint16_t(*reflowProfile)[2] = getReflowProfile();

  if (reflowProfile[0][0] == 0)
  {

    reflowProfile = defaultReflowProfile;
    saveReflowProfile(reflowProfile);

    printScreen(0, 0, "Loaded default");
    printScreen(0, 1, "profile.");
  }
  else
  {
    printScreen(0, 0, "Profile loaded.");
  }

  delay(2000);
  drawProfileManager(reflowProfile);
  delay(2000);

  Serial.println("Exiting Profile Manager");
}

void drawProfileManager(uint16_t (*reflowProfile)[2])
{
  uint8_t sectionIndex = 0;
  inManager = true;

  displaySections(reflowProfile[sectionIndex], sectionIndex);

  while (inManager)
  {
    uint8_t result = readButton();

    if (result == 1)
    {
      if (sectionIndex > 0)
      {
        sectionIndex--;
      }
      else
      {
        sectionIndex = 5;
      }
      displaySections(reflowProfile[sectionIndex], sectionIndex);
    }
    else if (result == 2)
    {
      if (sectionIndex < 5)
      {
        sectionIndex++;
      }
      else
      {
        sectionIndex = 0;
      }

      displaySections(reflowProfile[sectionIndex], sectionIndex);
    }
    else if (result == 3 && sectionIndex == 5)
    {
      saveReflowProfile(reflowProfile);
      lcd.clear();
      printScreen(0, 0, "Profile saved!");

      tone(BUZZER_PIN, NOTE_CLICK, 200);

      inManager = false;
    }
    else if (result == 3 && sectionIndex < 5)
    {
      printScreen(11, 0, "   ");
      printByte(12, selectedVar, (char)176);

      selectPressed = false;

      selectedVar = 0;

      while (selectPressed == false)
      {
        uint8_t result = readButton();

        if (result != 0 && result != 3)
        {
          printByte(12, selectedVar, (char)32);

          selectedVar = selectedVar == 0 ? 1 : 0;

          printByte(12, selectedVar, (char)176);
        }

        else if (result == 3)
        {
          selectPressed = true;
        }
      }

      lcd.clear();
      printScreen(0, 0, "Enter new value:");
      printScreen(0, 1, selectedVar == 0 ? "Temp: " : "Time: ");
      lcd.print(reflowProfile[sectionIndex][selectedVar]);

      selectPressed = false;

      while (selectPressed == false)
      {
        uint8_t result = readButton();

        if (result == 1)
        {
          reflowProfile[sectionIndex][selectedVar] += 5;

          printScreen(6, 1, "   ");
          printScreen(6, 1, reflowProfile[sectionIndex][selectedVar]);
        }
        else if (result == 2)
        {
          reflowProfile[sectionIndex][selectedVar] -= 5;

          printScreen(6, 1, "   ");
          printScreen(6, 1, reflowProfile[sectionIndex][selectedVar]);
        }
        else if (result == 3)
        {
          selectPressed = true;
        }
      }

      displaySections(reflowProfile[sectionIndex], sectionIndex);
    }
  }
}

void displaySections(uint16_t profile[2], uint8_t sectionIndex)
{
  lcd.clear();

  if (sectionIndex == 5)
  {
    printScreen(0, 0, "Press any button");
    printScreen(0, 1, "to save.");

    return;
  }

  printScreen(0, 0, "Temp: ");
  lcd.print(profile[0], 1);
  lcd.print((char)223);

  printScreen(0, 1, "Time: ");
  lcd.print(profile[1]);
  lcd.print("sec");

  lcd.setCursor(11, 0);
  lcd.print(sectionIndex + 1); // Convert sectionIndex + 1 to a string
  lcd.print("/5");

  drawMenuArrows();
}