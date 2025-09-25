/************************************************************************/
/*																		*/
/*	display_ctrl.h	--	Digilent Display Controller Driver				*/
/*																		*/
/************************************************************************/
/*	Author: Sam Bobrowicz												*/
/*	Copyright 2014, Digilent Inc.										*/
/************************************************************************/
/*  Module Description: 												*/
/*																		*/
/*		This module provides an easy to use API for controlling a    	*/
/*		Display attached to a Digilent system board via VGA or HDMI. 	*/
/*		run-time resolution setting and seamless framebuffer-swapping 	*/
/*		for tear-free animation. 										*/
/*																		*/
/*		To use this driver, you must have a Xilinx Video Timing 		*/
/* 		Controller core (vtc), Xilinx axi_vdma core, a Digilent 		*/
/*		axi_dynclk core, a Xilinx AXI Stream to Video core, and either  */
/*		a Digilent RGB2VGA or RGB2DVI core all present in your design.  */
/*		See the Video in or Display out reference projects for your     */
/*		system board to see how they need to be connected. Digilent     */
/*		reference projects and IP cores can be found at 				*/
/*		www.github.com/Digilent.			 							*/
/*																		*/
/*		The following steps should be followed to use this driver:		*/
/*		1) Create a DisplayCtrl object and pass a pointer to it to 		*/
/*		   DisplayInitialize.											*/
/*		2) Call DisplaySetMode to set the desired mode					*/
/*		3) Call DisplayStart to begin outputting data to the display	*/
/*		4) To create a seamless animation, draw the next image to a		*/
/*		   framebuffer currently not being displayed. Then call 		*/
/*		   DisplayChangeFrame to begin displaying that frame.			*/
/*		   Repeat as needed, only ever modifying inactive frames.		*/
/*		5) To change the resolution, call DisplaySetMode, followed by	*/
/*		   DisplayStart again.											*/
/*																		*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/* 																		*/
/*		2/20/2014(SamB): Created										*/
/*		11/25/2015(SamB): Changed from axi_disp_ctrl to Xilinx cores		*/
/*						  Separated Clock functions into dynclk library */
/*																		*/
/************************************************************************/

#ifndef DISPLAY_CTRL_H_
#define DISPLAY_CTRL_H_

/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */

#include "xil_types.h"
#include "vga_modes.h"
#include "xvtc.h"
#include "xil_io.h"

/* ------------------------------------------------------------ */
/*					General Type Declarations					*/
/* ------------------------------------------------------------ */

typedef enum {
	DISPLAY_STOPPED = 0,
	DISPLAY_RUNNING = 1
} DisplayState;

typedef struct {
		XVtc vtc; /*VTC driver struct*/
		VideoMode vMode; /*Current Video mode*/
		DisplayState state; /* Indicates if the Display is currently running */
} DisplayCtrl;

/* ------------------------------------------------------------ */
/*					Procedure Declarations						*/
/* ------------------------------------------------------------ */

int DisplayStop(DisplayCtrl *dispPtr);
int DisplayStart(DisplayCtrl *dispPtr);
int DisplayInitialize(DisplayCtrl *dispPtr, u16 vtcId);
int DisplaySetMode(DisplayCtrl *dispPtr, const VideoMode *newMode);
/* ------------------------------------------------------------ */

/************************************************************************/

#endif /* DISPLAY_CTRL_H_ */

