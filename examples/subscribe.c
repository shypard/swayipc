#include "swayipc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>


/* create event handler function in separate thread */
void *event_handler(void* args) {
    /* initialize buffer */
    char buf[2048];

    /* loop until swayipc is closed */
    while (1) {
        /* get next event */
        swayipc_get_event(buf, sizeof(buf));

        /* parse json */
        cJSON *json = cJSON_Parse(buf);
        if (!json) {
            printf("Error before: [%s]\n", cJSON_GetErrorPtr());
            return NULL;
        }

        /* pretty print */
        char *pretty = cJSON_Print(json);
        printf("sway event:\n%s\n", pretty);
        free(pretty);
    }
}


int main(void) {
    /* initialize swayipc and pthreads */
    swayipc_init();
    pthread_init();

    /* subscribe to WINDOW and WORKSPACE events */
    swayipc_subscribe([WINDOW, WORKSPACE], 2);

    /* start event handler thread */
    pthread_t thread;
    pthread_create(&thread, NULL, event_handler, NULL);
    pthreat_join(thread, NULL);


    /* close swayipc */
    swayipc_shutdown();

    return 0;
}
