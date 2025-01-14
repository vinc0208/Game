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
	int32_t x,y, velx, vely;
} posdata;

typedef struct {
	int32_t x,y, velx, vely;
} point;


typedef struct { //define asteroids as a position and on/off bol
	int32_t x,y,status;
} asteroid;







#endif /* MOVEMENT_AND_MATH_FUNCTIONS_H_ */
