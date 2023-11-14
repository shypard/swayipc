#ifndef SWAYIPC_H
#define SWAYIPC_H

#include "events.h"

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

// sway socket file descriptor
extern int         swayipc_fd;
extern const char* event_strings[];

// Initializes swayipc.
// Returns 0 on success or -1 on error.
extern int swayipc_init(void);

// Shutdown swayipc.
// Returns 0 on success or -1 on error.
extern int swayipc_shutdown(void);

// Sends a command to sway.
// Returns 0 on success or -1 on error.
extern int swayipc_send_command(const char* command, size_t len);

// subscribe to sway events
// Returns 0 on success or -1 on error.
extern int swayipc_subscribe(enum event_type* events, size_t len);

// gets list of current outputs
// Returns 0 on success or -1 on error.
extern int swayipc_get_outputs(char* outputs, size_t len);

// gets the node layout
// Returns 0 on success or -1 on error.
extern int swayipc_get_tree(char* tree, size_t len);

// gets sway version info
// Returns 0 on success or -1 on error.
extern int swayipc_get_version(char* version, size_t len);

// gets list of current marks
// Returns 0 on success or -1 on error.
extern int swayipc_get_marks(char* marks, size_t len);

// gets list of current bar configs
// Returns 0 on success or -1 on error.
extern int swayipc_get_bar_config(char* bar_config, size_t len);

// gets list of current binding modes
// Returns 0 on success or -1 on error.
extern int swayipc_get_binding_modes(char* binding_modes, size_t len);

// gets current sway config
// Returns 0 on success or -1 on error.
extern int swayipc_get_config(char* config, size_t len);

// gets current sway binding state
// Returns 0 on success or -1 on error.
extern int swayipc_get_binding_state(char* binding_state, size_t len);

// gets list of current inputs
// Returns 0 on success or -1 on error.
extern int swayipc_get_inputs(char* inputs, size_t len);

// gets list of current seats
// Returns 0 on success or -1 on error.
extern int swayipc_get_seats(char* seats, size_t len);

// gets list of current workspaces
// Returns 0 on success or -1 on error.
extern int swayipc_get_workspaces(char* workspaces, size_t len);

// gets sway event
// Returns 0 on success or -1 on error.
extern int swayipc_get_event(char* event, size_t len);

#endif
