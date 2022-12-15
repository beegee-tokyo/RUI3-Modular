#line 1 "d:\\#Github\\RUI3-Examples\\RUI3-Modular-Simplify\\module-files\\RAK12039_pm.cpp"
/**
 * @file RAK12039_pm.cpp
 * @author Bernd Giesecke (bernd.giesecke@rakwireless.com)
 * @brief PMSA003I particle matter sensor support
 * @version 0.1
 * @date 2022-07-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "main.h"
#include <RAK12039_PMSA003I.h>

/** Instance of sensor class */
RAK_PMSA003I PMSA003I;

/** Data structure */
PMSA_Data_t data;

/**
 * @brief Initialize the PMSA003I sensor
 *
 * @return true if sensor was found
 * @return false if sensor was not found
 */
bool init_rak12039(void)
{
	// On/Off control pin
	pinMode(SET_PIN, OUTPUT);

	// Sensor on
	digitalWrite(SET_PIN, HIGH);

	// Wait for sensor wake-up
	delay(300);
	Wire.begin();
	if (!PMSA003I.begin())
	{
		MYLOG("Dust", "PMSA003I begin fail,please check connection!");
		digitalWrite(SET_PIN, LOW);
		return false;
	}

	// digitalWrite(SET_PIN, LOW);
	return true;
}

/**
 * @brief Read ToF data from PMSA003I
 *     Data is added to Cayenne LPP payload as channels
 *     LPP_CHANNEL_PM_1_0, LPP_CHANNEL_PM_2_5, LPP_CHANNEL_PM_10_0
 *
 */
void read_rak12039(void)
{
	if (PMSA003I.readDate(&data))
	{

		MYLOG("PMS","PMSA003I read date success.");

		g_solution_data.addVoc_index(LPP_CHANNEL_PM_1_0,data.pm10_env);
		g_solution_data.addVoc_index(LPP_CHANNEL_PM_2_5,data.pm25_env);
		g_solution_data.addVoc_index(LPP_CHANNEL_PM_10_0,data.pm100_env);

		MYLOG("PMS","Std PM ug/m3: PM 1.0 %d PM 2.5 %d PM 10 %d",data.pm10_standard,data.pm25_standard,data.pm100_standard);
		MYLOG("PMS","Env PM ug/m3: PM 1.0 %d PM 2.5 %d PM 10 %d",data.pm10_env,data.pm25_env,data.pm100_env);
#if HAS_EPD > 0
	set_pm_rak14000(data.pm10_env,data.pm25_env,data.pm100_env);
#endif
	}
	else
	{
		Serial.println("PMSA003I read failed!");
	}
	return;
}