/**
 * @file RAK1906_env.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Definitions and includes for RAK1906
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _RAK1906_ENV_H_
#define _RAK1906_ENV_H_
#include <Arduino.h>

//Functions
bool init_rak1906(void);
void start_rak1906(void);
bool read_rak1906(void);
uint16_t get_alt_rak1906(void);

// Globals
extern float mean_sea_level_press;

#endif // _RAK1906_ENV_H_