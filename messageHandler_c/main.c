
#include <stdlib.h>
#include <stdio.h>
#include "message_handler.h"
#include "message_queue.h"

/**
 * My Receive Handler
 * @param handler Pointer to message type being handled
 * @param buffer  Pointer to message in heap.
 */
void myReceiveHandler(struct message_type *handler, uint8_t *buffer) {

    struct test_message_response {
        uint8_t packet1;
        uint8_t packet2;
        uint8_t packet3;
    };

    // convert buffer to test_message
    struct test_message_response *testMessage = (struct test_message_response *) buffer;

    // accessing the data through struct instead of byte array:
    printf("My packets are   %d %d %d\n", testMessage->packet1, testMessage->packet2, testMessage->packet3);
    printf("My raw buffer is %d %d %d\n", buffer[0], buffer[1], buffer[2]);

    // free message received from heap
    free(buffer);
}
/**
 * Do nothing handler
 * @param handler Pointer to message type being handled
 * @param buffer  Pointer to message in heap.
 */
void doNothingHandler(struct message_type *handler, uint8_t *buffer) {
    free(buffer);
}

int main(void) {
    struct message_type myHandlers[] = {
        {
        //ID 0
        .sendLength = 1,
        .receiveLength = 2,
        .receiveHandler = &doNothingHandler
        },
        {
        //ID 1,
        .sendLength = 1,
        .receiveLength = 5,
        .receiveHandler = &doNothingHandler
        },
        {
        //ID 2
        .sendLength = 1,
        .receiveLength = 3,
        .receiveHandler = &myReceiveHandler
        }
    };

    struct message_type *currentHandler;
    // scenario: no message is being handled, and a message containing ascii
    // 2 comes in. therefore, we generate the byte buffer for the message data  
    // for the message type 2.
    currentHandler = &myHandlers[2];

    uint8_t *message = malloc(currentHandler->receiveLength * sizeof(uint8_t)); 
 
    //scenario: a 1 comes in over UART
    message[0] = 1;
    //scenario: a 2 comes in over UART
    message[1] = 2;
    //scenario: a 3 comes in over UART
    message[2] = 3;

    message_queue_push(currentHandler, message);

    
    struct message_queue_item incomingMessage;
    while(1) {
        if(message_queue_has_next()) {
            incomingMessage = message_queue_pop();
            incomingMessage.message_type->receiveHandler(incomingMessage.message_type,incomingMessage.buffer);
        }
    }
    currentHandler->receiveHandler(currentHandler, message);
} 
