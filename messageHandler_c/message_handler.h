#include <stdlib.h>
#include <stdio.h>

#ifndef __message_handler_h
#define __message_handler_h
/**
 * Message handler:
 * Defines the id, and lengths of message protocol.
 */
struct message_type {
    uint8_t sendLength;
    uint8_t receiveLength;
    void (*receiveHandler)(struct message_type *handler, uint8_t *buffer);
};
#endif