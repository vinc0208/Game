/*
 * Gravity.h
 *
 *  Created on: 16 Jan 2025
 *      Author: vince
 */

#ifndef GRAVITY_H_
#define GRAVITY_H_



typedef struct {
	int32_t x,y,len;
	//All in 24.8 format!
} vector;

int32_t square(int32_t number);
int32_t to88(int32_t number);
int32_t from88(int32_t number);
vector initVector(int8_t x, int8_t y);
vector vecFromPoints(point p1, point p2);
vector vecFromPoints(point p1, point p2);
void lorentzForce(bullet* bullarr, asteroid* astarr, uint8_t n_bul, uint8_t n_ast);


#endif /* GRAVITY_H_ */
