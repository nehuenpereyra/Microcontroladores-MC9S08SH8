/*
 * keypad.h
 *
 *  Created on: 30/04/2020
 *      Author: Nehuen
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <mc9s08sh8.h>
#include "main.h"

uint8_t keypad_scan(uint8_t *pkey);

void keypad_init(void);

#endif /* KEYPAD_H_ */
