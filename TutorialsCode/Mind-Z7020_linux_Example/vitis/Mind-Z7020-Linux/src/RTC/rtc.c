/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

// pcf85063.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <stdbool.h>
#include"rtc.h"

#define PCF85063_SLAVE_ADDR     0x51    // 7bit

// registers addr
#define PCF85063_REG_CONTROL1         (0x00)
#define PCF85063_REG_CONTROL2         (0x01)
#define PCF85063_REG_OFFSET           (0x02)
#define PCF85063_REG_RAM_BYTE         (0x03)
#define PCF85063_REG_SECONDS          (0x04)
#define PCF85063_REG_MINUTES          (0x05)
#define PCF85063_REG_HOURS            (0x06)
#define PCF85063_REG_DAYS             (0x07)
#define PCF85063_REG_WEEKDAYS         (0x08)
#define PCF85063_REG_MONTHS           (0x09)
#define PCF85063_REG_YEARS            (0x0A)
#define PCF85063_REG_SECOND_ALARM     (0x0B)
#define PCF85063_REG_MINUTE_ALARM     (0x0C)
#define PCF85063_REG_HOUR_ALARM       (0x0D)
#define PCF85063_REG_DAY_ALARM        (0x0E)
#define PCF85063_REG_WEEKDAY_ALARM    (0x0F)
#define PCF85063_REG_TIMER_VALUE      (0x10)
#define PCF85063_REG_TIMER_MODE       (0x11)


// PCF8563 I2C slave address 
#define PCF8563_DEVICE_ADDR    0x51

// PCF8563 register addresses
#define PCF8563_REG_CONTROL_STATUS1  0x00
#define PCF8563_REG_CONTROL_STATUS2  0x01
#define PCF8563_REG_VL_SEC           0x02
#define PCF8563_REG_MINUTE           0x03
#define PCF8563_REG_HOUR             0x04
#define PCF8563_REG_DAY              0x05
#define PCF8563_REG_WEEKDAY          0x06
#define PCF8563_REG_MONTH            0x07
#define PCF8563_REG_YEAR             0x08
#define PCF8563_REG_ALARM_MINUTE     0x09
#define PCF8563_REG_ALARM_HOUR       0x0A
#define PCF8563_REG_ALARM_DAY        0x0B
#define PCF8563_REG_ALARM_WEEKDAY    0x0C
#define PCF8563_REG_CLKOUT_CONTROL   0x0D
#define PCF8563_REG_TIMER_CONTROL    0x0E
#define PCF8563_REG_TIMER            0x0F


#define USE_PCF8563     // use PCF8563 RTC or PCF85063 RTC

unsigned char dec2bcd(int dec) {
    return ((dec / 10) << 4) | (dec % 10);
}


uint8_t bcd2dec(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}


int open_rtc_dev(const char *i2c_dev)
{
    uint8_t buf[2];  // Register address + 1 data byte
    uint8_t slave_addr = PCF85063_SLAVE_ADDR; // Default slave address for PCF85063
    int fd = open(i2c_dev, O_RDWR);
    if (fd < 0) {
        perror("Failed to open I2C bus");
        return -1;
    }

#ifdef USE_PCF8563
    slave_addr = PCF8563_DEVICE_ADDR; // Use PCF8563 address if defined
#endif

    if (ioctl(fd, I2C_SLAVE, slave_addr) < 0) {
        perror("Failed to set I2C address");
        close(fd);
        return -1;
    }

    unsigned char reg = 0x04;
    if (fd < 0) {
        return false;
    }

#ifdef USE_PCF8563
    // reset PCF8563
    buf[0] = PCF8563_REG_CONTROL_STATUS1;
    buf[1] = 0x00;
    if (write(fd, buf, sizeof(buf)) != sizeof(buf)) {
        perror("set_rtc write failed");
        return false;
    }

    // disable PCF8563 alarm
    buf[0] = PCF8563_REG_CONTROL_STATUS2;
    buf[1] = 0x00;
    if (write(fd, buf, sizeof(buf)) != sizeof(buf)) {
        perror("set_rtc write failed");
        return false;
    }

    // Disable clock output
    buf[0] = PCF8563_REG_CLKOUT_CONTROL;
    buf[1] = 0x80;
    if (write(fd, buf, sizeof(buf)) != sizeof(buf)) {
        perror("set_rtc write failed");
        return false;
    }

    // disable timer
    buf[0] = PCF8563_REG_TIMER_CONTROL;
    buf[1] = 0x00;
    if (write(fd, buf, sizeof(buf)) != sizeof(buf)) {
        perror("set_rtc write failed");
        return false;
    }
#else
    // reset PCF85063
    buf[0] = PCF85063_REG_CONTROL1;
    buf[1] = 0x00;
    if (write(fd, buf, sizeof(buf)) != sizeof(buf)) {
        perror("set_rtc write failed");
        return false;
    }

    // Disable the alarm function and timer interrupt
    buf[0] = PCF85063_REG_CONTROL2;
    buf[1] = 0x00;
    if (write(fd, buf, sizeof(buf)) != sizeof(buf)) {
        perror("set_rtc write failed");
        return false;
    }

    // Disable clock output
    buf[0] = PCF85063_REG_TIMER_MODE;
    buf[1] = 0x00;
    if (write(fd, buf, sizeof(buf)) != sizeof(buf)) {
        perror("set_rtc write failed");
        return false;
    }
#endif

    return fd;
}

bool read_rtc(int fd, stDateTime *dt)
{
    unsigned char reg = PCF85063_REG_SECONDS; // read from second register
    unsigned char data[7];

    if (fd < 0 || dt == NULL) {
        return false;
    }

#ifdef USE_PCF8563
    reg = PCF8563_REG_VL_SEC; // read from second register for PCF8563
#endif

    // Set read start address (write 0x04)
    if (write(fd, &reg, 1) != 1) {
        perror("set read register failed");
        return false;
    }

    // Read 7 bytes
    if (read(fd, data, 7) != 7) {
        perror("read rtc failed");
        return false;
    }

    dt->second  = bcd2dec(data[0] & 0x7F);
    dt->minute  = bcd2dec(data[1] & 0x7F);
    dt->hour    = bcd2dec(data[2] & 0x3F);
    dt->day     = bcd2dec(data[3] & 0x3F);
    dt->weekday = bcd2dec(data[4] & 0x07);
    dt->month   = bcd2dec(data[5] & 0x1F);
    dt->year    = bcd2dec(data[6]);

    return true;
}

bool set_rtc(int fd, const stDateTime *dt)
{
    unsigned char reg = PCF85063_REG_SECONDS;
    if (fd < 0) {
        return false;
    }

#ifdef USE_PCF8563
    reg = PCF8563_REG_VL_SEC; // read from second register for PCF8563
#endif

    // Create a data buffer for writing
    uint8_t buf[8];  // Register header (1 byte) + 7-byte data field
    buf[0] = reg;    // Starting register address for write
    buf[1] = dec2bcd(dt->second);
    buf[2] = dec2bcd(dt->minute);
    buf[3] = dec2bcd(dt->hour);
    buf[4] = dec2bcd(dt->day);
    buf[5] = dec2bcd(dt->weekday);
    buf[6] = dec2bcd(dt->month);
    buf[7] = dec2bcd(dt->year % 100);

    // Write all data at once
    if (write(fd, buf, sizeof(buf)) != sizeof(buf)) {
        perror("set_rtc write failed");
        return false;
    }

    return true;
}

void close_rtc_dev(int fd)
{
    if (fd >= 0) {
        close(fd);  // Close the incoming file descriptor
    }
}
