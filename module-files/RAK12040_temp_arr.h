/**
 * @file RAK12040_temp_arr.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Functions and definitions for RAK12040
 * @version 0.1
 * @date 2022-10-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _RAK12040_TEMP_ARR_H_
#define _RAK12040_TEMP_ARR_H_
#include <Arduino.h>

// Functions
bool init_rak12040(void);
void read_rak12040(void);

/** HOT value (in degrees C) to adjust the contrast */
#define HOT 30.0
/** COLD value (in degrees C) to adjust the contrast */
#define COLD 25.0

#endif // _RAK12040_TEMP_ARR_H_