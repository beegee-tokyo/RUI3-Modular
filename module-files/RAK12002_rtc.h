/**
 * @file RAK12002_rtc.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Includes and defines for RAK1921
 *
 * @version 0.1
 * @date 2022-10-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _RAK12002_RTC_H_
#define _RAK12002_RTC_H_
#include <Arduino.h>

// Functions
bool init_rak12002(void);
void set_rak12002(uint16_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t minute);
void read_rak12002(void);
bool init_rtc_at(void);
int rtc_command_handler(SERIAL_PORT port, char *cmd, stParam *param);

/** RTC date/time structure */
struct date_time_s
{
	uint16_t year;
	uint8_t month;
	uint8_t weekday;
	uint8_t date;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
};
extern date_time_s g_date_time;

#endif // _RAK12002_RTC_H_