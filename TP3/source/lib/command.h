#ifndef COMMAND_H_
#define COMMAND_H_
#include "types.h"

#define COMMAND_OFF      0
#define COMMAND_ON       1
#define COMMAND_FREQ_SET 2
#define COMMAND_INVALID 0xFF

void command_parse(const char * line);

void command_get_args(uint16_t *);

int8_t command_operation(void);

int8_t command_calc_checksum(void);

int8_t command_response(uint8_t * line);

#endif
