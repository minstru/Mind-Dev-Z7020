/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include "qspi_op.h"



void FlashWrite(XQspiPs *QspiPtr, u32 Address, u32 ByteCount, u8 Command, u8 *wrt_buf)
{
	u8 WriteEnableCmd = { WRITE_ENABLE_CMD };
	u8 ReadStatusCmd[] = { READ_STATUS_CMD, 0 };  /* must send 2 bytes */
	u8 FlashStatus[2];

	/*
	 * Send the write enable command to the FLASH so that it can be
	 * written to, this needs to be sent as a seperate transfer before
	 * the write
	 */
	XQspiPs_PolledTransfer(QspiPtr, &WriteEnableCmd, NULL,
				sizeof(WriteEnableCmd));


	/*
	 * Setup the write command with the specified address and data for the
	 * FLASH
	 */
	*(wrt_buf +COMMAND_OFFSET)   = Command;
	*(wrt_buf + ADDRESS_1_OFFSET) = (u8)((Address & 0xFF0000) >> 16);
	*(wrt_buf + ADDRESS_2_OFFSET) = (u8)((Address & 0xFF00) >> 8);
	*(wrt_buf + ADDRESS_3_OFFSET) = (u8)(Address & 0xFF);

	/*
	 * Send the write command, address, and data to the FLASH to be
	 * written, no receive buffer is specified since there is nothing to
	 * receive
	 */
	XQspiPs_PolledTransfer(QspiPtr, wrt_buf, NULL,
				ByteCount + OVERHEAD_SIZE);

	/*
	 * Wait for the write command to the FLASH to be completed, it takes
	 * some time for the data to be written
	 */
	while (1) {
		/*
		 * Poll the status register of the FLASH to determine when it
		 * completes, by sending a read status command and receiving the
		 * status byte
		 */
		XQspiPs_PolledTransfer(QspiPtr, ReadStatusCmd, FlashStatus,
					sizeof(ReadStatusCmd));

		/*
		 * If the status indicates the write is done, then stop waiting,
		 * if a value of 0xFF in the status byte is read from the
		 * device and this loop never exits, the device slave select is
		 * possibly incorrect such that the device status is not being
		 * read
		 */
		if ((FlashStatus[1] & 0x01) == 0) {
			break;
		}
	}
}
void FlashRead(XQspiPs *QspiPtr, u32 Address, u32 ByteCount, u8 Command, u8 *rd_buf)
{
	/*
	 * Setup the write command with the specified address and data for the
	 * FLASH
	 */
	u8 wrt_cmd[4];
	wrt_cmd[COMMAND_OFFSET]   = Command;
	wrt_cmd[ADDRESS_1_OFFSET] = (u8)((Address & 0xFF0000) >> 16);
	wrt_cmd[ADDRESS_2_OFFSET] = (u8)((Address & 0xFF00) >> 8);
	wrt_cmd[ADDRESS_3_OFFSET] = (u8)(Address & 0xFF);

	if ((Command == FAST_READ_CMD) || (Command == DUAL_READ_CMD) ||
	    (Command == QUAD_READ_CMD)) {
		ByteCount += DUMMY_SIZE;
	}
	/*
	 * Send the read command to the FLASH to read the specified number
	 * of bytes from the FLASH, send the read command and address and
	 * receive the specified number of bytes of data in the data buffer
	 */
	XQspiPs_PolledTransfer(QspiPtr, wrt_cmd, rd_buf,
				ByteCount + OVERHEAD_SIZE);
}

void FlashErase(XQspiPs *QspiPtr, u32 Address, u32 ByteCount)
{
	u8 WriteEnableCmd = { WRITE_ENABLE_CMD };
	u8 ReadStatusCmd[] = { READ_STATUS_CMD, 0 };  /* must send 2 bytes */
	u8 FlashStatus[2];
	u8 wrt_cmd[4];
	int Sector;

	/*
	 * If erase size is same as the total size of the flash, use bulk erase
	 * command
	 */
	if (ByteCount == (NUM_SECTORS * SECTOR_SIZE)) {
		/*
		 * Send the write enable command to the FLASH so that it can be
		 * written to, this needs to be sent as a seperate transfer
		 * before the erase
		 */
		XQspiPs_PolledTransfer(QspiPtr, &WriteEnableCmd, NULL,
				  sizeof(WriteEnableCmd));

		/* Setup the bulk erase command*/
		wrt_cmd[COMMAND_OFFSET]   = BULK_ERASE_CMD;

		/*
		 * Send the bulk erase command; no receive buffer is specified
		 * since there is nothing to receive
		 */
		XQspiPs_PolledTransfer(QspiPtr, wrt_cmd, NULL,
					BULK_ERASE_SIZE);

		/* Wait for the erase command to the FLASH to be completed*/
		while (1) {
			/*
			 * Poll the status register of the device to determine
			 * when it completes, by sending a read status command
			 * and receiving the status byte
			 */
			XQspiPs_PolledTransfer(QspiPtr, ReadStatusCmd,
						FlashStatus,
						sizeof(ReadStatusCmd));

			/*
			 * If the status indicates the write is done, then stop
			 * waiting; if a value of 0xFF in the status byte is
			 * read from the device and this loop never exits, the
			 * device slave select is possibly incorrect such that
			 * the device status is not being read
			 */
			if ((FlashStatus[1] & 0x01) == 0) {
				break;
			}
		}

		return;
	}

	/*
	 * If the erase size is less than the total size of the flash, use
	 * sector erase command
	 */
	for (Sector = 0; Sector < ((ByteCount / SECTOR_SIZE) + 1); Sector++) {
		/*
		 * Send the write enable command to the SEEPOM so that it can be
		 * written to, this needs to be sent as a seperate transfer
		 * before the write
		 */
		XQspiPs_PolledTransfer(QspiPtr, &WriteEnableCmd, NULL,
					sizeof(WriteEnableCmd));

		/*
		 * Setup the write command with the specified address and data
		 * for the FLASH
		 */
		wrt_cmd[COMMAND_OFFSET]   = SEC_ERASE_CMD;
		wrt_cmd[ADDRESS_1_OFFSET] = (u8)(Address >> 16);
		wrt_cmd[ADDRESS_2_OFFSET] = (u8)(Address >> 8);
		wrt_cmd[ADDRESS_3_OFFSET] = (u8)(Address & 0xFF);

		/*
		 * Send the sector erase command and address; no receive buffer
		 * is specified since there is nothing to receive
		 */
		XQspiPs_PolledTransfer(QspiPtr, wrt_cmd, NULL,
					SEC_ERASE_SIZE);

		/*
		 * Wait for the sector erse command to the
		 * FLASH to be completed
		 */
		while (1) {
			/*
			 * Poll the status register of the device to determine
			 * when it completes, by sending a read status command
			 * and receiving the status byte
			 */
			XQspiPs_PolledTransfer(QspiPtr, ReadStatusCmd,
						FlashStatus,
						sizeof(ReadStatusCmd));

			/*
			 * If the status indicates the write is done, then stop
			 * waiting, if a value of 0xFF in the status byte is
			 * read from the device and this loop never exits, the
			 * device slave select is possibly incorrect such that
			 * the device status is not being read
			 */
			if ((FlashStatus[1] & 0x01) == 0) {
				break;
			}
		}

		Address += SECTOR_SIZE;
	}
}

int FlashReadID(XQspiPs *QspiPtr)
{
	int Status;
	u8 wrt_cmd[4];
	u8 rd_buf[RD_ID_SIZE];

	/* Read ID in Auto mode.*/
	wrt_cmd[COMMAND_OFFSET]   = READ_ID;
	wrt_cmd[ADDRESS_1_OFFSET] = 0x23;		/* 3 dummy bytes */
	wrt_cmd[ADDRESS_2_OFFSET] = 0x08;
	wrt_cmd[ADDRESS_3_OFFSET] = 0x09;

	Status = XQspiPs_PolledTransfer(QspiPtr, wrt_cmd, rd_buf,
				RD_ID_SIZE);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	xil_printf("FlashID=0x%x 0x%x 0x%x\n\r", rd_buf[1], rd_buf[2],
		rd_buf[3]);

	return XST_SUCCESS;
}
void FlashQuadEnable(XQspiPs *QspiPtr, u8 ctrl)
{
	u8 WriteEnableCmd = {WRITE_ENABLE_CMD};
	u8 ReadStatusCmd[] = {READ_STATUS_CMD, 0};
	u8 QuadEnableCmd[] = {WRITE_STATUS_CMD, 0};
	u8 FlashStatus[2];


	if (ctrl == 0x9D) {

		XQspiPs_PolledTransfer(QspiPtr, ReadStatusCmd,
					FlashStatus,
					sizeof(ReadStatusCmd));

		QuadEnableCmd[1] = FlashStatus[1] | 1 << 6;

		XQspiPs_PolledTransfer(QspiPtr, &WriteEnableCmd, NULL,
				  sizeof(WriteEnableCmd));

		XQspiPs_PolledTransfer(QspiPtr, QuadEnableCmd, NULL,
					sizeof(QuadEnableCmd));
	}
}

