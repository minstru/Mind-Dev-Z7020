/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "server.h"

#define BUFFER_SIZE     (512)


// start the server
int start_server(int port) 
{
    struct sockaddr_in addr;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) 
    {
        perror("socket");
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) 
    {
        perror("bind");
        close(server_fd);
        server_fd = -1;
        return -1;
    }

    if (listen(server_fd, 5) < 0) 
    {
        perror("listen");
        close(server_fd);
        server_fd = -1;
        return -1;
    }

    printf("Server started on port %d...\n", port);
    return server_fd;
}


// handle client session
void handle_client(int client_sock) 
{
    ssize_t len;
    char rcv_buf[BUFFER_SIZE];

    while ((len = read(client_sock, rcv_buf, sizeof(rcv_buf) - 1)) > 0) 
    {
        rcv_buf[len] = '\0';
        printf("Received: %s\n", rcv_buf);
        write(client_sock, rcv_buf, len); // echo back
    }

    printf("Client disconnected.\n");
    close(client_sock);
}

// server thread function
void* server_thread_func(void* arg) 
{
    if (arg == NULL) return -1;

    int fd = -1;
    int port = *(int*)arg;
    
    while (1) 
    {
        if ((fd = start_server(port)) < 0) 
        {
            sleep(2);   // avoid busy loop if server fails to start
            continue;
        }

        while (1) 
        {
            int client_sock = accept(fd, NULL, NULL);
            if (client_sock < 0) 
            {
                close(fd);
                fd = -1;
                break;
            }

            handle_client(client_sock);
        }
    }
}
