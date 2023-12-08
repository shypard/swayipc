#define _GNU_SOURCE

#include "swayipc.h"

#include <cJSON.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Global variables */
int running = 1;

/* signal handler */
void signal_handler(int signal_num) { running = 0; }

/* split windows */
void split(cJSON* json)
{
    /* pretty print event as JSON */
    char* j = cJSON_Print(json);
    printf("sway event:\n%s\n", j);
    free(j);
}

int main(void)
{
    cJSON*          json  = NULL;
    struct timespec ts    = {0, 1000 * 1000 * 10}; // 100 milliseconds
    enum event_type sub[] = {SWAY_EVENT_WINDOW};

    /* register signal handlers */
    signal(SIGINT, signal_handler);  // SIGINT: Ctrl+C
    signal(SIGTERM, signal_handler); // SIGTERM: Termination signal

    /* initialize swayipc */
    swayipc_init();

    /* subscribe to WINDOW and WORKSPACE events */
    swayipc_subscribe(sub, 1);

    /* loop until swayipc is closed */
    while (running) {
        /* sleep a few milliseconds to avoid 100% CPU usage */
        nanosleep(&ts, NULL);

        /* get last event from event_queue */
        event_s* last_event = swayipc_get_event();

        /* if no event is available, continue */
        if (last_event == NULL) continue;

        if (last_event->type == SWAY_EVENT_WINDOW) {

            /* parse JSON data */
            if ((json = cJSON_Parse(last_event->data)) == NULL) {
                printf("autotiling: error before: [%s]\n", cJSON_GetErrorPtr());
                continue;
            }

            /* split windows */
            split(json);
        }
    }

    /* shutdown swayipc */
    swayipc_shutdown();

    return 0;
}
