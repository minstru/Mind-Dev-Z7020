/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */


#ifndef SRC_SDTEST_H_
#define SRC_SDTEST_H_
#include "general.h"


static FATFS fatfs;
int platform_init_fs(uint8_t sd_id);
int sd_mount(uint8_t sd_id);
int sd_write_data(char *file_name, u32 src_addr, u32 byte_len);
int sd_read_data(char *file_name, u32 src_addr, u32 byte_len);
void sd_emmc_test(uint8_t sd_id);
#endif /* SRC_SDTEST_H_ */
    