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

// Enable modules if their code files exists
#if __has_include("RAK1901_temp.cpp")
#define _RAK1901_TEMP_H_
#endif
#if __has_include("RAK1902_press.cpp")
#define _RAK1902_PRESS_H_
#endif
#if __has_include("RAK1903_light.cpp")
#define _RAK1903_LIGHT_H_
#endif
#if __has_include("RAK1904_acc.cpp")
#define _RAK1904_ACC_H_
#endif
#if __has_include("RAK1905_9dof.cpp")
#define _RAK1905_9DOF_H_
#endif
#if __has_include("RAK1906_env.cpp")
#define _RAK1906_ENV_H_
#endif
#if __has_include("RAK1921_display.cpp")
#define _RAK1921_DISPLAY_H_
#endif
#if __has_include("RAK12002_rtc.cpp")
#define _RAK12002_RTC_H_
#endif
#if __has_include("RAK12003_fir.cpp")
#define _RAK12003_FIR_H_
#endif
#if __has_include("RAK12010_light.cpp")
#define _RAK12010_LIGHT_H_
#endif
#if __has_include("RAK12014_tof.cpp")
#define _RAK12014_TOF_H_
#endif
#if __has_include("RAK12019_uv.cpp")
#define _RAK12019_UV_H_
#endif
#if __has_include("RAK12027_seismic.cpp")
#define _RAK12027_SEISMIC_H_
#endif
#if __has_include("RAK12037_co2.cpp")
#define _RAK12037_CO2_H_
#endif
#if __has_include("RAK12039_pm.cpp")
#define _RAK12039_PM_H_
#endif
#if __has_include("RAK12039_pm.cpp")
#define _RAK12040_TEMP_ARR_H_
#endif
#if __has_include("RAK12047_voc.cpp")
#define _RAK12047_VOC_H_
#endif
#if __has_include("RAK12500_gnss.cpp")
#define _RAK12500_GNSS_H_
#endif
#if __has_include("RAK13011_switch.cpp")
#define _RAK13011_SWITCH_H_
#endif

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