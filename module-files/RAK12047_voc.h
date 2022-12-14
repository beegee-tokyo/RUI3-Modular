/**
 * @file RAK12047_voc.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Functions and definitions for RAK12047
 * @version 0.1
 * @date 2022-10-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _RAK12047_VOC_H_
#define _RAK12047_VOC_H_
#include <Arduino.h>

// Functions
bool init_rak12047(void);
void read_rak12047(void);
void do_read_rak12047(void *);

#endif // _RAK12047_VOC_H_