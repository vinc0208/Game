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

void menuSelect(int8_t menu, int8_t* level, int8_t* gamestart, int8_t* first);
int menuConfirm(int8_t menu, uint8_t sel, int8_t* gamestart);
void mainMenu();
void helpMenu();
void diffMenu();
void printMode(int lvl);
void deathMenu();
void pauseMenu();
void bossMenu();

void pause_unpause(int8_t *gamestart, int8_t *menu, uint8_t *key, int8_t *level, int8_t *first);
void boss_screen(int8_t *gamestart, int8_t *menu, uint8_t *key, int8_t *level, int8_t *first);


#endif /* MENU_FUNCTIONS_H_ */
