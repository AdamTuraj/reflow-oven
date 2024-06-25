#ifndef PROFILEMENU_H
#define PROFILEMENU_H

#include "lcd.h"
#include "thermocouple.h"
#include "tones.h"

#include "config.h"
#include "eeprom_driver.h"

#include "button.h"

void drawProfileMenu();
void enterProfileMenu();

// Private Functions
void drawProfileManager(uint16_t (*reflowProfile)[2]);

void displaySections(uint16_t profile[2], uint8_t sectionIndex);

uint8_t readButton();

#endif // PROFILEMENU_H