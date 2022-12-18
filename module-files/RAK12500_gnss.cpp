/**
 * @file RAK12500_gnss.cpp
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief GNSS functions
 * @version 0.1
 * @date 2022-04-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "main.h"

#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

/** Instance for RAK12500 GNSS sensor */
SFE_UBLOX_GNSS my_gnss;

/** GNSS polling function */
bool poll_gnss(void);

/** Flag if location was found */
volatile bool last_read_ok = false;

/** Flag if GNSS is serial or I2C */
bool i2c_gnss = false;

/** The GPS module to use */
uint8_t g_gnss_option = 0;

/** Counter for GNSS readings */
uint16_t check_gnss_counter = 0;
/** Max number of GNSS readings before giving up */
uint16_t check_gnss_max_try = 0;

/** Flag for GNSS readings active */
bool gnss_active = false;

/**
 * @brief GNSS format and precision
 * 0 = 4 digit standard Cayenne LPP format
 * 1 = 6 digit extended Cayenne LPP format
 * 2 = Helium Mapper data format
 */
uint8_t gnss_format = 0;

/**
 * @brief Initialize GNSS module
 *
 * @return true if GNSS module was found
 * @return false if no GNSS module was found
 */
bool init_gnss(void)
{
	// Power on the GNSS module
	digitalWrite(WB_IO2, HIGH);

	// Give the module some time to power up
	delay(500);

	if (g_gnss_option == NO_GNSS_INIT)
	{
		Wire.begin();
		if (!my_gnss.begin(Wire))
		{
			MYLOG("GNSS", "Could not initialize RAK12500 on Wire");
			i2c_gnss = false;
			return false;
		}
		else
		{
			i2c_gnss = true;
			MYLOG("GNSS", "RAK12500 found on I2C");
			i2c_gnss = true;
			my_gnss.setI2COutput(COM_TYPE_UBX); // Set the I2C port to output UBX only (turn off NMEA noise)
			g_gnss_option = RAK12500_GNSS;

			my_gnss.saveConfiguration(); // Save the current settings to flash and BBR

			my_gnss.setMeasurementRate(500);

			MYLOG("SETUP", "Create timer for GNSS polling");
			// Create a timer.
			api.system.timer.create(RAK_TIMER_1, gnss_handler, RAK_TIMER_PERIODIC);

			// Add GNSS custom AT commands
			init_gnss_at();
			return true;
		}
	}
	else
	{
		if (g_gnss_option == RAK12500_GNSS)
		{
			my_gnss.begin(Wire);
		}
		return true;
	}
	return false;
}

/**
 * @brief Check GNSS module for position
 *
 * @return true Valid position found
 * @return false No valid position
 */
bool poll_gnss(void)
{
	last_read_ok = false;

	time_t time_out = millis();
	int64_t latitude = 0;
	int64_t longitude = 0;
	int32_t altitude = 0;
	int16_t accuracy = 0;
	uint8_t satellites = 0;

	time_t check_limit = g_send_repeat_time / 2;

	bool has_pos = false;
	bool has_alt = false;

	if (g_gnss_option == RAK12500_GNSS)
	{
		if (my_gnss.getGnssFixOk())
		{
			byte fix_type = my_gnss.getFixType(); // Get the fix type
			char fix_type_str[32] = {0};
			if (fix_type == 0)
				sprintf(fix_type_str, "No Fix");
			else if (fix_type == 1)
				sprintf(fix_type_str, "Dead reckoning");
			else if (fix_type == 2)
				sprintf(fix_type_str, "Fix type 2D");
			else if (fix_type == 3)
				sprintf(fix_type_str, "Fix type 3D");
			else if (fix_type == 4)
				sprintf(fix_type_str, "GNSS fix");
			else if (fix_type == 5)
				sprintf(fix_type_str, "Time fix");

			if ((fix_type >= 3) && (my_gnss.getSIV() >= 5)) /** Fix type 3D and at least 5 satellites */
															// if (fix_type >= 3) /** Fix type 3D */
			{
				last_read_ok = true;
				latitude = my_gnss.getLatitude();
				longitude = my_gnss.getLongitude();
				altitude = my_gnss.getAltitude();
				accuracy = my_gnss.getHorizontalDOP();
				satellites = my_gnss.getSIV();

				// MYLOG("GNSS", "Fixtype: %d %s", my_gnss.getFixType(), fix_type_str);
				// MYLOG("GNSS", "Lat: %.4f Lon: %.4f", latitude / 10000000.0, longitude / 10000000.0);
				// MYLOG("GNSS", "Alt: %.2f", altitude / 1000.0);
				// MYLOG("GNSS", "Acy: %.2f ", accuracy / 100.0);
			}
		}
	}

	char disp_str[255];
	if (last_read_ok)
	{
		if ((latitude == 0) && (longitude == 0))
		{
			last_read_ok = false;
			return false;
		}

		switch (gnss_format)
		{
		case LPP_4_DIGIT:
			g_solution_data.addGNSS_4(LPP_CHANNEL_GPS, latitude, longitude, altitude);
			break;
		case LPP_6_DIGIT:
			g_solution_data.addGNSS_6(LPP_CHANNEL_GPS, latitude, longitude, altitude);
			break;
		case HELIUM_MAPPER:
			g_solution_data.addGNSS_H(latitude, longitude, altitude, accuracy, api.system.bat.get());
			break;
		case FIELD_TESTER:
			g_solution_data.addGNSS_T(latitude, longitude, altitude, accuracy, satellites);
			break;
		}

		// if (found_sensors[OLED_ID].found_sensor)
		// {
		// 	sprintf(disp_str, "%.2f %.2f %.2f", latitude / 10000000.0, longitude / 10000000.0, altitude / 1000.0, accuracy / 100.0);
		// 	rak1921_add_line(disp_str);
		// }
		return true;
	}
	else
	{
		// No location found
#if FAKE_GPS > 0
		MYLOG("GNSS", "Faking GPS");
		// 14.4213730, 121.0069140, 35.000
		latitude = 144213730;
		longitude = 1210069140;
		altitude = 35000;
		accuracy = 1;
		satellites = 5;

		switch (gnss_format)
		{
		case LPP_4_DIGIT:
			g_solution_data.addGNSS_4(LPP_CHANNEL_GPS, latitude, longitude, altitude);
			break;
		case LPP_6_DIGIT:
			g_solution_data.addGNSS_6(LPP_CHANNEL_GPS, latitude, longitude, altitude);
			break;
		case HELIUM_MAPPER:
			g_solution_data.addGNSS_H(latitude, longitude, altitude, accuracy, api.system.bat.get());
			break;
		case FIELD_TESTER:
			g_solution_data.addGNSS_T(latitude, longitude, altitude, accuracy, satellites);
			break;
		}
		last_read_ok = true;

		// if (found_sensors[OLED_ID].found_sensor)
		// {
		// 	sprintf(disp_str, "%.2f %.2f %.2f", latitude / 10000000.0, longitude / 10000000.0, altitude / 1000.0, accuracy / 100.0);
		// 	rak1921_add_line(disp_str);
		// }
		return true;
#endif
	}

	// if (found_sensors[OLED_ID].found_sensor)
	// {
	// 	sprintf(disp_str, "No valid location found");
	// 	rak1921_add_line(disp_str);
	// }
	// MYLOG("GNSS", "No valid location found");
	last_read_ok = false;
	return false;
}

/**
 * @brief GNSS location aqcuisition
 * Called every 2.5 seconds by timer 1
 * Gives up after 1/2 of send interval
 * or when location was aquired
 *
 */
void gnss_handler(void *)
{
	digitalWrite(LED_GREEN, HIGH);
	if (poll_gnss())
	{
		// Power down the module
		digitalWrite(WB_IO2, LOW);
		delay(100);
		MYLOG("GNSS", "Got location");
		api.system.timer.stop(RAK_TIMER_1);
		// Helium Mapper and Field Tester ignore sensors and sends only location data
		if ((gnss_format != HELIUM_MAPPER) && (gnss_format != FIELD_TESTER))
		{
			// Read sensor data
			get_sensor_values();

			// Add battery voltage
			g_solution_data.addVoltage(LPP_CHANNEL_BATT, api.system.bat.get());
		}
		send_packet();
	}
	else
	{
		if (check_gnss_counter >= check_gnss_max_try)
		{
			// Power down the module
			digitalWrite(WB_IO2, LOW);
			delay(100);
			MYLOG("GNSS", "Location timeout");
			api.system.timer.stop(RAK_TIMER_1);
			if ((gnss_format != HELIUM_MAPPER) && (gnss_format != FIELD_TESTER))
			{
				get_sensor_values();
				send_packet();
			}
		}
	}
	check_gnss_counter++;
	digitalWrite(LED_GREEN, LOW);
}

/**
 * @brief Start the GNSS location acquisition
 *
 */
void start_gnss(void)
{
	// Already active?
	if (gnss_active)
	{
		return;
	}

	// GNSS module found?
	if (i2c_gnss)
	{ // Set flag for GNSS active to avoid retrigger */
		gnss_active = true;
		// Startup GNSS module
		init_gnss();
		// Start the timer
		api.system.timer.start(RAK_TIMER_1, 2500, NULL);
		check_gnss_counter = 0;
		// Max location aquisition time is half of send interval
		check_gnss_max_try = g_send_repeat_time / 2 / 2500;
	}
}

/**
 * @brief Add custom GNSS AT commands
 *
 * @return true AT commands were added
 * @return false AT commands couldn't be added
 */
bool init_gnss_at(void)
{
	bool result = false;

	result = api.system.atMode.add((char *)"GNSS",
								   (char *)"Change GNSS precision and payload format. 0 = 4digit prec., 1 = 6digit prec, 2 = Helium Mapper format, 3 = Field Tester format",
								   (char *)"GNSS", gnss_format_handler);

	if (!get_gnss_setting())
	{
		MYLOG("AT_CMD", "Could not get default GNSS settings");
		result = false;
	}
	switch (gnss_format)
	{
	case LPP_4_DIGIT:
		MYLOG("AT_CMD", "GNSS 4 digit Cayenne LPP");
		break;
	case LPP_6_DIGIT:
		MYLOG("AT_CMD", "GNSS 6 digit extended Cayenne LPP");
		break;
	case HELIUM_MAPPER:
		MYLOG("AT_CMD", "GNSS Helium Mapper data format");
		break;
	case FIELD_TESTER:
		MYLOG("AT_CMD", "GNSS Field Tester data format");
		break;
	}

	return result;
}

/**
 * @brief Handler for custom AT command for GNSS settings
 *
 * @param port Serial port used
 * @param cmd char array with the received AT command
 * @param param char array with the received AT command parameters
 * @return int result of command parsing
 * 			AT_OK AT command & parameters valid
 * 			AT_PARAM_ERROR command or parameters invalid
 */
int gnss_format_handler(SERIAL_PORT port, char *cmd, stParam *param)
{
	if (param->argc == 1 && !strcmp(param->argv[0], "?"))
	{
		Serial.print(cmd);
		Serial.print("=");
		switch (gnss_format)
		{
		case LPP_4_DIGIT:
			Serial.println("4 digit Cayenne LPP");
			break;
		case LPP_6_DIGIT:
			Serial.println("6 digit extended Cayenne LPP");
			break;
		case HELIUM_MAPPER:
			Serial.println("Helium Mapper data format");
			break;
		case FIELD_TESTER:
			Serial.println("Field Tester data format");
			break;
		}
	}
	else if (param->argc == 1)
	{
		for (int i = 0; i < strlen(param->argv[0]); i++)
		{
			if (!isdigit(*(param->argv[0] + i)))
			{
				MYLOG("AT_CMD", "%d is no digit", i);
				return AT_PARAM_ERROR;
			}
		}

		uint32_t gnss_format_new = strtoul(param->argv[0], NULL, 10);

		MYLOG("AT_CMD", "Requested format %ld", gnss_format_new);

		if (gnss_format_new > FIELD_TESTER)
		{
			return AT_PARAM_ERROR;
		}

		MYLOG("AT_CMD", "Set format to %d", gnss_format_new);
		gnss_format = gnss_format_new;
		if (!save_gnss_setting())
		{
			MYLOG("AT_CMD", "Save failed");
			return AT_PARAM_ERROR;
		}
	}
	else
	{
		return AT_PARAM_ERROR;
	}

	return AT_OK;
}

/**
 * @brief Get setting from flash
 *
 * @return true read from flash was successful
 * @return false read from flash failed or invalid settings type
 */
bool get_gnss_setting(void)
{
	uint8_t flash_value[16];
	if (!api.system.flash.get(GNSS_OFFSET, flash_value, 2))
	{
		MYLOG("AT_CMD", "Failed to read GNSS value from Flash");
		return false;
	}
	if (flash_value[1] != 0xAA)
	{
		MYLOG("AT_CMD", "Invalid GNSS settings, using default");
		gnss_format = 0;
		save_gnss_setting();
	}
	if (flash_value[0] > FIELD_TESTER)
	{
		MYLOG("AT_CMD", "No valid GNSS value found, set to default, read 0X%0X", flash_value[0]);
		gnss_format = 0;
		return false;
	}
	gnss_format = flash_value[0];
	MYLOG("AT_CMD", "Found GNSS format to %d", flash_value[0]);
	return true;
}

/**
 * @brief Save GNSS setting to flash
 *
 * @return true write to flash was successful
 * @return false write to flash failed or invalid settings type
 */
bool save_gnss_setting(void)
{
	uint8_t flash_value[16] = {0};
	bool wr_result = false;
	flash_value[0] = gnss_format;
	flash_value[1] = 0xAA;
	return api.system.flash.set(GNSS_OFFSET, flash_value, 2);
}
