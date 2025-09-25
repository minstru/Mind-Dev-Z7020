/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include <stdbool.h>
#include "xparameters.h"
#include "xclk_wiz.h"
#include "clk_wiz.h"


#define CLK_WIZ_IN_FREQ     100 // MHz

XClk_Wiz clk_wiz_inst;

// clk_device_id: clk_wiz IP device ID
// freq: the target frequency to set, in MHz
// This function configures the clock wizard to generate a specific frequency.
// The input frequency is assumed to be 100 MHz, and the output frequency is set by
// calculating the division factor based on the desired frequency.
// The function waits until the clock is locked before returning.
// Note: The CLK_CFG0_OFFSET, CLK_CFG2_OFFSET, and CLK_CFG23_OFFSET
// offsets are specific to the clock wizard IP and may vary based on the design.
// Make sure to adjust these offsets if your design uses different ones.
// It will block until the clock is locked.
// If the input frequency is less than or equal to zero, the function returns immediately without making

bool clk_wiz_cfg(uint32_t clk_device_id, double freq_MHz, double freq2_MHz)
{
    double div_factor = 0;
    uint32_t div_factor_int = 0, div_factor_frac = 0;
    uint32_t clk_divide = 0;
    uint32_t status = 0;

    // init XCLK_Wiz
    XClk_Wiz_Config *clk_cfg_ptr;
    clk_cfg_ptr = XClk_Wiz_LookupConfig(clk_device_id);
    XClk_Wiz_CfgInitialize(&clk_wiz_inst, clk_cfg_ptr, clk_cfg_ptr->BaseAddr);

    if (freq_MHz <= 0) return false;
    // config to 10X
    XClk_Wiz_WriteReg(clk_cfg_ptr->BaseAddr, CLK_CFG0_OFFSET, 0x00000a01);

    // ===== config clockout1 =====
    div_factor = CLK_WIZ_IN_FREQ * 10 / freq_MHz;
    div_factor_int = (uint32_t)div_factor;
    div_factor_frac = (uint32_t)((div_factor - div_factor_int) * 1000);
    clk_divide = div_factor_int | (div_factor_frac << 8);
    XClk_Wiz_WriteReg(clk_cfg_ptr->BaseAddr, CLK_CFG2_OFFSET, clk_divide);

    // ===== config clockout2 =====
    if (freq2_MHz > 0)
    {
        double div_factor2 = CLK_WIZ_IN_FREQ * 10 / freq2_MHz;
        uint32_t div_factor2_int = (uint32_t)div_factor2;
        uint32_t div_factor2_frac = (uint32_t)((div_factor2 - div_factor2_int) * 1000);
        uint32_t clk_divide2 = div_factor2_int | (div_factor2_frac << 8);
        XClk_Wiz_WriteReg(clk_cfg_ptr->BaseAddr, CLK_CFG3_OFFSET, clk_divide2);
    }

    // update
    XClk_Wiz_WriteReg(clk_cfg_ptr->BaseAddr, CLK_CFG23_OFFSET, 0x00000003);

    // wait for lock
    while (1)
    {
        status = XClk_Wiz_ReadReg(clk_cfg_ptr->BaseAddr, CLK_SR_OFFSET);
        if (status & 0x00000001) // Bit0 Locked
            return true;

        usleep(1000);
    }

    return false;
}

