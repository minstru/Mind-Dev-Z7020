/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <termios.h>
//#include <sys/socket.h>
#include <sys/types.h>
#include "xuartps.h"

#define EMBEDDED_CLI_IMPL
#include "embedded_cli.h"



/* Private variables ---------------------------------------------------------*/
// CLI_UINT cliBuffer[BYTES_TO_CLI_UINTS(CLI_BUFFER_SIZE)];
EmbeddedCli *cli = NULL;

/* Private function prototypes -----------------------------------------------*/
typedef void (*WriteHandler)(EmbeddedCli*, char);
EmbeddedCli* init_cli(WriteHandler handler, CliCommandBinding *binding_array, size_t binding_count);
void writeChar(EmbeddedCli *embeddedCli, char c);
void onCommand(EmbeddedCli *embeddedCli, CliCommand *command);

void set_mode(EmbeddedCli *cli, char *args, void *context);
void get_mode(EmbeddedCli *cli, char *args, void *context);

extern void set_audio_mode(uint8_t mode);
extern XUartPs Uart_Ps;
extern uint8_t audio_mode;
extern int Uart_Status;

CliCommandBinding binding[] = {{
    "set_mode",
    "set audio mode: LineIn mode(0)/MIC mode(1)",
    true,
    NULL,
    set_mode
}, {
    "get_mode",
    "get audio mode",
    true,
    NULL,
    get_mode
}};


void writeChar(EmbeddedCli *embeddedCli, char c)
{
    if (Uart_Status < 0)
        return;

    if (c == '\n') {
        const char crlf[] = "\r\n";
        while(XUartPs_IsSending(&Uart_Ps));
        XUartPs_Send(&Uart_Ps, crlf, 2);
    } else {
        while(XUartPs_IsSending(&Uart_Ps));
        XUartPs_Send(&Uart_Ps, &c, 1);
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

    printf("Cli task has started. Enter your commands.\n");


    for (size_t i = 0; i < binding_count; i++) {
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

void onCommand(EmbeddedCli *embeddedCli, CliCommand *command) {
   //CLI_LOG(LOG_DBG, "Received command: %s\r\n", command->name);
    printf("Received command: %s\r\n", command->name);
    embeddedCliTokenizeArgs(command->args);
    for (int i = 1; i <= embeddedCliGetTokenCount(command->args); ++i) {
        //CLI_LOG(LOG_DBG, "arg %d: %s\r\n", i, embeddedCliGetToken(command->args, i));
        printf("arg %d: %s\r\n", i, embeddedCliGetToken(command->args, i));
    }
}


void set_mode(EmbeddedCli *cli, char *args, void *context)
{
    uint8_t mode = 0;

    uint16_t token_count = embeddedCliGetTokenCount(args);
    if (token_count != 1) {
        embeddedCliPrint(cli, "Usage: set_mode <mode>\n");
        return;
    }

    const char *mode_str = embeddedCliGetToken(args, 1);
    mode = atoi(mode_str);
    set_audio_mode(mode);

    if (mode == 0)
    {
        embeddedCliPrint(cli, "set to LineIn mode\n");
    }
    else 
    {
        embeddedCliPrint(cli, "set to MIC mode\n");
    }
}


void get_mode(EmbeddedCli *cli, char *args, void *context)
{
    if (audio_mode==0)
    {
        embeddedCliPrint(cli, "current mode is LineIN \n");
    }
    else
    {
        embeddedCliPrint(cli, "current mode is MIC\n");
    }
}




