/*
 * main.c
 *
 *  Created on: Feb 12, 2015
 *      Author: vartan
 */
#include "lpc11uxx.h"
#include "main.h"
#include "globals.h"
#include "MotorDriver.h"
#include "timers.h"
#include "message_handler.h"
#include "message_queue.h"
#include <stdbool.h>
void doNothingHandler (struct message_type *handler, uint8_t *buffer) {
}
	struct message_type myHandlers[] = {
			{
			.id             = 0,
			.sendLength     = 0,
			.receiveLength  = 0,
			.receiveHandler = &doNothingHandler
			},
			{
			.id             = 1,
			.sendLength     = 0,
			.receiveLength  = 0,
			.receiveHandler = &doNothingHandler
			},
			{
			.id             = 2,
			.sendLength     = 0,
			.receiveLength  = 0,
			.receiveHandler = &doNothingHandler
			},
			{
			.id             = 3,
			.sendLength     = 0,
			.receiveLength  = 6,
			.receiveHandler = &updateMotionVectorHandler
			}
	};
void simulateMessageReceive(void) {
    struct message_type *currentHandler;
    // scenario: no message is being handled, and a message containing ascii
    // 2 comes in. therefore, we generate the byte buffer for the message data  
    // for the message type 2.
    currentHandler = &myHandlers[3];

    uint8_t *message = malloc(currentHandler->receiveLength * sizeof(uint8_t)); 
		for(int i=0;i<currentHandler->receiveLength;i++)
			message[i] = (i*10)&0xFF;


    message_queue_push(currentHandler, message);
}
int main() {
	struct message_queue_item *incomingMessage;
  struct MotorDriver motors[MOTOR_COUNT];
	
	initMotorDrivers(motors);
	simulateMessageReceive();
	while(1) {
        if(message_queue_has_next()) {
            incomingMessage = message_queue_pop();
            incomingMessage->message_type->receiveHandler(
							incomingMessage->message_type,
							incomingMessage->buffer
						);
					  free(incomingMessage->buffer);
					  free(incomingMessage);
        }
	}
}
