/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include "xparameters.h"
#include "xgpiops.h"
#include "xstatus.h"
#include "xil_printf.h"
#include "sleep.h"

#include "xuartps.h"

#define GPIO_DEVICE_ID      XPAR_XGPIOPS_0_DEVICE_ID  // PS GPIO device ID
#define UART_DEVICE_ID      XPAR_XUARTPS_0_DEVICE_ID

// PS key and LED pin definitions
#define PS_LED0_PIN        (7)    // PS LED0 pin: MIO7
#define PS_LED1_PIN        (8)    // PS LED1 pin: MIO8
#define PS_KEY0_PIN        (0)    // PS KEY0 pin: MIO0
#define PS_KEY1_PIN        (11)   // PS KEY1 pin: MIO11


// 0~53 is for MIO, EMIO starts from 54
// EMIO pin definitions
#define EMIO_KEY0_PIN      (54)    // EMIO KEY0 pin
#define EMIO_KEY1_PIN      (55)    // EMIO KEY1 pin
#define EMIO_LED0_PIN      (56)    // EMIO LED0 pin
#define EMIO_LED1_PIN      (57)    // EMIO LED1 pin
#define EMIO_BEEP          (58)    // EMIO BEEP pin

XGpioPs Gpio;    // GPIO device instance


int main(void)
{
    int Uart_Status;
    int Status;
    XGpioPs_Config *ConfigPtr;
    u32 Key0Value, lastKey0Value = 1; // Initialize to 1 to avoid false trigger
    u32 Key1Value, lastKey1Value = 1; // Initialize to 1 to avoid false trigger
    u32 EmioKey0Value, lastEmioKey0Value = 1; // Initialize to 1 to avoid false trigger
    u32 EmioKey1Value, lastEmioKey1Value = 1; // Initialize to 1 to avoid false trigger

    xil_printf("ZYNQ7000 KEY & LED test\r\n");

    // initialize GPIO
    ConfigPtr = XGpioPs_LookupConfig(GPIO_DEVICE_ID);
    if (NULL == ConfigPtr) {
        return XST_FAILURE;
    }

    Status = XGpioPs_CfgInitialize(&Gpio, ConfigPtr, ConfigPtr->BaseAddr);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    // Set EMIO BEEP pin as output
    XGpioPs_SetDirectionPin(&Gpio, EMIO_BEEP, 1);
	XGpioPs_SetOutputEnablePin(&Gpio, EMIO_BEEP, 1);

    // Set PS LED pins as output
    XGpioPs_SetDirectionPin(&Gpio, PS_LED0_PIN, 1);
    XGpioPs_SetDirectionPin(&Gpio, PS_LED1_PIN, 1);
    XGpioPs_SetOutputEnablePin(&Gpio, PS_LED0_PIN, 1);
    XGpioPs_SetOutputEnablePin(&Gpio, PS_LED1_PIN, 1);

    // Set PS KEY pins as input
    XGpioPs_SetDirectionPin(&Gpio, PS_KEY0_PIN, 0);
    XGpioPs_SetDirectionPin(&Gpio, PS_KEY1_PIN, 0);
    XGpioPs_SetOutputEnablePin(&Gpio, PS_KEY0_PIN, 0);
    XGpioPs_SetOutputEnablePin(&Gpio, PS_KEY1_PIN, 0);

    // Set EMIO LED pins as output
    XGpioPs_SetDirectionPin(&Gpio, EMIO_LED0_PIN, 1);
    XGpioPs_SetDirectionPin(&Gpio, EMIO_LED1_PIN, 1);
    XGpioPs_SetOutputEnablePin(&Gpio, EMIO_LED0_PIN, 1);
    XGpioPs_SetOutputEnablePin(&Gpio, EMIO_LED1_PIN, 1);

    // Set EMIO KEY pins as input
    XGpioPs_SetDirectionPin(&Gpio, EMIO_KEY0_PIN, 0);
    XGpioPs_SetDirectionPin(&Gpio, EMIO_KEY1_PIN, 0);
    XGpioPs_SetOutputEnablePin(&Gpio, EMIO_KEY0_PIN, 0);
    XGpioPs_SetOutputEnablePin(&Gpio, EMIO_KEY1_PIN, 0);

    xil_printf("press keys, and observe LED status\r\n");

    while (1) 
    {
        // contrl beep
        XGpioPs_WritePin(&Gpio, EMIO_BEEP, 0);
        usleep(1000);
        XGpioPs_WritePin(&Gpio, EMIO_BEEP, 1);
        usleep(1000);

        // read PS key states
        Key0Value = XGpioPs_ReadPin(&Gpio, PS_KEY0_PIN);
        Key1Value = XGpioPs_ReadPin(&Gpio, PS_KEY1_PIN);

        // read EMIO key states
        EmioKey0Value = XGpioPs_ReadPin(&Gpio, EMIO_KEY0_PIN);
        EmioKey1Value = XGpioPs_ReadPin(&Gpio, EMIO_KEY1_PIN);

        if (lastKey0Value == 1 && Key0Value == 0) 
        {
            xil_printf("PS_KEY0 is pressed\r\n");
        } 
        else if (lastKey0Value == 0 && Key0Value == 1) 
        {
            xil_printf("PS_KEY0 is released\r\n");
        }
        lastKey0Value = Key0Value;

        if (lastKey1Value == 1 && Key1Value == 0) 
        {
            xil_printf("PS_KEY1 is pressed\r\n");
        } 
        else if (lastKey1Value == 0 && Key1Value == 1) 
        {
            xil_printf("PS_KEY1 is released\r\n");
        }
        lastKey1Value = Key1Value;

        // print the status of EMIO_KEY0
        if (lastEmioKey0Value == 1 && EmioKey0Value == 0) 
        {
            xil_printf("EMIO_KEY0 is pressed\r\n");
        } 
        else if (lastEmioKey0Value == 0 && EmioKey0Value == 1) 
        {
            xil_printf("EMIO_KEY0 is released\r\n");
        }
        lastEmioKey0Value = EmioKey0Value;

        // print the status of EMIO_KEY1
        if (lastEmioKey1Value == 1 && EmioKey1Value == 0) 
        {
            xil_printf("EMIO_KEY1 is pressed\r\n");
        } 
        else if (lastEmioKey1Value == 0 && EmioKey1Value == 1) 
        {
            xil_printf("EMIO_KEY1 is released\r\n");
        }
        lastEmioKey1Value = EmioKey1Value;

        XGpioPs_WritePin(&Gpio, PS_LED0_PIN, !Key0Value);
        XGpioPs_WritePin(&Gpio, PS_LED1_PIN, !Key1Value);

        XGpioPs_WritePin(&Gpio, EMIO_LED0_PIN, !EmioKey0Value);
        XGpioPs_WritePin(&Gpio, EMIO_LED1_PIN, !EmioKey1Value);

        usleep(100000); // 100ms
    }

    return XST_SUCCESS;
}

