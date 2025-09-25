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


#define IIC_DEVICE_ID          XPAR_XIICPS_0_DEVICE_ID
#define IIC_SCLK_RATE          100000   // I2C clock rate

u8 buffer[20];
XIicPs Iic;

int i2c_init(void);
extern void PCF8563_Test(void);
extern void PCF85063_Test(void);


int main(void) 
{
    int Status;

    Xil_ExceptionInit();

    Status = i2c_init();
    if (Status != XST_SUCCESS) {
        xil_printf("I2C initialization failed\r\n");
        return;
    }

    xil_printf("I2C initialized successfully\r\n");
    PCF8563_Test();
    //PCF85063_Test();
    return 0;
}


// BCD to Decimal conversion
u8 BCD_to_Decimal(u8 bcd) 
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

// Decimal to BCD conversion
u8 Decimal_to_BCD(u8 decimal) 
{
    return ((decimal / 10) << 4) | (decimal % 10);
}


// initialize I2C controller
int i2c_init(void) 
{
    XIicPs_Config *Config;
    int Status;

    // find I2C configuration
    Config = XIicPs_LookupConfig(IIC_DEVICE_ID);
    if (NULL == Config) {
        return XST_FAILURE;
    }

    // initialize I2C device
    Status = XIicPs_CfgInitialize(&Iic, Config, Config->BaseAddress);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    // self-test
    Status = XIicPs_SelfTest(&Iic);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    // set I2C clock frequency
    XIicPs_SetSClk(&Iic, IIC_SCLK_RATE);

    return XST_SUCCESS;
}
