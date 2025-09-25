/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include "sensor.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

// init shtc3 sensor device
int shtc3_init(const char *i2c_dev) {
    int fd = open(i2c_dev, O_RDWR);
    if (fd < 0) {
        perror("Failed to open I2C bus");
        return -1;
    }

    if (ioctl(fd, I2C_SLAVE, SHTC3_ADDR) < 0) {
        perror("Failed to open SHTC3 device");
        close(fd);
        return -1;
    }

    return fd;
}

// Read data from SHTC3 sensor
bool shtc3_read_data(int fd, shtc3_data_t *data) {
    unsigned char cmd[2];
    unsigned char sensor_data[6];

    if (fd < 0 || data == NULL) {
        return false;
    }

    // Wake up sensor
    cmd[0] = (CMD_WAKEUP >> 8) & 0xFF;
    cmd[1] = CMD_WAKEUP & 0xFF;
    if (write(fd, cmd, 2) != 2) {
        perror("SHTC3 wakeup failed");
        return false;
    }
    usleep(1000);

    // Send measurement command
    cmd[0] = (CMD_MEASURE >> 8) & 0xFF;
    cmd[1] = CMD_MEASURE & 0xFF;
    if (write(fd, cmd, 2) != 2) {
        perror("SHTC3 measure command failed");
        return false;
    }
    usleep(20000);

    // Read 6 bytes of data
    if (read(fd, sensor_data, 6) != 6) {
        perror("Failed to read SHTC3 data");
        return false;
    }

    // Convert raw data
    uint16_t raw_temp = (sensor_data[0] << 8) | sensor_data[1];
    uint16_t raw_hum = (sensor_data[3] << 8) | sensor_data[4];

    // Calculate temperature and humidity
    data->temperature = -45 + 175 * ((float)raw_temp / 65535.0);
    data->humidity = 100 * ((float)raw_hum / 65535.0);

    return true;
}

// Close SHTC3 sensor device
void shtc3_close(int fd) {
    if (fd >= 0) {
        unsigned char cmd[2];
        
        // Send sleep command
        cmd[0] = (CMD_SLEEP >> 8) & 0xFF;
        cmd[1] = CMD_SLEEP & 0xFF;
        write(fd, cmd, 2);
        
        close(fd);
    }
}
