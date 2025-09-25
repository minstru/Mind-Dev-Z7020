/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp_template.h"
#include <stdbool.h>

// add by mind
#include "xparameters.h"
#include "xaxivdma.h"
#include "xaxivdma_i.h"
#include "xdmaps.h"
#include "xscugic.h"
#include "xdma/xdma_api.h"
#include "display_ctrl/vga_modes.h"

/*********************
 *      DEFINES
 *********************/
#ifndef MY_DISP_HOR_RES
    // #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen width, default value 320 is used for now.
    #define MY_DISP_HOR_RES    1024     // modifid by mind
#endif

#ifndef MY_DISP_VER_RES
    // #warning Please define or replace the macro MY_DISP_VER_RES with the actual screen height, default value 240 is used for now.
    #define MY_DISP_VER_RES    600      // modifid by mind
#endif

#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB888)) /*will be 3 for RGB888 */

// add by mind
#define DMA_DEVICE_ID 			(XPAR_XDMAPS_1_DEVICE_ID)
#define DMA_TOTAL_LEN	        (MY_DISP_HOR_RES * (MY_DISP_VER_RES) * BYTE_PER_PIXEL)  // in bytes

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);

/**********************
 *  STATIC VARIABLES
 **********************/
// add by mind
extern uint32_t const frame_buffer_addr;
uint8_t frame_index=0;
extern VideoMode    vd_mode;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    LV_ASSERT(vd_mode.width == MY_DISP_HOR_RES);
    LV_ASSERT(vd_mode.height == MY_DISP_VER_RES);

    /*------------------------------------
     * Create a display and set a flush_cb
     * -----------------------------------*/
    lv_display_t * disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_flush_cb(disp, disp_flush);

    /* Example 1
     * One buffer for partial rendering*/
    // LV_ATTRIBUTE_MEM_ALIGN
    // static uint8_t buf_1_1[MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL];            /*A buffer for 10 rows*/
    // lv_display_set_buffers(disp, buf_1_1, NULL, sizeof(buf_1_1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    /* Example 2
     * Two buffers for partial rendering
     * In flush_cb DMA or similar hardware should be used to update the display in the background.*/
    // LV_ATTRIBUTE_MEM_ALIGN
    // static uint8_t buf_2_1[MY_DISP_HOR_RES * 10 * BYTE_PER_PIXEL];

    // LV_ATTRIBUTE_MEM_ALIGN
    // static uint8_t buf_2_2[MY_DISP_HOR_RES * 10 * BYTE_PER_PIXEL];
    // lv_display_set_buffers(disp, buf_2_1, buf_2_2, sizeof(buf_2_1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    /* Example 3
     * Two buffers screen sized buffer for double buffering.
     * Both LV_DISPLAY_RENDER_MODE_DIRECT and LV_DISPLAY_RENDER_MODE_FULL works, see their comments*/
    LV_ATTRIBUTE_MEM_ALIGN
    static uint8_t buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL];

    LV_ATTRIBUTE_MEM_ALIGN
    static uint8_t buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL];
    lv_display_set_buffers(disp, buf_3_1, buf_3_2, sizeof(buf_3_1), LV_DISPLAY_RENDER_MODE_DIRECT);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    /*You code here*/
    // add by mind
    xdma_init(DMA_DEVICE_ID, DMA_TOTAL_LEN);
}

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

/*Flush the content of the internal buffer the specific area on the display.
 *`px_map` contains the rendered image as raw pixel map and it should be copied to `area` on the display.
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_display_flush_ready()' has to be called when it's finished.*/
static void disp_flush(lv_display_t * disp_drv, const lv_area_t * area, uint8_t * px_map)
{
    if(disp_flush_enabled) {
        /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/

        // int32_t x;
        // int32_t y;
        // for(y = area->y1; y <= area->y2; y++) {
        //     for(x = area->x1; x <= area->x2; x++) {
        //         /*Put a pixel to the display. For example:*/
        //         /*put_px(x, y, *px_map)*/
        //         px_map++;
        //     }
        // }
        uint16_t x;
        uint16_t y;
        uint32_t color_index = 0;
        uint8_t * lcd_base_addr = (uint8_t *)frame_buffer_addr;

        // for(y = area->y1; y <= area->y2; y++)
        // {
        //     for(x = area->x1; x <= area->x2; x++)
        //     {
        //         /*Put a pixel to the display. For example:*/
        //         /*put_px(x, y, *color_p)*/
        //         // lcd_base_addr[y*vd_mode.width*3+x*3] = px_map[color_index+0];
        //         // lcd_base_addr[y*vd_mode.width*3+x*3+1] = px_map[color_index+1];
        //         // lcd_base_addr[y*vd_mode.width*3+x*3+2] = px_map[color_index+2];
        //         if (x < area->x1 + 10)
        //         {
        //             lcd_base_addr[y*vd_mode.width*3+x*3] = 0xFF;
        //             lcd_base_addr[y*vd_mode.width*3+x*3+1] = 0;
        //             lcd_base_addr[y*vd_mode.width*3+x*3+2] = 0;
        //         }
        //         else
        //         {
        //             lcd_base_addr[y*vd_mode.width*3+x*3] = px_map[color_index+0];
        //             lcd_base_addr[y*vd_mode.width*3+x*3+1] = px_map[color_index+1];
        //             lcd_base_addr[y*vd_mode.width*3+x*3+2] = px_map[color_index+2];
        //         }
        //         color_index = color_index + 3;
        //     }
        // }

        // add by mind
        if (frame_index == 0)
        {
            xdma_start((uint32_t)(frame_buffer_addr + DMA_TOTAL_LEN), (uint32_t)px_map);
        }
        else
        {
            xdma_start((uint32_t)frame_buffer_addr, (uint32_t)px_map);
        }
    }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_display_flush_ready(disp_drv);
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
