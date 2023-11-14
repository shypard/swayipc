#include "socket.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

const char ipc_magic[] = {'i', '3', '-', 'i', 'p', 'c'};
#define IPC_HEADER_SIZE (sizeof(ipc_magic) + 8)

int socket_open(void)
{
    char*              sway_socket_path = NULL;
    int                fd               = -1;
    struct sockaddr_un addr;

    if ((sway_socket_path = getenv("SWAYSOCK")) == NULL) {
        perror("Cannot get environment variable SWAYSOCK");
        return -errno;
    }

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("Cannot create socket");
        return -errno;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, sway_socket_path, sizeof(addr.sun_path) - 1);

    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("Cannot connect to sway socket");
        return -errno;
    }

    return fd;
}

int socket_close(int fd) { return close(fd); }

int socket_request(int fd, const message_s* message, message_s* reply)
{
    if (socket_send(fd, message) < 0) return -errno;

    if (socket_recv(fd, reply) < 0) return -errno;

    return 0;
}

int socket_send(int fd, const message_s* msg)
{
    char header[IPC_HEADER_SIZE];

    /* Prepare header */
    memcpy(header, ipc_magic, sizeof(ipc_magic));
    memcpy(header + sizeof(ipc_magic), &msg->size, sizeof(msg->size));
    memcpy(header + sizeof(ipc_magic) + sizeof(msg->size), &msg->type,
           sizeof(msg->type));

    /* Send header first */
    if (send(fd, header, IPC_HEADER_SIZE, 0) == -1) {
        perror("Error sending message header");
        return -errno;
    }

    /* Skip sending data if size is 0 */
    if (msg->size == 0) return 0;

    if (send(fd, (const void*)msg->data, msg->size, 0) == -1) {
        perror("Error sending message data");
        return -errno;
    }
    return 0;
}

int socket_recv(int fd, message_s* msg)
{
    char header[IPC_HEADER_SIZE];

    // Receive incoming header
    if (recv_n(fd, header, IPC_HEADER_SIZE) == -1) {
        perror("Unable to receive IPC response");
        return -errno;
    }

    // Create message from header
    memcpy(&msg->size, header + sizeof(ipc_magic), sizeof(msg->size));
    memcpy(&msg->type, header + sizeof(ipc_magic) + sizeof(msg->size),
           sizeof(msg->type));

    // Allocate memory for payload
    msg->data = malloc(msg->size + 1);
    if (msg->data == NULL) {
        perror("Unable to allocate memory for IPC response");
        return -errno;
    }

    // Receive incoming data
    if (recv_n(fd, msg->data, msg->size) == -1) {
        perror("Unable to receive IPC response");
        free(msg->data);
        return -errno;
    }

    // Null-terminate the payload
    msg->data[msg->size] = '\0';

    return 0;
}

int socket_peek(int fd, message_s* msg) {
    char header[IPC_HEADER_SIZE];

    // Receive incoming header
    if (recv_n(fd, header, IPC_HEADER_SIZE, MSG_PEEK) == -1) {
        perror("Unable to receive IPC response");
        return -errno;
    }

    // Create message from header
    memcpy(&msg->size, header + sizeof(ipc_magic), sizeof(msg->size));
    memcpy(&msg->type, header + sizeof(ipc_magic) + sizeof(msg->size),
           sizeof(msg->type));

    return 0;
}


int recv_n(int fd, void* buffer, size_t size, int flags)
{
    size_t  total = 0;
    ssize_t received;

    while (total < size) {
        received = recv(fd, (char*)buffer + total, size - total, flags);
        if (received <= 0) {
            return -1;
        }
        total += received;
    }

    return 0;
}
