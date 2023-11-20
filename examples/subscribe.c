#include "swayipc.h"

#include <cJSON.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* create event handler function in separate thread */
void* event_handler(void* args)
{
    cJSON* json   = NULL;
    char*  pretty = NULL;

    /* loop until swayipc is closed */
    while (1) {
        /* get last event from event_queue */
        event_s* last_event = swayipc_get_event();

        /* if no event is available, continue */
        if (last_event == NULL) continue;

        if (last_event->type == SWAY_EVENT_WINDOW) {
            if ((json = cJSON_Parse(last_event->data)) == NULL) {
                printf("Error before: [%s]\n", cJSON_GetErrorPtr());
                continue;
            }

            /* pretty print event as JSON */
            pretty = cJSON_Print(json);
            printf("sway event:\n%s\n", pretty);
            free(pretty);
        }
    }
}

int main(void)
{
    /* initialize swayipc */
    swayipc_init();

    enum event_type to_sub[] = {SWAY_EVENT_WORKSPACE, SWAY_EVENT_WINDOW};

    /* subscribe to WINDOW and WORKSPACE events */
    swayipc_subscribe(to_sub, 2);

    /* start event handler thread */
    pthread_t thread;
    pthread_create(&thread, NULL, event_handler, NULL);

    /* run until swayipc is closed */
    while (1) {
        // sleep a few milliseconds
        swayipc_handle_events();
    }

    /* close swayipc */
    swayipc_shutdown();

    return 0;
}
