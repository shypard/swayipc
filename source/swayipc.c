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

int swayipc_get_info(enum message_type type, char* info)
{
    int ret;

    message_s msg = {.size = 0, .type = type, .data = 0};
    message_s reply;

    ret = socket_request(swayipc_fd, &msg, &reply);
    // printf("Reply: %s\n", reply.data);
    if (ret < 0) {
        perror("Cannot send request");
        return -errno;
    }

    return ret;
}

int swayipc_get_outputs(char* buffer)
{
    return swayipc_get_info(GET_OUTPUTS, buffer);
}

int swayipc_get_workspaces(char* buffer)
{
    return swayipc_get_info(GET_WORKSPACES, buffer);
}

int swayipc_get_version(char* buffer)
{
    return swayipc_get_info(GET_VERSION, buffer);
}

int swayipc_get_bar_config(char* buffer)
{
    return swayipc_get_info(GET_BAR_CONFIG, buffer);
}

int swayipc_get_binding_modes(char* buffer)
{
    return swayipc_get_info(GET_BINDING_MODES, buffer);
}

int swayipc_get_config(char* buffer)
{
    return swayipc_get_info(GET_CONFIG, buffer);
}

int swayipc_get_binding_state(char* buffer)
{
    return swayipc_get_info(GET_BINDING_STATE, buffer);
}

int swayipc_get_inputs(char* buffer)
{
    return swayipc_get_info(GET_INPUTS, buffer);
}

int swayipc_get_marks(char* buffer)
{
    return swayipc_get_info(GET_MARKS, buffer);
}

int swayipc_get_tree(char* buffer)
{
    return swayipc_get_info(GET_TREE, buffer);
}

int swayipc_get_seats(char* buffer)
{
    return swayipc_get_info(GET_SEATS, buffer);
}
