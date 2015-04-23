#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#ifndef __message_handler_h__
#define __message_handler_h__

struct message_queue_item {
    struct message_type *message_type;
    uint8_t *buffer;
    struct message_queue_item *next;
};
bool message_queue_has_next(void);
uint8_t message_queue_size(void);
void message_queue_push(struct message_type *message_type, uint8_t *message);
struct message_queue_item *message_queue_pop(void);

#endif
