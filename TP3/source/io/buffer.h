#ifndef BUFFER_H_
#define BUFFER_H_
#include "types.h"

#define BUFFER_CAPACIDAD 32
#define BUFFER_MOD_MASK 0x1F

struct buffer {
	uint8_t size;
	uint8_t head;
	uint8_t tail;
	uint8_t array[BUFFER_CAPACIDAD];
};

void buffer_init(volatile struct buffer *);

void buffer_push(volatile struct buffer *, uint8_t val);

uint8_t buffer_pop(volatile struct buffer *);

uint8_t buffer_size(volatile struct buffer *);

uint8_t buffer_empty(volatile struct buffer *);

uint8_t buffer_full (volatile struct buffer *);

#endif /* BUFFER_H_ */
