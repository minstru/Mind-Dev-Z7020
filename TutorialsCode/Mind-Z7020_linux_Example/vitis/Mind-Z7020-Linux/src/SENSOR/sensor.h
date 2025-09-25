/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#ifndef _SHTC3_H_
#define _SHTC3_H_

#include <stdint.h>
#include <stdbool.h>

// SHTC3 I2C address
#define SHTC3_ADDR 0x70


#define CMD_WAKEUP  0x3517
#define CMD_MEASURE 0x7866
#define CMD_SLEEP   0xB098


typedef struct {
    float temperature;
    float humidity;
} shtc3_data_t;


int shtc3_init(const char *i2c_dev);


bool shtc3_read_data(int fd, shtc3_data_t *data);


void shtc3_close(int fd);

#endif // _SHTC3_H_
