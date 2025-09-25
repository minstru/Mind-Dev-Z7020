/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

/***************************** Include Files *********************************/
#include "xparameters.h"
#include "sleep.h"
#include "xiicps.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include "xplatform_info.h"

/************************** Constant Definitions *****************************/
#define INTC_DEVICE_ID	 XPAR_SCUGIC_SINGLE_DEVICE_ID //interrupt controller device ID
#define I2C0_DEVICE_ID   XPAR_XIICPS_0_DEVICE_ID      //IIC controller 0 device ID
#define I2C0_INT_ID      XPAR_XIICPS_0_INTR           //IIC controller 0 interrupt ID

#define IIC_SCLK_RATE		(100000)                  //IIC clock rate
#define SLV_MON_LOOP_COUNT  (0x0001FFFF)	          //Slave monitor loop counter

//The page size of the onboard e2prom device is 32 bytes
#define PAGE_SIZE_32	        (32)
//The starting word address for read/write tests in the e2prom
#define E2PROM_START_ADDRESS    (0)
#define E2PROM_SLAVE_ADDR       (0x50) //The e2prom slave address

/**************************** Type Definitions *******************************/
typedef u16 AddressType;   //The word address type for the onboard e2prom

/************************** Function Prototypes ******************************/
int IicPsE2promIntrExample(void);
static int E2promWriteData(XIicPs *IicInstance, u16 ByteCount);
static int E2promReadData(XIicPs *IicInstance, u8 *BufferPtr, u16 ByteCount);
static void Handler(void *CallBackRef, u32 Event);
static int IicPsSlaveMonitor(u16 Address, u16 DeviceId, u32 Int_Id);
static int SetupInterruptSystem(XIicPs *IicPsPtr, u32 Int_Id);
static int IicPsFindE2prom(u16 *E2promSlvAddr, u32 *PageSize);
static int IicPsConfig(u16 DeviceId, u32 Int_Id);

/************************** Variable Definitions *****************************/
XIicPs IicInstance;		        //i2c controller instance
XScuGic GicInstance;	        //generic interrupt controller instance

//buffer for writing data to eeprom
u8 WriteBuffer[sizeof(AddressType) + PAGE_SIZE_32];
//buffer for reading data from eeprom
u8 ReadBuffer[PAGE_SIZE_32];

volatile u8 TransmitComplete;	//check transmit complete flag
volatile u8 ReceiveComplete;	//check receive complete flag
volatile u32 TotalErrorCount;	//total error count flag
volatile u32 SlaveResponse;		//slave response flag

u16 E2promSlvAddr;
u32 PageSize;

/************************** Function Definitions *****************************/
int main(void)
{
    int Status;
    int Index;

    xil_printf("IIC EEPROM Interrupt Example Test \r\n");

    Status = IicPsE2promIntrExample();
    if (Status != XST_SUCCESS) {
        xil_printf("IIC EEPROM Interrupt Example Test Failed\r\n");
        return XST_FAILURE;
    }
    xil_printf("Successfully ran IIC EEPROM Interrupt Example Test\r\n");

    for (Index = 0; Index <PageSize; Index++) {
        xil_printf("eeprom word address is %d,Data is %d\r\n",Index, ReadBuffer[Index]);
    }

    return XST_SUCCESS;
}

/*****************************************************************************/
/**
* This function writes, reads, and verifies the data to the IIC EEPROM. It
* does the write as a single page write, performs a buffered read.
*
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
int IicPsE2promIntrExample()
{
    u32 Index;
    int Status;
    AddressType Address = E2PROM_START_ADDRESS;
    int WrBfrOffset;

    IicPsFindE2prom(&E2promSlvAddr, &PageSize);

    // Initialize the data to write and the read buffer.
    WriteBuffer[0] = (u8) (Address >> 8);
    WriteBuffer[1] = (u8) (Address);
    WrBfrOffset = 2;
    for (Index = 0; Index < PageSize; Index++) {
        WriteBuffer[WrBfrOffset + Index] = Index;
        ReadBuffer[Index] = 0;
    }
    // Write to the EEPROM
    Status = E2promWriteData(&IicInstance, WrBfrOffset + PageSize);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }
    // Read from the EEPROM.
    Status = E2promReadData(&IicInstance, ReadBuffer, PageSize);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }
    // Verify the data read against the data written.
    for (Index = 0; Index < PageSize; Index++) {
        if (ReadBuffer[Index] != WriteBuffer[Index + WrBfrOffset]) {
            return XST_FAILURE;
        }
    }
    return XST_SUCCESS;
}


 static int IicPsFindE2prom(u16 *E2promSlvAddr,u32 *PageSize)
{
    int Status;

    Status = IicPsSlaveMonitor(E2PROM_SLAVE_ADDR,I2C0_DEVICE_ID,I2C0_INT_ID);
    if (Status == XST_SUCCESS) {
        *E2promSlvAddr = E2PROM_SLAVE_ADDR;
        *PageSize = PAGE_SIZE_32;
        return XST_SUCCESS;
    }
    return XST_FAILURE;
}

/******************************************************************************/
/**
*
* This function setups the interrupt system such that interrupts can occur
* for the IIC.
*
* @param	IicPsPtr contains a pointer to the instance of the Iic
*		which is going to be connected to the interrupt controller.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None.
*
*******************************************************************************/
static int SetupInterruptSystem(XIicPs *IicPsPtr, u32 Int_Id)
{
    XScuGic_Config *IntcConfig;

    //  Initialize the interrupt controller driver so that it is ready to use
    IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
    XScuGic_CfgInitialize(&GicInstance, IntcConfig,
                IntcConfig->CpuBaseAddress);

    /*
    * Connect the interrupt controller interrupt handler to the hardware
    * interrupt handling logic in the processor.
    */
    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
        (Xil_ExceptionHandler)XScuGic_InterruptHandler,
        &GicInstance);
    Xil_ExceptionEnable();

    /*
    * Connect the device driver handler that will be called when an
    * interrupt for the device occurs, the handler defined above performs
    * the specific interrupt processing for the device.
    */
    XScuGic_Connect(&GicInstance, Int_Id,
        (Xil_InterruptHandler)XIicPs_MasterInterruptHandler,
        (void *)IicPsPtr);

    // Enable the interrupt for the Iic device
    XScuGic_Enable(&GicInstance, Int_Id);
    return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function is the handler which performs processing to handle data events
* from the IIC.  It is called from an interrupt context such that the amount
* of processing performed should be minimized.
*
* This handler provides an example of how to handle data for the IIC and
* is application specific.
*
* @param	CallBackRef contains a callback reference from the driver, in
*		this case it is the instance pointer for the IIC driver.
* @param	Event contains the specific kind of event that has occurred.
* @param	EventData contains the number of bytes sent or received for sent
*		and receive events.
*
* @return	None.
*
* @note		None.
*
*******************************************************************************/
void Handler(void *CallBackRef, u32 Event)
{
    // All of the data transfer has been finished.
    if (0 != (Event & XIICPS_EVENT_COMPLETE_SEND)) {
        TransmitComplete = TRUE;
    } else if (0 != (Event & XIICPS_EVENT_COMPLETE_RECV)){
        ReceiveComplete = TRUE;
    } else if (0 != (Event & XIICPS_EVENT_SLAVE_RDY)) {
        SlaveResponse = TRUE;
    } else if (0 != (Event & XIICPS_EVENT_ERROR)){
        TotalErrorCount++;
    }
}

/*****************************************************************************/
/**
* This function perform the initial configuration for the IICPS Device.
*
* @param	DeviceId instance and Interrupt ID mapped to the device.
*
* @return	XST_SUCCESS if pass, otherwise XST_FAILURE.
*
* @note		None.
*
****************************************************************************/
static int IicPsConfig(u16 DeviceId, u32 Int_Id)
{
    XIicPs_Config *ConfigPtr;

    // Initialize the IIC driver so that it is ready to use.
    ConfigPtr = XIicPs_LookupConfig(DeviceId);
    XIicPs_CfgInitialize(&IicInstance, ConfigPtr,
                    ConfigPtr->BaseAddress);

    // Setup the Interrupt System.
    SetupInterruptSystem(&IicInstance, I2C0_INT_ID);

    /*
    * Setup the handlers for the IIC that will be called from the
    * interrupt context when data has been sent and received, specify a
    * pointer to the IIC driver instance as the callback reference so
    * the handlers are able to access the instance data.
    */
    XIicPs_SetStatusHandler(&IicInstance, (void *) &IicInstance,(XIicPs_IntrHandler) Handler);

    // Set the IIC serial clock rate.
    XIicPs_SetSClk(&IicInstance, IIC_SCLK_RATE);
    return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function checks the availability of a slave using slave monitor mode.
*
* @param	DeviceId is the Device ID of the IicPs Device and is the
*		XPAR_<IICPS_instance>_DEVICE_ID value from xparameters.h
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note 	None.
*
*******************************************************************************/
static int IicPsSlaveMonitor(u16 Address, u16 DeviceId, u32 Int_Id)
{
    u32 Index;
    XIicPs *IicPtr;
    SlaveResponse = FALSE;

    // Initialize the IIC driver so that it is ready to use.
    IicPsConfig(DeviceId,Int_Id);

    IicPtr = &IicInstance;
    XIicPs_DisableAllInterrupts(IicPtr->Config.BaseAddress);
    XIicPs_EnableSlaveMonitor(&IicInstance, Address);

    TotalErrorCount = 0;
    Index = 0;

    /*
    * Wait for the Slave Monitor Interrupt, the interrupt processing
    * works in the background, this function may get locked up in this
    * loop if the interrupts are not working correctly or the slave
    * never responds.
    */
    while ((!SlaveResponse) && (Index < SLV_MON_LOOP_COUNT)) {
        Index++;

        /*
            * Ignore any errors. The hardware generates NACK interrupts
            * if the slave is not present.
            */
        if (0 != TotalErrorCount) {
            xil_printf("Test error unexpected NACK\n");
            return XST_FAILURE;
        }
    }

    if (Index >= SLV_MON_LOOP_COUNT) {
        return XST_FAILURE;
    }
    XIicPs_DisableSlaveMonitor(&IicInstance);
    return XST_SUCCESS;
}

/*****************************************************************************/
/**
* This function writes a buffer of data to the IIC serial EEPROM.
*
* @param	ByteCount contains the number of bytes in the buffer to be
*		written.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		The Byte count should not exceed the page size of the EEPROM as
*		noted by the constant PAGE_SIZE.
*
******************************************************************************/
static int E2promWriteData(XIicPs *IicInstance, u16 ByteCount)
{
    TransmitComplete = FALSE;

    // Send the Data
    XIicPs_MasterSend(IicInstance, WriteBuffer,
                ByteCount, E2promSlvAddr);

    /*
    * Wait for the entire buffer to be sent, letting the interrupt
    * processing work in the background, this function may get
    * locked up in this loop if the interrupts are not working
    * correctly.
    */
    while (TransmitComplete == FALSE) {
        if (0 != TotalErrorCount) {
            return XST_FAILURE;
        }
    }
    // Wait until bus is idle to start another transfer.
    while (XIicPs_BusIsBusy(IicInstance));
    // Wait for a bit of time to allow the programming to complete
    // AT24C64 EEPROM requires a maximum of 10ms between writes.
    usleep(10000);

    return XST_SUCCESS;
}

/*****************************************************************************/
/**
* This function reads data from the IIC serial EEPROM into a specified buffer.
*
* @param	BufferPtr contains the address of the data buffer to be filled.
* @param	ByteCount contains the number of bytes in the buffer to be read.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
static int E2promReadData(XIicPs *IicInstance, u8 *BufferPtr, u16 ByteCount)
{
    AddressType Address = E2PROM_START_ADDRESS;
    int WrBfrOffset;

    // Position the Pointer in EEPROM.
    WriteBuffer[0] = (u8) (Address >> 8);
    WriteBuffer[1] = (u8) (Address);
    WrBfrOffset = 2;

    E2promWriteData(IicInstance, WrBfrOffset);

    ReceiveComplete = FALSE;

    // Receive the Data.
    XIicPs_MasterRecv(IicInstance, BufferPtr,
                ByteCount, E2promSlvAddr);

    while (ReceiveComplete == FALSE) {
        if (0 != TotalErrorCount) {
            return XST_FAILURE;
        }
    }
    // Wait until bus is idle to start another transfer.
    while (XIicPs_BusIsBusy(IicInstance));

    return XST_SUCCESS;
}

