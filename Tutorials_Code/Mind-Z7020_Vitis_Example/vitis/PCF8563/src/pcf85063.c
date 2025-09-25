/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include "xparameters.h"
#include "xiicps.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "xil_exception.h"
#include "sleep.h"
#include"stdbool.h"

// PCF85063 I2C slave address (default is 0x51)
#define PCF85063_DEVICE_ADDR    0x51

// PCF85063 register addresses
#define PCF85063_REG_CONTROL1         0x00
#define PCF85063_REG_CONTROL2         0x01
#define PCF85063_REG_OFFSET           0x02
#define PCF85063_REG_RAM_BYTE         0x03
#define PCF85063_REG_SECONDS          0x04
#define PCF85063_REG_MINUTES          0x05
#define PCF85063_REG_HOURS            0x06
#define PCF85063_REG_DAYS             0x07
#define PCF85063_REG_WEEKDAYS         0x08
#define PCF85063_REG_MONTHS           0x09
#define PCF85063_REG_YEARS            0x0A
#define PCF85063_REG_SECOND_ALARM     0x0B
#define PCF85063_REG_MINUTE_ALARM     0x0C
#define PCF85063_REG_HOUR_ALARM       0x0D
#define PCF85063_REG_DAY_ALARM        0x0E
#define PCF85063_REG_WEEKDAY_ALARM    0x0F
#define PCF85063_REG_TIMER_VALUE      0x10
#define PCF85063_REG_TIMER_MODE       0x11


extern u8 buffer[20];
extern XIicPs Iic;
extern u8 BCD_to_Decimal(u8 bcd);
extern u8 Decimal_to_BCD(u8 decimal);


// write a byte to PCF85063
int PCF85063_WriteByte(u8 reg_addr, u8 data) {
    buffer[0] = reg_addr;
    buffer[1] = data;

    return XIicPs_MasterSendPolled(&Iic, buffer, 2, PCF85063_DEVICE_ADDR);
}

// read a byte from PCF85063
int PCF85063_ReadByte(u8 reg_addr, u8 *data) {
    int Status;

    buffer[0] = reg_addr;

    // send register address
    Status = XIicPs_MasterSendPolled(&Iic, buffer, 1, PCF85063_DEVICE_ADDR);
    if (Status != XST_SUCCESS) {
        return Status;
    }

    // receive data
    Status = XIicPs_MasterRecvPolled(&Iic, data, 1, PCF85063_DEVICE_ADDR);

    return Status;
}


// initialize PCF85063
int PCF85063_Init(void) {
    int Status;

    // reset PCF85063 (set CAP_SEL bit for 12.5pF load capacitance)
    Status = PCF85063_WriteByte(PCF85063_REG_CONTROL1, 0x00);
    if (Status != XST_SUCCESS) {
        return Status;
    }

    // disable alarm
    Status = PCF85063_WriteByte(PCF85063_REG_CONTROL2, 0x00);
    if (Status != XST_SUCCESS) {
        return Status;
    }

    // disable clock output
    Status = PCF85063_WriteByte(PCF85063_REG_TIMER_MODE, 0x00);
    if (Status != XST_SUCCESS) {
        return Status;
    }

    return XST_SUCCESS;
}

// set PCF85063 time
int PCF85063_SetTime(u8 year, u8 month, u8 day, u8 weekday, u8 hour, u8 minute, u8 second) {
    int Status;

    Status = PCF85063_WriteByte(PCF85063_REG_YEARS, Decimal_to_BCD(year));
    if (Status != XST_SUCCESS) return Status;

    Status = PCF85063_WriteByte(PCF85063_REG_MONTHS, Decimal_to_BCD(month));
    if (Status != XST_SUCCESS) return Status;

    Status = PCF85063_WriteByte(PCF85063_REG_DAYS, Decimal_to_BCD(day));
    if (Status != XST_SUCCESS) return Status;

    Status = PCF85063_WriteByte(PCF85063_REG_WEEKDAYS, Decimal_to_BCD(weekday));
    if (Status != XST_SUCCESS) return Status;

    Status = PCF85063_WriteByte(PCF85063_REG_HOURS, Decimal_to_BCD(hour));
    if (Status != XST_SUCCESS) return Status;

    Status = PCF85063_WriteByte(PCF85063_REG_MINUTES, Decimal_to_BCD(minute));
    if (Status != XST_SUCCESS) return Status;

    // clear the VL bit in seconds register
    Status = PCF85063_WriteByte(PCF85063_REG_SECONDS, Decimal_to_BCD(second) & 0x7F);
    if (Status != XST_SUCCESS) return Status;

    return XST_SUCCESS;
}

// read PCF85063 time
int PCF85063_ReadTime(u8 *year, u8 *month, u8 *day, u8 *weekday, u8 *hour, u8 *minute, u8 *second) {
    int Status;
    u8 data[7];

    // read time data
    buffer[0] = PCF85063_REG_SECONDS;
    Status = XIicPs_MasterSendPolled(&Iic, buffer, 1, PCF85063_DEVICE_ADDR);
    if (Status != XST_SUCCESS) return Status;

    Status = XIicPs_MasterRecvPolled(&Iic, data, 7, PCF85063_DEVICE_ADDR);
    if (Status != XST_SUCCESS) return Status;

    // convert BCD format to decimal
    *second = BCD_to_Decimal(data[0] & 0x7F);  // clear VL bit
    *minute = BCD_to_Decimal(data[1] & 0x7F);
    *hour = BCD_to_Decimal(data[2] & 0x3F);
    *day = BCD_to_Decimal(data[3] & 0x3F);
    *weekday = BCD_to_Decimal(data[4] & 0x07);
    *month = BCD_to_Decimal(data[5] & 0x1F);
    *year = BCD_to_Decimal(data[6]);

    return XST_SUCCESS;
}

void PCF85063_Test(void) {
    int Status;
    u8 year, month, day, weekday, hour, minute, second;

    xil_printf("\r\n=======================================\r\n");
    xil_printf("PCF85063 RTC Test\r\n");
    xil_printf("=======================================\r\n");

    // initialize PCF85063
    Status = PCF85063_Init();
    if (Status != XST_SUCCESS) {
        xil_printf("PCF85063 initialization failed\r\n");
        return;
    }

    xil_printf("PCF85063 initialized successfully\r\n");

    // set time to 2023-10-01 Sunday 12:00:00
    Status = PCF85063_SetTime(23, 10, 1, 0, 12, 0, 0);
    if (Status != XST_SUCCESS) {
        xil_printf("Failed to set time\r\n");
        return;
    }

    xil_printf("Time set to 2023-10-01 12:00:00\r\n");
    xil_printf("Starting time read test...\r\n");

    // read time 10 times, each interval 1 second
    for (int i = 0; i < 10; i++) {
        Status = PCF85063_ReadTime(&year, &month, &day, &weekday, &hour, &minute, &second);

        if (Status != XST_SUCCESS) {
            xil_printf("Failed to read time\r\n");
            return;
        }

        xil_printf("Time %d: 20%02d-%02d-%02d %02d:%02d:%02d\r\n",
            i+1, year, month, day, hour, minute, second);

        sleep(1);
    }

    xil_printf("PCF85063 test completed successfully\r\n");
    xil_printf("=======================================\r\n");
}









