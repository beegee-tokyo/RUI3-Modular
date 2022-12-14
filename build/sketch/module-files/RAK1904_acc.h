#line 1 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\module-files\\RAK1904_acc.h"
/**
 * @file RAK1904_acc.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Includes and definitions for RAK1904
 * @version 0.1
 * @date 2022-10-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _RAK1904_ACC_H_
#define _RAK1904_ACC_H_
#include <Arduino.h>

// Functions
bool rak1904_writeRegister(uint8_t chip_reg, uint8_t dataToWrite);
bool rak1904_readRegister(uint8_t *outputPointer, uint8_t chip_reg);
bool init_rak1904(void);
void read_rak1904(void);
void int_assign_rak1904(uint8_t new_irq_pin);
void int_callback_rak1904(void);
void clear_int_rak1904(void);
bool handle_rak1904_int(void);

#ifdef _RAK12500_GNSS_H_
extern uint8_t gnss_format;
extern bool gnss_active;
#endif // _RAK12500_GNSS_H_

#endif // _RAK1904_ACC_H_