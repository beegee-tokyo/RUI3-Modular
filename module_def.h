/**
 * @file module_def.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Definitions and globals for the WisBlock Modules
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
// RAK1901
#ifdef _RAK1901_TEMP_H_
#pragma message("Enabled RAK1901")
// Functions
bool init_rak1901(void);
void read_rak1901(void);
void get_rak1901_values(float *values);
#endif // _RAK1901_TEMP_H_

// RAK1902
#ifdef _RAK1902_PRESS_H_
#pragma message("Enabled RAK1902")
// Functions
bool init_rak1902(void);
void read_rak1902(void);
uint16_t get_alt_rak1902(void);
// Globals
extern float mean_sea_level_press;
#endif // _RAK1902_PRESS_H_

// RAK1903
#ifdef _RAK1903_LIGHT_H_
#pragma message("Enabled RAK1903")
// Functions
bool init_rak1903(void);
void read_rak1903();
#endif // _RAK1903_LIGHT_H_

// RAK1904
#ifdef _RAK1904_ACC_H_
#pragma message("Enabled RAK1904")
// Functions
bool rak1904_writeRegister(uint8_t chip_reg, uint8_t dataToWrite);
bool rak1904_readRegister(uint8_t *outputPointer, uint8_t chip_reg);
bool init_rak1904(void);
void read_rak1904(void);
void int_assign_rak1904(uint8_t new_irq_pin);
void int_callback_rak1904(void);
void clear_int_rak1904(void);
bool handle_rak1904_int(void);
#ifdef _RAK12500_GNSS_H_
extern uint8_t gnss_format;
extern bool gnss_active;
#endif // _RAK12500_GNSS_H_
#endif // _RAK1904_ACC_H_

// RAK1905
#ifdef _RAK1905_9DOF_H_
#pragma message("Enabled RAK1905")
// Functions
bool init_rak1905(void);
void read_rak1905(void);
void int_assign_rak1905(uint8_t new_irq_pin);
void int_callback_rak1905(void);
void clear_int_rak1905(void);
#endif // _RAK1905_9DOF_H_

// RAK1906
#ifdef _RAK1906_ENV_H_
#pragma message("Enabled RAK1906")
// Functions
bool init_rak1906(void);
void start_rak1906(void);
bool read_rak1906(void);
uint16_t get_alt_rak1906(void);
// Globals
extern float mean_sea_level_press;
#endif // _RAK1906_ENV_H_

// RAK1921
#ifdef _RAK1921_DISPLAY_H_
#pragma message("Enabled RAK1921")
// Functions
bool init_rak1921(void);
void rak1921_add_line(char *line);
void rak1921_show(void);
void rak1921_write_header(char *header_line);
// Definitions
/** Width of the display in pixel */
#define OLED_WIDTH 128
/** Height of the display in pixel */
#define OLED_HEIGHT 64
/** Height of the status bar in pixel */
#define STATUS_BAR_HEIGHT 11
/** Height of a single line */
#define LINE_HEIGHT 10
/** Number of message lines */
#define NUM_OF_LINES (OLED_HEIGHT - STATUS_BAR_HEIGHT) / LINE_HEIGHT
#endif // _RAK1921_DISPLAY_H_

// RAK12002
#ifdef _RAK12002_RTC_H_
#pragma message("Enabled RAK12002")
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

// RAK12003
#ifdef _RAK12003_FIR_H_
#pragma message("Enabled RAK12003")
// Functions
bool init_rak12003(void);
void read_rak12003(void);
#endif // _RAK12003_FIR_H_

// RAK12010
#ifdef _RAK12010_LIGHT_H_
#pragma message("Enabled RAK12010")
// Functions
bool init_rak12010(void);
void read_rak12010(void);
#endif // _RAK12010_LIGHT_H_

// RA12014
#ifdef _RAK12014_TOF_H_
#pragma message("Enabled RAK12014")
// Functions
bool init_rak12014(void);
void read_rak12014(void);
#endif // _RAK12014_TOF_H_

// RAK12019
#ifdef _RAK12019_UV_H_
#pragma message("Enabled RAK12019")
// Functions
bool init_rak12019(void);
void read_rak12019(void);
#endif // _RAK12019_UV_H_

// RAK12027
#ifdef _RAK12027_SEISMIC_H_
#pragma message("Enabled RAK12027")
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

// RAK12037
#ifdef _RAK12037_CO2_H_
#pragma message("Enabled RAK12037")
// Functions
bool init_rak12037(void);
void read_rak12037(void);
#endif // _RAK12037_CO2_H_

// RAK12039
#ifdef _RAK12039_PM_H_
#pragma message("Enabled RAK12039")
// Functions
bool init_rak12039(void);
void read_rak12039(void);
#define SET_PIN WB_IO6
#endif // _RAK12039_PM_H_

// RAK12040
#ifdef _RAK12040_TEMP_ARR_H_
#pragma message("Enabled RAK12040")
// Functions
bool init_rak12040(void);
void read_rak12040(void);
/** HOT value (in degrees C) to adjust the contrast */
#define HOT 30.0
/** COLD value (in degrees C) to adjust the contrast */
#define COLD 25.0
#endif // _RAK12040_TEMP_ARR_H_

// RAK12047
#ifdef _RAK12047_VOC_H_
#pragma message("Enabled RAK12047")
// Functions
bool init_rak12047(void);
void read_rak12047(void);
void do_read_rak12047(void *);
#endif // _RAK12047_VOC_H_

// RAK12500
#ifdef _RAK12500_GNSS_H_
#pragma message("Enabled RAK12500")
#if defined(_VARIANT_RAK3172_) || defined(_VARIANT_RAK3172_SIP_)
#pragma warning("RAK12500 is not supported by RAK3172")
#endif
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

// RAK13011
#ifdef _RAK13011_SWITCH_H_
#pragma message("Enabled RAK13011")
// Functions
bool init_rak13011(void);
void handle_rak13011(void *);
#define LPP_CHANNEL_SWITCH 48 // RAK13011
#endif // _RAK13011_SWITCH_H_