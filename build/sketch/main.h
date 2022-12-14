#line 1 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\main.h"
/**
 * @file main.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Globals and Includes
 * @version 0.1
 * @date 2022-04-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Arduino.h>

// Debug
// Debug output set to 0 to disable app debug output
#ifndef MY_DEBUG
#define MY_DEBUG 1
#endif

#if MY_DEBUG > 0
#define MYLOG(tag, ...)                  \
	do                                   \
	{                                    \
		if (tag)                         \
			Serial.printf("[%s] ", tag); \
		Serial.printf(__VA_ARGS__);      \
		Serial.printf("\n");             \
	} while (0);                         \
	delay(100)
#else
#define MYLOG(...)
#endif

// Globals
extern uint32_t g_send_repeat_time;
extern volatile bool tx_active;

/** Module stuff */
#include "module_handler.h"
