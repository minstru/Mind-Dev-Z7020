/******************************************************************************
* Copyright (c) 2012 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file qspi.h
*
* This file contains the interface for the QSPI FLASH functionality
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver	Who	Date		Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a ecm	01/10/10 Initial release
* 3.00a mb	01/09/12  Added the Delay Values defines for qspi
* 5.00a sgd	05/17/13 Added Flash Size > 128Mbit support
* 					 Dual Stack support
* 6.00a bsv	09/04/20 Added support for 2Gb flash parts
* </pre>
*
* @note
*
******************************************************************************/
#ifndef ___QSPI_H___
#define ___QSPI_H___

#ifdef __cplusplus
extern "C" {
#endif

#include "xparameters.h"    /* SDK generated parameters */
#include "xqspips.h"        /* QSPI device driver */
#include "xil_printf.h"




#define WRITE_STATUS_CMD    0x01
#define WRITE_CMD           0x02
#define READ_CMD            0x03
#define WRITE_DISABLE_CMD   0x04
#define READ_STATUS_CMD     0x05
#define WRITE_ENABLE_CMD    0x06
#define FAST_READ_CMD       0x0B
#define DUAL_READ_CMD       0x3B
#define QUAD_READ_CMD       0x6B
#define BULK_ERASE_CMD      0xC7
#define SEC_ERASE_CMD       0xD8
#define READ_ID             0x9F


#define COMMAND_OFFSET      0 // Flash instruction
#define ADDRESS_1_OFFSET    1 // MSB byte of address to read or write
#define ADDRESS_2_OFFSET    2 // Middle byte of address to read or write
#define ADDRESS_3_OFFSET    3 // LSB byte of address to read or write
#define DATA_OFFSET         4 // Start of Data for Read/Write
#define DUMMY_OFFSET        4 // Dummy byte offset for reads

#define DUMMY_SIZE          1 // Number of dummy bytes for reads
#define RD_ID_SIZE          4 // Read ID command + 3 bytes ID response
#define BULK_ERASE_SIZE     1 // Bulk Erase command size
#define SEC_ERASE_SIZE      4 // Sector Erase command + Sector address

#define OVERHEAD_SIZE       4 // control information: command and address

#define SECTOR_SIZE         0x10000
#define NUM_SECTORS         0x100
#define NUM_PAGES           0x10000
#define PAGE_SIZE           256

/* Number of Flash pages to be written.*/
#define PAGE_COUNT      1

/* Flash address to which data is to be written.*/
#define TEST_ADDRESS    0x00055000
#define UNIQUE_VALUE    0x05

#define MAX_DATA        (PAGE_COUNT * PAGE_SIZE)

void FlashErase(XQspiPs *QspiPtr, u32 Address, u32 ByteCount);
void FlashWrite(XQspiPs *QspiPtr, u32 Address, u32 ByteCount, u8 Command, u8 *wrt_buf);
void FlashRead(XQspiPs *QspiPtr, u32 Address, u32 ByteCount, u8 Command, u8 *rd_buf);
int  FlashReadID(XQspiPs *QspiPtr);
void FlashQuadEnable(XQspiPs *QspiPtr, u8 ctrl);


#ifdef __cplusplus
}
#endif


#endif /* ___QSPI_H___ */

