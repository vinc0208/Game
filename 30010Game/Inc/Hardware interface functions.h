/*
 * Hardware interface functions.h
 *
 *  Created on: 13 Jan 2025
 *      Author: vince
 */

#include "stdio.h"
#include "stdint.h"

typedef struct {
	uint16_t hour, minute, second, hsecond, msecond;
} TimeFormat;
TimeFormat TimeMaster;

typedef struct {
	int life, score, ammo;
} stats;
stats player;

#ifndef HARDWARE_INTERFACE_FUNCTIONS_H_
#define HARDWARE_INTERFACE_FUNCTIONS_H_

void uartStringModifier(char arr[]);

char uartKeyRead();



#endif /* HARDWARE_INTERFACE_FUNCTIONS_H_ */
