#include "eeprom_driver.h"

uint16_t (*getReflowProfile())[2]
{
  static uint16_t profile[5][2];

  for (uint8_t i = 0; i < 5; i++)
  {
    EEPROM.get(START_PROFILE_ADDRESS + (i * 4), profile[i][0]);
    EEPROM.get(START_PROFILE_ADDRESS + (i * 4) + 2, profile[i][1]);
  }

  return profile;
}

void saveReflowProfile(uint16_t profile[5][2])
{
  for (uint8_t i = 0; i < 5; i++)
  {
    EEPROM.put(START_PROFILE_ADDRESS + (i * 4), profile[i][0]);
    EEPROM.put(START_PROFILE_ADDRESS + (i * 4) + 2, profile[i][1]);
  }
}