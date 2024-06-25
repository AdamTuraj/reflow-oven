#ifndef LCD_H
#define LCD_H

// Includes
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "config.h"

// LCD Section
extern LiquidCrystal_I2C lcd;

void setup_lcd();

void printScreen(uint8_t col, uint8_t row, const char text[]);
void printScreen(uint8_t col, uint8_t row, uint8_t number);

void printByte(uint8_t col, uint8_t row, char text);

void drawMenuArrows();

#endif // LCD_H