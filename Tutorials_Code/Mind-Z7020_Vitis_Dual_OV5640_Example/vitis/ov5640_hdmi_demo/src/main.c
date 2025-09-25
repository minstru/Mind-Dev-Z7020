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
#include "emio_sccb_cfg/emio_sccb_cfg.h"
#include "ov5640/ov5640_init.h"

#define CAM0_VDMA_ID        XPAR_AXIVDMA_2_DEVICE_ID    // camera0 VDMA device ID
#define CAM1_VDMA_ID        XPAR_AXIVDMA_3_DEVICE_ID    // camera1 VDMA device ID
#define HDMI_VDMA_ID        XPAR_AXIVDMA_0_DEVICE_ID    // HDMI VDMA device ID
#define LCD_VDMA_ID         XPAR_AXIVDMA_1_DEVICE_ID    // LCD VDMA device ID
#define HDMI_VTC_ID         XPAR_VTC_0_DEVICE_ID        // HDMI VTC device ID
#define LCD_VTC_ID          XPAR_VTC_1_DEVICE_ID        // LCD VTC device ID
#define HDMI_CLK_WIZ_ID     XPAR_CLK_WIZ_0_DEVICE_ID    // HDMI clock wiz device ID
#define LCD_CLK_WIZ_ID      XPAR_CLK_WIZ_1_DEVICE_ID    // LCD clock wiz device ID

#define BYTES_PIXEL        3                           // RGB888 => 3bytes

//frame buffer address
unsigned int const cam0_frame_buffer_addr = (XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x1000000);
unsigned int const disp_frame_buffer_addr = cam0_frame_buffer_addr;
unsigned int cam1_frame_buffer_addr;


XAxiVdma     cam0_vdma;
XAxiVdma     cam1_vdma;
XAxiVdma     hdmi_vdma;
XAxiVdma     lcd_vdma;
DisplayCtrl  hdmi_disp_ctrl;
DisplayCtrl  lcd_disp_ctrl;
// VideoMode    *vd_mode = &VMODE_1024x600;
VideoMode    *vd_mode = &VMODE_1280x720;

int main(void)
{
    u32 status0,status1;
    u16 cmos_h_pixel; 
    u16 cmos_v_pixel; 
    u16 total_h_pixel;
    u16 total_v_pixel;

    if (vd_mode == &VMODE_800x480)
    {
        total_h_pixel = 1800;
        total_v_pixel = 600;
    }
    else if (vd_mode == &VMODE_1024x600)
    {
        total_h_pixel = 2200;
        total_v_pixel = 1000;
    }
    else if (vd_mode == &VMODE_1280x720)
    {
        total_h_pixel = 2570;
        total_v_pixel = 980;
    }

    Xil_DCacheDisable();

    cam1_frame_buffer_addr = cam0_frame_buffer_addr + vd_mode->width * BYTES_PIXEL/2;

    emio_init();
    status0 = ov5640_init(CAM0_CH0,vd_mode->width/2,
                        vd_mode->height,
                        total_h_pixel,
                        total_v_pixel);

    status1 = ov5640_init(CAM1_CH1,vd_mode->width/2,
                        vd_mode->height,
                        total_h_pixel,
                        total_v_pixel);

    if(status0 == 0 && status1 == 0)
        xil_printf("Dual OV5640 detected successful!\r\n");
    else
        xil_printf("Dual OV5640 detected failed!\r\n");

    //CAM0 VDMA
    run_vdma_frame_buffer(&cam0_vdma, CAM0_VDMA_ID, vd_mode->width, vd_mode->height,
                            cam0_frame_buffer_addr,0,0,ONLY_WRITE);
    //CAM1 VDMA
    run_vdma_frame_buffer(&cam1_vdma, CAM1_VDMA_ID, vd_mode->width, vd_mode->height,
                            cam1_frame_buffer_addr,0,0,ONLY_WRITE);

    //HDMI
    run_vdma_frame_buffer(&hdmi_vdma, HDMI_VDMA_ID, vd_mode->width, vd_mode->height,
                            disp_frame_buffer_addr,0,0,ONLY_READ);
    clk_wiz_cfg(HDMI_CLK_WIZ_ID, vd_mode->freq, vd_mode->freq2);
    DisplayInitialize(&hdmi_disp_ctrl, HDMI_VTC_ID);
    DisplaySetMode(&hdmi_disp_ctrl, vd_mode);
    DisplayStart(&hdmi_disp_ctrl);

    // //LCD
    // run_vdma_frame_buffer(&lcd_vdma, LCD_VDMA_ID, vd_mode->width, vd_mode->height,
    //                         disp_frame_buffer_addr,0,0,ONLY_READ);

    // clk_wiz_cfg(LCD_CLK_WIZ_ID, vd_mode->freq);
    // DisplayInitialize(&lcd_disp_ctrl, LCD_VTC_ID);
    // DisplaySetMode(&lcd_disp_ctrl, vd_mode);
    // DisplayStart(&lcd_disp_ctrl);

    while(1)
    {
    }
    
    return 0;
}
