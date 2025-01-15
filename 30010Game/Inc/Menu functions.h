/*
 * Menu functions.h
 *
 *  Created on: 15 Jan 2025
 *      Author: vince
 */
#include "stdio.h"
#include "stdint.h"

#ifndef MENU_FUNCTIONS_H_
#define MENU_FUNCTIONS_H_

void menuSelect(int menu, int* level);
int menuConfirm(int menu, uint8_t sel);


#endif /* MENU_FUNCTIONS_H_ */
