/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */


#ifndef _VDMA_API_H_
#define _VDMA_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "xaxivdma.h"
#include "xparameters.h"

#define BYTES_PIXEL        (3)    // RGB888 format

typedef enum
{
	READ_ONLY=1,
	WRITE_ONLY,
	READ_WRITE
}vdma_work_mode;

int run_vdma_frame_buffer(XAxiVdma* InstancePtr, int DeviceId, int hsize,
		int vsize, int buf_base_addr, int number_frame_count,
		int enable_frm_cnt_intr, vdma_work_mode mode);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_VDMA_API_H_*/

