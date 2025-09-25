/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xil_types.h"
#include "xil_cache.h"
#include "xparameters.h"
#include "xaxivdma.h"
#include "xaxivdma_i.h"
#include "display_ctrl_hdmi/display_ctrl_hdmi.h"
#include "vdma_api/vdma_api.h"


#define VDMA_ID            XPAR_AXIVDMA_0_DEVICE_ID   //VDMA device ID
#define DISP_VTC_ID        XPAR_VTC_0_DEVICE_ID       //VTC device ID


XAxiVdma     vdma;
DisplayCtrl  dispCtrl;
VideoMode    vd_mode;

unsigned int const frame_buffer_addr = (XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x1000000);

int main(void)
{
    xil_printf("HDMI Display 1920*1080 \r\n");

    //set video parameters, resolution: 1920*1080
    vd_mode = VMODE_1920x1080;

    //configure VDMA
    run_vdma_frame_buffer(&vdma, VDMA_ID, vd_mode.width, vd_mode.height,
        frame_buffer_addr,0, 0,ONLY_READ);

    //initialize Display controller
    DisplayInitialize(&dispCtrl, DISP_VTC_ID);
    //set VideoMode
    DisplaySetMode(&dispCtrl, &vd_mode);
    DisplayStart(&dispCtrl);

    int y = 0;
    int x = 0;
    for(y = 0; y < vd_mode.height; y++)
    {
        for(x = 0; x < vd_mode.width; x++)
            if (x >= 0 && x < (vd_mode.width / 4) * 1)  
            {
                // white
                *((u8 *)frame_buffer_addr+y*vd_mode.width*3+3*x+0)=0xff;
                *((u8 *)frame_buffer_addr+y*vd_mode.width*3+3*x+1)=0xff;
                *((u8 *)frame_buffer_addr+y*vd_mode.width*3+3*x+2)=0xff;
            }
            else if (x >= (vd_mode.width/4)*1 && x < (vd_mode.width/4)*2) 
            {
                // red
                *((u8 *)frame_buffer_addr+y*vd_mode.width*3+3*x+0)=0x00;
                *((u8 *)frame_buffer_addr+y*vd_mode.width*3+3*x+1)=0x00;
                *((u8 *)frame_buffer_addr+y*vd_mode.width*3+3*x+2)=0xff;

            }
            else if (x >= (vd_mode.width/4)*2 && x < (vd_mode.width/4)*3) 
            {
                // green
                *((u8 *)frame_buffer_addr+y*vd_mode.width*3+3*x+0)=0x00;
                *((u8 *)frame_buffer_addr+y*vd_mode.width*3+3*x+1)=0xff;
                *((u8 *)frame_buffer_addr+y*vd_mode.width*3+3*x+2)=0x00;
            }
            else 
            {
                // blue
                *((u8 *)frame_buffer_addr+y*vd_mode.width*3+3*x+0)=0xff;
                *((u8 *)frame_buffer_addr+y*vd_mode.width*3+3*x+1)=0x00;
                *((u8 *)frame_buffer_addr+y*vd_mode.width*3+3*x+2)=0x00;
            }
    }

    Xil_DCacheFlush();     //flush Cache，update data to DDR
    while(1)
    {

    }

    return 0;
}