/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */


#include "SDtest.h"
#include "ff.h"
#define SD_TEST

const char *sd_path[] = {"0:/", "1:/"};
const char *file_name[] = {"0:/test.txt", "1:/test.txt"};

const char src_str[30] = "this is a test string!";

//Initialize file system
int platform_init_fs(uint8_t sd_id)
{
    FRESULT status;

    BYTE work[FF_MAX_SS];

    status = f_mount (&fatfs, sd_path[sd_id], 1 );
    if (status != FR_OK)
    {
        xil_printf("Volume is not FAT formated; formating FAT\r\n");

        status = f_mkfs(sd_path[sd_id], FM_FAT32, 0, work, sizeof work);
        if (status != FR_OK)
        {
            xil_printf("Unable to format FATfs\r\n");
            return -1;
        }

        status = f_mount(&fatfs, sd_path[sd_id], 1);
        if (status != FR_OK)
        {
            xil_printf("Unable to mount FATfs\r\n" );
            return -1;
        }
    }
    return 0;
}


//Mount SD (TF) card
int sd_mount(uint8_t sd_id)
{
    FRESULT status;

    status = platform_init_fs(sd_id);
    if (status)
    {
        xil_printf("ERROR: f_mount returned %d!\n", status);
        return XST_FAILURE;
    }
    return XST_SUCCESS;
}

//SD card write data
int sd_write_data(char *file_name, u32 src_addr, u32 byte_len)
{
    FIL fil;
    UINT bw;

    f_open(&fil, file_name, FA_CREATE_ALWAYS | FA_WRITE);
    f_lseek(&fil, 0);
    f_write(&fil, (void *)src_addr, byte_len, &bw);
    f_close(&fil);
    return 0;
}

//SD card Read data
int sd_read_data(char *file_name, u32 src_addr, u32 byte_len)
{
    FIL fil;
    UINT br;

    f_open(&fil, file_name, FA_READ);
    f_lseek(&fil, 0);
    f_read(&fil, (void *)src_addr, byte_len, &br);
    f_close(&fil);
    return 0;
}

void sd_emmc_test(uint8_t sd_id)
{
    int status, len;
    char dest_str[30] = "";

    if (sd_id == 0)
    {
        xil_printf("Start to test TF card...\r\n");
    }
    else
    {
        xil_printf("Start to test eMMC...\r\n");
    }

    status = sd_mount(sd_id);
    if(status != XST_SUCCESS )
    {
        xil_printf("Failed to open %s!\r\n", (sd_id == 0) ? "TF Card" : "eMMC");
        return 0;
    }
    else
        xil_printf("Success to open %s!\r\n", (sd_id == 0) ? "TF Card" : "eMMC");

    len = strlen(src_str );
    sd_write_data(file_name[sd_id],(u32)src_str, len );
    sd_read_data(file_name[sd_id],(u32)dest_str, len );

    if (strcmp(src_str, dest_str) == 0)
    {
        xil_printf("%s test success!\r\n", (sd_id == 0) ? "TF Card" : "eMMC");
    }
    else
    {
        xil_printf("%s test failed!\r\n", (sd_id == 0) ? "TF Card" : "eMMC");
    }
}
