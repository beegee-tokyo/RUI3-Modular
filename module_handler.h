/**
 * @file module_handler.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Globals and defines for module handling
 * @version 0.1
 * @date 2022-04-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MODULE_HANDLER_H
#define MODULE_HANDLER_H

// Module handler stuff
void init_modules(void);
void get_sensor_values(void);

// Forward declarations
void sensor_handler(void *);
void send_packet(void);

// LoRaWAN stuff
#include "wisblock_cayenne.h"
// Cayenne LPP Channel numbers per sensor value
#define LPP_CHANNEL_BATT 1			   // Base Board
#define LPP_CHANNEL_HUMID 2			   // RAK1901
#define LPP_CHANNEL_TEMP 3			   // RAK1901
#define LPP_CHANNEL_PRESS 4			   // RAK1902
#define LPP_CHANNEL_LIGHT 5			   // RAK1903
#define LPP_CHANNEL_HUMID_2 6		   // RAK1906
#define LPP_CHANNEL_TEMP_2 7		   // RAK1906
#define LPP_CHANNEL_PRESS_2 8		   // RAK1906
#define LPP_CHANNEL_GAS_2 9			   // RAK1906
#define LPP_CHANNEL_GPS 10			   // RAK1910/RAK12500
#define LPP_CHANNEL_SOIL_TEMP 11	   // RAK12035
#define LPP_CHANNEL_SOIL_HUMID 12	   // RAK12035
#define LPP_CHANNEL_SOIL_HUMID_RAW 13  // RAK12035
#define LPP_CHANNEL_SOIL_VALID 14	   // RAK12035
#define LPP_CHANNEL_LIGHT2 15		   // RAK12010
#define LPP_CHANNEL_VOC 16			   // RAK12047
#define LPP_CHANNEL_GAS 17			   // RAK12004
#define LPP_CHANNEL_GAS_PERC 18		   // RAK12004
#define LPP_CHANNEL_CO2 19			   // RAK12008
#define LPP_CHANNEL_CO2_PERC 20		   // RAK12008
#define LPP_CHANNEL_ALC 21			   // RAK12009
#define LPP_CHANNEL_ALC_PERC 22		   // RAK12009
#define LPP_CHANNEL_TOF 23			   // RAK12014
#define LPP_CHANNEL_TOF_VALID 24	   // RAK12014
#define LPP_CHANNEL_GYRO 25			   // RAK12025
#define LPP_CHANNEL_GESTURE 26		   // RAK14008
#define LPP_CHANNEL_UVI 27			   // RAK12019
#define LPP_CHANNEL_UVS 28			   // RAK12019
#define LPP_CHANNEL_CURRENT_CURRENT 29 // RAK16000
#define LPP_CHANNEL_CURRENT_VOLTAGE 30 // RAK16000
#define LPP_CHANNEL_CURRENT_POWER 31   // RAK16000
#define LPP_CHANNEL_TOUCH_1 32		   // RAK14002
#define LPP_CHANNEL_TOUCH_2 33		   // RAK14002
#define LPP_CHANNEL_TOUCH_3 34		   // RAK14002
#define LPP_CHANNEL_CO2_2 35		   // RAK12037
#define LPP_CHANNEL_CO2_Temp_2 36	   // RAK12037
#define LPP_CHANNEL_CO2_HUMID_2 37	   // RAK12037
#define LPP_CHANNEL_TEMP_3 38		   // RAK12003
#define LPP_CHANNEL_TEMP_4 39		   // RAK12003
#define LPP_CHANNEL_PM_1_0 40		   // RAK12039
#define LPP_CHANNEL_PM_2_5 41		   // RAK12039
#define LPP_CHANNEL_PM_10_0 42		   // RAK12039
#define LPP_CHANNEL_EQ_EVENT 43		   // RAK12027
#define LPP_CHANNEL_EQ_SI 44		   // RAK12027
#define LPP_CHANNEL_EQ_PGA 45		   // RAK12027
#define LPP_CHANNEL_EQ_SHUTOFF 46	   // RAK12027
#define LPP_CHANNEL_EQ_COLLAPSE 47	   // RAK12027

extern WisCayenne g_solution_data;

// Uncomment the sensors that are used
// #define _RAK1901_TEMP_H_ // Requires library from ZIP file: https://downloads.rakwireless.com/RUI/RUI3/Library/RAKwireless_RAK1901_Temperature_and_Humidity_SHTC3.zip
// #define _RAK1902_PRESS_H_ // Click here to get the library: http://librarymanager/All#Adafruit_LPS2X
// #define _RAK1903_LIGHT_H_ // Click here to get the library: http://librarymanager/All#OPT3001
// #define _RAK1904_ACC_H_	  // Click here to get the library: http://librarymanager/All#SparkFun-LIS3DH
// #define _RAK1905_9DOF_H_  // Click here to get the library: http://librarymanager/All#MPU9250_WE
// #define _RAK1906_ENV_H_	  // Click here to get the library: http://librarymanager/All#Adafruit_BME680
// #define _RAK1921_DISPLAY_H_ // Click here to get the library: http://librarymanager/All#nRF52_OLED
// #define _RAK12002_RTC_H_	// Click here to get the library: http://librarymanager/All#Melopero_RV3028
// #define _RAK12003_FIR_H_	// Click here to get the library: http://librarymanager/AllSparkFun_MLX90632_Arduino_Library
// #define _RAK12010_LIGHT_H_	// Click here to get the library: http://librarymanager/All#Light_veml7700
// #define _RAK12014_TOF_H_	// Click here to get the library: http://librarymanager/All#VL53L0X
// #define _RAK12019_UV_H_		// Click here to get the library: http://librarymanager/All#RAK12019_LTR390
// #define _RAK12027_SEISMIC_H_ // Click here to get the library: http://librarymanager/All#RAK12027_D7S
// #define _RAK12037_CO2_H_	 // Click here to get the library: http://librarymanager/All#SparkFun_SCD30
// #define _RAK12039_PM_H_		 // Click here to get the library: http://librarymanager/All#RAK12039_PMSA003I
// #define _RAK12040_TEMP_ARR_H_ // Click here to get the library: http://librarymanager/Melopero_AMG8833
// #define _RAK12047_VOC_H_	  // Click here to get the library: http://librarymanager/http://librarymanager/All#SensirionI2CSgp40
// #define _RAK12500_GNSS_H_	  // Click here to get the library: http://librarymanager/http://librarymanager/All#SparkFun_u-blox_GNSS
// #define _RAK13011_SWITCH_H_	  // No library required

#include "module_def.h"

// Custom AT commands
bool init_status_at(void);
bool init_interval_at(void);
bool get_at_setting(void);
bool save_at_setting(void);

// Sensor global definitions
extern float mean_sea_level_press;
extern time_t last_trigger;
extern bool motion_detected;

// Flash offsets for custom settings
/** GNSS settings offset in flash */
#define GNSS_OFFSET 0x00000000 // length 1 byte
/** Send Interval offset in flash */
#define SEND_FREQ_OFFSET 0x00000002 // length 4 bytes

#endif