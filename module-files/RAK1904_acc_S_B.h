/**
 * @file RAK1904_acc_S_B.cpp
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Header for RAK1904 in slot B
 * @version 0.1
 * @date 2022-04-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Arduino.h>

//******************************************************************//
// RAK1904 INT1_PIN
//******************************************************************//
// Slot A      WB_IO1
// Slot B      WB_IO2 ( not recommended, pin conflict with IO2)
// Slot C      WB_IO3
// Slot D      WB_IO5
// Slot E      WB_IO4
// Slot F      WB_IO6
//******************************************************************//

/** Interrupt pin, depends on slot */
uint8_t acc_int_pin = WB_IO2;
