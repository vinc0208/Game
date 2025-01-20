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
void fireBullet(spaceship *ship, bullet*bul, int pp, uint8_t* reload_timer);

void drawSpaceship(spaceship*shp);
void drawEnemy(enemy*ene);
void drawAsteroid(asteroid* ast,short style);
void drawPowerup(powerup *pow);

void initAsteroid(asteroid* all_asteroids,int n_ast);
void initEnemy(enemy* all_enemies,int n_ene, uint8_t difficulty);
void initSpaceship(spaceship* ship, uint8_t difficulty, int style);
void initBullet(bullet* bul,int n_bull);
void initPowerup(powerup *pow,int n_pow);
void updateEnemy(enemy* ene, int n_ene);
uint8_t CheckOnScr(uint8_t x, uint8_t y);
void SpawnEnemy(enemy* all_enemies,int n_ene,int difficulty);
void SpawnAsteroid(asteroid* ast,int n_ast);
void updateAsteroid(asteroid* ast, int n_ast);
void updateAll(spaceship * shp, enemy * ene, bullet* bul, asteroid* ast,powerup* pow, int n_ene, int n_ast, int n_bul, int n_pow, int *pp);
void updatePowerup(powerup* pow, int n_pow);
void eraseSpaceship(spaceship* shp);
#endif /* GRAPHICS_FUNCTIONS_H_ */
