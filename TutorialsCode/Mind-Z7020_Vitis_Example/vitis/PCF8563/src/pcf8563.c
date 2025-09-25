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

// PCF8563 I2C slave address (default is 0x50)
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

extern u8 buffer[20];
extern XIicPs Iic;
extern u8 BCD_to_Decimal(u8 bcd);
extern u8 Decimal_to_BCD(u8 decimal);



// write a byte to PCF8563
int PCF8563_WriteByte(u8 reg_addr, u8 data) 
{
    buffer[0] = reg_addr;
    buffer[1] = data;

    return XIicPs_MasterSendPolled(&Iic, buffer, 2, PCF8563_DEVICE_ADDR);
}

// read a byte from PCF8563
int PCF8563_ReadByte(u8 reg_addr, u8 *data) 
{
    int Status;

    buffer[0] = reg_addr;

    // send register address
    Status = XIicPs_MasterSendPolled(&Iic, buffer, 1, PCF8563_DEVICE_ADDR);
    if (Status != XST_SUCCESS) {
        return Status;
    }

    // receive data
    Status = XIicPs_MasterRecvPolled(&Iic, data, 1, PCF8563_DEVICE_ADDR);

    return Status;
}

// initialize PCF8563
int PCF8563_Init(void) 
{
    int Status;

    // reset PCF8563
    Status = PCF8563_WriteByte(PCF8563_REG_CONTROL_STATUS1, 0x00);
    if (Status != XST_SUCCESS) {
        return Status;
    }

    // disable PCF8563 alarm
    Status = PCF8563_WriteByte(PCF8563_REG_CONTROL_STATUS2, 0x00);
    if (Status != XST_SUCCESS) {
        return Status;
    }

    // disable clock output
    Status = PCF8563_WriteByte(PCF8563_REG_CLKOUT_CONTROL, 0x80);
    if (Status != XST_SUCCESS) {
        return Status;
    }

    // disable timer
    Status = PCF8563_WriteByte(PCF8563_REG_TIMER_CONTROL, 0x00);
    if (Status != XST_SUCCESS) {
        return Status;
    }

    return XST_SUCCESS;
}

// set PCF8563 time
int PCF8563_SetTime(u8 year, u8 month, u8 day, u8 weekday, u8 hour, u8 minute, u8 second) 
{
    int Status;

    Status = PCF8563_WriteByte(PCF8563_REG_YEAR, Decimal_to_BCD(year));
    if (Status != XST_SUCCESS) return Status;

    Status = PCF8563_WriteByte(PCF8563_REG_MONTH, Decimal_to_BCD(month));
    if (Status != XST_SUCCESS) return Status;

    Status = PCF8563_WriteByte(PCF8563_REG_DAY, Decimal_to_BCD(day));
    if (Status != XST_SUCCESS) return Status;

    Status = PCF8563_WriteByte(PCF8563_REG_WEEKDAY, Decimal_to_BCD(weekday));
    if (Status != XST_SUCCESS) return Status;

    Status = PCF8563_WriteByte(PCF8563_REG_HOUR, Decimal_to_BCD(hour));
    if (Status != XST_SUCCESS) return Status;

    Status = PCF8563_WriteByte(PCF8563_REG_MINUTE, Decimal_to_BCD(minute));
    if (Status != XST_SUCCESS) return Status;

    // clear the VL bit in seconds register
    Status = PCF8563_WriteByte(PCF8563_REG_VL_SEC, Decimal_to_BCD(second) & 0x7F);
    if (Status != XST_SUCCESS) return Status;

    return XST_SUCCESS;
}

// read PCF8563 time
int PCF8563_ReadTime(u8 *year, u8 *month, u8 *day, u8 *weekday, u8 *hour, u8 *minute, u8 *second) 
{
    int Status;
    u8 data[7];

    // read time data
    buffer[0] = PCF8563_REG_VL_SEC;
    Status = XIicPs_MasterSendPolled(&Iic, buffer, 1, PCF8563_DEVICE_ADDR);
    if (Status != XST_SUCCESS) return Status;

    Status = XIicPs_MasterRecvPolled(&Iic, data, 7, PCF8563_DEVICE_ADDR);
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

void PCF8563_Test(void) 
{
    int Status;
    u8 year, month, day, weekday, hour, minute, second;

    xil_printf("\r\n=======================================\r\n");
    xil_printf("PCF8563 RTC Test\r\n");
    xil_printf("=======================================\r\n");

    // initialize PCF8563
    Status = PCF8563_Init();
    if (Status != XST_SUCCESS) {
        xil_printf("PCF8563 initialization failed\r\n");
        return;
    }

    xil_printf("PCF8563 initialized successfully\r\n");

    // set time to 2023-10-01 Sunday 12:00:00
    Status = PCF8563_SetTime(23, 10, 1, 0, 12, 0, 0);
    if (Status != XST_SUCCESS) {
        xil_printf("Failed to set time\r\n");
        return;
    }

    xil_printf("Time set to 2023-10-01 12:00:00\r\n");
    xil_printf("Starting time read test...\r\n");

    // read time 10 times, each interval 1 second
    for (int i = 0; i < 10; i++) {
        Status = PCF8563_ReadTime(&year, &month, &day, &weekday, &hour, &minute, &second);
        if (Status != XST_SUCCESS) {
            xil_printf("Failed to read time\r\n");
            return;
        }

        xil_printf("Time %d: 20%02d-%02d-%02d %02d:%02d:%02d\r\n",
                    i+1, year, month, day, hour, minute, second);

        sleep(1);
    }

    xil_printf("PCF8563 test completed successfully\r\n");
    xil_printf("=======================================\r\n");
}


