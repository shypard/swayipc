#ifndef SOCKET_H
#define SOCKET_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// Structure representing a message
typedef struct {
    uint32_t size;
    uint32_t type;
    char*    data;
} message_s;

/**
 * Opens a socket.
 *
 * @return File descriptor for the opened socket, or -1 on failure
 */
int socket_open(void);

/**
 * Closes a socket.
 *
 * @param fd File descriptor of the socket to be closed
 * @return 0 if successful, -1 otherwise
 */
int socket_close(int fd);

/**
 * Receives a message from the socket.
 *
 * @param fd File descriptor of the socket
 * @param msg Pointer to the message structure to store the received message
 * @return 0 if successful, -1 otherwise
 */
int socket_recv(int fd, message_s* msg);

/**
 * Peeks at the next message in the socket without removing it from the queue.
 *
 * @param fd File descriptor of the socket
 * @param msg Pointer to the message structure to store the peeked message
 * @return 0 if successful, -1 otherwise
 */
int socket_peek(int fd, message_s* msg);

/**
 * Sends a message through the socket.
 *
 * @param fd File descriptor of the socket
 * @param msg Pointer to the message structure to be sent
 * @return Number of bytes sent, or -1 on failure
 */
int socket_send(int fd, const message_s* msg);

/**
 * Sends a request message and receives a reply through the socket.
 *
 * @param fd File descriptor of the socket
 * @param msg Pointer to the message structure to be sent as a request
 * @param reply Pointer to the message structure to store the received reply
 * @return 0 if successful, -1 otherwise
 */
int socket_request(int fd, const message_s* msg, message_s* reply);

/**
 * Receives a specified number of bytes from the socket.
 *
 * @param fd File descriptor of the socket
 * @param buffer Pointer to the buffer to store the received data
 * @param size Number of bytes to receive
 * @param flags Flags specifying the behavior of the recv function
 * @return Number of bytes received, or -1 on failure
 */
int recv_n(int fd, void* buffer, size_t size, int flags);

#endif
