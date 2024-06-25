/*
These are some overall configuration options for the project.
This is where you can define the pins for the buttons, and buzzer.
Other configuration can be found with their respective header file
*/

#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG 0 // This will enable the debug profile generator

// **** Buzzer ****
#define BUZZER_PIN 8

// **** Buttons ****
#define BUTTON_UP_PIN 7
#define BUTTON_DOWN_PIN 5
#define BUTTON_SELECT_PIN 6

// **** Relay pins ****
#define HEATER_TOP_PIN 4
#define HEATER_BOTTOM_PIN 9

// **** PID Variables ****
// **** PRE-HEAT STAGE ****
#define PID_KP_PREHEAT 100
#define PID_KI_PREHEAT 0.025
#define PID_KD_PREHEAT 20
// *** SOAKING STAGE ****
#define PID_KP_SOAK 300
#define PID_KI_SOAK 0.05
#define PID_KD_SOAK 250
// **** REFLOW STAGE ****
#define PID_KP_REFLOW 300
#define PID_KI_REFLOW 0.05
#define PID_KD_REFLOW 350

// **** Holding Temperature ****
#define PID_KP_HOLD 100
#define PID_KI_HOLD 0.025
#define PID_KD_HOLD 20

// **** Thermocouple Configuration ****
#define LED_HOT_PIN 4

#define THERMOCOUPLE_CS 10
#define THERMOCOUPLE_SDI 11
#define THERMOCOUPLE_SDO 12
#define THERMOCOUPLE_CLK 13

#define THERMOCOUPLE_TYPE MAX31856_TCTYPE_K

#define THERMOCOUPLE_IC_THRESHHOLD_HIGH 60   // Shouldn't ever reach this temperature
#define THERMOCOUPLE_HOT_THRESHHOLD_HIGH 300 // You should never reflow above this temperature

// **** LCD Configuration ****
#define I2C_LCD_ADDRESS 0x27 // This will always be the address unless manually changed by bridging 3 pins on the breakout board

// Code assumes you are using these sizes
#define I2C_LCD_COLUMNS 16
#define I2C_LCD_ROWS 2

#endif // CONFIG_H
