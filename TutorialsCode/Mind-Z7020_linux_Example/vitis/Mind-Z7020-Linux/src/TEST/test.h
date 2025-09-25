/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include "main.h"
#include "rtc.h"
#include "sensor.h"
#include "eeprom.h"
#include "gpio.h"
#include "can.h"
#include "server.h"
#include "client.h"
#include "embedded_cli.h"


void test_rtc(EmbeddedCli *cli,const char *i2c_dev);
void test_shtc3(EmbeddedCli *cli,const char *i2c_dev);
void test_eeprom(EmbeddedCli *cli,const char *i2c_dev);
void test_can(EmbeddedCli *cli);
void test_xadc(EmbeddedCli *cli);
