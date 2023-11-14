#include "socket.h"
#include "swayipc.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int         swayipc_fd;
const char* event_strings[] = {
    "workspace", "mode",     "window", "barconfig_update",
    "binding",   "shutdown", "tick",   "bar_state_update",
    "input"};

int swayipc_init(void)
{
    if ((swayipc_fd = socket_open()) <= 0) {
        perror("Cannot open sway socket");
        return -errno;
    }
    return 0;
}

int swayipc_shutdown(void) { return socket_close(swayipc_fd); }

int swayipc_handle_events(void)
{
    message_s msg = {.size = 0, .type = GET_EVENT, .data = 0};
    message_s reply;

    if (socket_peek(swayipc_fd, &msg, &reply) < 0) {
        perror("Cannot send request");
        return -errno;
    }
    /* check if reply is an event and save to event stream */
    if (swayipc_is_event(reply.type) == 0) {
        printf("Event: %s\n", reply.data);
        // TODO: save to event stream
        // TODO: remove from socket buffer
        return 0;
    } else {
        return -1;
    }

    int swayipc_subscribe(enum event_type * events, size_t len)
    {
        message_s msg = {.size = 0, .type = SUBSCRIBE, .data = 0};
        message_s reply;
        char      buf[1024];
        size_t    pos = 0;

        buf[pos++] = '[';
        for (size_t i = 0; i < len; i++) {
            if (i > 0) buf[pos++] = ',';
            pos += snprintf(&buf[pos], sizeof(buf) - pos, "\"%s\"",
                            event_strings[events[i]]);
        }

        buf[pos++] = ']';
        buf[pos]   = '\0';

        msg.size = pos;
        msg.data = buf;

        if (socket_request(swayipc_fd, &msg, &reply) < 0) {
            perror("Cannot send request");
            return -errno;
        }

        /* TODO: Use a more sophisticated check*/
        return strncmp("{\"success\": true}", reply.data, reply.size);
    }

    int swayipc_get_info(enum message_type type, char* buf, size_t len)
    {
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
