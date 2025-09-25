/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include <stdbool.h>
#include "xparameters.h"
#include "xaxivdma.h"
#include "xaxivdma_i.h"
#include "xdmaps.h"
#include "xscugic.h"
#include "FreeRTOS.h"
#include "task.h"




#define DMA_DONE_INTR_0			XPAR_XDMAPS_0_DONE_INTR_0
#define DMA_DONE_INTR_1			XPAR_XDMAPS_0_DONE_INTR_1
#define DMA_DONE_INTR_2			XPAR_XDMAPS_0_DONE_INTR_2
#define DMA_DONE_INTR_3			XPAR_XDMAPS_0_DONE_INTR_3
#define DMA_DONE_INTR_4			XPAR_XDMAPS_0_DONE_INTR_4
#define DMA_DONE_INTR_5			XPAR_XDMAPS_0_DONE_INTR_5
#define DMA_DONE_INTR_6			XPAR_XDMAPS_0_DONE_INTR_6
#define DMA_DONE_INTR_7			XPAR_XDMAPS_0_DONE_INTR_7


#define DMA_BURST_SIZE      (4)
#define DMA_BURST_LEN       (16)

#define MAX_DMA_LENGTH		(256 * 256 * DMA_BURST_SIZE * DMA_BURST_LEN)
#define MAX_DMA_CHANNELS	4

extern XScuGic gic_inst;
XDmaPs dma_inst;
static XDmaPs_Cmd xdma_cmd[MAX_DMA_CHANNELS];
static bool xdma_done[MAX_DMA_CHANNELS];
static int chans_used = 0; // Number of channels used
static int dma_len_per_chan = 0; // Length per channel
extern XAxiVdma vdma;
extern uint8_t frame_index;

static uint16_t dma_done_intr_ids[] = {
    DMA_DONE_INTR_0,
    DMA_DONE_INTR_1,
    DMA_DONE_INTR_2,
    DMA_DONE_INTR_3,
    DMA_DONE_INTR_4,
    DMA_DONE_INTR_5,
    DMA_DONE_INTR_6,
    DMA_DONE_INTR_7
};

static Xil_InterruptHandler xdma_done_isr[] = {
    (Xil_InterruptHandler)XDmaPs_DoneISR_0,
    (Xil_InterruptHandler)XDmaPs_DoneISR_1,
    (Xil_InterruptHandler)XDmaPs_DoneISR_2,
    (Xil_InterruptHandler)XDmaPs_DoneISR_3,
    (Xil_InterruptHandler)XDmaPs_DoneISR_4,
    (Xil_InterruptHandler)XDmaPs_DoneISR_5,
    (Xil_InterruptHandler)XDmaPs_DoneISR_6,
    (Xil_InterruptHandler)XDmaPs_DoneISR_7
};


static void xdma_done_handler(unsigned int Channel, XDmaPs_Cmd *xdma_cmd, void *CallbackRef)
{
    xdma_done[Channel] = true;

    for (int i = 0; i < MAX_DMA_CHANNELS; i++)
    {
        if (xdma_done[i] == false)
        {
            return; // wait for all channels to complete
        }
    }
    frame_index = (frame_index + 1) % 2;
    XAxiVdma_StartParking(&vdma, frame_index, XAXIVDMA_READ);
}


static bool setup_dma_interrupt(XDmaPs *DmaPtr, uint32_t chan)
{
	XScuGic_Connect(&gic_inst, dma_done_intr_ids[chan], 
        (Xil_InterruptHandler)xdma_done_isr[chan], (void *)DmaPtr);

	XScuGic_Enable(&gic_inst, dma_done_intr_ids[chan]);

    return XST_SUCCESS;
}


bool xdma_init(uint32_t dma_dev_id, int dma_length)
{
    int32_t Status = XST_FAILURE;
    dma_len_per_chan = dma_length;

    XDmaPs_Config *xmda_cfg = XDmaPs_LookupConfig(dma_dev_id);
    Status = XDmaPs_CfgInitialize(&dma_inst, xmda_cfg, xmda_cfg->BaseAddress);
    if (Status != XST_SUCCESS) return XST_FAILURE;

    if (dma_length > MAX_DMA_LENGTH * MAX_DMA_CHANNELS || dma_length < 0)
    {
        xil_printf("Invalid DMA length: %d\n", dma_length);
        return XST_FAILURE;
    }

    for (int i = 0; i < MAX_DMA_CHANNELS; i++)
    {
        xdma_done[i] = true;  // Initialize all channels as done
    }

    while (dma_len_per_chan > MAX_DMA_LENGTH)
    {
        dma_len_per_chan = dma_len_per_chan / 2;
    }

    for (int i = 0; i < MAX_DMA_CHANNELS; i++)
    {
        chans_used++;
        setup_dma_interrupt(&dma_inst, i);

        XDmaPs_SetDoneHandler(&dma_inst, i, xdma_done_handler, NULL);
        memset(&(xdma_cmd[i]), 0, sizeof(XDmaPs_Cmd));

        xdma_cmd[i].ChanCtrl.SrcBurstSize = DMA_BURST_SIZE;
        xdma_cmd[i].ChanCtrl.SrcBurstLen = DMA_BURST_LEN;
        xdma_cmd[i].ChanCtrl.SrcInc = 1;
        xdma_cmd[i].ChanCtrl.DstBurstSize = DMA_BURST_SIZE;
        xdma_cmd[i].ChanCtrl.DstBurstLen = DMA_BURST_LEN;
        xdma_cmd[i].ChanCtrl.DstInc = 1;

        xdma_cmd[i].BD.SrcAddr = (u32) NULL;
        xdma_cmd[i].BD.DstAddr = (u32) NULL;
        xdma_cmd[i].BD.Length = dma_len_per_chan;

        if (dma_len_per_chan * chans_used >= dma_length)
        {
            break;
        }
    }

    return XST_SUCCESS;
}

void xdma_start(uint32_t dst_addr, uint32_t src_addr)
{
    for (int chan = 0; chan < chans_used; chan++)
    {
        xdma_cmd[chan].BD.DstAddr = dst_addr + (chan * dma_len_per_chan);
        xdma_cmd[chan].BD.SrcAddr = src_addr + (chan * dma_len_per_chan);
        xdma_done[chan] = false;
    }

    for (int chan = 0; chan < chans_used; chan++)
    {
        XDmaPs_Start(&dma_inst, chan, &(xdma_cmd[chan]), 0);
    }
}
