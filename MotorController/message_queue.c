#include "message_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "message_handler.h"
#include <stdint.h>
static struct {
    struct message_queue_item *head;
    struct message_queue_item *tail;
    uint8_t length;
} message_queue_list ;

bool message_queue_has_next() {
	return message_queue_list.length > 0;
}
uint8_t message_queue_size() {
	return message_queue_list.length;
}
void message_queue_push(struct message_type *message_type, uint8_t *message) {
	// create the message_queue_item in the heap
	struct message_queue_item *item = malloc(sizeof(struct message_queue_item));
	item->message_type = message_type;
	item->buffer 	   = message;
	if(message_queue_list.length > 0) {
		message_queue_list.tail->next = item;
		message_queue_list.tail = item;
	} else {
		message_queue_list.head = item;
		message_queue_list.tail = item;
	}
	message_queue_list.length++;
}

struct message_queue_item message_queue_pop() {
	// create a copy of the head item
	struct message_queue_item head;
	head = *message_queue_list.head; 
	// delete the actual head in the heap
	free(message_queue_list.head); 
	// set the new head
	message_queue_list.head = head.next; 
	message_queue_list.length--;
	return head;
}
