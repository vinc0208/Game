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
	int8_t x,y, velx, vely;
} posdata;

typedef struct {
	int8_t x,y, velx, vely;
} point;


typedef struct { //define asteroids as a position and on/off bol
	int8_t x,y,status;
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
	//status is an on/off bol indicating wether it is active.
	// status>1 determines type of the powerup
	int8_t x,y,status;
} powerup;



//functions
void UpdateObjPos(spaceship* ship,enemy* all_ene,bullet* all_bul,int n_ene, int n_bul);





#endif /* MOVEMENT_AND_MATH_FUNCTIONS_H_ */
