/*
 * Movement and math functions.c
 *
 *  Created on: 13 Jan 2025
 *      Author: vince
 */

#define ESC 0x1B
#include "stdint.h"
#include "stdio.h"
#include <ansi.h>
#include <lut.h>
#include <math.h>
#include "stm32f30x_conf.h"
#include "30010_io.h" 		// Input/output library for this course
#include "sinusoid.h"
#include "Graphics functions.h"

//Typedefs
void printFix(int32_t i) {
	// Prints a signed 16.16 fixed point number
	if ((i & 0x80000000) != 0) { // Handle negative numbers
		printf("-");i = ~i + 1;
	}
	printf("%ld.%04ld", i >> 16, 10000 * (uint32_t)(i & 0xFFFF) >> 16);
	// Print a maximum of 4 decimal digits to avoid overflow
}
int32_t expand(int32_t i) {
// Converts an 18.14 fixed point number to 16.16
return i << 2;
}

//Math


int16_t vecsinus(int angle) {						//Without expand and printFix
	int step = round(angle * 512.0 / 360.0);
	if (step < 0) {
		int n = floor(~step / 512);
		step += (n+1)*512;
	} else {
		int n = floor(step / 512);
		step -= n*512;
	}
	int y = SIN[step];
	return y;
}

int32_t vecosinus(int angle){
	return vecsinus(angle+180);
}
int32_t sinus(int angle){
	int32_t index=angle%512;
	if (angle<0){
		index+=512;
	}
	return (expand(SIN[index]));
}
int32_t cosinus(int angle){

	return sinus(angle+128);
}

//Movement

//looks for bullet collisions with all relevant objects
void CheckBulletCollisions(spaceship * shp, enemy * ene, bullet* bul, asteroid* ast, int n_ene, int n_ast, int n_bul) {
	int i,k;
	for(i=0;i<n_bul;i++){
		if(bul[i].status !=0){


			for(k=0;k<n_ast;k++){ // check for asteroid collision
				if((bul[i].x >= ast[k].x-3) && (bul[i].x <= ast[k].x+2) && (bul[i].y >= ast[k].y-1) && (bul[i].y <= ast[k].y+2)) {
					bul[i].status=0;
					gotoxy(bul[i].x,bul[i].y);
					printf(" ");
				}

			}
			/*for(k=0;k<n_ast;k++){ // check for enemy collision
				if((bul[i].x >= ast[k].x-3) && (bul[i].x <= ast[k].x+2) && (bul[i].y >= ast[k].y-1) && (bul[i].y <= ast[k].y+2)) {
					bul[i].status=0;
					gotoxy(bul[i].x,bul[i].y);
					printf(" ");
				}

			}*/

	}}}


//updates obejcts with movement independent of the player
void UpdateObjPos(spaceship* ship,enemy* all_ene,bullet* all_bul,int n_ene, int n_bul){
	int i,k;
	//bullets first
	for(i=0;i<n_bul;i++){
		if(all_bul[i].status!=0){ //check status
			if(all_bul[i].x+all_bul[i].velx>=189||all_bul[i].x+all_bul[i].velx<=1||all_bul[i].y+all_bul[i].vely<=1||all_bul[i].y+all_bul[i].vely>=49){
				all_bul[i].status=0; // removes out of bounds bullets
				gotoxy(all_bul[i].x,all_bul[i].y);
				printf(" ");
			} else {
				gotoxy(all_bul[i].x,all_bul[i].y);
				printf(" ");
				all_bul[i].x+= all_bul[i].velx;
				all_bul[i].y+= all_bul[i].vely;
				drawBullet(&all_bul[i]);
			}}}
	// then enemies
	for(i=0;i<n_ene;i++){
			if(all_ene[i].status!=0){ //check status
				if(CheckOnScr(all_ene[i].x,all_ene[i].y)==0){
					all_ene[i].status=0; // deactivate and delete enemies that are off screen
					gotoxy(all_ene[i].x-1,all_ene[i].y-1);
					printf("     ");
					gotoxy(all_ene[i].x-3,all_ene[i].y);
					printf("      ");
					gotoxy(all_ene[i].x-2,all_ene[i].y+1);
					printf("      ");
				} else {
					gotoxy(all_ene[i].x-2,all_ene[i].y-1); //delete old image
					printf("     ");
					gotoxy(all_ene[i].x-3,all_ene[i].y);
					printf("      ");
					gotoxy(all_ene[i].x-2,all_ene[i].y+1);
					printf("      "); //the following is the enemy movement algorithm
					//it looks at their position relative to the spaceship and moves them toward it
					//to avoid making them go conga at the ships coords, they check the ratio between x and y as well
					if((all_ene[i].x > ship->x) && (all_ene[i].y>ship->y) && !(abs(all_ene[i].x-95) / abs(all_ene[i].y-25) >=4 ) && !(abs(all_ene[i].y-25) / abs(all_ene[i].x-95) >=1 )){ //ship->x=95 ship->y=25
						all_ene[i].x-= 3;  // position is then updated
						all_ene[i].y-= 1;
						all_ene[i].dir=8; //and direction
					} else if((all_ene[i].x < ship->x) && (all_ene[i].y>ship->y)&& !(abs(all_ene[i].x-95) / abs(all_ene[i].y-25) >=4 )  && !(abs(all_ene[i].y-25) / abs(all_ene[i].x-95) >=1 )){
						all_ene[i].x+= 3;
						all_ene[i].y-= 1;
						all_ene[i].dir=2;
					}else if((all_ene[i].x < ship->x) && (all_ene[i].y < ship->y)&& !(abs(all_ene[i].x-95) / abs(all_ene[i].y-25) >=4 )  && !(abs(all_ene[i].y-25) / abs(all_ene[i].x-95) >=1 )){
						all_ene[i].x+= 3;
						all_ene[i].y+= 1;
						all_ene[i].dir=4;
					}else if((all_ene[i].x > ship->x) && (all_ene[i].y < ship->y) && !(abs(all_ene[i].x-95) / abs(all_ene[i].y-25) >=4 )  && !(abs(all_ene[i].y-25) / abs(all_ene[i].x-95) >=1 )){
						all_ene[i].x-= 3;
						all_ene[i].y+= 1;
						all_ene[i].dir=6;
					}else if(((all_ene[i].x) < (ship->x))  && !(abs(all_ene[i].y-25) / abs(all_ene[i].x-95) >=1 )){
						all_ene[i].x+= 3;
						all_ene[i].dir=3;
					}else if((all_ene[i].x > ship->x) && !(abs(all_ene[i].y-25) / abs(all_ene[i].x-95) >=1 )){
						all_ene[i].x-= 3;
						all_ene[i].dir=7;
					}else if(all_ene[i].y > ship->y){
						all_ene[i].y-= 1;
						all_ene[i].dir=1;
					}else if(all_ene[i].y < ship->y){
						all_ene[i].y+= 1;
						all_ene[i].dir=5;
					}
					//drawEnemy(&all_ene[i]); //one could draw each enemy after updating their position
				}}}}
