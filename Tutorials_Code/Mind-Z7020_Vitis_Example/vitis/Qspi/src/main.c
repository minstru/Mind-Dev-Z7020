/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include "xparameters.h"    /* SDK generated parameters */
#include "xqspips.h"        /* QSPI device driver */
#include "xil_printf.h"
#include "qspi_op.h"

#define QSPI_DEVICE_ID      XPAR_XQSPIPS_0_DEVICE_ID

XQspiPs QspiInstance;

/*
 * The following variable allows a test value to be added to the values that
 * are written to the FLASH such that unique values can be generated to
 * guarantee the writes to the FLASH were successful
 */
int Test = 5;

u8 ReadBuffer[MAX_DATA + DATA_OFFSET + DUMMY_SIZE];
u8 WriteBuffer[PAGE_SIZE + DATA_OFFSET];

int main(void)
{
    int Status;
    u8 *BufferPtr;
    u8 UniqueValue = UNIQUE_VALUE;
    int Count;
    int Page;
    XQspiPs_Config *QspiConfig;

    xil_printf("QSPI Flash Polled Example Test \r\n");

    // initialize the QSPI device
    QspiConfig = XQspiPs_LookupConfig(QSPI_DEVICE_ID);
    XQspiPs_CfgInitialize(&QspiInstance, QspiConfig, QspiConfig->BaseAddress);

    // initialize read/write BUFFER
    for (Count = 0; Count < PAGE_SIZE; Count++, UniqueValue++) 
    {
        WriteBuffer[DATA_OFFSET + Count] = (u8)(UniqueValue + Test);
    }
    memset(ReadBuffer, 0x00, sizeof(ReadBuffer));

    XQspiPs_SetOptions(&QspiInstance, XQSPIPS_MANUAL_START_OPTION |
            XQSPIPS_FORCE_SSELECT_OPTION |
            XQSPIPS_HOLD_B_DRIVE_OPTION);
    // set QSPI clock prescaler
    XQspiPs_SetClkPrescaler(&QspiInstance, XQSPIPS_CLK_PRESCALE_8);
    // set slave select
    XQspiPs_SetSlaveSelect(&QspiInstance);
    // read Flash ID
    FlashReadID(&QspiInstance);
    // enable Flash Quad mode
    FlashQuadEnable(&QspiInstance, 0);
    // erase Flash
    FlashErase(&QspiInstance, TEST_ADDRESS, MAX_DATA);

    // write data to Flash
    for (Page = 0; Page < PAGE_COUNT; Page++) 
    {
        FlashWrite(&QspiInstance, (Page * PAGE_SIZE) + TEST_ADDRESS, PAGE_SIZE, WRITE_CMD, WriteBuffer);

        // read data from Flash using QUAD mode
        FlashRead(&QspiInstance, (Page * PAGE_SIZE) + TEST_ADDRESS, PAGE_SIZE, QUAD_READ_CMD, ReadBuffer);

        // compare written data with read data from Flash
        BufferPtr = &ReadBuffer[DATA_OFFSET + DUMMY_SIZE];
        UniqueValue = UNIQUE_VALUE;
        for (Count = 0; Count < PAGE_SIZE; Count++, UniqueValue++) 
        {
            if (BufferPtr[Count] != (u8)(UniqueValue + Test)) {
                xil_printf("failed to run QSPI Flash Polled Example Test\r\n");
                return XST_FAILURE;
            }
        }
    }
    

    xil_printf("Successfully ran QSPI Flash Polled Example Test\r\n");
    return XST_SUCCESS;
}

