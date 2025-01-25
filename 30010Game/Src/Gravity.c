/*
 * Gravity.c
 *
 *  Created on: 16 Jan 2025
 *      Author: vince
 */

#include <stdio.h>
#include <stdint.h>
#include "Movement and math functions.h"
#include "Gravity.h"


//The necessary math functions:

//Algorithm approximating the square root of a number in fixed point 24.8 format
//Input number must be in x.8 fixed point format
int32_t square(int32_t number){
	int32_t x = 1;
	while(x*x < number){
		x++;
	}
	return x << 4;
	//Returns the approximated square root in 24.8 format
}

//Converts x.0 fixed point format to x-8.8 format
int32_t to88(int32_t number){
	return number << 8;
}

//Converts x-8.8 format to x.0 format
int32_t from88(int32_t number){
	int32_t temp = (number & 0x00FF);
	int32_t numb = number >> 8;
	if(temp >= 127){
		numb++;
	}
	return numb;
}

//initializes a vector, returning a type struct vector that stores the coordinates and length in 24.8 format
vector initVector(int8_t x, int8_t y){
	//All is in 8.8 format!
	vector vec;
	vec.x = to88(x);
	vec.y = to88(y);
	vec.len = square(((vec.x/3*vec.x/3)>>8) + ((vec.y*vec.y)>>8));
	//					24.8	  *   24.8 		24.8 * 24.8  : bitshifting >>8 to get x*x and y*y in 24.8 format instead of 16.16
	//The function returns the perceived length of the vector, not the actual length, as y = 3x approx visually
	return vec;
}

//Same as above, but not used in this program. Also coordinates stored in normal integers
vector vecFromPoints(point p1, point p2){
	vector vec;
	vec.x = p2.x - p1.x;
	vec.y = p2.y - p1.y;
	vec.len = square(to88(vec.x*vec.x+vec.y*vec.y));
	return vec;
}


//Lorentzforce function manipulating the bullets velocities in x and y direction based on how far
//away they are from asteroids
void lorentzForce(bullet* bullarr, asteroid* astarr, uint8_t n_bul, uint8_t n_ast){
	for(int8_t i = 0; i < n_bul; i++){
		if(bullarr[i].status != 0){
			for(int8_t j = 0; j < n_ast; j++){
				vector v = initVector(astarr[j].x - bullarr[i].x, astarr[j].y - bullarr[i].y);

				//The asteroids do not have a center point on the y axis, therefore correction is needed
				if(bullarr[i].y <= astarr[j].y){
					if(v.len < (10<<8)){
						bullarr[i].velx += (v.x/40) * (to88(10)/v.len);
						bullarr[i].vely += (v.y/40) * (to88(10)/v.len);
					}
				}else if(bullarr[i].y >= astarr[j].y){
					if(v.len < (11<<8)){
						bullarr[i].velx += (v.x/40) * (to88(11)/v.len);
						bullarr[i].vely += (v.y/40) * (to88(11)/v.len);
					}
				}
			}
		}

	}
}
