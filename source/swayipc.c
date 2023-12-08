#define _GNU_SOURCE

#include "events.h"
#include "socket.h"
#include "swayipc.h"

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SWAYIPC_SLEEP_TIME_NS 50 * 1000 * 1000 // 50ms

// Global variables
int            run_event_loop = 1;
int            swayipc_fd;
event_queue_s* events;
pthread_t      event_loop_thread;

// Internal function declarations
void* swayipc_start_event_loop(void*);

int swayipc_init(void)
{
    if ((swayipc_fd = socket_open()) <= 0) {
        perror("Cannot open sway socket");
        return -errno;
    }

    // create event queue
    events = event_queue_init();
    if (events == NULL) {
        perror("Cannot create event queue");
        return -errno;
    }

    // start listening for events
    pthread_create(&event_loop_thread, NULL, swayipc_start_event_loop, NULL);

    return 0;
}

void* swayipc_start_event_loop(void*)
{
    struct timespec ts = {.tv_sec = 0, .tv_nsec = SWAYIPC_SLEEP_TIME_NS};
    while (run_event_loop) {
        nanosleep(&ts, NULL);
        swayipc_handle_events();
    }
    return NULL;
}

int swayipc_shutdown(void)
{
    run_event_loop = 0;
    pthread_join(event_loop_thread, NULL);
    event_queue_destroy(events);
    socket_close(swayipc_fd);
    return 0;
}

event_s* swayipc_get_event(void)
{
    if (event_queue_is_empty(events)) {
        return NULL;
    }
    return event_queue_pop(events);
}

int swayipc_is_event(uint32_t event)
{
    switch (event) {
    case SWAY_EVENT_WORKSPACE:
    case SWAY_EVENT_MODE:
    case SWAY_EVENT_WINDOW:
    case SWAY_EVENT_BARCONFIG_UPDATE:
    case SWAY_EVENT_BINDING:
    case SWAY_EVENT_SHUTDOWN:
    case SWAY_EVENT_TICK:
        return 1;
    default:
        return 0;
    }
}

// Converts a sway event type to its string representation
const char* swayipc_get_event_string(uint32_t event)
{
    switch (event) {
    case SWAY_EVENT_WORKSPACE:
        return "workspace";
    case SWAY_EVENT_MODE:
        return "mode";
    case SWAY_EVENT_WINDOW:
        return "window";
    case SWAY_EVENT_BARCONFIG_UPDATE:
        return "barconfig_update";
    case SWAY_EVENT_BINDING:
        return "binding";
    case SWAY_EVENT_SHUTDOWN:
        return "shutdown";
    case SWAY_EVENT_TICK:
        return "tick";
    case SWAY_EVENT_INPUT:
        return "input";
    default:
        return "unknown";
    }
}

int swayipc_handle_events(void)
{
    message_s msg;

    // check if there is a message
    if (socket_peek(swayipc_fd, &msg) < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return 0;
        perror("Cannot peek socket");
        return -errno;
    }

    // check incoming is an event and save to event stream
    if (swayipc_is_event(msg.type)) {
        event_s* event = malloc(sizeof(event_s));
        if (event == NULL) {
            perror("Cannot allocate memory for event");
            return -errno;
        }

        // read full message from socket
        socket_recv(swayipc_fd, &msg);

        event->type = msg.type;
        event->size = msg.size;
        event->data = msg.data;

        // push event to event queue
        event_queue_push(events, event);
        return 0;
    } else {
        // clear message from socket
        socket_recv(swayipc_fd, &msg);
        return -1;
    }
}

int swayipc_subscribe(enum event_type* events, size_t len)
{
    message_s msg = {.size = 0, .type = SUBSCRIBE, .data = 0};
    message_s reply;
    char      buf[1024];
    size_t    pos = 0;

    buf[pos++] = '[';
    for (size_t i = 0; i < len; i++) {
        if (i > 0) buf[pos++] = ',';
        pos += snprintf(&buf[pos], sizeof(buf) - pos, "\"%s\"",
                        swayipc_get_event_string(events[i]));
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

int swayipc_send_command(const char* command, size_t len)
{
    message_s msg = {.size = len, .type = RUN_COMMAND, .data = command};
    message_s reply;

    if (socket_request(swayipc_fd, &msg, &reply) < 0) {
        perror("Cannot send request");
        return -errno;
    }

    // TODO: Use a more sophisticated check
    return strncmp("[ { \"success\": true } ]", reply.data, reply.size);
}
