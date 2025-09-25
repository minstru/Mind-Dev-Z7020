/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */


#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <stdint.h>
#include <stdbool.h>

#include <termios.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

int32_t open_serial(char *dev, int32_t speed, int32_t databits, int32_t stopbits, int32_t parity);
int32_t read_serial(int32_t fd, uint8_t *buf, int32_t size);
int32_t write_serial(int32_t fd, const uint8_t *buf, int32_t size);
void flush_serial(int32_t fd);
int32_t close_serial(int32_t fd);

#ifdef __cplusplus
}
#endif

#endif /* _SERIALH_ */
