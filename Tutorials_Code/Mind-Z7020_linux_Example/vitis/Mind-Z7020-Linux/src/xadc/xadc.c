/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xadc.h"


// Helper function: read integer from sysfs
int read_sysfs_int(const char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("fopen");
        return -1;
    }
    int val;
    if (fscanf(fp, "%d", &val) != 1) {
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return val;
}

// Helper function: read float (scale)
double read_sysfs_double(const char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("fopen");
        return -1;
    }
    double val;
    if (fscanf(fp, "%lf", &val) != 1) {
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return val;
}


// Read voltage channel (raw * scale)
double read_voltage_channel(const char *name) {
    char raw_path[256], scale_path[256];
    snprintf(raw_path, sizeof(raw_path), "%s/%s_raw", IIO_DEV_PATH, name);
    snprintf(scale_path, sizeof(scale_path), "%s/%s_scale", IIO_DEV_PATH, name);

    int raw = read_sysfs_int(raw_path);
    double scale = read_sysfs_double(scale_path);

    if (raw < 0 || scale < 0)
        return -1;

    return raw * scale; // Usually returns in mV
}

// Read temperature channel ((raw + offset) * scale)
double read_temp_channel(const char *name) {
    char raw_path[256], scale_path[256], offset_path[256];
    snprintf(raw_path, sizeof(raw_path), "%s/%s_raw", IIO_DEV_PATH, name);
    snprintf(scale_path, sizeof(scale_path), "%s/%s_scale", IIO_DEV_PATH, name);
    snprintf(offset_path, sizeof(offset_path), "%s/%s_offset", IIO_DEV_PATH, name);

    int raw = read_sysfs_int(raw_path);
    int offset = read_sysfs_int(offset_path);
    double scale = read_sysfs_double(scale_path);

    if (raw < 0 || scale < 0)
        return -1;

    return (raw + offset) * scale; // Usually milli-Celsius
}


double xadc_read_all(XAdcValues *vals) {
    if (!vals) return -1;

    vals->temperature = read_temp_channel("in_temp0");
    vals->vccint      = read_voltage_channel("in_voltage0_vccint");
    vals->vccaux      = read_voltage_channel("in_voltage1_vccaux");
    vals->vccbram     = read_voltage_channel("in_voltage2_vccbram");
    vals->vpvn        = read_voltage_channel("in_voltage8_vpvn"); 

    return 0;
}

