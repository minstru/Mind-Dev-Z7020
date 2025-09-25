/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include "FreeRTOS.h"
#include "task.h"

#include "touch/gt911.h"
#include "xgpiops.h"
#include "xiicps.h"

#define LCD_BLK     (58)
#define TP_RESET    (59)
#define TP_INT      (60)

#define GT911_SLAVE_ADDR        (0xBA >> 1)  // 7-bit address
// #define GT911_SLAVE_ADDR        (0x28 >> 1)  // 7-bit address

#define GT911_CFG_START_ADDR   0x8047
#define GT911_PRODUCT_ID_ADDR  0x8140
#define GT911_STATUS_ADDR      0x814E
#define GT911_POINT_DATA_ADDR  0x814F

#define GT911_I2C_DEV_ID        XPAR_XIICPS_1_DEVICE_ID
static XIicPs i2c;
#define GPIO_DEVICE_ID  	XPAR_XGPIOPS_0_DEVICE_ID
static XGpioPs Gpio;

static bool GT911_ReadReg(uint16_t reg, uint8_t *buf, uint16_t len)
{
    uint8_t reg_buf[2];
    int status;

    // Set the high and low bytes of the register address
    reg_buf[0] = (uint8_t)(reg >> 8);
    reg_buf[1] = (uint8_t)(reg & 0xFF);

    // send the read cmd
    status = XIicPs_MasterSendPolled(&i2c, reg_buf, 2, GT911_SLAVE_ADDR);
    if (status != XST_SUCCESS)
    {
        return false;
    }

    // Wait for the I2C bus to be idle
    while (XIicPs_BusIsBusy(&i2c));

    // Receive data from the I2C bus
    status = XIicPs_MasterRecvPolled(&i2c, buf, len, GT911_SLAVE_ADDR);
    if (status != XST_SUCCESS)
    {
        return false;
    }

    // Wait for the I2C bus to be idle again
    while (XIicPs_BusIsBusy(&i2c));

    return true;
}

static bool GT911_WriteReg(uint16_t reg, uint8_t *buf, uint16_t len)
{
    uint8_t reg_buf[256] = {0};
    int status;

    // Set the high and low bytes of the register address
    reg_buf[0] = (uint8_t)(reg >> 8);
    reg_buf[1] = (uint8_t)(reg & 0xFF);

    // Copy the data from the buffer into reg_buf
    memcpy(&reg_buf[2], buf, len);

    // Send the write command
    status = XIicPs_MasterSendPolled(&i2c, reg_buf, len + 2, GT911_SLAVE_ADDR);
    if (status != XST_SUCCESS) {
        return false;
    }

    // Wait for the I2C bus to be idle
    while (XIicPs_BusIsBusy(&i2c));

    return true;
}

bool GT911_Init(void)
{
    uint8_t id[4] = {0};
    XIicPs_Config *i2cConfig = NULL;
    XGpioPs_Config *ConfigPtr = NULL;

	ConfigPtr = XGpioPs_LookupConfig(GPIO_DEVICE_ID);
	XGpioPs_CfgInitialize(&Gpio, ConfigPtr,ConfigPtr->BaseAddr);

    XGpioPs_SetDirectionPin(&Gpio, LCD_BLK, 1);
    XGpioPs_SetOutputEnablePin(&Gpio, LCD_BLK, 1);
    XGpioPs_WritePin(&Gpio, LCD_BLK, 1);

    XGpioPs_SetDirectionPin(&Gpio, TP_RESET, 1);   // Set TP_RESET as output
    XGpioPs_SetDirectionPin(&Gpio, TP_INT, 1);     // Set TP_INT as output
    XGpioPs_SetOutputEnablePin(&Gpio, TP_RESET, 1);
    XGpioPs_SetOutputEnablePin(&Gpio, TP_INT, 1);

    //SET 0XBA/0XBB
    XGpioPs_WritePin(&Gpio, TP_RESET, 0);          // Set TP_RESET low
    XGpioPs_WritePin(&Gpio, TP_INT, 0);            // Set TP_INT low: SET addr to 0XBA/0XBB
    vTaskDelay(10); // Delay at least 100us
    XGpioPs_WritePin(&Gpio, TP_RESET, 1);
    vTaskDelay(20); // Delay at least 5ms
    XGpioPs_SetDirectionPin(&Gpio, TP_INT, 0);//input_floating
    XGpioPs_SetOutputEnablePin(&Gpio, TP_INT, 0);
    vTaskDelay(10);

    i2cConfig = XIicPs_LookupConfig(GT911_I2C_DEV_ID);
    XIicPs_CfgInitialize(&i2c, i2cConfig, i2cConfig->BaseAddress);
    XIicPs_SetSClk(&i2c, 100000);

    //READ ID
    GT911_ReadReg(GT911_PRODUCT_ID_ADDR, id, 4);
    id[3]='\0';
	xil_printf("CTP ID:%s\r\n", id);

	if(strcmp((char*)id,"911")==0){
		return 0;
	}

    return 1;
}

uint8_t GT911_ScanTouch(GT911_TouchPoint *points, uint8_t max_points)
{
    uint8_t status = 0;
    uint8_t touch_num = 0;
    uint8_t clear = 0;

    if (!GT911_ReadReg(GT911_STATUS_ADDR, &status, 1)) goto _exit;

    touch_num = status & 0x0F;
    if (touch_num == 0 || touch_num > max_points) goto _exit;

    uint8_t buf[8 * GT911_MAX_TOUCHES] = {0};
    if (!GT911_ReadReg(GT911_POINT_DATA_ADDR, buf, touch_num * 8)) goto _exit;

    for (uint8_t i = 0; i < touch_num; ++i)
    {
        uint8_t *p = &buf[i * 8];
        points[i].id = p[0];
        points[i].x  = p[1] | (p[2] << 8);
        points[i].y  = p[3] | (p[4] << 8);
        points[i].size = p[5] | (p[6] << 8);
    }

_exit:
    // clear the status register
    GT911_WriteReg(GT911_STATUS_ADDR, &clear, 1);

    return touch_num;
}

