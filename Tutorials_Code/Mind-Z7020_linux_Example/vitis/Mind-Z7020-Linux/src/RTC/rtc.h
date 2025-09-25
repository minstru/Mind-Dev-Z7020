/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */


#ifndef _PCF85063_H_
#define _PCF85063_H_

#include <stdint.h>  // define uint16_t
#include <stdbool.h> // define bool

typedef struct
{
    uint16_t year;
    uint16_t month;
    uint16_t day;
    uint16_t weekday;
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
}stDateTime;

int open_rtc_dev(const char *i2c_dev);
bool read_rtc(int fd, stDateTime *dt);
bool set_rtc(int fd, const stDateTime *dt);
void close_rtc_dev(int fd);

#endif // _PCF85063_H_
