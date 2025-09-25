/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include "serial.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <termios.h>
#include <errno.h>
//#include <libexplain/tcsetattr.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <fcntl.h>



/**
 * \brief configure serial dev baud rate
*/
bool set_speed(int32_t fd, int32_t speed)
{
    int32_t   status;
    struct termios   Opt;

    tcgetattr(fd, &Opt);

    tcflush(fd, TCIOFLUSH);
    switch( speed )
    {
        case 2400:
            cfsetispeed(&Opt, B2400);
            cfsetospeed(&Opt, B2400);
            break;
        case 4800:
            cfsetispeed(&Opt, B4800);
            cfsetospeed(&Opt, B4800);
            break;
        case 9600:
            cfsetispeed(&Opt, B9600);
            cfsetospeed(&Opt, B9600);
            break;
        case 19200:
            cfsetispeed(&Opt, B19200);
            cfsetospeed(&Opt, B19200);
            break;
        case 38400:
            cfsetispeed(&Opt, B38400);
            cfsetospeed(&Opt, B38400);
            break;
        case 57600:
            cfsetispeed(&Opt, B57600);
            cfsetospeed(&Opt, B57600);
            break;
        case 115200:
            cfsetispeed(&Opt, B115200);
            cfsetospeed(&Opt, B115200);
            break;
        case 230400:
            cfsetispeed(&Opt, B230400);
            cfsetospeed(&Opt, B230400);
            break;
        case 460800:
            cfsetispeed(&Opt, B460800);
            cfsetospeed(&Opt, B460800);
            break;
        case 921600:
            cfsetispeed(&Opt, B921600);
            cfsetospeed(&Opt, B921600);
            break;
        default:
            cfsetispeed(&Opt, B19200);
            cfsetospeed(&Opt, B19200);
            break;
	}
    status = tcsetattr(fd, TCSANOW, &Opt);

    if (status != 0)
    {
        return false;
    }
    tcflush(fd,TCIOFLUSH);
    return true;
}


/**
 * \brief configure serial dev parity
 * \note  databits - 7 or 8; stopbits - 1 or 2; parity - N,E,O,S
*/
bool set_parity(int32_t fd, int32_t databits, int32_t stopbits, int32_t parity)
{
    struct termios options;
    if ( tcgetattr(fd, &options) != 0)
    {
        return(false);
    }
    //cfmakeraw(&options);        // configured in raw mode: no need to press Enter or terminator to receive data
    options.c_cflag &= ~CSIZE ;
    switch (databits)
    {
        case 7:
            options.c_cflag |= CS7;
            break;
        case 8:
        default:
            options.c_cflag |= CS8;
            break;
    }

    switch (parity)
    {
        case 'o':
        case 'O':
            options.c_cflag |= (PARODD | PARENB);   // even check for parity
            options.c_iflag |= INPCK;               // Disnable parity checking
            break;
        case 'e':
        case 'E':
            options.c_cflag |= PARENB;          // Enable parity
            options.c_cflag &= ~PARODD;         // odd check for parity
            options.c_iflag |= INPCK;           // Disnable parity checking
            break;
        case 'S':
        case 's':  // as no parity
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;
            break;
        case 'n':
        case 'N':
        default:
            options.c_cflag &= ~PARENB;     // Clear parity enable
            options.c_iflag &= ~INPCK;      // Enable parity checking
            break;
    }

    switch (stopbits)
    {
        case 2:
            options.c_cflag |= CSTOPB;
            break;
        case 1:
        default:
            options.c_cflag &= ~CSTOPB;
            break;
    }

    options.c_cc[VTIME] = 0;      // unit:100ms
    options.c_cc[VMIN]  = 0;

    options.c_lflag &= ~(ECHO | ICANON);

    options.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    options.c_oflag &= ~OPOST;
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);

    tcflush(fd,TCIFLUSH);           // Update the options and do it NOW
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        return (false);
    }
    return (true);
}

/**
 * \brief open serial dev
*/
int32_t open_serial(char *dev, int32_t speed, int32_t databits, int32_t stopbits, int32_t parity)
{
    int32_t fd = -1;
    fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0)
    {
        return -1;
    }

    if (fcntl(fd, F_SETFL, 0) < 0)  // restore the serial port to the blocked state
    {
        close(fd);
        return -1;
    }

	if(!set_speed(fd, speed))
    {
        close();
        return -1;
	}
	if(!set_parity(fd, databits, stopbits, parity))
    {
        close();
        return -1;
	}
    // sleep(2);   // note: linux bug? must sleep for a while,then tcflush to work
    tcflush(fd, TCIOFLUSH);

    return fd;
}

/**
 * \brief read data from serial dev
*/
int32_t read_serial(int32_t fd, uint8_t *buf, int32_t size)
{
    int32_t total_cnt = 0, rec_cnt = 0, retval = 0;
    struct timeval tv;
    fd_set rfds;

    if (fd < 0) return 0;

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    // must set tv again
    tv.tv_sec = 0;
    tv.tv_usec = 10000;
    retval = select(fd + 1, &rfds, NULL, NULL, &tv);
    if (retval != 0)
    {
        return read(fd, buf, size);
    }
    else
    {
        return 0;
    }
}


/**
 * \brief write data to serial dev
*/
int32_t write_serial(int32_t fd, const uint8_t *buf, int32_t size)
{
    int32_t ret = 0, wr_sz = 0, sz_to_wr = 0;

    if (fd < 0) return -1;

    sz_to_wr = size;

__wloop:
    ret = write(fd, buf + wr_sz, sz_to_wr);

    if (ret >= 0 && (ret != sz_to_wr))
    {
    	wr_sz += ret;
    	sz_to_wr -= ret;
        goto __wloop;
    }

    if (ret >= 0)
    {
    	wr_sz += ret;
    }
    else
    {
    	wr_sz = ret;
    }
    
	return wr_sz;
}


/**
 * \brief flush serial dev
*/
void flush_serial(int32_t fd)
{
    if(fd >= 0)
    {
        tcflush(fd,TCIOFLUSH);
    }
}


/**
 * \brief close serial dev
*/
int32_t close_serial(int32_t fd)
{
    int32_t ret = 0;
    if(fd >= 0)
    {
        ret = close(fd);
    }
    return ret;
}




