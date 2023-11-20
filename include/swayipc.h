#ifndef SWAYIPC_H
#define SWAYIPC_H

#include "events.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// Enum defining different sway message types
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

// Extern declaration of sway socket file descriptor
extern int swayipc_fd;

/**
 * Initializes swayipc.
 *
 * @return 0 on success or -1 on error.
 */
extern int swayipc_init(void);

/**
 * Shuts down swayipc.
 *
 * @return 0 on success or -1 on error.
 */
extern int swayipc_shutdown(void);

/**
 * Gets the last sway event.
 *
 * @return Pointer to the last sway event on success, NULL on error.
 */
extern event_s* swayipc_get_event(void);

/**
 * Checks if an event is a sway event.
 *
 * @param event The event to check
 * @return 0 if the event is a sway event, -1 otherwise.
 */
extern int swayipc_is_event(uint32_t event);

/**
 * Reads the next event from IPC and saves it to the event queue.
 *
 * @return 0 on success or -1 on error.
 */
extern int swayipc_handle_events(void);

/**
 * Sends a command to sway.
 *
 * @param command The command to send
 * @param len Length of the command
 * @return 0 on success or -1 on error.
 */
extern int swayipc_send_command(const char* command, size_t len);

/**
 * Subscribes to sway events.
 *
 * @param events Array of events to subscribe to
 * @param len Length of the events array
 * @return 0 on success or -1 on error.
 */
extern int swayipc_subscribe(enum event_type* events, size_t len);

/**
 * Gets a list of current outputs.
 *
 * @param outputs Pointer to store the list of outputs
 * @param len Length of the outputs array
 * @return 0 on success or -1 on error.
 */
extern int swayipc_get_outputs(char* outputs, size_t len);

/**
 * Gets the node layout.
 *
 * @param tree Pointer to store the node layout
 * @param len Length of the tree array
 * @return 0 on success or -1 on error.
 */
extern int swayipc_get_tree(char* tree, size_t len);

/**
 * Gets sway version info.
 *
 * @param version Pointer to store the version info
 * @param len Length of the version array
 * @return 0 on success or -1 on error.
 */
extern int swayipc_get_version(char* version, size_t len);

/**
 * Gets a list of current marks.
 *
 * @param marks Pointer to store the list of marks
 * @param len Length of the marks array
 * @return 0 on success or -1 on error.
 */
extern int swayipc_get_marks(char* marks, size_t len);

/**
 * Gets the bar config.
 *
 * @param bar_config Pointer to store the bar config
 * @param len Length of the bar_config array
 * @return 0 on success or -1 on error.
 */
extern int swayipc_get_bar_config(char* bar_config, size_t len);

/**
 * Gets the list of current binding modes.
 *
 * @param binding_modes Pointer to store the list of binding modes
 * @param len Length of the binding_modes array
 * @return 0 on success or -1 on error.
 */
extern int swayipc_get_binding_modes(char* binding_modes, size_t len);

/**
 * Gets the current sway configuration.
 *
 * @param config Pointer to store the sway configuration
 * @param len Length of the config array
 * @return 0 on success or -1 on error.
 */
extern int swayipc_get_config(char* config, size_t len);

/**
 * Gets the current sway binding state.
 *
 * @param binding_state Pointer to store the binding state
 * @param len Length of the binding_state array
 * @return 0 on success or -1 on error.
 */
extern int swayipc_get_binding_state(char* binding_state, size_t len);

/**
 * Gets the list of current inputs.
 *
 * @param inputs Pointer to store the list of inputs
 * @param len Length of the inputs array
 * @return 0 on success or -1 on error.
 */
extern int swayipc_get_inputs(char* inputs, size_t len);

/**
 * Gets the list of current seats.
 *
 * @param seats Pointer to store the list of seats
 * @param len Length of the seats array
 * @return 0 on success or -1 on error.
 */
extern int swayipc_get_seats(char* seats, size_t len);

/**
 * Gets the list of current workspaces.
 *
 * @param workspaces Pointer to store the list of workspaces
 * @param len Length of the workspaces array
 * @return 0 on success or -1 on error.
 */
extern int swayipc_get_workspaces(char* workspaces, size_t len);

/**
 * Gets the string representation of an event.
 *
 * @param event The event type to get the string representation for
 * @return The string representation of the event, or "unknown" on error.
 */
extern const char* swayipc_get_event_string(uint32_t event);

#endif
