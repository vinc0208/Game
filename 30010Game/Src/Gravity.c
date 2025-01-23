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

int32_t square(int32_t number){
	int32_t x = 1;
	while(x*x < number){
		x++;
	}
	return x << 4;
	//Returns the approximated square root in 8.8 format
}	//number argument has to be in x.8 format

int32_t to88(int32_t number){
	return number << 8;
}

int32_t from88(int32_t number){
	int32_t temp = (number & 0x00FF);
	int32_t numb = number >> 8;
	if(temp >= 127){
		numb++;
	}
	return numb;
}

vector initVector(int8_t x, int8_t y){
	//All is in 8.8 format!
	vector vec;
	vec.x = to88(x);
	vec.y = to88(y);
	vec.len = square(((vec.x/3*vec.x/3)>>8) + ((vec.y*vec.y)>>8));
	//					24.8	  *   24.8 		24.8 * 24.8   bitshifting >>8 to get result in x.8
	//The function also returns the perceived length of the vector, not the actual length, as y = 3x approx.
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

void lorentzForce(bullet* bullarr, asteroid* astarr, uint8_t n_bul, uint8_t n_ast){
	for(int8_t i = 0; i < n_bul; i++){
		if(bullarr[i].status != 0){
			for(int8_t j = 0; j < n_ast; j++){
				vector v = initVector(astarr[j].x - bullarr[i].x, astarr[j].y - bullarr[i].y);
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








