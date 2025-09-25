/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */


#include "emio_sccb_cfg.h"
#include "sleep.h"

#define  GPIOPS_ID  XPAR_XGPIOPS_0_DEVICE_ID  //PS GPIO device ID

static  XGpioPs  gpiops_inst; // PS GPIO instance

// init emio
void emio_init(void)
{
	XGpioPs_Config *gpiops_cfg_ptr;

	gpiops_cfg_ptr = XGpioPs_LookupConfig(GPIOPS_ID);
	XGpioPs_CfgInitialize(&gpiops_inst, gpiops_cfg_ptr, gpiops_cfg_ptr->BaseAddr);

    XGpioPs_SetDirectionPin(&gpiops_inst, LCD_BLK, 1);
    XGpioPs_SetOutputEnablePin(&gpiops_inst, LCD_BLK, 1);
    XGpioPs_WritePin(&gpiops_inst, LCD_BLK, 1);

    // XGpioPs_SetDirectionPin(&gpiops_inst, EMIO_BEEP, 1);
	// XGpioPs_SetOutputEnablePin(&gpiops_inst, EMIO_BEEP, 1);

	// config CAM0 sscb to output
	XGpioPs_SetDirectionPin(&gpiops_inst, EMIO_SCL0_NUM, 1);
	XGpioPs_SetDirectionPin(&gpiops_inst, EMIO_SDA0_NUM, 1);
	// enable CAM0 sscb output
	XGpioPs_SetOutputEnablePin(&gpiops_inst, EMIO_SCL0_NUM, 1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst, EMIO_SDA0_NUM, 1);
    // set CAM0 sscb pins to high
	XGpioPs_WritePin(&gpiops_inst, EMIO_SCL0_NUM, 1);
	XGpioPs_WritePin(&gpiops_inst, EMIO_SDA0_NUM, 1);

	XGpioPs_SetDirectionPin(&gpiops_inst, EMIO_SCL1_NUM, 1);
	XGpioPs_SetDirectionPin(&gpiops_inst, EMIO_SDA1_NUM, 1);

	XGpioPs_SetOutputEnablePin(&gpiops_inst, EMIO_SCL1_NUM, 1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst, EMIO_SDA1_NUM, 1);

	XGpioPs_WritePin(&gpiops_inst, EMIO_SCL1_NUM, 1);
	XGpioPs_WritePin(&gpiops_inst, EMIO_SDA1_NUM, 1);
}


void sccb_start(u8 cam_ch)
{
	u8 emio_scl = 0 ,emio_sda = 0;
    if(cam_ch == 0){
        emio_scl = EMIO_SCL0_NUM;
        emio_sda = EMIO_SDA0_NUM;
    }
    else{
        emio_scl = EMIO_SCL1_NUM;
        emio_sda = EMIO_SDA1_NUM;        
    }

	XGpioPs_WritePin(&gpiops_inst, emio_scl, 1);
	XGpioPs_WritePin(&gpiops_inst, emio_sda, 1);

	usleep(4);

 	XGpioPs_WritePin(&gpiops_inst, emio_sda, 0);  //START:when CLK is high,DATA change form high to low

 	usleep(4);

 	XGpioPs_WritePin(&gpiops_inst, emio_scl, 0); 

}

void sccb_stop(u8 cam_ch)
{
	u8 emio_scl = 0 ,emio_sda = 0;
        if(cam_ch == 0){
        emio_scl = EMIO_SCL0_NUM;
        emio_sda = EMIO_SDA0_NUM;
    }
    else{
        emio_scl = EMIO_SCL1_NUM;
        emio_sda = EMIO_SDA1_NUM;        
    }
    
	XGpioPs_WritePin(&gpiops_inst, emio_scl, 0);

	XGpioPs_WritePin(&gpiops_inst,emio_sda, 0);  //STOP:when CLK is high DATA change form low to high

 	usleep(4);

	XGpioPs_WritePin(&gpiops_inst, emio_scl, 1);

	usleep(4);

	XGpioPs_WritePin(&gpiops_inst, emio_sda, 1); 

}

void sccb_send_byte(u8 cam_ch,u8 txd)
{
    u8 t;
    u8 emio_scl = 0 ,emio_sda = 0;
        if(cam_ch == 0){
        emio_scl = EMIO_SCL0_NUM;
        emio_sda = EMIO_SDA0_NUM;
    }
    else{
        emio_scl = EMIO_SCL1_NUM;
        emio_sda = EMIO_SDA1_NUM;        
    }
    
    XGpioPs_WritePin(&gpiops_inst, emio_scl, 0); 

    for(t=0; t<8; t++)
    {
        XGpioPs_WritePin(&gpiops_inst, emio_sda, (txd&0x80)>>7);

        txd<<=1;

        usleep(4);

        XGpioPs_WritePin(&gpiops_inst, emio_scl, 1);

        usleep(4);

        XGpioPs_WritePin(&gpiops_inst, emio_scl, 0);

        usleep(4);
    }
}

u8  sccb_rece_byte(u8 cam_ch)
{
	unsigned char i=0 , rxd=0;
	u8 emio_scl = 0 ,emio_sda = 0;
    if(cam_ch == 0){
        emio_scl = EMIO_SCL0_NUM;
        emio_sda = EMIO_SDA0_NUM;
    }
    else{
        emio_scl = EMIO_SCL1_NUM;
        emio_sda = EMIO_SDA1_NUM;        
    }

	XGpioPs_SetOutputEnablePin(&gpiops_inst, emio_sda, 0);
	XGpioPs_SetDirectionPin(&gpiops_inst, emio_sda, 0);

	XGpioPs_WritePin(&gpiops_inst, emio_scl, 0);
	usleep(4);

	for(i=0;i<8;i++ )
	{
        XGpioPs_WritePin(&gpiops_inst, emio_scl, 1);
        usleep(2);

        rxd <<= 1;
        if( XGpioPs_ReadPin(&gpiops_inst, emio_sda) ) {
        	rxd = rxd | 0x01;
        }
		usleep(2);

		XGpioPs_WritePin(&gpiops_inst, emio_scl, 0);
		usleep(4);
    }

	XGpioPs_SetDirectionPin(&gpiops_inst, emio_sda, 1); 
	XGpioPs_SetOutputEnablePin(&gpiops_inst, emio_sda, 1);

    return rxd;

}

void sccb_ack(u8 cam_ch)
{
	u8 emio_scl = 0 ,emio_sda = 0;
    if(cam_ch == 0){
        emio_scl = EMIO_SCL0_NUM;
        emio_sda = EMIO_SDA0_NUM;
    }
    else{
        emio_scl = EMIO_SCL1_NUM;
        emio_sda = EMIO_SDA1_NUM;        
    }
    
	XGpioPs_WritePin(&gpiops_inst, emio_scl, 0);
	XGpioPs_WritePin(&gpiops_inst, emio_sda, 0);

	usleep(4);

	XGpioPs_WritePin(&gpiops_inst, emio_scl, 1);

	usleep(4);

	XGpioPs_WritePin(&gpiops_inst, emio_scl, 0);

	usleep(4);
}

