/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */


#include"xgpiops.h"
#include"sleep.h"

#ifndef sccb_EMIO_CFG_
#define sccb_EMIO_CFG_
// PL_KEY: 54/55
// PL_LED: 56/57 
// LCD_BL: 58
// LCD_TP_RESET: 59
// LCD_TP_INT: 60
#define LCD_BLK     (58)

#define EMIO_SCL0_NUM (61)
#define EMIO_SDA0_NUM (62)

#define EMIO_SCL1_NUM (63)
#define EMIO_SDA1_NUM (64)

#define EMIO_BEEP (65)

#define CAM0_CH0      (0)  //CAM0
#define CAM1_CH1      (1)  //CAM1

void emio_init(void);
void sccb_start(u8 cam_ch);
void sccb_stop(u8 cam_ch);
void sccb_ack(u8 cam_ch);
void sccb_send_byte(u8 cam,u8 txd);
u8  sccb_rece_byte(u8 cam);

#endif /* sccb_EMIO_CFG_ */
