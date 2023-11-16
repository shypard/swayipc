#include "events.h"


event_queue_s* event_queue_init(void) {
    event_queue_s* queue = malloc(sizeof(event_queue_s));
    if (queue == NULL) {
        return NULL;
    }
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
    return queue;
}


int event_queue_push(event_queue_s* queue, enum event_type event) {
    if (event_queue_is_full(queue))
        return -1;
    queue->events[queue->tail] = event;
    queue->tail = (queue->tail + 1) % EVENT_QUEUE_SIZE;
    queue->size++;
    return 0;
}

int event_queue_pop(event_queue_s* queue, enum event_type* event) {
    if (event_queue_is_empty(queue))
        return -1;
    *event = queue->events[queue->head];
    queue->head = (queue->head + 1) % EVENT_QUEUE_SIZE;
    queue->size--;
    return 0;
}

int event_queue_destroy(event_queue_s* queue) {
    free(queue);
    return 0;
}

int event_queue_is_empty(event_queue_s* queue) {
    return queue->size == 0;
}

int event_queue_is_full(event_queue_s* queue) {
    return queue->size == EVENT_QUEUE_SIZE;
}

