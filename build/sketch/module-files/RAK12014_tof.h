#line 1 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\module-files\\RAK12014_tof.h"
/**
 * @file RAK12014_tof.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Functions and definitions for RAK12014
 * @version 0.1
 * @date 2022-10-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _RAK12014_TOF_H_
#define _RAK12014_TOF_H_
#include <Arduino.h>

// Functions
bool init_rak12014(void);
void read_rak12014(void);

#endif // _RAK12014_TOF_H_