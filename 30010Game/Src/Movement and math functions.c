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

//Typedefs


//Math


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
	/*for(i=0;i<n_ene;i++){
			if(all_ene[i].status!=0){ //check status
				if(all_ene[i].x+all_ene[i].velx>=189||all_ene[i].x+all_ene[i].velx<=1||all_ene[i].y+all_ene[i].vely<=1||all_ene[i].y+all_ene[i].vely>=49){
					all_ene[i].status=0;
				} else {
					gotoxy(all_ene[i].x,all_ene[i].y);
					printf(" ");
					all_ene[i].x+= all_ene[i].velx;
					all_ene[i].y+= all_ene[i].vely;
					drawEnemy(&all_ene[i]);
				}}}*/
}
