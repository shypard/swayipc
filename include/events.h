#ifndef EVENTS_H
#define EVENTS_H

#include <stdlib.h>

#define EVENT_QUEUE_SIZE 100

// sway event types
enum event_type {
    SWAY_EVENT_WORKSPACE,
    SWAY_EVENT_MODE,
    SWAY_EVENT_WINDOW,
    SWAY_EVENT_BARCONFIG_UPDATE,
    SWAY_EVENT_BINDING,
    SWAY_EVENT_SHUTDOWN,
    SWAY_EVENT_TICK,
    SWAY_EVENT_BAR_STATE_UPDATE,
    SWAY_EVENT_INPUT
};

typedef struct {
    enum event_type events[EVENT_QUEUE_SIZE];
    size_t          head;
    size_t          tail;
    size_t          size;
    pthread_mutex_t lock;
} event_queue_s;

event_queue_s* event_queue_init(void);
int event_queue_push(event_queue_s* queue, enum event_type event);
int event_queue_pop(event_queue_s* queue, enum event_type* event);
int event_queue_destroy(event_queue_s* queue);
int event_queue_is_empty(event_queue_s* queue);
int event_queue_is_full(event_queue_s* queue);
int event_queue_destroy(event_queue_s* queue);

#endif
