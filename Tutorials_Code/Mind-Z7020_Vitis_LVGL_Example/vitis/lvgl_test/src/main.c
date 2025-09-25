/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
/* Xilinx includes. */
#include "xil_printf.h"
#include "xil_cache.h"
#include "xparameters.h"
#include "xscugic.h"

#include "clk_wiz/clk_wiz.h"
#include "xgpiops.h"
#include "xaxivdma.h"
#include "xaxivdma_i.h"
#include "display_ctrl/display_ctrl.h"
#include "vdma/vdma_api.h"

// LVGL
#include "lvgl/lvgl.h"
#include "lv_port_indev_template.h"
#include "lv_port_disp_template.h"
#include "music/lv_demo_music.h"
#include "widgets/lv_demo_widgets.h"


#define INTC_DEVICE_ID	   XPAR_SCUGIC_SINGLE_DEVICE_ID
#define CLK_WIZ_ID         XPAR_CLK_WIZ_0_DEVICE_ID   // clk IP ID
#define VDMA_ID            XPAR_AXIVDMA_1_DEVICE_ID   // VDMA ID
#define DISP_VTC_ID        XPAR_VTC_1_DEVICE_ID       // VTC ID

/*-----------------------------------------------------------*/

static void prvLvglTask( void *pvParameters );
/*-----------------------------------------------------------*/

/* The queue used by the Tx and Rx tasks, as described at the top of this
file. */
static TaskHandle_t xLvglTask;

XScuGic gic_inst;
XAxiVdma     vdma;
DisplayCtrl  disp_ctrl;
VideoMode    vd_mode = VMODE_1024x600;
uint32_t const frame_buffer_addr = (XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x2000000);


static bool SetupInterruptSystem()
{
    XScuGic_Config *gic_config = NULL;
    int32_t Status = XST_FAILURE;

    Xil_ExceptionInit();
    gic_config = XScuGic_LookupConfig(INTC_DEVICE_ID);
    Status = XScuGic_CfgInitialize(&gic_inst, gic_config, gic_config->CpuBaseAddress);
    if (Status != XST_SUCCESS) return XST_FAILURE;

    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT, 
        (Xil_ExceptionHandler)XScuGic_InterruptHandler, &gic_inst);

    Xil_ExceptionEnable();

    return XST_SUCCESS;
}


int main( void )
{
    xil_printf( "Hello from Freertos example main\r\n" );

    SetupInterruptSystem();

    xTaskCreate( prvLvglTask, 					/* The function that implements the task. */
                ( const char * ) "Lvgl", 		/* Text name for the task, provided to assist debugging only. */
                configMINIMAL_STACK_SIZE*50, 	/* The stack allocated to the task. */
                NULL, 						/* The task parameter is not used, so set to NULL. */
                tskIDLE_PRIORITY+1,			/* The task runs at the idle priority. */
                &xLvglTask );


    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
    will never be reached.  If the following line does execute, then there was
    insufficient FreeRTOS heap memory available for the idle and/or timer tasks
    to be created.  See the memory management section on the FreeRTOS web site
    for more details. */
    for( ;; );
}


/*-----------------------------------------------------------*/
static void prvLvglTask( void *pvParameters )
{
    run_vdma_frame_buffer(&vdma, VDMA_ID, vd_mode.width, vd_mode.height,
        frame_buffer_addr,0, 0, READ_ONLY);

    clk_wiz_cfg(CLK_WIZ_ID, vd_mode.freq);
    DisplayInitialize(&disp_ctrl, DISP_VTC_ID);
    DisplaySetMode(&disp_ctrl, &vd_mode);
    DisplayStart(&disp_ctrl);

    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    lv_demo_music();
    // lv_demo_widgets();
    // lv_demo_benchmark();

    while (1)
    {
        lv_task_handler();
        vTaskDelay(10);
    }
}


void vApplicationTickHook()
{
    lv_tick_inc(1); 	// lvgl heartbeat: 1ms
}

