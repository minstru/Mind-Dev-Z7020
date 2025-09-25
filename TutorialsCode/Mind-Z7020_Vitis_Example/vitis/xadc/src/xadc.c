/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include "xparameters.h"
#include "xadcps.h"
#include "stdio.h"
#include "xil_printf.h"
#include "sleep.h"

#define XADC_DEVICE_ID   XPAR_XADCPS_0_DEVICE_ID

static  XAdcPs           xadc_inst;

int read_xadc(void)
{
    XAdcPs_Config *ConfigPtr;

    u32 temp_rawdata=0;           	// temperature raw data
    u32 vcc_pint_rawdata=0;       	// PS internal voltage raw data
    u32 vcc_paux_rawdata;       	// PS auxiliary voltage raw data
    u32 vcc_pddr_rawData;       	// PS DDR voltage raw data
    u32 vcc_int_rawdata;        	// PL internal voltage raw data
    u32 vcc_aux_rawdata;        	// PL auxiliary voltage raw data
    u32 vcc_bram_rawData;       	// PL BRAM voltage raw data
    u32 vcc_vpvn_rawData;           // VPVN raw data

    float temp=0;                 	// temperature
    float vcc_pint=0;             	// PS internal voltage
    float vcc_paux=0;             	// PS auxiliary voltage
    float vcc_pddr=0;             	// PS DDR voltage
    float vcc_int=0;              	// PL internal voltage
    float vcc_aux=0;              	// PL auxiliary voltage
    float vcc_bram=0;             	// PL BRAM voltage
    float vcc_vpvn=0;               // VpVn voltage

    // initialize XADC driver
    ConfigPtr = XAdcPs_LookupConfig(XADC_DEVICE_ID);
    XAdcPs_CfgInitialize(&xadc_inst, ConfigPtr, ConfigPtr->BaseAddress);

    // set XADC operation mode to "default safe mode"
    XAdcPs_SetSequencerMode(&xadc_inst, XADCPS_SEQ_MODE_SAFE);

    XAdcPs_SetSeqChEnables(&xadc_inst, XADCPS_SEQ_CH_VPVN);

    XAdcPs_SetSequencerMode(&xadc_inst, XADCPS_SEQ_MODE_CONTINPASS);

    while(1)
    {
        // get temperature sensor raw data
        temp_rawdata = XAdcPs_GetAdcData(&xadc_inst, XADCPS_CH_TEMP);
        // convert to temperature information
        temp = XAdcPs_RawToTemperature(temp_rawdata);

        // get VCCPINT sensor data and convert to voltage information
        vcc_pint_rawdata = XAdcPs_GetAdcData(&xadc_inst, XADCPS_CH_VCCPINT);
        vcc_pint = XAdcPs_RawToVoltage(vcc_pint_rawdata);

        // get VCCPAUX sensor data and convert to voltage information
        vcc_paux_rawdata = XAdcPs_GetAdcData(&xadc_inst, XADCPS_CH_VCCPAUX);
        vcc_paux = XAdcPs_RawToVoltage(vcc_paux_rawdata);

        // get VCCPDRO sensor data and convert to voltage information
        vcc_pddr_rawData = XAdcPs_GetAdcData(&xadc_inst, XADCPS_CH_VCCPDRO);
        vcc_pddr = XAdcPs_RawToVoltage(vcc_pddr_rawData);

        // get VCCINT sensor data and convert to voltage information
        vcc_int_rawdata = XAdcPs_GetAdcData(&xadc_inst, XADCPS_CH_VCCINT);
        vcc_int = XAdcPs_RawToVoltage(vcc_int_rawdata);

        // get VCCAUX sensor data and convert to voltage information
        vcc_aux_rawdata = XAdcPs_GetAdcData(&xadc_inst, XADCPS_CH_VCCAUX);
        vcc_aux = XAdcPs_RawToVoltage(vcc_aux_rawdata);

        // get VBRAM sensor data and convert to voltage information
        vcc_bram_rawData = XAdcPs_GetAdcData(&xadc_inst, XADCPS_CH_VBRAM);
        vcc_bram = XAdcPs_RawToVoltage(vcc_bram_rawData);

        // get VpVn raw data and convert to voltage information
        vcc_vpvn_rawData = XAdcPs_GetAdcData(&xadc_inst, XADCPS_CH_VPVN);
        vcc_vpvn = XAdcPs_RawToVoltage(vcc_vpvn_rawData) /3;

        // printf results
        printf("Raw Temp    %lu, Real Temp    %fC \n", temp_rawdata,     temp);
        printf("Raw VccPInt %lu, Real VccPInt %fV \n", vcc_pint_rawdata, vcc_pint);
        printf("Raw VccPAux %lu, Real VccPAux %fV \n", vcc_paux_rawdata, vcc_paux);
        printf("Raw VccPDDR %lu, Real VccPDDR %fV \n", vcc_pddr_rawData, vcc_pddr);
        printf("Raw VccInt  %lu, Real VccInt  %fV \n", vcc_int_rawdata,  vcc_int);
        printf("Raw VccAux  %lu, Real VccAux  %fV \n", vcc_aux_rawdata,  vcc_aux);
        printf("Raw VccBram %lu, Real VccBram %fV \n",vcc_bram_rawData, vcc_bram);
        printf("Raw VpVn    %lu, Real VpVn    %fV \n\r", vcc_vpvn_rawData, vcc_vpvn);

        sleep(2);
    }

    return 0;
}
