#include "swayipc.h"

#include <cJSON.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* create event handler function in separate thread */
void* event_handler(void* args)
{
    /* loop until swayipc is closed */
    while (1) {
        printf("Waiting for event...\n");
        sleep(1);
        /* get last event from event_queue */
        event_s* last_event = swayipc_get_event();
        if (last_event == NULL) {
            
            continue;
        }

        printf("Recv event: %s\n", swayipc_get_event_string(last_event->type));

        /* check if last event was a window event */
        if (last_event->type == SWAY_EVENT_WINDOW) {
            printf("window event\n");
        }

        /*
        // parse json
        cJSON *json = cJSON_Parse(buf);
        if (!json) {
            printf("Error before: [%s]\n", cJSON_GetErrorPtr());
            return NULL;
        }

        // pretty print json
        char *pretty = cJSON_Print(json);
        printf("sway event:\n%s\n", pretty);
        free(pretty);
        */
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
