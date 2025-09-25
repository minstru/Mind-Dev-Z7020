/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */


#include "test.h"
#include "can.h"
#include "xadc.h"


void test_xadc(EmbeddedCli *cli)
{
    XAdcValues vals;
    char buf[128];

    snprintf(buf, sizeof(buf), "XADC Readings:\n");

    for (int i = 0; i < 10; i++)
    {
        if (xadc_read_all(&vals) < 0) {
            snprintf(buf, sizeof(buf), "XADC read failed!\n");
            embeddedCliPrint(cli, buf);
            return;
        }

        snprintf(buf, sizeof(buf), "Temp: %.2f °C, VCCINT: %.3f V, VCCAUX: %.3f, VCCBRAM: %.3f, VP/VN: %.3f\r\n", 
            vals.temperature / 1000.0, vals.vccint / 1000.0, vals.vccaux / 1000.0, vals.vccbram / 1000.0, vals.vpvn / 1000.0);
        embeddedCliPrint(cli, buf);

        usleep(10000);
    }

    return 0;
}

void test_rtc(EmbeddedCli *cli,const char *i2c_dev)
{
    int fd;
    unsigned char reg = 0x04; // Read starting from seconds register
    unsigned char data[7];
    char buf[128];
    stDateTime dt;

    fd = open_rtc_dev(i2c_dev);

    embeddedCliPrint(cli, "read RTC before config RTC: \r\n");
    for (int i = 0; i < 5; i++)
    {
        sleep(1);
        read_rtc(fd, &dt);

        // printf("RTC Time: 20%02d-%02d-%02d %02d:%02d:%02d (Weekday %d)\n",
        //        dt.year,dt.month,dt.day,dt.hour, dt.minute, dt.second,dt.weekday);
        snprintf(buf, sizeof(buf),
                "RTC Time: 20%02d-%02d-%02d %02d:%02d:%02d (Weekday %d)\n",
                dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second, dt.weekday);
        embeddedCliPrint(cli, buf);
    }

    dt.year=2025;
    dt.month=7;
    dt.day=9;
    dt.hour=12;
    dt.minute=0;
    dt.second=0;
    dt.weekday=3;
    set_rtc(fd, &dt);

    embeddedCliPrint(cli, "read RTC after config RTC: \r\n");
    for (int i = 0; i < 5; i++)
    {
        sleep(1);
        read_rtc(fd, &dt);

        // printf("RTC Time: 20%02d-%02d-%02d %02d:%02d:%02d (Weekday %d)\n",
        //        dt.year,dt.month,dt.day,dt.hour, dt.minute, dt.second,dt.weekday);
        snprintf(buf, sizeof(buf),
                "RTC Time: 20%02d-%02d-%02d %02d:%02d:%02d (Weekday %d)\n",
                dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second, dt.weekday);
        embeddedCliPrint(cli, buf);
    }         

    close(fd);
}


void test_shtc3(EmbeddedCli *cli,const char *i2c_dev) 
{
    int fd;
    shtc3_data_t data;
    char buf[128];
    embeddedCliPrint(cli, "Starting SHTC3 sensor test...\n");
    //printf("Starting SHTC3 sensor test...\n");

    fd = shtc3_init(i2c_dev);
    if (fd < 0)
    {
        embeddedCliPrint(cli, "SHTC3 initialization failed\n");
        // fprintf(stderr, "SHTC3 initialization failed\n");
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        if (shtc3_read_data(fd, &data)) 
        {
            snprintf(buf, sizeof(buf),
                        "[%d] Temperature: %.2f °C, Humidity: %.2f %%RH\n",
                        i + 1, data.temperature, data.humidity);
            embeddedCliPrint(cli, buf);
            // printf("[%d] Temperature: %.2f °C, Humidity: %.2f %%RH\n",
            //        i+1, data.temperature, data.humidity);
        } else 
        {
            snprintf(buf, sizeof(buf), "[%d] Failed to read sensor data\n", i + 1);
            embeddedCliPrint(cli, buf);
            // printf("[%d] Failed to read sensor data\n", i+1);
        }
        sleep(1);
    }

    shtc3_close(fd);
    embeddedCliPrint(cli, "SHTC3 test completed.\n");
    // printf("SHTC3 test completed.\n");
}


void test_eeprom(EmbeddedCli *cli,const char *i2c_dev)
{
    int fd;
    unsigned char write_data = 0xAB;
    unsigned char read_data;
    char buf[128];
    int status = 0;

    embeddedCliPrint(cli, "\r\nStarting EEPROM test...\n");

    // printf("Starting EEPROM test...\n");

    fd = eeprom_init(i2c_dev);
    if (fd < 0) 
    {
        embeddedCliPrint(cli, "EEPROM initialization failed\n");
        // fprintf(stderr, "EEPROM initialization failed\n");
        return;
    }

    // snprintf(buf, sizeof(buf), "Writing 0x%02X to address 0x0000\n", write_data);
    // embeddedCliPrint(cli, buf);
    //    printf("Writing 0x%02X to address 0x0000\n", write_data);
    if (!eeprom_write(fd, 0x0000, &write_data, 1))
    {
        embeddedCliPrint(cli, "EEPROM write failed\n");
        //    fprintf(stderr, "EEPROM write failed\n");
        eeprom_close(fd);
        return;
    }

    // Wait for write completion
    usleep(10000);
    // embeddedCliPrint(cli, "Reading from address 0x0000\n");
    //printf("Reading from address 0x0000\n");
    if (!eeprom_read(fd, 0x0000, &read_data, 1)) 
    {
        embeddedCliPrint(cli, "EEPROM read failed\n");
        //fprintf(stderr, "EEPROM read failed\n");
        eeprom_close(fd);
        return;
    } 
    else
    {
        // snprintf(buf, sizeof(buf), "Read value: 0x%02X, ", read_data);
        // embeddedCliPrint(cli, buf);
        //printf("Read value: 0x%02X\n", read_data);
    }

    if (read_data != write_data) 
    {
        // snprintf(buf, sizeof(buf), "Data mismatch: written 0x%02x, read 0x%02X\n", write_data, read_data);
        embeddedCliPrint(cli, "EEPROM read failed\r");
        // fprintf(stderr, "Data mismatch: written 0x%02x, read 0x%02X\n", read_data);
        eeprom_close(fd);
        return;
    } 
    else 
    {
        // snprintf(buf, sizeof(buf), "Data match: 0x%02X\n", read_data);
        // embeddedCliPrint(cli, buf);
        // printf("Data match: 0x%02X\n", read_data);
    }

    // Test multi-byte read/write
    uint8_t wrt_buf[4] = {0};
    uint8_t rd_buf[4] = {0};

    for (uint8_t i = 0; i < sizeof(wrt_buf); i++) 
    {
        wrt_buf[i] = i + 1; // Fill with sequential data
    }

    // embeddedCliPrint(cli, "\nTesting multi-byte operations...\n");
    // embeddedCliPrint(cli, "Writing 4 bytes to address 0x0010\n");
    // printf("\nTesting multi-byte operations...\n");
    // printf("Writing 4 bytes to address 0x0010\n");
    if (!eeprom_write(fd, 0x0010, wrt_buf, sizeof(wrt_buf))) 
    {
        embeddedCliPrint(cli, "Multi-byte write failed\n");
        // fprintf(stderr, "Multi-byte write failed\n");
        eeprom_close(fd);
        return;
    }

    usleep(20000);
    // embeddedCliPrint(cli, "Reading 4 bytes from address 0x0010\n");
    //printf("Reading 4 bytes from address 0x0010\n");
    if (!eeprom_read(fd, 0x0010, rd_buf, sizeof(rd_buf))) 
    {
        embeddedCliPrint(cli, "Multi-byte read failed\n");
        // fprintf(stderr, "Multi-byte read failed\n");
        eeprom_close(fd);
        return;
    }
    else 
    {
        for (uint8_t i = 0; i < sizeof(rd_buf); i++) 
        {
            if (rd_buf[i] != wrt_buf[i]) 
            {
                // snprintf(buf, sizeof(buf), "E2PROM Data mismatch at byte %d: written 0x%02X, read 0x%02X\n", 
                //         i, wrt_buf[i], rd_buf[i]);
                // embeddedCliPrint(cli, buf);
                // fprintf(stderr, "Data mismatch: written 0x%02x, read 0x%02X\n", read_data);

                embeddedCliPrint(cli, "E2PROM Multi-byte test failed\n");
                eeprom_close(fd);
                return;
            } 
        }
        // embeddedCliPrint(cli, "Multi-byte read success, data matches\n");
        // fprintf(stderr, "Multi-byte read success, data matches\n");
    }

    eeprom_close(fd);
    embeddedCliPrint(cli, "EEPROM test completed successfully.\n");
    //printf("EEPROM test completed.\n");
}


void test_can(EmbeddedCli *cli)
{
    char buf[128];
    uint32_t can_id = 0x0123;
    uint8_t data_buf[CAN_DATA_LEN] = {0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28};
    embeddedCliPrint(cli, "\nStarting CAN test...\n");

    if (!can_open(&g_can_handle, CAN_DEV)) 
    {
        embeddedCliPrint(cli, "CAN initialization failed\n");
        return;
    }

    snprintf(buf, sizeof(buf), "CAN device(%s) is UP(bitrate=%d, mode=%s)\n", 
        CAN_DEV, can_baud_rate, (can_mode == 0) ? "normal" : "loopback");
    embeddedCliPrint(cli, buf);

    // send CAN message
    int ret = can_send(&g_can_handle, can_id, data_buf, sizeof(data_buf));
    if (!ret) 
    {
        embeddedCliPrint(cli, "CAN message send failed");
        can_close(&g_can_handle);
        return;
    }

    usleep(300000);

    if (get_can_rcv_status() && (can_rcv_len == sizeof(data_buf)) )
    {
        clear_can_rcv_status();
        for (int i = 0; i < can_rcv_len; i++) 
        {
            if (can_rcv_buf[i] != data_buf[i]) 
            {
                snprintf(buf, sizeof(buf), 
                    "CAN message data mismatch at byte %d: expected 0x%02X, got 0x%02X\n", 
                    i, data_buf[i], can_rcv_buf[i]);
                embeddedCliPrint(cli, buf);
                can_close(&g_can_handle);
                return;
            }
        }
    } 
    else 
    {
        embeddedCliPrint(cli, "No CAN message received, and test failed\n");
        can_close(&g_can_handle);
        return;
    }

    embeddedCliPrint(cli, "CAN test completed successfully.\n");
    can_close(&g_can_handle);
}