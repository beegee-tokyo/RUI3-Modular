#line 1 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\module-files\\RAK12027_seismic.h"
/**
 * @file RAK12027_seismic.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Global definitions and forward declarations
 * @version 0.1
 * @date 2022-09-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _RAK12027_SEISMIC_H_
#define _RAK12027_SEISMIC_H_
#include <Arduino.h>
#include <Wire.h>

//******************************************************************//
// RAK12027 INT1_PIN
//******************************************************************//
// Slot A      WB_IO1
// Slot B      WB_IO2 ( not recommended, pin conflict with IO2)
// Slot C      WB_IO3
// Slot D      WB_IO5
// Slot E      WB_IO4
// Slot F      WB_IO6
//******************************************************************//
//******************************************************************//
// RAK12027 INT2_PIN
//******************************************************************//
// Slot A      WB_IO2 ( not recommended, pin conflict with IO2)
// Slot B      WB_IO1
// Slot C      WB_IO4
// Slot D      WB_IO6
// Slot E      WB_IO3
// Slot F      WB_IO5
//******************************************************************//

/** Interrupt pin, depends on slot */
#define INT1_PIN WB_IO3 // interrupt pin INT1 of D7S attached to WB_IO3 of WisBlock Base Board Slot C
#define INT2_PIN WB_IO4 // interrupt pin INT2 of D7S attached to WB_IO4 of WisBlock Base Board Slot C

bool init_rak12027(void);
bool calib_rak12027(void);
void read_rak12027(bool add_values);
void handle_rak12027(void);
uint8_t check_event_rak12027(bool is_int1);
void check_alarm(void *);
void enable_int_rak12027(void);
void report_status(void);
void d7s_int1_handler(void);
void d7s_int2_handler(void);
extern bool shutoff_alert;
extern bool collapse_alert;
extern bool earthquake_start;
extern bool earthquake_end;
extern volatile uint16_t g_seismic_event;

/** Wakeup triggers for application events */
#define SEISMIC_EVENT 0b0000100000000000
#define N_SEISMIC_EVENT 0b1111011111111111
#define SEISMIC_ALERT 0b0000010000000000
#define N_SEISMIC_ALERT 0b1111101111111111

#endif // _RAK12027_SEISMIC_H_