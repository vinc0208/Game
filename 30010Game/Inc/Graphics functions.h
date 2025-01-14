/*
 * Graphics functions.h
 *
 *  Created on: 13 Jan 2025
 *      Author: vince
 */

#ifndef GRAPHICS_FUNCTIONS_H_
#define GRAPHICS_FUNCTIONS_H_


void window(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2, char* txt, short style);
void drawSpaceship(int x,int y,short style,int direction);
void drawEnemy(int x,int y, int direction);
void drawAsteroid(int x,int y,short style);
void drawPowerup(int x, int y, short type);

#endif /* GRAPHICS_FUNCTIONS_H_ */
