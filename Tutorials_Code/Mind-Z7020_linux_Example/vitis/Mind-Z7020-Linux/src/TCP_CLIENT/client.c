/*
 * Copyright (c) 2025-present Mind Instrument
 * Distributed under the MIT software license, see the accompanying file LICENSE.txt.
 * For those auto-generated code, please refer to the original author license.
 */

#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

static uint8_t host_ip[4] = {192, 168, 3, 232};  // server host IP
static uint16_t host_port = 5003;             // server host port
static pthread_mutex_t host_mutex = PTHREAD_MUTEX_INITIALIZER;

// set host(server) IP and port
void set_host_ip_port(int ip[4], uint16_t port) 
{
    if (!ip || port == 0) {
        return;
    }

    pthread_mutex_lock(&host_mutex);
    memcpy(host_ip, ip, sizeof(host_ip));
    host_port = port;
    pthread_mutex_unlock(&host_mutex);
}

bool check_host_ip_valid()
{
    pthread_mutex_lock(&host_mutex);
    bool valid = !(host_ip[0] == 0 && host_ip[1] == 0 && 
                host_ip[2] == 0 && host_ip[3] == 0) && 
                (host_port != 0);
    pthread_mutex_unlock(&host_mutex);
    return valid;
}

void get_host_ip_str(char *ip_str, size_t size)
{
    pthread_mutex_lock(&host_mutex);
    snprintf(ip_str, size, "%d.%d.%d.%d", 
             host_ip[0], host_ip[1], host_ip[2], host_ip[3]);
    pthread_mutex_unlock(&host_mutex);
}

// Connect to server
int connect_to_server(const char *ip, int port) {
    int sockfd;
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        close(sockfd);
        return -1;
    }

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        close(sockfd);
        return -1;
    }

    printf("Connected to server %s:%d\n", ip, port);
    return sockfd;
}

// receive data from server and send back
int recv_handler(int sockfd) {
    static char buffer[BUFFER_SIZE];
    ssize_t sent_len, recv_len;

    recv_len = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (recv_len <= 0) {
        return -1;
    }
    
    buffer[recv_len] = '\0';
    printf("Server replied: %s\n", buffer);

    sent_len = send(sockfd, buffer, strlen(buffer), 0);
    if (sent_len < 0) 
    {
        return -1;
    }

    return 0;
}

// Client thread function
void *client_pthread_func(void *arg)
{
    int port;
    char ip_str[16];

    while (1)
    {
        if (!check_host_ip_valid())
        {
            sleep(1);
            continue;
        }

        get_host_ip_str(ip_str, sizeof(ip_str));
        
        pthread_mutex_lock(&host_mutex);
        port = host_port;
        pthread_mutex_unlock(&host_mutex);

        int sockfd = connect_to_server(ip_str, port);
        if (sockfd < 0)
        {
            sleep(1);
            continue;
        }

        while (1)
        {
            if (recv_handler(sockfd) < 0)
            {
                close(sockfd);
                sockfd = -1;
                break;
            }
            sleep(1);
        }
    }
    return NULL;
}
