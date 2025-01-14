/*
 * Graphics functions.h
 *
 *  Created on: 13 Jan 2025
 *      Author: vince
 */

#ifndef GRAPHICS_FUNCTIONS_H_
#define GRAPHICS_FUNCTIONS_H_
#include <Movement and math functions.h>

void window(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2, char* txt, short style);
void drawSpaceship(int x,int y,short style,int direction);
void drawEnemy(enemy*ene);
void drawAsteroid(asteroid* ast,short style);
void drawPowerup(int x, int y, short type);
void initAsteroid(asteroid* all_asteroids,int n_ast);
void initEnemy(enemy* all_enemies,int n_ene);
#endif /* GRAPHICS_FUNCTIONS_H_ */
