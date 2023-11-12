#ifndef SWAYIPC_H
#define SWAYIPC_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// sway message types
enum message_type {
    RUN_COMMAND       = 0,
    GET_WORKSPACES    = 1,
    SUBSCRIBE         = 2,
    GET_OUTPUTS       = 3,
    GET_TREE          = 4,
    GET_MARKS         = 5,
    GET_BAR_CONFIG    = 6,
    GET_VERSION       = 7,
    GET_BINDING_MODES = 8,
    GET_CONFIG        = 9,
    SEND_TICK         = 10,
    SYNC              = 11,
    GET_BINDING_STATE = 12,
    GET_INPUTS        = 100,
    GET_SEATS         = 101
};

// sway event types
enum event_type {
    WORKSPACE        = 0x80000000,
    MODE             = 0x80000002,
    WINDOW           = 0x80000003,
    BARCONFIG_UPDATE = 0x80000004,
    BINDING          = 0x80000005,
    SHUTDOWN         = 0x80000006,
    TICK             = 0x80000007,
    BAR_STATE_UPDATE = 0x80000014,
    INPUT            = 0x80000015
};

// sway socket file descriptor
extern int swayipc_fd;

// Initializes swayipc.
// Returns 0 on success or -1 on error.
extern int swayipc_init(void);

// Shutdown swayipc.
// Returns 0 on success or -1 on error.
extern int swayipc_shutdown(void);

// Sends a command to sway.
// Returns 0 on success or -1 on error.
extern int swayipc_send_command(const char* command);

// subscribe to sway events
// Returns 0 on success or -1 on error.
extern int swayipc_subscribe(const char* event);

// gets list of current outputs
// Returns 0 on success or -1 on error.
extern int swayipc_get_outputs(char* outputs);

// gets the node layout
// Returns 0 on success or -1 on error.
extern int swayipc_get_tree(char* tree);

// gets sway version info
// Returns 0 on success or -1 on error.
extern int swayipc_get_version(char* version);

// gets list of current marks
// Returns 0 on success or -1 on error.
extern int swayipc_get_marks(char* marks);

// gets list of current bar configs
// Returns 0 on success or -1 on error.
extern int swayipc_get_bar_config(char* bar_config);

// gets list of current binding modes
// Returns 0 on success or -1 on error.
extern int swayipc_get_binding_modes(char* binding_modes);

// gets current sway config
// Returns 0 on success or -1 on error.
extern int swayipc_get_config(char* config);

// gets current sway binding state
// Returns 0 on success or -1 on error.
extern int swayipc_get_binding_state(char* binding_state);

// gets list of current inputs
// Returns 0 on success or -1 on error.
extern int swayipc_get_inputs(char* inputs);

// gets list of current seats
// Returns 0 on success or -1 on error.
extern int swayipc_get_seats(char* seats);

// gets list of current workspaces
// Returns 0 on success or -1 on error.
extern int swayipc_get_workspaces(char* workspaces);

#endif
