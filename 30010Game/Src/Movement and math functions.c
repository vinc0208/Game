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


		}}
}
