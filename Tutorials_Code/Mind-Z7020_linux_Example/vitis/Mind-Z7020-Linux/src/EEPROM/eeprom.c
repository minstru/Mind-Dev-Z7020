/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include "eeprom.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

// init EEPROM device
int eeprom_init(const char *i2c_dev) {
    int fd = open(i2c_dev, O_RDWR);
    if (fd < 0) {
        perror("Failed to open I2C bus");
        return -1;
    }

    if (ioctl(fd, I2C_SLAVE, EEPROM_ADDR) < 0) {
        perror("Failed to set I2C address");
        close(fd);
        return -1;
    }

    return fd;
}

// Write data to EEPROM
bool eeprom_write(int fd, unsigned short addr, const unsigned char *data, unsigned int len) {
    if (fd < 0 || data == NULL || len == 0) {
        return false;
    }

    // Create a data buffer for writing
    unsigned char *buf = malloc(len + 2);
    if (buf == NULL) {
        perror("Memory allocation failed");
        return false;
    }

    // Set address (16-bit)
    buf[0] = (addr >> 8) & 0xFF;  // High byte
    buf[1] = addr & 0xFF;         // Low byte

    // copy data
    memcpy(buf + 2, data, len);

    // write data
    if (write(fd, buf, len + 2) != (len + 2)) {
        perror("EEPROM write failed");
        free(buf);
        return false;
    }

    free(buf);
    usleep(10000); // Wait for write completion
    return true;
}

// Read data from EEPROM
bool eeprom_read(int fd, unsigned short addr, unsigned char *data, unsigned int len) {
    if (fd < 0 || data == NULL || len == 0) {
        return false;
    }

    // Set read address (16-bit)
    unsigned char addr_buf[2];
    addr_buf[0] = (addr >> 8) & 0xFF;  // High byte
    addr_buf[1] = addr & 0xFF;         // Low byte

    if (write(fd, addr_buf, 2) != 2) {
        perror("EEPROM set read address failed");
        return false;
    }

    // read data
    if (read(fd, data, len) != len) {
        perror("EEPROM read failed");
        return false;
    }

    return true;
}

// Close EEPROM device
void eeprom_close(int fd) {
    if (fd >= 0) {
        close(fd);
    }
}
