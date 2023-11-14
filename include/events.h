#ifndef EVENTS_H
#define EVENTS_H

#include <stdlib.h>

#define EVENT_QUEUE_SIZE 100

// sway event types
enum event_type {
    WORKSPACE,
    MODE,
    WINDOW,
    BARCONFIG_UPDATE,
    BINDING,
    SHUTDOWN,
    TICK,
    BAR_STATE_UPDATE,
    INPUT
};

typedef struct {
    enum event_type events[EVENT_QUEUE_SIZE];
    size_t          head;
    size_t          tail;
    size_t          size;
    pthread_mutex_t lock;
} event_queue_s;

// TODO: implement event queue functions
int event_queue_init(event_queue_s* queue);
int event_queue_push(event_queue_s* queue, enum event_type event);
int event_queue_pop(event_queue_s* queue, enum event_type* event);
int event_queue_destroy(event_queue_s* queue);
int event_queue_is_empty(event_queue_s* queue);
int event_queue_is_full(event_queue_s* queue);

// TODO: implement check for event
int swayipc_is_event(int event);

// TODO: implement event stream
int swayipc_get_event(void);

#endif
