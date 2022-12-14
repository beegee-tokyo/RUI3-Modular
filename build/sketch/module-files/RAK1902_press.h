#line 1 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\module-files\\RAK1902_press.h"
/**
 * @file RAK1902_press.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Includes and definitions for RAK1902
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _RAK1902_PRESS_H_
#define _RAK1902_PRESS_H_
#include <Arduino.h>

// Functions
bool init_rak1902(void);
void read_rak1902(void);
uint16_t get_alt_rak1902(void);

// Globals
extern float mean_sea_level_press;

#endif // _RAK1902_PRESS_H_