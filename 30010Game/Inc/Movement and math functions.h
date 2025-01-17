/*
 * Movement and math functions.h
 *
 *  Created on: 13 Jan 2025
 *      Author: vince
 */
#include "stdio.h"
#include "stdint.h"

#ifndef MOVEMENT_AND_MATH_FUNCTIONS_H_
#define MOVEMENT_AND_MATH_FUNCTIONS_H_

typedef struct {
	int16_t x,y, velx, vely;
} posdata;

typedef struct {
	int16_t x,y, velx, vely;
} point;


typedef struct { //define asteroids as a position and on/off bol
	int16_t x,y,status;
} asteroid;

typedef struct {
//define enemies as a position, direction([1,8]),hp and velocity.
	//status is an on/off bol indicating wether it is alive
	int16_t x,y,velx, vely,hp,status,dir;
} enemy;

typedef struct {
//define bullets as a position and a direction([1,8]).
	//status is an on/off bol indicating wether the bullet is active
	//status>0 corresponds to it's dmg.
	int16_t x,y,velx,vely,status,dir;
} bullet;

typedef struct {
//define the player spaceship as a position, direction([1,8]),hp and style.
	//status is an on/off bol indicating wether it is alive
	int16_t x,y,hp,status,dir,style;
} spaceship;

typedef struct {
//define powerups as a position and a status.
	//status 0: inactive, 1: Speed boost, 2: Dmg boost, 3: Score multiplier, 4: Bullet type 1, 5: Bullet type 2, 6: Bullet type 3.
	// status>1 determines type of the powerup
	int16_t x,y,status;
} powerup;



//functions
void CheckBulletCollisions(spaceship * shp, enemy * ene, bullet* bul, asteroid* ast,powerup* pow, int n_ene, int n_ast, int n_bul, int n_pow);
void CheckSpaceshipCollisions(spaceship * shp, enemy * ene, asteroid* ast,powerup* pow, int n_ene, int n_ast, int n_pow, int  pp);
void printFix(int32_t i);
int32_t expand(int32_t i);
int16_t vecsinus(int angle);
int32_t vecosinus(int angle);
int32_t sinus(int angle);
int32_t cosinus(int angle);
void UpdateBulletPos(spaceship* ship,bullet* all_bul, int n_bul);
void add_power(powerup pow, int  pp);
void UpdateEnemyPos(spaceship* ship,enemy* all_ene,int n_ene);

void playerMovePosAdd(bullet* bullarr, asteroid* astarr, enemy* enearr, powerup* powarr, spaceship* player, int8_t k);
void playerMove(bullet* bullarr, asteroid* astarr, enemy* enearr, powerup* powarr, spaceship* player, int8_t k);



#endif /* MOVEMENT_AND_MATH_FUNCTIONS_H_ */
