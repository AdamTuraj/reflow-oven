#ifndef TESTMENU_H
#define TESTMENU_H

#include "lcd.h"
#include "thermocouple.h"
#include "config.h"

void drawTestMenu();
void enterTestMenu();

void waitForButtonPress(uint8_t, uint8_t, uint8_t);

#endif // TESTMENU_H