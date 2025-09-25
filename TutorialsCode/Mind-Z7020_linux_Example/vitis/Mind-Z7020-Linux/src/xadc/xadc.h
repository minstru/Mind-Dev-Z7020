/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#ifndef _XADC_H_
#define _XADC_H_


#define IIO_DEV_PATH "/sys/bus/iio/devices/iio:device0/"

typedef struct {
    double temperature;
    double vccint;
    double vccaux;
    double vccbram;
    double vpvn;
} XAdcValues;


double xadc_read_all(XAdcValues *vals);


#endif //_XADC_H_