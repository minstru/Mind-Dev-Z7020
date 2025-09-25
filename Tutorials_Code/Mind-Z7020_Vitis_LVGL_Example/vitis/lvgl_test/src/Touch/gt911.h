/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#ifndef __GT911_H
#define __GT911_H

#include <stdint.h>
#include <stdbool.h>

#define GT911_MAX_TOUCHES     5

typedef struct {
    uint8_t id;
    uint16_t x;
    uint16_t y;
    uint16_t size; // touch area or pressure
} GT911_TouchPoint;

bool GT911_Init(void);
uint8_t GT911_ScanTouch(GT911_TouchPoint *points, uint8_t max_points);

#endif
