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
TimeFormat TimeMaster15; // The reason why we have a global variable here is because we need to be able to access the time anywhere
TimeFormat SpeedIncrease;// Another global variable needed for increasing game speed over time

typedef struct {
	int life, score, ammo;
} stats;
stats player;

#ifndef HARDWARE_INTERFACE_FUNCTIONS_H_
#define HARDWARE_INTERFACE_FUNCTIONS_H_

void uartStringModifier(char arr[]);
void TIM1_BRK_TIM15_IRQHandler(void);
void Timer15Config(void);
void lcd_write_string(char* string, uint8_t slice, uint16_t line, uint8_t* buffer);
void lcd_update(char* string, char* tbu, uint8_t slice, uint16_t line, uint8_t* buffer);
void StartTime();
void StopTime();
void ResetTime();
void GameSpeed(int* level);

char uartKeyRead();

void initJoystick();
uint8_t readJoystick();

void init_radar(uint8_t *buffer);
void init_lcd(uint8_t* buffer);
void radar(uint8_t* buffer);




#endif /* HARDWARE_INTERFACE_FUNCTIONS_H_ */
