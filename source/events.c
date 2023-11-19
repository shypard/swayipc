#include "events.h"

#include <pthread.h>
#include <stdio.h>

event_queue_s* event_queue_init(void)
{
    event_queue_s* queue = malloc(sizeof(event_queue_s));
    if (queue == NULL) {
        return NULL;
    }
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;

    // Initialize the mutex
    pthread_mutex_init(&queue->lock, NULL);

    return queue;
}

int event_queue_push(event_queue_s* queue, event_s* event)
{
    pthread_mutex_lock(&queue->lock);

    if (queue->size == EVENT_QUEUE_SIZE) {
        pthread_mutex_unlock(&queue->lock);
        return -1;
    }

    queue->events[queue->tail] = event;
    queue->tail                = (queue->tail + 1) % EVENT_QUEUE_SIZE;
    queue->size++;

    pthread_mutex_unlock(&queue->lock);
    return 0;
}

event_s* event_queue_pop(event_queue_s* queue)
{
    pthread_mutex_lock(&queue->lock);

    if (queue->size == 0) {
        pthread_mutex_unlock(&queue->lock);
        return NULL;
    }

    event_s* event = queue->events[queue->head];
    queue->head    = (queue->head + 1) % EVENT_QUEUE_SIZE;
    queue->size--;

    pthread_mutex_unlock(&queue->lock);
    return event;
}

int event_queue_destroy(event_queue_s* queue)
{
    pthread_mutex_lock(&queue->lock);

    // Check if the queue is already freed
    if (queue == NULL) {
        pthread_mutex_unlock(&queue->lock);
        return -1;
    }

    // Iterate over all events and free them
    for (int i = 0; i < queue->size; i++) {
        event_s* event = queue->events[i];
        if (event != NULL) {
            free(event);
            event = NULL;
        }
    }

    // Destroy the mutex
    pthread_mutex_destroy(&queue->lock);

    // Lastly, free the queue itself
    free(queue);
    queue = NULL;
    return 0;
}

int event_queue_is_empty(event_queue_s* queue)
{
    pthread_mutex_lock(&queue->lock);
    int empty = (queue->size == 0);
    pthread_mutex_unlock(&queue->lock);
    return empty;
}

int event_queue_is_full(event_queue_s* queue)
{
    pthread_mutex_lock(&queue->lock);
    int full = (queue->size == EVENT_QUEUE_SIZE);
    pthread_mutex_unlock(&queue->lock);
    return full;
}
