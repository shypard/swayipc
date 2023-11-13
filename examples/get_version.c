#include "swayipc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cJSON.h>

#define LEN 2048

int main(void) {
    /* initialize swayipc */
    swayipc_init();

    /* get version */
    char version[LEN];
    swayipc_get_version(version, LEN);

    /* parse json */
    cJSON *json = cJSON_Parse(version);
    if (!json) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        return 1;
    }

    /* pretty print */
    char *pretty = cJSON_Print(json);
    printf("sway get_version:\n%s\n", pretty);
    free(pretty);

    /* close swayipc */
    swayipc_shutdown();

    return 0;
}
