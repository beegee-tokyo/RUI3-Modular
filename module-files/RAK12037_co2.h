/**
 * @file RAK12037_co2.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Functions and definitions for RAK12037
 * @version 0.1
 * @date 2022-10-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _RAK12037_CO2_H_
#define _RAK12037_CO2_H_
#include <Arduino.h>

// Functions
bool init_rak12037(void);
void read_rak12037(void);

#endif // _RAK12037_CO2_H_