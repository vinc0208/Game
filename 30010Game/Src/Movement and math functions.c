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
#include <stdlib.h>
#include "stm32f30x_conf.h"
#include "30010_io.h" 		// Input/output library for this course
#include "sinusoid.h"
#include "Graphics functions.h"
#include "Score.h"

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
void CheckBulletCollisions(spaceship * shp, enemy * ene, bullet* bul, asteroid* ast,powerup* pow, int n_ene, int n_ast, int n_bul, int n_pow) {
	int8_t i,k,m,r;
	for(i=0;i<n_bul;i++){
		if(bul[i].status !=0){


			for(k=0;k<n_ast;k++){ // check for asteroid collision
				if((bul[i].x >= ast[k].x-3) && (bul[i].x <= ast[k].x+2) && (bul[i].y >= ast[k].y-1) && (bul[i].y <= ast[k].y+2)) {
					bul[i].status=0; // bullets are removed on collision
					gotoxy(bul[i].x,bul[i].y);
					printf(" ");
				}}

			for(k=0;k<n_ene;k++){ // check for enemy collision
				if((bul[i].x >= ene[k].x-2) && (bul[i].x <= ene[k].x+2) && (bul[i].y >= ene[k].y-2) && (bul[i].y <= ene[k].y+2)) {
					ene[k].hp-=bul[i].status;
					if (ene[k].hp <= 0){ //check for enemy death
						ene[k].status=0;
						ScoreTracker(100);
						r=rand() % (4 + 1);
						if(r==4){ //randomly spawn a powerup
							for(m=0;m<n_pow;m++){
								if(pow[m].status==0){
									r=(rand() % (5 + 1))+1;
									pow[m].status=r;
									pow[m].x=ene[k].x;
									pow[m].y=ene[k].y;
									drawPowerup(&pow[m]);
									break;
							}}}}
					bul[i].status=0; //bullets are removed on collision
					gotoxy(bul[i].x,bul[i].y);
					printf(" ");
				}}}}}

void CheckSpaceshipCollisions(spaceship * shp, enemy * ene, asteroid* ast,powerup* pow, int n_ene, int n_ast, int n_pow, int pp) {
	int8_t i,k,m,r;

	for(k=0;k<n_ast;k++){ // check for asteroid collision
		if(ast[k].status !=0){
			if((shp->x >= ast[k].x-3) && (shp->x <= ast[k].x+2) && (shp->y >= ast[k].y-1) && (shp->y <= ast[k].y+2)) {
				ast[k].status=0; // asteroids are removed on collision
				shp->hp-=1;
				gotoxy(ast[k].x-2,ast[k].y-1);
				printf("     ");
				gotoxy(ast[k].x-3,ast[k].y);
				printf("       ");
				gotoxy(ast[k].x-3,ast[k].y+1);
				printf("       ");
				gotoxy(ast[k].x-2,ast[k].y+2);
				printf("     ");
					}}}
	for(k=0;k<n_ene;k++){ // check for enemy collision
			if(ene[k].status !=0){
				if((shp->x >= ene[k].x-2) && (shp->x <= ene[k].x+2) && (shp->y >= ene[k].y-1) && (shp->y <= ene[k].y+1)) {
					ene[k].status=0; // enemies are removed on collision and their sprite deleted
					shp->hp-=1;
					gotoxy(ene[k].x-1,ene[k].y-1);
					printf("     ");
					gotoxy(ene[k].x-3,ene[k].y);
					printf("      ");
					gotoxy(ene[k].x-2,ene[k].y+1);
					printf("      ");
						}}}
	for(k=0;k<n_pow;k++){ // check for powerup collision
				if(pow[k].status !=0){
					if((shp->x >= pow[k].x-2) && (shp->x <= pow[k].x+2) && (shp->y >= pow[k].y-1) && (shp->y <= pow[k].y+1)) {
						add_power(pow[k], &pp); // add to player powerups
						pow[k].status=0; // powerups are removed on collision and their sprite deleted
						gotoxy(pow[k].x-1,pow[k].y-1);
						printf("  ");
							}}}}



//updates obejcts with movement independent of the player (bullets)
void UpdateBulletPos(spaceship* ship,bullet* all_bul, int n_bul){
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
			}}}}

	// then enemies
void UpdateEnemyPos(spaceship* ship,enemy* all_ene,int n_ene){
	int i,k;
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


void add_power(powerup pow, int pp) {	//Takes powerup status and adds corresponding power (pow) and ads to player powers (pp)
	if (pow.status == 1){
		if (!(pp & 0x00000001) && !(pp & 0x00000010)){
			pp |= 0x00000001;
		} else if (pp & 0x00000001){
			pp |= 0x00000010;
		} else {}
	} else if (pow.status == 2){
		if (!(pp & 0x00000100) && !(pp & 0x00001000)){
			pp |= 0x00000100;
		} else if (pp & 0x00000100){
			pp |= 0x00001000;
		} else {}
	} else if (pow.status == 3){
		if (!(pp & 0x00010000)) {
			pp |= 0x00010000;
		} else {}
	} else if (pow.status == 4){
		pp &= ~(0x11100000);
		pp |= 0x00100000;
	} else if (pow.status == 5){
		pp &= ~(0x11100000);
		pp |= 0x01000000;
	} else if (pow.status == 6){
		pp &= ~(0x11100000);
		pp |= 0x10000000;
	}
}

