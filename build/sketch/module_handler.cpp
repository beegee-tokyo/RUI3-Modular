#line 1 "d:\\#Github\\RUI3-Examples\\RUI3-Modular-Simplify\\module_handler.cpp"
/**
 * @file module_handler.cpp
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Find and handle WisBlock sensor modules
 * @version 0.1
 * @date 2022-04-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "main.h"
// #include "module_handler.h"

/** Mean Sea Level Pressure */
float mean_sea_level_press = 1013.25;

/**
 * @brief Initialize modules
 *
 */
void init_modules(void)
{
	Wire.begin();
	// Some modules support only 100kHz
	Wire.setClock(100000);

#ifdef _RAK1901_TEMP_H_
	if (!init_rak1901())
	{
		MYLOG("MODS", "Could not initialize RAK1901");
	}
	else
	{
		Serial.println("+EVT:RAK1901 OK");
	}
#endif // _RAK1901_TEMP_H_

#ifdef _RAK1902_PRESS_H_
	if (!init_rak1902())
	{
		MYLOG("MODS", "Could not initialize RAK1902");
	}
	else
	{
		Serial.println("+EVT:RAK1902 OK");
	}
#endif // _RAK1902_PRESS_H_

#ifdef _RAK1903_LIGHT_H_
	if (!init_rak1903())
	{
		MYLOG("MODS", "Could not initialize RAK1903");
	}
	else
	{
		Serial.println("+EVT:RAK1903 OK");
	}
#endif // _RAK1903_LIGHT_H_

#ifdef _RAK1904_ACC_H_
	if (!init_rak1904())
	{
		MYLOG("MODS", "Could not initialize RAK1904");
	}
	else
	{
		Serial.println("+EVT:RAK1904 OK");
	}
#endif // _RAK1904_ACC_H_

#ifdef _RAK1905_9DOF_H_
	if (!init_rak1905())
	{
		MYLOG("MODS", "Could not initialize RAK1905");
	}
	else
	{
		Serial.println("+EVT:RAK1905 OK");
	}
#endif // _RAK1905_9DOF_H_

#ifdef _RAK1906_ENV_H_
	if (!init_rak1906())
	{
		MYLOG("MODS", "Could not initialize RAK1906");
	}
	else
	{
		Serial.println("+EVT:RAK1906 OK");
	}
#endif // _RAK1906_ENV_H_

#ifdef _RAK1921_DISPLAY_H_
	if (!init_rak1921())
	{
		MYLOG("MODS", "Could not initialize RAK1921");
	}
	else
	{
		rak1921_write_header((char *)"WisBlock Node");
			Serial.println("+EVT:RAK1921 OK");
	}
#endif // _RAK1921_DISPLAY_H_

#ifdef _RAK12002_RTC_H_
	if (!init_rak12002())
	{
		MYLOG("MODS", "Could not initialize RAK12002");
	}
	else
	{
		Serial.println("+EVT:RAK12002 OK");
	}
#endif // _RAK12002_RTC_H_

#ifdef _RAK12003_FIR_H_
	if (!init_rak12003())
	{
		MYLOG("MODS", "Could not initialize RAK12003");
	}
	else
	{
		Serial.println("+EVT:RAK12003 OK");
	}
#endif // _RAK12003_FIR_H_

#ifdef _RAK12010_LIGHT_H_
	if (!init_rak12010())
	{
		MYLOG("MODS", "Could not initialize RAK12010");
	}
	else
	{
		Serial.println("+EVT:RAK12010 OK");
	}
#endif // _RAK12010_LIGHT_H_

#ifdef _RAK12014_TOF_H_
	if (!init_rak12014())
	{
		MYLOG("MODS", "Could not initialize RAK12014");
	}
	{
		Serial.println("+EVT:RAK12014 OK");
	}
#endif // _RAK12014_TOF_H_

#ifdef _RAK12019_UV_H_
	if (!init_rak12019())
	{
		MYLOG("MODS", "Could not initialize RAK12019");
	}
	{
		Serial.println("+EVT:RAK12019 OK");
	}
#endif // _RAK12019_UV_H_

#ifdef _RAK12025_GYRO_H_
	if (!init_rak12025())
	{
		MYLOG("MODS", "Could not initialize RAK12025");
	}
	{
		Serial.println("+EVT:RAK12025 OK");
	}
#endif // _RAK12025_GYRO_H_

#ifdef _RAK12027_SEISMIC_H_
	if (!init_rak12027())
	{
		MYLOG("MODS", "Could not initialize RAK12027");
	}
	{
		Serial.println("+EVT:RAK12027 OK");
	}
#endif // _RAK12025_GYRO_H_

#ifdef _RAK12037_CO2_H_
	if (!init_rak12037())
	{
		MYLOG("MODS", "Could not initialize RAK12037");
	}
	{
		Serial.println("+EVT:RAK12037 OK");
	}
#endif // _RAK12037_CO2_H_

#ifdef _RAK12040_TEMP_ARR_H_
	if (!init_rak12040())
	{
		MYLOG("MODS", "Could not initialize RAK12040");
	}
	{
		Serial.println("+EVT:RAK12040 OK");
	}
#endif // _RAK12040_TEMP_ARR_H_

#ifdef _RAK12047_VOC_H_
	if (!init_rak12047())
	{
		MYLOG("MODS", "Could not initialize RAK12047");
	}
	{
		Serial.println("+EVT:RAK12047 OK");
	}
#endif // _RAK12047_VOC_H_

#ifdef _RAK12500_GNSS_H_
	if (!init_gnss())
	{
		MYLOG("MODS", "Could not initialize RAK12500");
	}
	{
		Serial.println("+EVT:RAK12500 OK");
	}
#endif // _RAK12500_GNSS_H_

#ifdef _RAK13011_SWITCH_H_
	if (!init_rak13011())
	{
		MYLOG("MODS", "Could not initialize RAK13011");
	}
	{
		Serial.println("+EVT:RAK13011 OK");
	}
#endif // _RAK13011_SWITCH_H_
}

/**
 * @brief Read values from the found modules
 *
 */
void get_sensor_values(void)
{
#ifdef _RAK1901_TEMP_H_
	read_rak1901();
#endif // _RAK1901_TEMP_H_

#ifdef _RAK1902_PRESS_H_
	read_rak1902();
#endif // _RAK1902_PRESS_H_

#ifdef _RAK1903_LIGHT_H_
	read_rak1903();
#endif // _RAK1903_LIGHT_H_

#ifdef _RAK1904_ACC_H_
	read_rak1904();
#endif // _RAK1904_ACC_H_

#ifdef _RAK1905_9DOF_H_
	read_rak1905();
#endif // _RAK1905_9DOF_H_

#ifdef _RAK1906_ENV_H_
	// Start reading sensor data
	start_rak1906();
	delay(100);
	// Reading sensor data
	read_rak1906();
#endif // _RAK1906_ENV_H_

#ifdef _RAK12003_FIR_H_
	read_rak12003();
#endif // _RAK12003_FIR_H_

#ifdef _RAK12010_LIGHT_H_
	read_rak12010();
#endif // _RAK12010_LIGHT_H_

#ifdef _RAK12014_TOF_H_
	read_rak12014();
#endif // _RAK12014_TOF_H_

#ifdef _RAK12019_UV_H_
	read_rak12019();
#endif // _RAK12019_UV_H_

#ifdef _RAK12037_CO2_H_
	read_rak12037();
#endif // _RAK12037_CO2_H_

#ifdef _RAK12040_TEMP_ARR_H_
	read_rak12040();
#endif // _RAK12040_TEMP_ARR_H_

#ifdef _RAK12047_VOC_H_
	read_rak12047();
#endif // _RAK12047_VOC_H_
}