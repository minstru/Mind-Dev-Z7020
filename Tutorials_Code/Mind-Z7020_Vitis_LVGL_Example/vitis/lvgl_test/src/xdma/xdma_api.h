/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */


#ifndef _XDMA_API_H_
#define _XDMA_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool xdma_init(uint32_t dma_dev_id, int dma_length);
void xdma_start(uint32_t dst_addr, uint32_t src_addr);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_XDMA_API_H_*/

