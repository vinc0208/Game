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

void menuSelect(int menu, int* level, int* gamestart);
int menuConfirm(int menu, uint8_t sel, int* gamestart);
void mainMenu();
void helpMenu();
void diffMenu();
void printMode(int lvl);
void deathMenu();
void pauseMenu();


#endif /* MENU_FUNCTIONS_H_ */
