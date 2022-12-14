/**
 * @file RAK1921_display.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Includes and defines for RAK1921
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _RAK1921_DISPLAY_H_
#define _RAK1921_DISPLAY_H_
#include <Arduino.h>

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