#ifndef EEPROM_H
#define EEPROM_H

#include <EEPROM.h>

#define START_PROFILE_ADDRESS 1

uint16_t (*getReflowProfile())[2];
void saveReflowProfile(uint16_t profile[5][2]);

#endif // EEPROM_H