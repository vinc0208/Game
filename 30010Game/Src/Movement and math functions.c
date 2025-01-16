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


int32_t vesinus(int angle){
	int32_t index=angle%512;
	if (angle<0){
		index+=512;
	}
	return (SIN[index]);
}
int32_t vecosinus(int angle){
	return vesinus(angle+128);
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

//updates obejcts with movement independent of the player
void UpdateObjPos(enemy* all_ene,bullet* all_bul,int n_ene, int n_bul){
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
					all_ene[i].status=0; // deactivate and delete enemies going off screen
					gotoxy(all_ene[i].x-1,all_ene[i].y-1);
					printf("      ");
					gotoxy(all_ene[i].x-1,all_ene[i].y);
					printf("      ");
					gotoxy(all_ene[i].x-1,all_ene[i].y+1);
					printf("      ");
				} else {
					gotoxy(all_ene[i].x-1,all_ene[i].y-1); //delete old image
					printf("      ");
					gotoxy(all_ene[i].x-1,all_ene[i].y);
					printf("      ");
					gotoxy(all_ene[i].x-1,all_ene[i].y+1);
					printf("      ");
					/*
					all_ene[i].x+= all_ene[i].velx;
					all_ene[i].y+= all_ene[i].vely;
					drawEnemy(&all_ene[i]);
				*/}}}
}
