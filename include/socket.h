#ifndef SOCKET_H
#define SOCKET_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint32_t size;
    uint32_t type;
    char*    data;
} message_s;

int socket_open(void);
int socket_close(int fd);
int socket_recv(int fd, message_s* msg);
int socket_peek(int fd, message_s* msg);
int socket_send(int fd, const message_s* msg);
int socket_request(int fd, const message_s* msg, message_s* reply);
int recv_n(int fd, void* buffer, size_t size);

#endif
