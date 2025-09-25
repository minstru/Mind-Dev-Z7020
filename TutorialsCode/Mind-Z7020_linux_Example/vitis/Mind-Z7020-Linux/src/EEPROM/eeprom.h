/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#ifndef EEPROM_H
#define EEPROM_H

#include <stdbool.h>

// EEPROM I2C address
#define EEPROM_ADDR 0x50

/*i2c_dev I2C device address("/dev/i2c-0")*/
int eeprom_init(const char *i2c_dev);

bool eeprom_write(int fd, unsigned short addr, const unsigned char *data, unsigned int len);

bool eeprom_read(int fd, unsigned short addr, unsigned char *data, unsigned int len);

void eeprom_close(int fd);

#endif // EEPROM_H
