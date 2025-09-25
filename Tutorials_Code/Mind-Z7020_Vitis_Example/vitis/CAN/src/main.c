/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */


#include "xparameters.h"
#include "xcanps.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include "xscugic.h"

#define CAN_DEVICE_ID      XPAR_XCANPS_0_DEVICE_ID
#define INTC_DEVICE_ID     XPAR_SCUGIC_SINGLE_DEVICE_ID
#define CAN_INTR_ID        XPAR_XCANPS_0_INTR

#define TEST_MESSAGE_ID            2000
#define FRAME_DATA_LENGTH          8
#define TEST_BTR_SYNCJUMPWIDTH     3
#define TEST_BTR_SECOND_TIMESEGMENT 2
#define TEST_BTR_FIRST_TIMESEGMENT 15
#define TEST_BRPR_BAUD_PRESCALAR   29

static XCanPs Can;
static XScuGic Intc;
static u32 RxFrame[XCANPS_MAX_FRAME_SIZE / sizeof(u32)];
static u32 TxFrame[XCANPS_MAX_FRAME_SIZE / sizeof(u32)];
static volatile int SendDone = FALSE;
static volatile int LoopbackError = FALSE;
static volatile int RecvDone = FALSE;


void CanRecvHandler(void *CallBackRef);
void CanSendHandler(void *CallBackRef);
void CanErrorHandler(void *CallBackRef, u32 ErrorMask);
void CanEventHandler(void *CallBackRef, u32 Mask);

static void CanConfig(XCanPs *InstancePtr);
static int SetupInterruptSystem(XScuGic *IntcInstancePtr, XCanPs *CanInstancePtr, u16 CanIntrId);
static void SendFrame(XCanPs *InstancePtr);

int main(void)
{
    xil_printf("CAN Echo Node Started\r\n");

    int Status;
    XCanPs_Config *ConfigPtr;

    ConfigPtr = XCanPs_LookupConfig(CAN_DEVICE_ID);
    if (NULL == ConfigPtr)
        return XST_FAILURE;

    Status = XCanPs_CfgInitialize(&Can, ConfigPtr, ConfigPtr->BaseAddr);
    if (Status != XST_SUCCESS)
        return XST_FAILURE;


    Status = XCanPs_SelfTest(&Can);
    if (Status != XST_SUCCESS)
        return XST_FAILURE;

    CanConfig(&Can);

    XCanPs_SetHandler(&Can, XCANPS_HANDLER_RECV, CanRecvHandler, &Can);
    XCanPs_SetHandler(&Can, XCANPS_HANDLER_SEND, CanSendHandler, &Can);
    XCanPs_SetHandler(&Can, XCANPS_HANDLER_ERROR, CanErrorHandler, &Can);
    XCanPs_SetHandler(&Can, XCANPS_HANDLER_EVENT, CanEventHandler, &Can);

    Status = SetupInterruptSystem(&Intc, &Can, CAN_INTR_ID);
    if (Status != XST_SUCCESS)
        return XST_FAILURE;

    XCanPs_IntrEnable(&Can, XCANPS_IXR_ALL);

    // XCanPs_EnterMode(&Can, XCANPS_MODE_NORMAL);     // normal mode
    // while (XCanPs_GetMode(&Can) != XCANPS_MODE_NORMAL);
    XCanPs_EnterMode(&Can, XCANPS_MODE_LOOPBACK); // loopback mode
    while (XCanPs_GetMode(&Can) != XCANPS_MODE_LOOPBACK);

    xil_printf("CAN Ready. Waiting for frames...\r\n");

    while (1) {
        RecvDone = FALSE;
        LoopbackError = FALSE;
        SendDone = FALSE;
        SendFrame(&Can);
        // wait until sending have been completed
        while ((SendDone != TRUE) && (RecvDone != TRUE));

        if (LoopbackError == TRUE)
        {
            xil_printf("CAN loopback error!\r\n");
        }
        else
        {
            xil_printf("CAN loopback success!\r\n");
        }
    }

    return 0;
}

static void SendFrame(XCanPs *InstancePtr)
{
	u8 *FramePtr;
	int Index;
	int Status;

	/*
	 * Create correct values for Identifier and Data Length Code Register.
	 */
	TxFrame[0] = (u32)XCanPs_CreateIdValue((u32)TEST_MESSAGE_ID, 0, 0, 0, 0);
	TxFrame[1] = (u32)XCanPs_CreateDlcValue((u32)FRAME_DATA_LENGTH);

	/*
	 * Now fill in the data field with known values so we can verify them
	 * on receive.
	 */
	FramePtr = (u8 *)(&TxFrame[2]);
	for (Index = 0; Index < FRAME_DATA_LENGTH; Index++) {
		*FramePtr++ = (u8)Index;
	}

	/*
	 * Now wait until the TX FIFO is not full and send the frame.
	 */
	while (XCanPs_IsTxFifoFull(InstancePtr) == TRUE);

	Status = XCanPs_Send(InstancePtr, TxFrame);
	if (Status != XST_SUCCESS) {
		/*
		 * The frame could not be sent successfully.
		 */
		SendDone = TRUE;
	}
}

void CanRecvHandler(void *CallBackRef)
{
    XCanPs *InstancePtr = (XCanPs *)CallBackRef;
    u8 *FramePtr;
    int i;
    int Index;

    if (XCanPs_Recv(InstancePtr, RxFrame) != XST_SUCCESS)
        return;

    /*
    * Verify Identifier and Data Length Code.
    */
    if (RxFrame[0] != (u32)XCanPs_CreateIdValue((u32)TEST_MESSAGE_ID, 0, 0, 0, 0)) {
        LoopbackError = TRUE;
        RecvDone = TRUE;
        return;
    }

    if ((RxFrame[1] & ~XCANPS_DLCR_TIMESTAMP_MASK) != TxFrame[1]) {
        LoopbackError = TRUE;
        RecvDone = TRUE;
        return;
    }

    /*
        * Verify the Data field contents.
        */
    FramePtr = (u8 *)(&RxFrame[2]);
    for (Index = 0; Index < FRAME_DATA_LENGTH; Index++) {
        if (*FramePtr++ != (u8)Index) {
            LoopbackError = TRUE;
            break;
        }
    }

    RecvDone = TRUE;
}

void CanSendHandler(void *CallBackRef)
{
    SendDone = 1;
    xil_printf("CAN frame echoed back successfully.\r\n");
}

void CanErrorHandler(void *CallBackRef, u32 ErrorMask)
{
    xil_printf("CAN error occurred: 0x%08X\r\n", ErrorMask);
}

void CanEventHandler(void *CallBackRef, u32 IntrMask)
{
    xil_printf("CAN event occurred: 0x%08X\r\n", IntrMask);
}

static void CanConfig(XCanPs *InstancePtr)
{
    XCanPs_EnterMode(InstancePtr, XCANPS_MODE_CONFIG);
    while (XCanPs_GetMode(InstancePtr) != XCANPS_MODE_CONFIG);

    XCanPs_SetBaudRatePrescaler(InstancePtr, TEST_BRPR_BAUD_PRESCALAR);
    XCanPs_SetBitTiming(InstancePtr, TEST_BTR_SYNCJUMPWIDTH,
                        TEST_BTR_SECOND_TIMESEGMENT,
                        TEST_BTR_FIRST_TIMESEGMENT);
}

static int SetupInterruptSystem(XScuGic *IntcInstancePtr, XCanPs *CanInstancePtr, u16 CanIntrId)
{
    XScuGic_Config *IntcConfig;
    int Status;

    Xil_ExceptionInit();

    IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
    if (IntcConfig == NULL)
        return XST_FAILURE;

    Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig, IntcConfig->CpuBaseAddress);
    if (Status != XST_SUCCESS)
        return XST_FAILURE;

    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
                                 (Xil_ExceptionHandler)XScuGic_InterruptHandler,
                                 IntcInstancePtr);
    XScuGic_Connect(IntcInstancePtr, CanIntrId,
                    (Xil_InterruptHandler)XCanPs_IntrHandler,
                    (void *)CanInstancePtr);

    XScuGic_Enable(IntcInstancePtr, CanIntrId);
    Xil_ExceptionEnable();

    return XST_SUCCESS;
}






