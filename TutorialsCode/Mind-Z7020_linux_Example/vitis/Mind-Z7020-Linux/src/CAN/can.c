/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include "can.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

bool can_is_up = false;
volatile bool can_send_active = false;
volatile bool can_recv_thread_running = false;
volatile bool can_rcv_status=false;
uint8_t can_send_buf[CAN_DATA_LEN] = {0};
uint8_t can_send_len = 0;

uint8_t can_rcv_buf[CAN_DATA_LEN];
uint8_t can_rcv_len;

uint32_t can_baud_rate = 166667;
uint8_t can_mode = 0;   // 0: normal mode, 1: loopback mode

CAN_Handle_t g_can_handle = {
    .sockfd = -1,
    .ifname = {0}
};

bool can_set_baud_mode(uint32_t baud, uint8_t mode)
{
    can_baud_rate = baud;
    can_mode = mode;
}

bool can_open(CAN_Handle_t *h, const char *ifname)
{
    uint8_t cmd_cfg[64];
    int ret = -1;

    can_close(h);
    can_is_up = false;
    can_send_active = false;
    can_rcv_status = false;

    sprintf(cmd_cfg, "ip link set can0 type can bitrate %d loopback %s", 
        can_baud_rate, (can_mode == 0) ?"off":"on");
    ret = system(cmd_cfg);

    if (ret != -1)
    {
        ret = system("ip link set can0 up");
    }

    if (ret == -1) 
    {
        perror("open can interface failed");
        return false;
    }

    struct ifreq ifr;
    struct sockaddr_can addr;

    if (!h || !ifname) return false;

    h->sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (h->sockfd < 0) 
    {
        perror("socket(PF_CAN)");
        return false;
    }

    strncpy(h->ifname, ifname, sizeof(h->ifname) - 1);

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name) - 1);
    if (ioctl(h->sockfd, SIOCGIFINDEX, &ifr) < 0) 
    {
        perror("ioctl(SIOCGIFINDEX)");
        close(h->sockfd);
        h->sockfd = -1;
        return false;
    }

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(h->sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    {
        perror("bind");
        close(h->sockfd);
        h->sockfd = -1;
        return false;
    }

    can_is_up = true;
    can_send_active = false;
    can_rcv_status = false;
    return true;
}

void can_close(CAN_Handle_t *h)
{
    const char *cmd = {"ip link set can0 down"};
    int ret = system(cmd);
    if (ret == -1)
    {
        perror("system");
    }

    if (h && h->sockfd >= 0)
    {
        close(h->sockfd);
        h->sockfd= -1;
    }
}


bool can_send(CAN_Handle_t *h, uint32_t can_id, const uint8_t *data, uint8_t len)
{
    struct can_frame frame;

    if (!can_is_up)
    {
        return false;
    }

    if (!h || h->sockfd < 0 || len > 8) return false;

    memset(&frame, 0, sizeof(frame));
    frame.can_id = can_id;
    frame.can_dlc = len;
    memcpy(frame.data, data, len);

    int nbytes = write(h->sockfd, &frame, sizeof(frame));
    if (nbytes != sizeof(frame)) 
    {
        perror("write(CAN)");
        return false;
    }
    return true;
}

bool can_recv(CAN_Handle_t *h, uint32_t *can_id, uint8_t *data, uint8_t *len)
{
    struct can_frame frame;
    int nbytes;

    if (!h || h->sockfd < 0) return false;

    nbytes = read(h->sockfd, &frame, sizeof(frame));
    if (nbytes <= 0) 
    {
        perror("read(CAN)");
        return false;
    }

    if (can_id) *can_id = frame.can_id;
    if (len) *len = frame.can_dlc;
    if (data) memcpy(data, frame.data, frame.can_dlc);

    return true;
}


void *can_recv_thread(void *arg)
{
    CAN_Handle_t *h = (CAN_Handle_t *)arg;
    uint32_t id = 0;

    while (1) 
    {
        if (can_is_up && (can_recv(h, &id, can_rcv_buf, &can_rcv_len) > 0)) 
        {
            printf("Received CAN frame: ID=0x%X, Data=", id);
            for (int i = 0; i < can_rcv_len; i++) 
            {
                printf("%02X ", can_rcv_buf[i]);
            }
            can_rcv_status = true;
            printf("\n");
        } 
        else 
        {
            usleep(1000);
        }
    }

    printf("CAN receive thread exiting.\n");
    return NULL;
}

bool get_can_rcv_status()
{
    return can_rcv_status;
}

void clear_can_rcv_status()
{
    can_rcv_status = false;
}




