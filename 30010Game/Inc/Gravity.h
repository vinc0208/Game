/*
 * Gravity.h
 *
 *  Created on: 16 Jan 2025
 *      Author: vince
 */

#ifndef GRAVITY_H_
#define GRAVITY_H_



typedef struct {
	int16_t x,y,len;
	//x, y is in 16.0, len in 8.8
} vector;

int16_t square(int16_t number);
int16_t to88(int16_t number);
int16_t from88(int16_t number);
vector initVector(int8_t x, int8_t y);
vector vecFromPoints(point p1, point p2);
vector vecFromPoints(point p1, point p2);


#endif /* GRAVITY_H_ */
