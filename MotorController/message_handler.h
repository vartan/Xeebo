#include <stdlib.h>
#include <stdio.h>

#ifndef __message_handler_h
#define __message_handler_h
/**
 * Message handler:
 * Defines the id, and lengths of message protocol.
 */
struct message_type {
	uint8_t id;
    uint8_t sendLength;
    uint8_t receiveLength;
    void (*receiveHandler)(struct message_type *handler, uint8_t *buffer);
};
enum SerialMessageNames {
	MSG_FLUSH       = 0x00, // Do nothing; Send (MAX(num bytes)) times to flush out messages if out of sync.
	MSG_PING        = 0x01, // Send a ping to verify that the line is valid
	MSG_PONG        = 0x02, // Reply to a ping with a pong
	MSG_NEW_MOTION  = 0x03, // Update the motion vectors to move the robot
	MSG_GET_MOTION  = 0x04, // Request the motion vector state controlling the motors
	MSG_GET_BATTERY = 0x05, // Request the current battery life
};
extern struct message_type message_handlers[];
#endif
