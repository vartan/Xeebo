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
int main() {
	struct message_queue_item *incomingMessage;
  struct MotorDriver motors[MOTOR_COUNT];
	initMotorDrivers(motors);
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
