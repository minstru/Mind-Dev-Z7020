/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#ifndef _CAN_H_
#define _CAN_H_

#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

#define CAN_DEV "can0"
//#define CAN_ID 0x123
#define CAN_DATA_LEN 8

#define CAN_SEND_ID 0x7D0


typedef struct {
    int sockfd;
    char ifname[16];
} CAN_Handle_t;


extern bool can_is_up;
extern volatile bool can_send_active;
extern volatile bool can_rcv_status; // if true, recieved new data
extern uint8_t can_send_buf[CAN_DATA_LEN];
extern uint8_t can_send_len;
extern uint8_t can_rcv_buf[CAN_DATA_LEN];
extern uint8_t can_rcv_len;
extern CAN_Handle_t g_can_handle;
extern uint32_t can_baud_rate;
extern uint8_t can_mode;   // 0: normal mode, 1: loopback mode


// 初始化与关闭
bool can_open(CAN_Handle_t *h, const char *ifname);
void can_close(CAN_Handle_t *h);

// 发送/接收
bool can_send(CAN_Handle_t *h, uint32_t can_id, const uint8_t *data, uint8_t len);
bool can_recv(CAN_Handle_t *h, uint32_t *can_id, uint8_t *data, uint8_t *len);

// 线程函数
//void *can_send_thread(void *arg);
void *can_recv_thread(void *arg);

// 测试函数
//void test(void);

#endif //_CAN_H_

