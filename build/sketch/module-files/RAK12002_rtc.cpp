#line 1 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\module-files\\RAK12002_rtc.cpp"
/**
 * @file RAK12002_rtc.cpp
 * @author Bernd Giesecke (bernd.giesecke@rakwireless.com)
 * @brief Initialization and usage of RAK12002 RTC module
 * @version 0.1
 * @date 2022-02-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "main.h"
#include <Melopero_RV3028.h>

/** Instance of the RTC class */
Melopero_RV3028 rtc;

date_time_s g_date_time;

/**
 * @brief Initialize the RTC
 *
 * @return true if success
 * @return false if failed
 */
bool init_rak12002(void)
{
	Wire.begin();
	rtc.initI2C(Wire);

	rtc.useEEPROM(false);

	rtc.writeToRegister(0x35, 0x00);
	rtc.writeToRegister(0x37, 0xB4); // Direct Switching Mode (DSM): when VDD < VBACKUP, switchover occurs from VDD to VBACKUP

	rtc.set24HourMode(); // Set the device to use the 24hour format (default) instead of the 12 hour format

	g_date_time.year = rtc.getYear();
	g_date_time.month = rtc.getMonth();
	g_date_time.weekday = rtc.getWeekday();
	g_date_time.date = rtc.getDate();
	g_date_time.hour = rtc.getHour();
	g_date_time.minute = rtc.getMinute();
	g_date_time.second = rtc.getSecond();

	MYLOG("RTC", "%d.%02d.%02d %d:%02d:%02d", g_date_time.year, g_date_time.month, g_date_time.date, g_date_time.hour, g_date_time.minute, g_date_time.second);
	return true;
}

/**
 * @brief Set the RAK12002 date and time
 *
 * @param year in 4 digit format, e.g. 2020
 * @param month 1 to 12
 * @param date 1 to 31
 * @param hour 0 to 23
 * @param minute 0 to 59
 */
void set_rak12002(uint16_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t minute)
{
	uint8_t weekday = (date + (uint16_t)((2.6 * month) - 0.2) - (2 * (year / 100)) + year + (uint16_t)(year / 4) + (uint16_t)(year / 400)) % 7;
	// MYLOG("RTC", "Calculated weekday is %d", weekday);
	rtc.setTime(year, month, weekday, date, hour, minute, 0);
}

/**
 * @brief Update g_data_time structure with current the date
 *        and time from the RTC
 *
 */
void read_rak12002(void)
{
	g_date_time.year = rtc.getYear();
	g_date_time.month = rtc.getMonth();
	g_date_time.weekday = rtc.getWeekday();
	g_date_time.date = rtc.getDate();
	g_date_time.hour = rtc.getHour();
	g_date_time.minute = rtc.getMinute();
	g_date_time.second = rtc.getSecond();

	MYLOG("RTC", "%d.%02d.%02d %d:%02d:%02d", g_date_time.year, g_date_time.month,
		  g_date_time.date, g_date_time.hour,
		  g_date_time.minute, g_date_time.second);
}

/**
 * @brief Add custom RTC AT commands
 *
 * @return true AT commands were added
 * @return false AT commands couldn't be added
 */
bool init_rtc_at(void)
{
	return api.system.atMode.add((char *)"RTC",
								 (char *)"Set/Get time of RTC module RAK12002 format [yyyy:mm:dd:hh:MM]",
								 (char *)"RTC", rtc_command_handler);
}

/**
 * @brief Handler for custom AT command for the RTC module
 *
 * @param port Serial port used
 * @param cmd char array with the received AT command
 * @param param char array with the received AT command parameters
 * @return int result of command parsing
 * 			AT_OK AT command & parameters valid
 * 			AT_PARAM_ERROR command or parameters invalid
 */
int rtc_command_handler(SERIAL_PORT port, char *cmd, stParam *param)
{
	MYLOG("AT_CMD", "Param size %d", param->argc);
	if (param->argc == 1 && !strcmp(param->argv[0], "?"))
	{
		read_rak12002();
		Serial.print(cmd);
		Serial.print("=");
		Serial.printf("%d.%02d.%02d %d:%02d:%02d\n", g_date_time.year, g_date_time.month,
					  g_date_time.date, g_date_time.hour,
					  g_date_time.minute, g_date_time.second);
	}
	else if (param->argc == 5)
	{
		for (int j = 0; j < param->argc; j++)
		{
			for (int i = 0; i < strlen(param->argv[j]); i++)
			{
				if (!isdigit(*(param->argv[j] + i)))
				{
					// MYLOG("AT_CMD", "%d is no digit in param %d", i, j);
					return AT_PARAM_ERROR;
				}
			}
		}
		uint32_t year;
		uint32_t month;
		uint32_t date;
		uint32_t hour;
		uint32_t minute;

		/* Check year */
		year = strtoul(param->argv[0], NULL, 0);

		if (year > 3000)
		{
			// MYLOG("AT_CMD", "Year error %d", year);
			return AT_PARAM_ERROR;
		}

		if (year < 2022)
		{
			// MYLOG("AT_CMD", "Year error %d", year);
			return AT_PARAM_ERROR;
		}

		/* Check month */
		month = strtoul(param->argv[1], NULL, 0);

		if ((month < 1) || (month > 12))
		{
			// MYLOG("AT_CMD", "Month error %d", month);
			return AT_PARAM_ERROR;
		}

		// Check day
		date = strtoul(param->argv[2], NULL, 0);

		if ((date < 1) || (date > 31))
		{
			// MYLOG("AT_CMD", "Day error %d", date);
			return AT_PARAM_ERROR;
		}

		// Check hour
		hour = strtoul(param->argv[3], NULL, 0);

		if (hour > 24)
		{
			// MYLOG("AT_CMD", "Hour error %d", hour);
			return AT_PARAM_ERROR;
		}

		// Check minute
		minute = strtoul(param->argv[4], NULL, 0);

		if (minute > 59)
		{
			// MYLOG("AT_CMD", "Minute error %d", minute);
			return AT_PARAM_ERROR;
		}

		set_rak12002((uint16_t)year, (uint8_t)month, (uint8_t)date, (uint8_t)hour, (uint8_t)minute);

		return AT_OK;
	}
	else
	{
		return AT_PARAM_ERROR;
	}

	return AT_OK;
}
