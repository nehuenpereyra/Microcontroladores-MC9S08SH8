#ifndef SERIAL_H_
#define SERIAL_H_
#include "types.h"

void serial_init(void);

void serial_send(const char * str);

void serial_recv(char *str, const uint8_t n);

void serial_tx_handler(void);

void serial_rx_handler(void);

#endif /* SERIAL_H_ */
