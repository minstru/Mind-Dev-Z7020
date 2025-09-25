/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include "xparameters.h"
#include "xiicps.h"
#include "sleep.h"
#include <stdio.h>

#define SHTC3_ADDR               0x70  // 7-bit I2C address
#define SHTC3_READ_ID_CMD        0xEFC8
#define SHTC3_WAKEUP_CMD         0x3517
#define SHTC3_SLEEP_CMD          0xB098
#define SHTC3_SOFT_RESET_CMD     0x805D
#define SHTC3_MEASURE_CMD        0x7866  // Normal mode, clock stretching disabled
#define SHTC3_ID_MASK            0x083F  // ID mask for SHTC3

XIicPs IicInstance;

// write command to SHTC3 sensor
int SHTC3_WriteCmd(uint16_t cmd) {
    uint8_t buf[2];
    buf[0] = (cmd >> 8) & 0xFF;
    buf[1] = cmd & 0xFF;

    int status = XIicPs_MasterSendPolled(&IicInstance, buf, 2, SHTC3_ADDR);
    usleep(1000);
    return status;
}

// read data from SHTC3 sensor
int SHTC3_ReadData(uint8_t *data, uint8_t len) {
    return XIicPs_MasterRecvPolled(&IicInstance, data, len, SHTC3_ADDR);
}

// calculate CRC8 for SHTC3 data
uint8_t SHTC3_CRC8(uint8_t *data) {
    uint8_t crc = 0xFF;
    for (int i = 0; i < 2; ++i) {
        crc ^= data[i];
        for (int j = 0; j < 8; ++j) {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x31;
            else
                crc <<= 1;
        }
    }
    return crc;
}

// verify SHTC3 ID
// Returns XST_SUCCESS if ID matches, otherwise XST_FAILURE
int SHTC3_VerifyID(uint16_t *id) {
    uint8_t id_data[3];

    SHTC3_WriteCmd(SHTC3_READ_ID_CMD);
    usleep(1000);

    if (SHTC3_ReadData(id_data, 3) != XST_SUCCESS) {
        printf("ID read failed!\r\n");
        return XST_FAILURE;
    }

    if (SHTC3_CRC8(id_data) != id_data[2]) {
        printf("ID CRC error!\r\n");
        return XST_FAILURE;
    }

    uint16_t val = ((uint16_t)id_data[0] << 8) | id_data[1];
    *id = val & SHTC3_ID_MASK;

    // the id of SHTC3 is 0x0807
    if (*id != 0x0807) {
        printf("Invalid SHTC3 ID: 0x%04X\r\n", *id);
        return XST_FAILURE;
    }

    return XST_SUCCESS;
}

void SHTC3_Test() {
    uint8_t raw_data[6];
    uint16_t raw_temp, raw_hum;
    float temp_c, hum_rh;
    uint16_t chip_id;

    printf("\r\n----- SHTC3 Test Start -----\r\n");

    // 1. wake up the SHTC3 sensor
    SHTC3_WriteCmd(SHTC3_WAKEUP_CMD);
    usleep(1000);

    // 2. verify chip ID
    if (SHTC3_VerifyID(&chip_id) != XST_SUCCESS) {
        printf("SHTC3 ID verification failed!\r\n");
        return;
    }
    printf("SHTC3 ID Verified: 0x%04X\r\n", chip_id);

    // 3. soft reset command
    SHTC3_WriteCmd(SHTC3_SOFT_RESET_CMD);
    usleep(10000);

    // 4. measurement command
    SHTC3_WriteCmd(SHTC3_MEASURE_CMD);
    usleep(20000);  // wait for measurement to complete

    // 5. read data
    if (SHTC3_ReadData(raw_data, 6) != XST_SUCCESS) {
        printf("I2C read error.\r\n");
        return;
    }

    // 6. CRC check
    if (SHTC3_CRC8(&raw_data[0]) != raw_data[2]) {
        printf("Temperature CRC error.\r\n");
        return;
    }
    if (SHTC3_CRC8(&raw_data[3]) != raw_data[5]) {
        printf("Humidity CRC error.\r\n");
        return;
    }

    // 7. Data conversion
    raw_temp = ((uint16_t)raw_data[0] << 8) | raw_data[1];
    raw_hum  = ((uint16_t)raw_data[3] << 8) | raw_data[4];
    temp_c = -45 + 175 * ((float)raw_temp / 65535.0f);
    hum_rh = 100 * ((float)raw_hum / 65535.0f);

    // 8. Print results
    printf("Temperature: %.2f \xE2\x84\x83\r\n", temp_c);
    printf("Humidity   : %.2f %%RH\r\n", hum_rh);

    // 9. Enter sleep mode
    SHTC3_WriteCmd(SHTC3_SLEEP_CMD);
    printf("----- Test Complete -----\r\n");
}

int I2C_Init(u16 DeviceId) {
    XIicPs_Config *Config;
    int status;

    Config = XIicPs_LookupConfig(DeviceId);
    if (NULL == Config) {
        return XST_FAILURE;
    }

    status = XIicPs_CfgInitialize(&IicInstance, Config, Config->BaseAddress);
    if (status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    XIicPs_SetSClk(&IicInstance, 100000);  // 100kHz
    return XST_SUCCESS;
}

int main() {
    int status;

    status = I2C_Init(XPAR_XIICPS_0_DEVICE_ID);
    if (status != XST_SUCCESS) {
        printf("I2C init failed!\r\n");
        return -1;
    }

    while (1) {
        SHTC3_Test();
        sleep(1);
    }

    return 0;
}
