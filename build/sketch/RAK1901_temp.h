#line 1 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RAK1901_temp.h"
/**
 * @file RAK1901_temp.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Definitions and includes for RAK1901
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _RAK1901_TEMP_H_
#define _RAK1901_TEMP_H_
#include <Arduino.h>

// Functions
bool init_rak1901(void);
void read_rak1901(void);
void get_rak1901_values(float *values);
#endif // _RAK1901_TEMP_H_