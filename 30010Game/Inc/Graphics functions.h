/*
 * Graphics functions.h
 *
 *  Created on: 13 Jan 2025
 *      Author: vince
 */

#ifndef GRAPHICS_FUNCTIONS_H_
#define GRAPHICS_FUNCTIONS_H_
#include <Movement and math functions.h>

void window(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2, short style);
void drawBullet(bullet*bul);
void fireBullet(spaceship *ship,bullet*bul);
void drawSpaceship(spaceship*shp);
void drawEnemy(enemy*ene);
void drawAsteroid(asteroid* ast,short style);
void drawPowerup(powerup *pow);
void initAsteroid(asteroid* all_asteroids,int n_ast);
void initEnemy(enemy* all_enemies,int n_ene);
void initSpaceship(spaceship* ship,int difficulty, int style);
void initBullet(bullet * bul,int maxn_bull);
#endif /* GRAPHICS_FUNCTIONS_H_ */
