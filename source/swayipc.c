#include "socket.h"
#include "swayipc.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int swayipc_get_info(enum message_type type, char* buf, size_t len) {
    message_s msg = {.size = 0, .type = type, .data = 0};
    message_s reply;

    if (socket_request(swayipc_fd, &msg, &reply) < 0) {
        perror("Cannot send request");
        return -errno;
    }

    snprintf(buf, len, "%s", reply.data);
    return 0;
}

int swayipc_get_outputs(char* buf, size_t len)
{
    return swayipc_get_info(GET_OUTPUTS, buf, len);
}

int swayipc_get_workspaces(char* buf, size_t len)
{
    return swayipc_get_info(GET_WORKSPACES, buf, len);
}

int swayipc_get_version(char* buf, size_t len)
{
    return swayipc_get_info(GET_VERSION, buf, len);
}

int swayipc_get_bar_config(char* buf, size_t len)
{
    return swayipc_get_info(GET_BAR_CONFIG, buf, len);
}

int swayipc_get_binding_modes(char* buf, size_t len)
{
    return swayipc_get_info(GET_BINDING_MODES, buf, len);
}

int swayipc_get_config(char* buf, size_t len)
{
    return swayipc_get_info(GET_CONFIG, buf, len);
}

int swayipc_get_binding_state(char* buf, size_t len)
{
    return swayipc_get_info(GET_BINDING_STATE, buf, len);
}

int swayipc_get_inputs(char* buf, size_t len)
{
    return swayipc_get_info(GET_INPUTS, buf, len);
}

int swayipc_get_marks(char* buf, size_t len)
{
    return swayipc_get_info(GET_MARKS, buf, len);
}

int swayipc_get_tree(char* buf, size_t len)
{
    return swayipc_get_info(GET_TREE, buf, len);
}

int swayipc_get_seats(char* buf, size_t len)
{
    return swayipc_get_info(GET_SEATS, buf, len);
}
