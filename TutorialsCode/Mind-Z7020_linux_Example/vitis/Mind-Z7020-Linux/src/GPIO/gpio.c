/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "gpio.h"


// export GPIO
void export_gpio(int pin) 
{
    char buffer[10];
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0) {
        perror("Failed to open export");
        exit(1);
    }
    snprintf(buffer, sizeof(buffer), "%d", pin);
    write(fd, buffer, strlen(buffer));
    close(fd);
    usleep(100000); // wait sysfs node build
}

// set GPIO direction
void set_direction(int pin, const char* direction) 
{
    char path[64];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);
    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open direction");
        exit(1);
    }
    write(fd, direction, strlen(direction));
    close(fd);
}

//  write GPIO
void write_gpio(int pin, int value) 
{
    char path[64];
    char val = value ? '1' : '0';
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open value for writing");
        exit(1);
    }
    write(fd, &val, 1);
    close(fd);
}

// read GPIO
int read_gpio(int pin) 
{
    char path[64];
    char val;
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open value for reading");
        exit(1);
    }
    read(fd, &val, 1);
    close(fd);
    return (val == '1') ? 1 : 0;
}


// Client thread function
void *gpio_thread(void *arg)
{
    const int led_gpio_map[4] = {PS_LED0_PIN, PS_LED1_PIN, EMIO_LED0_PIN, EMIO_LED1_PIN};
    const int key_gpio_map[4] = {PS_KEY0_PIN, PS_KEY1_PIN, EMIO_KEY0_PIN, EMIO_KEY1_PIN};
    const int mio_gpio_map[2] = {PS_MIO12_PIN, PS_MIO13_PIN};
    int key_val[4] = {1, 1, 1, 1};
    bool axi_gpio_status = true;
    bool last_axi_gpio_status = false;

    export_gpio(BEEP_PIN);
    set_direction(BEEP_PIN, "out");
    write_gpio(BEEP_PIN, 0);

    for (int i = 0; i < sizeof(led_gpio_map)/sizeof(int); i++)
    {
        export_gpio(led_gpio_map[i]);
        set_direction(led_gpio_map[i], "out");
        write_gpio(led_gpio_map[i], 0);
    }

    for (int i = 0; i < sizeof(key_gpio_map)/sizeof(int); i++)
    {
        export_gpio(key_gpio_map[i]);
        set_direction(key_gpio_map[i], "in");
    }

    // beep test
    for(int i = 0; i < 200; i++)
    {
        write_gpio(BEEP_PIN, 0);
        usleep(1000);
        write_gpio(BEEP_PIN, 1);
        usleep(1000);
    }

    for (int i = 0; i < sizeof(mio_gpio_map)/sizeof(int); i++)
    {
        export_gpio(mio_gpio_map[i]);
        set_direction(mio_gpio_map[i], "out");
        write_gpio(mio_gpio_map[i], 0);
    }

    for (int i = 0; i < AXI_GPIO0_NUM; i++)
    {
        export_gpio(AXI_GPIO0_BASE + i);
        set_direction(AXI_GPIO0_BASE + i, "out");
        write_gpio(AXI_GPIO0_BASE + i, 0);
    }

    for (int i = 0; i < AXI_GPIO1_NUM; i++)
    {
        export_gpio(AXI_GPIO1_BASE + i);
        set_direction(AXI_GPIO1_BASE + i, "out");
        write_gpio(AXI_GPIO1_BASE + i, 0);
    }

    axi_gpio_status = true;
    last_axi_gpio_status = false;

    while (1)
    {
        for (int i = 0; i < sizeof(key_gpio_map)/sizeof(int); i++)
        {
            key_val[i] = read_gpio(key_gpio_map[i]);
        }

        for (int i = 0; i < sizeof(led_gpio_map)/sizeof(int); i++)
        {
            write_gpio(led_gpio_map[i], (key_val[i] == 0) ? 1:0);
        }

        if (key_val[0] == 0)
        {
            axi_gpio_status = true;
        }
        if (key_val[1] == 0)
        {
            axi_gpio_status = false;
        }

        if (axi_gpio_status && (!last_axi_gpio_status))
        {
            for (int i = 0; i < AXI_GPIO0_NUM; i++)
            {
                write_gpio(AXI_GPIO0_BASE + i, 1);
                usleep(500000);
            }

            for (int i = 0; i < AXI_GPIO1_NUM; i++)
            {
                write_gpio(AXI_GPIO1_BASE + i, 1);
                usleep(500000);
            }

            for (int i = 0; i < sizeof(mio_gpio_map)/sizeof(int); i++)
            {
                write_gpio(mio_gpio_map[i], 1);
                usleep(500000);
            }
            last_axi_gpio_status = true;
        }
        else if ((!axi_gpio_status) && last_axi_gpio_status)
        {
            for (int i = 0; i < AXI_GPIO0_NUM; i++)
            {
                write_gpio(AXI_GPIO0_BASE + i, 0);
                usleep(500000);
            }

            for (int i = 0; i < AXI_GPIO1_NUM; i++)
            {
                write_gpio(AXI_GPIO1_BASE + i, 0);
                usleep(500000);
            }

            for (int i = 0; i < sizeof(mio_gpio_map)/sizeof(int); i++)
            {
                write_gpio(mio_gpio_map[i], 0);
                usleep(500000);
            }
            last_axi_gpio_status = false;
        }
        usleep(10000);
    }
    return NULL;
}



