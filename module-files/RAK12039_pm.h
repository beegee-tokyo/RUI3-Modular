/**
 * @file RAK12039_pm.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Functions and definitions for RAK12039
 * @version 0.1
 * @date 2022-10-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _RAK12039_PM_H_
#define _RAK12039_PM_H_
#include <Arduino.h>

// Functions
bool init_rak12039(void);
void read_rak12039(void);

/*
 * @brief WB_IO6 is connected to the SET pin.
 *        Set pin/TTL level @3.3V, high level or suspending is normal working status.
 *        while low level is sleeping mode.
 */
#define SET_PIN WB_IO6

#endif // _RAK12039_PM_H_