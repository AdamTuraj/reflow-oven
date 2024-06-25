#include "lcd.h"

// LCD Section
LiquidCrystal_I2C lcd(I2C_LCD_ADDRESS, I2C_LCD_COLUMNS, I2C_LCD_ROWS);

// Custom characters
uint8_t arrowUp[] = {
    0b00000,
    0b00100,
    0b01110,
    0b10101,
    0b00100,
    0b00100,
    0b00100,
    0b00000};

uint8_t arrowDown[] = {
    0b00000,
    0b00100,
    0b00100,
    0b00100,
    0b10101,
    0b01110,
    0b00100,
    0b00000};

void setup_lcd()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);

  lcd.createChar(0, arrowUp);
  lcd.createChar(1, arrowDown);
}

void printScreen(uint8_t col, uint8_t row, const char text[])
{
  lcd.setCursor(col, row);
  lcd.print(text);
}

void printScreen(uint8_t col, uint8_t row, uint8_t text)
{
  lcd.setCursor(col, row);
  lcd.print(text);
}

void printByte(uint8_t col, uint8_t row, char text)
{
  lcd.setCursor(col, row);
  lcd.print(text);
}

void drawMenuArrows()
{
  printByte(15, 0, 0);
  printByte(15, 1, 1);
}