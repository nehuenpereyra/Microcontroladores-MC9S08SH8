#ifndef SOUND_H_
#define SOUND_H_
#include "types.h"

void sound_init(void);

void sound_on(void);

void sound_off(void);

char sound_set_freq(const uint16_t f); 

void sound_int_handler(void);

#endif
