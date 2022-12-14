/**
 * @file RAK1905_9dof.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Includes and definitions for RAK1905
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _RAK1905_9DOF_H_
#define _RAK1905_9DOF_H_
#include <Arduino.h>

// Functions
bool init_rak1905(void);
void read_rak1905(void);
void int_assign_rak1905(uint8_t new_irq_pin);
void int_callback_rak1905(void);
void clear_int_rak1905(void);

#endif // _RAK1905_9DOF_H_