/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <termios.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/can.h>

#include "gpio.h"
#include "eeprom.h"
#include "client.h"
#include <pthread.h>

#include "rtc.h"
#include "sensor.h"
#include "main.h"
#include "can.h"
#include "xadc.h"

#include "test.h"
#include "main.h"

#define EMBEDDED_CLI_IMPL
#include "embedded_cli.h"


const char VER_INFO[] = "V1.0.0";
const char COMPILE_DATE[] = __DATE__;
const char COMPILE_TIME[] = __TIME__;

/* Private variables ---------------------------------------------------------*/
// CLI_UINT cliBuffer[BYTES_TO_CLI_UINTS(CLI_BUFFER_SIZE)];
EmbeddedCli *cli = NULL;


/* Private function prototypes -----------------------------------------------*/
typedef void (*WriteHandler)(EmbeddedCli*, char);
EmbeddedCli* init_cli(WriteHandler handler, CliCommandBinding *binding_array, size_t binding_count);
void writeChar(EmbeddedCli *embeddedCli, char c);
void onCommand(EmbeddedCli *embeddedCli, CliCommand *command);
static bool is_valid_date(int year, int month, int day);

//void onCmd(EmbeddedCli *cli, char *args, void *context);
void on_get_version(EmbeddedCli *cli, char *args, void *context);
void on_get_local_ip(EmbeddedCli *cli, char *args, void *context);
void on_set_host_IP(EmbeddedCli *cli, char *args, void *context);
void on_get_sensor_data(EmbeddedCli *cli, char *args, void *context);
void on_set_rtc_data(EmbeddedCli *cli, char *args, void *context);
void on_get_rtc_data(EmbeddedCli *cli, char *args, void *context);
void on_write_e2prom_data(EmbeddedCli *cli, char *args, void *context);
void on_read_e2prom_data(EmbeddedCli *cli, char *args, void *context);

void on_set_CAN_baudrate_mode(EmbeddedCli *cli, char *args, void *context);
void on_CAN_up(EmbeddedCli *cli, char *args, void *context);
void on_CAN_down(EmbeddedCli *cli, char *args, void *context);
void on_send_CAN_msg(EmbeddedCli *cli, char *args, void *context);
void on_rcv_CAN_msg(EmbeddedCli *cli, char *args, void *context);
void on_self_test(EmbeddedCli *cli, char *args, void *context);
void on_read_xadc_data(EmbeddedCli *cli, char *args, void *context);

extern int uart_fd;

CliCommandBinding binding[] = {{
    "get_version",
    "get version info",
    true,
    NULL,
    on_get_version
}, {
    "get_local_IP",
    "Get server IP and port",
    true,
    NULL,
    on_get_local_ip
}, {
    "set_host_IP",
    "SET HOST IP,PORT",
    true,
    NULL,
    on_set_host_IP
}, {
    "get_sensor_data",
    "Get temperature and humidity from SHTC3 sensor",
    true,
    NULL,
    on_get_sensor_data
}, {
    "set_time",
    "Set RTC: year,month,day,hour,minute,second,weekday",
    true,
    NULL,
    on_set_rtc_data
}, {
    "get_time",
    "Get RTC: year,month,day,hour,minute,second,weekday",
    true,
    NULL,
    on_get_rtc_data
}, {
    "write_eeprom_data",
    "Write EEPROM: <addr>,<data1>,[data2 ...]",
    true,
    NULL,
    on_write_e2prom_data
}, {
    "read_eeprom_data",
    "Read EEPROM: <addr>,<length>",
    true,
    NULL,
    on_read_e2prom_data
}, {
    "set_can_baudrate_mode",
    "set_can_baudrate_mode: <rate>,<mode>",
    true,
    NULL,
    on_set_CAN_baudrate_mode
}, {
    "can_up",
    "CAN ON",
    true,
    NULL,
    on_CAN_up
}, {
    "can_down",
    "CAN OFF",
    true,
    NULL,
    on_CAN_down
}, {
    "can_send",
    "SEND DATA: <id>,<data1>,[data2 ...]",
    true,
    NULL,
    on_send_CAN_msg
}, {
    "can_rcv",
    "RCV DATA",
    true,
    NULL,
    on_rcv_CAN_msg
}, {
    "self_test",
    "SELF TEST",
    true,
    NULL,
    on_self_test
}, {
    "xadc_read",
    "READ XADC DATA",
    true,
    NULL,
    on_read_xadc_data
}};


void writeChar(EmbeddedCli *embeddedCli, char c)
{
    if (uart_fd < 0) return;

    if (c == '\n') 
    {
        const char crlf[] = "\r\n";
        write(uart_fd, crlf, 2);
    } 
    else 
    {
        write(uart_fd, &c, 1);
    }
}


EmbeddedCli* init_cli(WriteHandler handler, CliCommandBinding *binding_array, size_t binding_count)
{
    EmbeddedCli* embeddedCli;

    EmbeddedCliConfig *config = embeddedCliDefaultConfig();
    config->maxBindingCount = 15;
    embeddedCli = embeddedCliNew(config);
    if (embeddedCli == NULL)
    {
        printf("Cli was not created. Check sizes!\n");
        return NULL;
    }

    for (size_t i = 0; i < binding_count; i++) 
    {
        embeddedCliAddBinding(embeddedCli, binding_array[i]);
    }

    embeddedCli->onCommand = onCommand;
    embeddedCli->writeChar = handler;

    return embeddedCli;
}


void init_cmd_cli()
{
    size_t binding_count = sizeof(binding) / sizeof(binding[0]);
    cli = init_cli(writeChar, binding, binding_count);
}


void onCommand(EmbeddedCli *embeddedCli, CliCommand *command) 
{
    printf("Received command: %s\r\n", command->name);
    embeddedCliTokenizeArgs(command->args);
    for (int i = 1; i <= embeddedCliGetTokenCount(command->args); ++i) 
    {
        printf("arg %d: %s\r\n", i, embeddedCliGetToken(command->args, i));
    }
}

// task cli
void cli_task(void *param)
{
    char c;
    init_cmd_cli();

    sleep(1);

    on_self_test(cli, NULL, NULL);

    while (1)
    {
        if (read(uart_fd, &c, 1) > 0)
        {
            embeddedCliReceiveChar(cli, c); //input cmd
            embeddedCliProcess(cli);
        }
        else
        {
            usleep(2000);
        }
    }
    return NULL;
}

void on_read_xadc_data(EmbeddedCli *cli, char *args, void *context)
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

void on_self_test(EmbeddedCli *cli, char *args, void *context)
{
    on_get_version(cli, args, context);
    test_rtc(cli, i2c0_dev);
    test_shtc3(cli, i2c0_dev);
    test_eeprom(cli, i2c0_dev);
    test_can(cli);
    test_xadc(cli);
    
    embeddedCliPrint(cli, "Self test completed.\n");
}

// set CAN baudrate and mode
void on_set_CAN_baudrate_mode(EmbeddedCli *cli, char *args, void *context)
{
    char debug_msg[64];
    int32_t baudrate = 0;
    uint8_t mode = 0;   // 0: normal mode, 1: loopback mode

    // 打印参数个数
    uint16_t token_count = embeddedCliGetTokenCount(args);
    snprintf(debug_msg, sizeof(debug_msg), "Token count: %u\n", token_count);
    embeddedCliPrint(cli, debug_msg);

    if (token_count < 2) 
    {
        embeddedCliPrint(cli, "Usage: on_set_CAN_baudrate_mode <baud>,<mode>\n");
        return;
    }

    const char *baud_str = embeddedCliGetToken(args, 1);
    const char *mode_str = embeddedCliGetToken(args, 2);

    baudrate = atoi(baud_str);
    if (baudrate <= 0) 
    {
        snprintf(debug_msg, sizeof(debug_msg), "Invalid baudrate: %s\n", baud_str);
        embeddedCliPrint(cli, debug_msg);
        return;
    }

    if (strcmp(mode_str, "loopback") == 0) 
    {
        mode = 1;
    } 
    else if (strcmp(mode_str, "normal") == 0) 
    {
        mode = 0;
    } 
    else 
    {
        snprintf(debug_msg, sizeof(debug_msg), "Unsupported mode: %s\n", mode_str);
        embeddedCliPrint(cli, debug_msg);
        return;
    }

    // set CAN baudrate and mode
    can_set_baud_mode(baudrate, mode);

    snprintf(debug_msg, sizeof(debug_msg),
        "CAN %s configured: baudrate = %d, mode = %s\n", CAN_DEV, baudrate, mode_str);
    embeddedCliPrint(cli, debug_msg);
}

// 
void on_CAN_up(EmbeddedCli *cli, char *args, void *context)
{
    char cmd[64];
    char msg[64];

    if (!can_open(&g_can_handle, CAN_DEV)) 
    {
        embeddedCliPrint(cli, "CAN initialization failed\n");
        return;
    }

    snprintf(msg, sizeof(msg), "CAN device %s is UP and initialized\n", CAN_DEV);
    embeddedCliPrint(cli, msg);
}


void on_CAN_down(EmbeddedCli *cli, char *args, void *context)
{
    char msg[32];
    can_close(&g_can_handle);
    snprintf(msg, sizeof(msg), "CAN device %s is DOWN\n", CAN_DEV);
    embeddedCliPrint(cli, msg);
}



void on_send_CAN_msg(EmbeddedCli *cli, char *args, void *context)
{
    char buf[64];
    uint8_t len;
    uint16_t token_count = embeddedCliGetTokenCount(args);

    const char *id_str = embeddedCliGetToken(args, 1);
    if (!id_str) 
    {
        embeddedCliPrint(cli, "Missing CAN ID");
        return;
    }

    unsigned int can_id = 0;
    if (sscanf(id_str, "%x", &can_id) != 1 ) 
    {
        embeddedCliPrint(cli, "Invalid CAN ID");
        return;
    }

    int data_len = token_count - 1;
    unsigned char *data_buf = malloc(data_len);
    if (!data_buf) 
    {
        embeddedCliPrint(cli, "Memory allocation failed\n");
        return;
    }

    // parse data bytes
    for (int i = 0; i < data_len; i++) 
    {
        const char *data_str = embeddedCliGetToken(args, i + 2);
        unsigned int val = 0;
        if (sscanf(data_str, "%i", &val) != 1) 
        {
            snprintf(buf, sizeof(buf), "Invalid data format at argument %d\n", i + 2);
            embeddedCliPrint(cli, buf);
            free(data_buf);
            return;
        }
        if (val > 0xFF) 
        {  
            snprintf(buf, sizeof(buf), "Data byte out of range at argument %d\n", i + 2);
            embeddedCliPrint(cli, buf);
            free(data_buf);
            return;
        }
        data_buf[i] = (unsigned char)val; 
    }

    // send CAN message
    int ret = can_send(&g_can_handle, can_id, data_buf, data_len);
    if (ret) 
    {
        snprintf(buf, sizeof(buf), "Sending CAN message: ID=0x%X, Len=%d\n", can_id, data_len);
        embeddedCliPrint(cli, buf);
    } else {
        embeddedCliPrint(cli, "CAN message send failed");
    }

    free(data_buf);
}


void on_rcv_CAN_msg(EmbeddedCli *cli, char *args, void *context)
{
    bool status = false;
    char msg[160];
    uint8_t len = 0;
    uint32_t id = 0;

    if (args != NULL)
    {
        int token_count = embeddedCliGetTokenCount(args);
        if (token_count != 0) 
        {
            embeddedCliPrint(cli, "Usage: can_rcv\n");
            return;
        }
    }

    if (!can_is_up)
    {
        embeddedCliPrint(cli, "CAN interface is not up. Use 'can_up' first.\n");
        return;
    }

    status = get_can_rcv_status();
    if (status)
    {
        len = snprintf(msg, sizeof(msg), "New Data Received: ID=0x%X, Data=", id);
        for (int i = 0; i < can_rcv_len; i++)
        {
            len += snprintf(msg + len, sizeof(msg), "0x%02x ", can_rcv_buf[i]);
        }
        *(msg + len) = '\n';
        *(msg + len + 1) = '\0';
        embeddedCliPrint(cli, msg);

        clear_can_rcv_status();
    }
    else
    {
        embeddedCliPrint(cli, "No New Data Received.\n");
    }
}


void on_write_e2prom_data(EmbeddedCli *cli, char *args, void *context)
{
    char buf[64];
    uint16_t token_count = embeddedCliGetTokenCount(args);
    if (token_count < 2) 
    {
        embeddedCliPrint(cli, "Usage: write_eeprom_data <addr> <data1> [data2 ...]\n");
        return;
    }

    // parse address
    const char *addr_str = embeddedCliGetToken(args, 1);
    unsigned int addr = 0;
    if (sscanf(addr_str, "%i", &addr)!=1) 
    {
        embeddedCliPrint(cli, "Invalid address format\n");
        return;
    }

    if (addr > 0xFFFF) 
    {
        embeddedCliPrint(cli, "Address out of range (0~0xFFFF)\n");
        return;
    }

    // calculate data length
    int data_len = token_count - 1;
    unsigned char *data_buf = malloc(data_len);
    if (!data_buf) 
    {
        embeddedCliPrint(cli, "Memory allocation failed\n");
        return;
    }

    // parse data bytes
    for (int i = 0; i < data_len; i++) 
    {
        const char *data_str = embeddedCliGetToken(args, i + 2);
        unsigned int val = 0;
        if (sscanf(data_str,"%i",&val) != 1) 
        {
            snprintf(buf, sizeof(buf), "Invalid data format at argument %d\n", i + 2);
            embeddedCliPrint(cli, buf);
            free(data_buf);
            return;
        }
        if (val > 0xFF) 
        {
            snprintf(buf, sizeof(buf), "Data byte out of range at argument %d\n", i + 2);
            embeddedCliPrint(cli, buf);

            free(data_buf);
            return;
        }
        data_buf[i] = (unsigned char)val;
    }

    int fd = eeprom_init("/dev/i2c-0");
    if (fd < 0) 
    {
        embeddedCliPrint(cli, "Failed to open EEPROM device\n");
        free(data_buf);
        return;
    }

    if (eeprom_write(fd, (unsigned short)addr, data_buf, data_len)) 
    {
        embeddedCliPrint(cli, "EEPROM write success\n");
    } 
    else 
    {
        embeddedCliPrint(cli, "EEPROM write failed\n");
    }

    eeprom_close(fd);
    free(data_buf);
}

void on_read_e2prom_data(EmbeddedCli *cli, char *args, void *context)
{
    char debug_msg[128];

    uint16_t token_count = embeddedCliGetTokenCount(args);
    snprintf(debug_msg, sizeof(debug_msg), "Token count: %u\n", token_count);
    embeddedCliPrint(cli, debug_msg);

    if (token_count < 2) 
    {
        embeddedCliPrint(cli, "Usage: read_eeprom_data <addr>,<len>\n");
        return;
    }

    // parse address parameter
    const char *addr_str = embeddedCliGetToken(args, 1);
    unsigned int addr = 0;
    if (sscanf(addr_str, "%i", &addr) != 1 ) 
    {
        snprintf(debug_msg, sizeof(debug_msg), "Invalid address format: '%s'\n", addr_str);
        embeddedCliPrint(cli, debug_msg);
        return;
    }

    // parse length parameter
    const char *len_str = embeddedCliGetToken(args, 2);
    unsigned int len = 0;
    if (sscanf(len_str, "%i", &len) != 1) 
    {
        snprintf(debug_msg, sizeof(debug_msg), "Invalid length format: '%s'\n", len_str);
        embeddedCliPrint(cli, debug_msg);
        return;
    }

    // check range
    if (addr > 0xFFFF) 
    {
        embeddedCliPrint(cli, "Address out of range (0~0xFFFF)\n");
        return;
    }
    if (len == 0 || len > 256) 
    {
        embeddedCliPrint(cli, "Length out of valid range (1~256)\n");
        return;
    }

    // print parsed result
    snprintf(debug_msg, sizeof(debug_msg), "Parsed addr=0x%04X, len=%u\n", addr, len);
    embeddedCliPrint(cli, debug_msg);

    // allocate memory buffer
    unsigned char *data_buf = malloc(len);
    if (!data_buf) 
    {
        embeddedCliPrint(cli, "Memory allocation failed\n");
        return;
    }

    // initialize I2C device
    int fd = eeprom_init("/dev/i2c-0");
    if (fd < 0) 
    {
        embeddedCliPrint(cli, "Failed to open EEPROM device\n");
        free(data_buf);
        return;
    }

    // try to read
    if (!eeprom_read(fd, (unsigned short)addr, data_buf, len)) 
    {
        embeddedCliPrint(cli, "EEPROM read failed\n");
        eeprom_close(fd);
        free(data_buf);
        return;
    }

    // print read data
    snprintf(debug_msg, sizeof(debug_msg), "EEPROM read success at 0x%04X, %u bytes:\n", addr, len);
    embeddedCliPrint(cli, debug_msg);

    for (unsigned int i = 0; i < len; i++) 
    {
        snprintf(debug_msg, sizeof(debug_msg), "  [0x%04X] = 0x%02X (%3u)\n", addr + i, data_buf[i], data_buf[i]);
        embeddedCliPrint(cli, debug_msg);
    }

    eeprom_close(fd);
    free(data_buf);
}

static bool is_valid_date(int year, int month, int day)
{
    if (year < 1900 || year > 2099) return false;
    if (month < 1 || month > 12) return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // leap year adjustment for February
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1])
        return false;

    return true;
}


void on_set_rtc_data(EmbeddedCli *cli, char *args, void *context)
{
    uint16_t token_num = embeddedCliGetTokenCount(args);

    if (token_num != 7) 
    {
        embeddedCliPrint(cli, "Invalid number of arguments. Use: set_time YYYY MM DD hh mm ss ww\n");
        return;
    }

    int year = atoi(embeddedCliGetToken(args, 1));
    int month = atoi(embeddedCliGetToken(args, 2));
    int day = atoi(embeddedCliGetToken(args, 3));
    int hour = atoi(embeddedCliGetToken(args, 4));
    int minute = atoi(embeddedCliGetToken(args, 5));
    int second = atoi(embeddedCliGetToken(args, 6));
    int weekday = atoi(embeddedCliGetToken(args, 7));

    if (!is_valid_date(year, month, day) ||
        hour < 0 || hour > 23 ||
        minute < 0 || minute > 59 ||
        second < 0 || second > 59 ||
        weekday < 0 || weekday > 6)
    {
        embeddedCliPrint(cli, "Invalid date/time value.\n");
        return;
    }

    stDateTime rtcTime = {
        .year = year,
        .month = month,
        .day = day,
        .weekday = weekday,
        .hour = hour,
        .minute = minute,
        .second = second
    };

    int fd = open_rtc_dev("/dev/i2c-0");
    if (fd < 0) 
    {
        embeddedCliPrint(cli, "Failed to open RTC device\n");
        return;
    }

    if (!set_rtc(fd, &rtcTime)) 
    {
        embeddedCliPrint(cli, "Failed to set RTC\n");
        close_rtc_dev(fd);
        return;
    }

    close_rtc_dev(fd);

    char msg[128];
    snprintf(msg, sizeof(msg),
            "RTC set to: %04d-%02d-%02d %02d:%02d:%02d weekday=%d\n",
            year, month, day, hour, minute, second, weekday);
    embeddedCliPrint(cli, msg);
}



void on_get_rtc_data(EmbeddedCli *cli, char *args, void *context)
{
    const char *i2c_dev = "/dev/i2c-0";
    stDateTime dt = {0};
    char msg[128];

    // initialize RTC device
    int fd = open_rtc_dev(i2c_dev);
    if (fd < 0) {
        embeddedCliPrint(cli, "Failed to open RTC device");
        return;
    }

    // read time data
    if (!read_rtc(fd, &dt)) {
        embeddedCliPrint(cli, "Failed to read RTC time");
        close_rtc_dev(fd);
        return;
    }

    int full_year = (dt.year >= 70) ? (1900 + dt.year) : (2000 + dt.year);

    // format output
    const char *weekday_str[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    snprintf(msg, sizeof(msg),
            "RTC Time: %04d-%02d-%02d %02d:%02d:%02d %s",
            full_year, dt.month, dt.day,
            dt.hour, dt.minute, dt.second,
            (dt.weekday < 7) ? weekday_str[dt.weekday] : "Invalid");

    embeddedCliPrint(cli, msg);
    close_rtc_dev(fd);
}


void on_get_sensor_data(EmbeddedCli *cli, char *args, void *context)
{
    const char *i2c_dev = "/dev/i2c-0";
    shtc3_data_t sensor_data;
    char msg[64];

    // initialize sensor
    int fd = shtc3_init(i2c_dev);
    if (fd < 0) 
    {
        embeddedCliPrint(cli, "Failed to initialize SHTC3 sensor");
        return;
    }

    // read data
    if (shtc3_read_data(fd, &sensor_data)) 
    {
        snprintf(msg, sizeof(msg), "Temperature: %.2f C", sensor_data.temperature);
        embeddedCliPrint(cli, msg);

        snprintf(msg, sizeof(msg), "Humidity: %.2f %%", sensor_data.humidity);
        embeddedCliPrint(cli, msg);
    } 
    else 
    {
        embeddedCliPrint(cli, "Failed to read sensor data");
    }

    // close sensor
    shtc3_close(fd);

}

void on_get_version(EmbeddedCli *cli, char *args, void *context)
{
    embeddedCliPrint(cli, VER_INFO);
    embeddedCliPrint(cli, COMPILE_DATE);
    embeddedCliPrint(cli, COMPILE_TIME);
    embeddedCliPrint(cli, "");
}


//as server
void on_get_local_ip(EmbeddedCli *cli, char *args, void *context)
{
    embeddedCliPrint(cli, "IP: 192.168.3.193 PORT1:12345 , PORT2:8 ");
}


//as client
void on_set_host_IP(EmbeddedCli *cli, char *args, void *context)
{
    // support two formats:
    // set_host_ip 192.168.1.10 8888 (space separated)
    // set_host_ip 192.168.1.10,8888 (comma separated)

    char msg[64];

    uint16_t token_num = embeddedCliGetTokenCount(args);
    if (token_num != 1 && token_num != 2) 
    {
        embeddedCliPrint(cli, "Usage: set_host_ip <ip> <port>");
        embeddedCliPrint(cli, "Or: set_host_ip <ip>,<port>");
        return;
    }

    char ip_str[16];
    int port = 0;
    int ip[4];

    if (token_num == 1) 
    {
        // process comma-separated format
        const char *input = embeddedCliGetToken(args, 1);
        if (sscanf(input, "%d.%d.%d.%d,%d", &ip[0], &ip[1], &ip[2], &ip[3], &port) != 5) 
        {
            embeddedCliPrint(cli, "Invalid format. Use: IP,port (e.g. 192.168.1.10,8888)");
            return;
        }
    }
    else 
    {
        // process space-separated format
        const char *ip_input = embeddedCliGetToken(args, 1);
        if (sscanf(ip_input, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]) != 4) 
        {
            embeddedCliPrint(cli, "Invalid IP format");
            return;
        }
        port = atoi(embeddedCliGetToken(args, 2));
    }

    // validate IP and port
    for (int i = 0; i < 4; i++) 
    {
        if (ip[i] < 0 || ip[i] > 255) 
        {
            embeddedCliPrint(cli, "IP octet out of range 0-255");
            return;
        }
    }

    if (port <= 0 || port > 65535) 
    {
        embeddedCliPrint(cli, "Port must be 1-65535");
        return;
    }

    set_host_ip_port(ip, port);

    // construct IP string for display
    snprintf(ip_str, sizeof(ip_str), "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

    
    snprintf(msg, sizeof(msg), "Server IP set to %s:%d", ip_str, port);
    embeddedCliPrint(cli, msg);
}

