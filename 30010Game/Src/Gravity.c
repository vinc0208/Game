/*
 * Gravity.c
 *
 *  Created on: 16 Jan 2025
 *      Author: vince
 */

#include "stdio.h"
#include "stdint.h"
#include "Movement and math functions.h"
#include "Gravity.h"


//The necessary math functions:

int16_t square(int16_t number){
	int16_t x = 1;
	while(x*x < number){
		x++;
	}
	return x << 4;
	//Returns the approximated square root in 8.8 format
}

int16_t to88(int16_t number){
	return number << 8;
}

int16_t from88(int16_t number){
	int16_t temp = (number & 0x00FF);
	int16_t numb = number >> 8;
	if(temp >= 127){
		numb++;
	}else if(temp < 127){
		numb--;
	}
	return numb;
}

vector initVector(int8_t x, int8_t y){
	//vec.len is in 8.8 format!
	vector vec;
	vec.x = x;
	vec.y = y;
	vec.len = square(to88(vec.x*vec.x+vec.y*vec.y));
	return vec;
}

vector vecFromPoints(point p1, point p2){
	vector vec;
	vec.x = p2.x - p1.x;
	vec.y = p2.y - p1.y;
	vec.len = square(to88(vec.x*vec.x+vec.y*vec.y));
	return vec;
}


//The functions related to Lorentz force:

void lorentzForce(bullet* bullarr[], asteroid* astarr[]){
	for(int8_t i = 0; i < sizeof *bullarr; i++){
		if(bullarr[i]->status != 0){
			vector v = initVector(astarr[i]->x - bullarr[i]->x, astarr[i]->y - bullarr[i]->y);
			if(v.len < to88(10)){
				if(bullarr[i]->y >= astarr[i]->y){

				}else if(bullarr[i]->y < astarr[i]->y){

				}
			}
		}
	}
}

/*len vec(Bpos->astoroid) < value{
	case over centery astoroid
		find vector between top of astoroid and Bpos
		find angle between above vector and bullet velocityvector
		calculate magnitude of Lorentz force as a vector perpendicular to velocity
		(add Lorentz force to the position of bullet) - maybe not necessary
		accelerate velocity composants of the bullet velocity based on the Lorentz force

	case under centery astoroid
		find vector between bottom of astoroid and Bpos
		find angle between above vector and bullet velocityvector
		calculate magnitude of Lorentz force as a vector perpendicular to velocity
		(add Lorentz force to the position of bullet) - maybe not necessary
		accelerate velocity composants of the bullet velocity based on the Lorentz force

}
 */








