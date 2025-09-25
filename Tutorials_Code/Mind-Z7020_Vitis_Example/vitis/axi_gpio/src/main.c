/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include "xgpio.h"
#include "xgpiops.h"
#include "xparameters.h"
#include "xil_printf.h"
#include "sleep.h"

// AXI GPIO device ID
#define GPIO_0_DEVICE_ID XPAR_GPIO_0_DEVICE_ID
#define GPIO_1_DEVICE_ID XPAR_GPIO_1_DEVICE_ID

#define MIO_GPIO_DEVICE_ID XPAR_XGPIOPS_0_DEVICE_ID

#define BUTTON_MIO_PIN (0)

#define GPIO0_CHAN1_NUM (32) // gpio0~31: output
#define GPIO0_CHAN2_NUM (32) // gpio0~31: output
#define GPIO1_CHAN1_NUM (23) // gpio0~21: output, gpio23: input

int mio_pins[] = {12, 13};
XGpio Gpio0, Gpio1;
XGpioPs GpioPs;

int init_axi_gpio();
int init_mio();
void wait_for_button_press();
void light_up_leds_one_by_one();

int main()
{
    int status = XST_FAILURE;

    xil_printf("Zynq GPIO control program starting...\r\n");

    status = init_axi_gpio();
    if (status != XST_SUCCESS)
    {
        xil_printf("AXI GPIO initialization failed!\r\n");
        return XST_FAILURE;
    }

    status = init_mio();
    if (status != XST_SUCCESS)
    {
        xil_printf("PS MIO initialization failed!\r\n");
        return XST_FAILURE;
    }

    while (1)
    {
        xil_printf("press key to light on leds...\r\n");
        wait_for_button_press();

        light_up_leds_one_by_one();

        for (int i = 0; i < sizeof(mio_pins) / sizeof(int); i++)
        {
            XGpioPs_WritePin(&GpioPs, mio_pins[i], 1);
            usleep(300000);
        }

        xil_printf("press key to light off all leds...\r\n");
        wait_for_button_press();

        // light off all axi gpio leds
        XGpio_DiscreteWrite(&Gpio0, 1, 0x0);
        XGpio_DiscreteWrite(&Gpio0, 2, 0x0);
        XGpio_DiscreteWrite(&Gpio1, 1, 0x0);

        // light off MIO LED
        for (int i = 0; i < sizeof(mio_pins) / sizeof(int); i++)
        {
            XGpioPs_WritePin(&GpioPs, mio_pins[i], 0);
        }
    }

    return 0;
}

int init_axi_gpio()
{
    int status;

    status = XGpio_Initialize(&Gpio0, GPIO_0_DEVICE_ID);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    status = XGpio_Initialize(&Gpio1, GPIO_1_DEVICE_ID);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    // set direction: 0->output, 1->input
    XGpio_SetDataDirection(&Gpio0, 1, 0x0); // all GPIO used as output
    XGpio_SetDataDirection(&Gpio0, 2, 0x0);
    XGpio_SetDataDirection(&Gpio1, 1, 0xFF800000 | (0x01 << 22)); // GPIO0~21: ouput, GPIO22: input

    return XST_SUCCESS;
}

int init_mio()
{
    XGpioPs_Config *ConfigPtr;
    ConfigPtr = XGpioPs_LookupConfig(MIO_GPIO_DEVICE_ID);
    if (ConfigPtr == NULL)
    {
        xil_printf("MIO GPIO config lookup failed.\r\n");
        return XST_FAILURE;
    }

    XGpioPs_CfgInitialize(&GpioPs, ConfigPtr, ConfigPtr->BaseAddr);

    // config MIO pins output
    for (int i = 0; i < sizeof(mio_pins) / sizeof(int); i++)
    {
        int pin = mio_pins[i];
        XGpioPs_SetDirectionPin(&GpioPs, pin, 1);    // set direction: 1->output, 0->input
        XGpioPs_SetOutputEnablePin(&GpioPs, pin, 1); // enable output
        XGpioPs_WritePin(&GpioPs, pin, 0);           // output to low
    }

    XGpioPs_SetDirectionPin(&GpioPs, BUTTON_MIO_PIN, 0);    // set button as input
    XGpioPs_SetOutputEnablePin(&GpioPs, BUTTON_MIO_PIN, 0); // disable output
    return XST_SUCCESS;
}

void light_up_leds_one_by_one()
{
    // AXI GPIO0 channel1
    u32 led_state = 0;
    for (int i = 0; i < GPIO0_CHAN1_NUM; i++)
    {
        led_state |= (1 << i);
        XGpio_DiscreteWrite(&Gpio0, 1, led_state); // light up
        xil_printf("GPIO0 Channel 1 LED %d is ON\r\n", i + 1);
        usleep(300000);
        // XGpio_DiscreteWrite(&Gpio0, 1, 0x0); //light down
        // xil_printf("GPIO0 Channel 1 LED %d is OFF\r\n", i + 1);
        // usleep(500000);
    }

    u32 led_state1 = 0;
    // AXI GPIO0 channel2
    for (int i = 0; i < GPIO0_CHAN2_NUM; i++)
    {
        led_state1 |= (1 << i);
        XGpio_DiscreteWrite(&Gpio0, 2, led_state1);
        xil_printf("GPIO0 Channel 2 LED %d is ON\r\n", i + 1);
        usleep(300000);
        // XGpio_DiscreteWrite(&Gpio0, 2, 0x0);
        // xil_printf("GPIO0 Channel 2 LED %d is OFF\r\n", i + 1);
        // usleep(500000);
    }

    u32 led_state2 = 0;
    // AXI GPIO1 channel1: GPIO22 used as input
    for (int i = 0; i < GPIO1_CHAN1_NUM - 1; i++)
    {
        led_state2 |= (1 << i);
        XGpio_DiscreteWrite(&Gpio1, 1, led_state2);
        xil_printf("GPIO1 Channel 1 LED %d is ON\r\n", i + 1);
        usleep(300000);
        // XGpio_DiscreteWrite(&Gpio1, 1, 0x0);
        // xil_printf("GPIO1 Channel 1 LED %d is OFF\r\n", i + 1);
        // usleep(500000);
    }

    // GPIO1 channel1 pin23: input,can't light up
    xil_printf("GPIO1 Channel 1 LED 23 is set to input (cannot light up)\r\n");
}

void wait_for_button_press()
{
    while (1)
    {
        if (XGpioPs_ReadPin(&GpioPs, BUTTON_MIO_PIN)) // wait for key down
        {
            usleep(200000);
            while (XGpioPs_ReadPin(&GpioPs, BUTTON_MIO_PIN)); // wait for key up
            break;
        }
        usleep(10000);
    }

    return;
}
