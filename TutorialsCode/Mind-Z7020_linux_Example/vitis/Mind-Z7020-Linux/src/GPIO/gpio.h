/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#ifndef _GPIO_H_
#define _GPIO_H_
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define GPIO_BASE          (819)
#define PS_LED0_PIN        (GPIO_BASE + 7)
#define PS_LED1_PIN        (GPIO_BASE + 8)
#define PS_KEY0_PIN        (GPIO_BASE + 0)
#define PS_KEY1_PIN        (GPIO_BASE + 11)
#define PS_MIO12_PIN       (GPIO_BASE + 12)
#define PS_MIO13_PIN       (GPIO_BASE + 13)

#define EMIO_KEY0_PIN      (GPIO_BASE + 54 + 0)
#define EMIO_KEY1_PIN      (GPIO_BASE + 54 + 1)
#define EMIO_LED0_PIN      (GPIO_BASE + 54 + 2)
#define EMIO_LED1_PIN      (GPIO_BASE + 54 + 3)

#define BEEP_PIN           (GPIO_BASE + 54 + 4)


#define AXI_GPIO0_BASE     (937)
#define AXI_GPIO0_NUM      (23)

#define AXI_GPIO1_BASE     (960)
#define AXI_GPIO1_NUM      (64)

// export GPIO
void export_gpio(int pin);

// set GPIO direction
void set_direction(int pin, const char* direction);

//  write GPIO
void write_gpio(int pin, int value);

// read GPIO
int read_gpio(int pin);

void *gpio_thread(void *arg);


#endif //_GPIO_H_