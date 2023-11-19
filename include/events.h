#ifndef EVENTS_H
#define EVENTS_H

#include <pthread.h>
#include <stdlib.h>

#define EVENT_QUEUE_SIZE 100

// sway event types
enum event_type {
    SWAY_EVENT_WORKSPACE        = 0x80000000,
    SWAY_EVENT_MODE             = 0x80000002,
    SWAY_EVENT_WINDOW           = 0x80000003,
    SWAY_EVENT_BARCONFIG_UPDATE = 0x80000004,
    SWAY_EVENT_BINDING          = 0x80000005,
    SWAY_EVENT_SHUTDOWN         = 0x80000006,
    SWAY_EVENT_TICK             = 0x80000007,
    SWAY_EVENT_BAR_STATE_UPDATE = 0x80000014,
    SWAY_EVENT_INPUT            = 0x80000015,
};

// sway event
typedef struct {
    enum event_type type;
    char*           data;
    size_t          size;
} event_s;

// sway event queue
typedef struct {
    event_s*        events[EVENT_QUEUE_SIZE];
    size_t          head;
    size_t          tail;
    size_t          size;
    pthread_mutex_t lock;
} event_queue_s;

event_queue_s* event_queue_init(void);
int            event_queue_push(event_queue_s* queue, event_s* event);
event_s*       event_queue_pop(event_queue_s* queue);
int            event_queue_destroy(event_queue_s* queue);
int            event_queue_is_empty(event_queue_s* queue);
int            event_queue_is_full(event_queue_s* queue);
int            event_queue_destroy(event_queue_s* queue);

#endif
