#include "socket.h"
#include "swayipc.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int swayipc_fd;

int swayipc_init(void)
{
    if ((swayipc_fd = socket_open()) <= 0) {
        perror("Cannot open sway socket");
        return -errno;
    }
    return 0;
}

int swayipc_shutdown(void) { return socket_close(swayipc_fd); }

int swayipc_get_outputs(char* outputs)
{
    int ret;

    message_s  msg   = {.size = 0, .type = GET_OUTPUTS, .data = 0};
    message_s* reply = (message_s*)malloc(sizeof(message_s));

    ret = socket_request(swayipc_fd, &msg, reply);
    printf("Reply: %s\n", reply->data);
    return ret;
}

int swayipc_get_version(char* version)
{
    int ret;

    message_s  msg   = {.size = 0, .type = GET_VERSION, .data = 0};
    message_s* reply = (message_s*)malloc(sizeof(message_s));

    ret = socket_request(swayipc_fd, &msg, reply);
    printf("Reply: %s\n", reply->data);
    return ret;
}
