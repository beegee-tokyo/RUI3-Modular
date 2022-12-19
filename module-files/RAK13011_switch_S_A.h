/**
 * @file RAK13011_S_A.cpp
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Header for RAK13011 in slot A
 * @version 0.1
 * @date 2022-04-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Arduino.h>

//******************************************************************//
// RAK13011 INT1_PIN
//******************************************************************//
// Slot A      WB_IO1
// Slot B      WB_IO2 ( not recommended, pin conflict with IO2)
// Slot C      WB_IO3
// Slot D      WB_IO5
// Slot E      WB_IO4
// Slot F      WB_IO6
//******************************************************************//

/** Interrupt pin, depends on slot */
#define SW_INT_PIN WB_IO1
