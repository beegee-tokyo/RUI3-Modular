#line 1 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\module-files\\RAK12500_gnss.h"
/**
 * @file RAK12500_gnss.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Includes and defines for RAK12500
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _RAK12500_GNSS_H_
#define _RAK12500_GNSS_H_
#include <Arduino.h>
#include "main.h"

// Functions
bool init_gnss(void);
bool poll_gnss(void);
void gnss_handler(void *);
void start_gnss(void);
bool init_gnss_at(void);
int gnss_format_handler(SERIAL_PORT port, char *cmd, stParam *param);
bool save_gnss_setting(void);
bool get_gnss_setting(void);

extern uint8_t gnss_format;
extern bool gnss_active;

// GNSS definitions
#define NO_GNSS_INIT 0
#define RAK12500_GNSS 1

// Fake GPS Enable (1) Disable (0)
#define FAKE_GPS 0

// GNSS precision and data format definitions
/** GNSS 4 digit precision and standard Cayenne LPP format */
#define LPP_4_DIGIT 0
/** GNSS 6 digit precision and extended Cayenne LPP format */
#define LPP_6_DIGIT 1
/** Helium Mapper format */
#define HELIUM_MAPPER 2
/** Field Tester format */
#define FIELD_TESTER 3

#endif // _RAK12500_GNSS_H_