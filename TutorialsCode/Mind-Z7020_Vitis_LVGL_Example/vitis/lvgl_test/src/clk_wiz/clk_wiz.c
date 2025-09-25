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
bool clk_wiz_cfg(uint32_t clk_device_id, double freq_MHz)
{
	double div_factor = 0;
	uint32_t div_factor_int = 0, div_factor_frac = 0;
	uint32_t clk_divide = 0;
	uint32_t status = 0;

	// Initialize XCLK_Wiz
	XClk_Wiz_Config *clk_cfg_ptr;
	clk_cfg_ptr = XClk_Wiz_LookupConfig(clk_device_id);
	XClk_Wiz_CfgInitialize(&clk_wiz_inst, clk_cfg_ptr, clk_cfg_ptr->BaseAddr);

	if(freq_MHz <= 0) return false;

	// Configure input clock frequency
	XClk_Wiz_WriteReg(clk_cfg_ptr->BaseAddr, CLK_CFG0_OFFSET, 0x00000a01);  //10x input clock frequency
	// Calculate output frequency
	div_factor = CLK_WIZ_IN_FREQ * 10 / freq_MHz;
	div_factor_int = (uint32_t)div_factor;
	div_factor_frac = (uint32_t)((div_factor - div_factor_int) * 1000);
	clk_divide = div_factor_int | (div_factor_frac << 8);

	XClk_Wiz_WriteReg(clk_cfg_ptr->BaseAddr, CLK_CFG2_OFFSET, clk_divide);

    // bit0: SADDR_LOAD, bit1: SEN
	XClk_Wiz_WriteReg(clk_cfg_ptr->BaseAddr, CLK_CFG23_OFFSET, 0x00000003); 

	// Wait for the clock IP to lock
	while(1)
    {
		status = XClk_Wiz_ReadReg(clk_cfg_ptr->BaseAddr,CLK_SR_OFFSET);
		if(status & 0x00000001)    //Bit0 Locked status
        {
            return true;  // Clock is locked, return success
        }
        
        vTaskDelay(1);  // Delay to avoid busy waiting
	}

    return false;
}
