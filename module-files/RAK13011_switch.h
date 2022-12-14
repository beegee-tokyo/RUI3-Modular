/**
 * @file RAK13011_switch.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Functions and definitions for RAK13011
 * @version 0.1
 * @date 2022-10-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _RAK13011_SWITCH_H_
#define _RAK13011_SWITCH_H_
#include <Arduino.h>

// Functions
bool init_rak13011(void);
void handle_rak13011(void *);

#define LPP_CHANNEL_SWITCH 48 // RAK13011

#endif // _RAK13011_SWITCH_H_