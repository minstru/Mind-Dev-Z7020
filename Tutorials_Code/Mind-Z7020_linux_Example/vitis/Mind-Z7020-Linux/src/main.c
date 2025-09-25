/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

// main.c
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <termios.h>
#include <errno.h>
#include"main.h"
#include"rtc.h"
#include "gpio.h"
#include "SENSOR/sensor.h"
#include "eeprom.h"
#include "can.h"
#include <pthread.h>
#include "server.h"
#include "client.h"
#include "embedded_cli.h"
#include "serial.h"



int uart_fd = -1;

void cli_task(void *param);
int init_uart(const char *dev_path);


int main()
 {
    pthread_t cli_thread;
    pthread_t tcp_client_thread;
    pthread_t tcp_server_thread1, tcp_server_thread2;
    pthread_t can_tid;
    pthread_t gpio_tid;
    int       port1 = 12345;
    int       port2 = 8;

    // uart_fd = open_serial("/dev/ttyPS1", 115200, 8, 1, 'N');

    // initialize ttyPS1 UART
    if ((uart_fd = init_uart("/dev/ttyPS1")) < 0) {
        printf("Failed to initialize UART.\n");
        return -1;
    }

    write(uart_fd, "start Mind linux APP ...\r\n", 26);

    // 2. tcp client thread
    if (pthread_create(&tcp_client_thread, NULL, client_pthread_func, NULL) != 0) {
        perror("Failed to create TCP client thread");
        return -1;
    }

    // 3. tcp server thread
    if (pthread_create(&tcp_server_thread1, NULL, server_thread_func, &port1) != 0) {
        perror("Failed to create server thread");
        return -1;
    }

    if (pthread_create(&tcp_server_thread2, NULL, server_thread_func, &port2) != 0) {
        perror("Failed to create server thread");
        return -1;
    }
   
    //4.CAN recv pthread
    if (pthread_create(&can_tid, NULL, can_recv_thread, &g_can_handle) != 0) {
        perror("Failed to create server thread");
        return -1;
    }

    //4.gpio recv pthread
    if (pthread_create(&gpio_tid, NULL, gpio_thread, &g_can_handle) != 0) {
        perror("Failed to create server thread");
        return -1;
    }

    // 6. embedded CLI thread
    if (pthread_create(&cli_thread, NULL, cli_task, NULL) != 0) {
        perror("Failed to create CLI thread");
        return -1;
    }
    while (1) {
     
        sleep(1);
    }
    return 0;
}


int init_uart(const char *dev_path)
{
    int fd = -1;
    fd = open(dev_path, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0) 
    {
        perror("open uart");
        return -1;
    }

    if (fcntl(fd, F_SETFL, 0) < 0)  // restore the serial port to the blocked state
    {
        close(fd);
        return -1;
    }

    struct termios tty;
    tcgetattr(fd, &tty);
    tcflush(fd, TCIOFLUSH);

    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);
    // tcsetattr(fd, TCSANOW, &tty);
    // tcflush(fd,TCIOFLUSH);

    // tcgetattr(fd, &tty);

    tty.c_cflag &= ~CSIZE ;
    tty.c_cflag |= CS8;         // 8bit data bits
    tty.c_cflag &= ~PARENB;     // Clear parity enable
    tty.c_iflag &= ~INPCK;      // Enable parity checking
    tty.c_cflag &= ~CSTOPB;     // 1 stop bit

    tty.c_cc[VTIME] = 0;      // unit:100ms
    tty.c_cc[VMIN]  = 0;

    tty.c_lflag &= ~(ECHO | ICANON);

    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_oflag &= ~OPOST;
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);

    tcflush(fd,TCIFLUSH); 
    tcsetattr(fd, TCSANOW, &tty);

    tcflush(fd, TCIOFLUSH);
    return fd;
}
