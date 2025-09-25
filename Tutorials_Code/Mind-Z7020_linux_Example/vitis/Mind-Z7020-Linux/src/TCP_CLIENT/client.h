/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#ifndef _CLIENT_H_
#define _CLIENT_H_
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>


void set_host_ip_port(int ip[4], uint16_t port);

void *client_pthread_func(void *arg);

#endif // _CLIENT_H_
