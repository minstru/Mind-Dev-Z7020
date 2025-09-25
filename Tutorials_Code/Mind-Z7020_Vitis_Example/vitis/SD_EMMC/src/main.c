/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */


#include "general.h"
#include "SDtest.h"

int main()
{
    init_platform();

    sd_emmc_test(0);    // sd0
    sd_emmc_test(1);    // sd1

    cleanup_platform();
    return 0;
}
