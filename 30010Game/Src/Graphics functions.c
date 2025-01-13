/*
 * Graphics functions.c
 *
 *  Created on: 13 Jan 2025
 *      Author: vince
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include <Graphics functions.h>
#include <ansi.h>
#define ESC 0x1B
#include <stdint.h> // whatever
#include <stdio.h>

void drawSpaceship(int x,int y,short style,int direction){
	int8_t i=0,size=3; //setup size
	gotoxy(x-1,y-1);
	if(style==1){ //setup coloration based on style
		fgcolor(1);
	} else if(style==0){
		fgcolor(11);
	} else {
		fgcolor(2);
	}
	//based on direction one block is called

	if(direction==1 ||direction==2){
		for(i=0;i<size+1;i++){
			printf("%c",220); //draws base
		}
		gotoxy(x-1,y);
		for(i=0;i<size+1;i++){
			printf("%c",223);
		}
		fgcolor(6); //drawing window color
		if (direction==1){ //drawing window
			gotoxy(x,y-1);
			printf("%c%c",220,220);
		} else{
			gotoxy(x,y);
			printf("%c%c",223,223);
		}}
	if(direction==3 ||direction==4){ //next direction here but same structure for all
		for(i=0;i<size-1;i++){
			printf("%c",220);
		}
		gotoxy(x-1,y);
		for(i=0;i<size-1;i++){
			printf("%c",219);
		}
		gotoxy(x-1,y+1);
		for(i=0;i<size-1;i++){
			printf("%c",223);
		}
		fgcolor(6);
		if (direction==3){
			gotoxy(x-1,y);
		} else{
			gotoxy(x,y);
		} printf("%c",219);
		}
	if(direction==5 ||direction==6){
		gotoxy(x,y-1);
		for(i=0;i<size-1;i++){
			printf("%c",220);
		}
		gotoxy(x-2,y);
		printf("%c",220);
		for(i=0;i<size-1;i++){
			printf("%c",219);
		}
		printf("%c",223);
		gotoxy(x-2,y+1);
		for(i=0;i<size-1;i++){
			printf("%c",223);
		}
		fgcolor(6);
		if (direction==5){
			gotoxy(x-1,y);
			printf("%c",219);
		} else{
			gotoxy(x,y);
			printf("%c",219);

		}}
	if(direction==7 ||direction==8){
		gotoxy(x-2,y-1);
		for(i=0;i<size-1;i++){
			printf("%c",220);
		}
		gotoxy(x-2,y);
		printf("%c",223);
		for(i=0;i<size-1;i++){
			printf("%c",219);
		}
		printf("%c",220);
		gotoxy(x,y+1);
		for(i=0;i<size-1;i++){
			printf("%c",223);
		}
		fgcolor(6);
			if (direction==8){
			gotoxy(x-1,y);
		printf("%c",219);
		} else{
			gotoxy(x,y);
			printf("%c",219);
}}}
void drawEnemy(int x,int y, int direction){
	int8_t i=0,size=3; //setup size
		gotoxy(x-1,y-1);
		fgcolor(2);
		if(direction==1 ||direction==2){
			printf("%c%c%c%c%c[%dD%c[%dB%c%c%c%c",220,220,220,220,ESC,4,ESC,1,223,223,223,223);
			if(direction==1){
				fgcolor(5);
				printf("%c[%dA%c[%dD%c%c[%dD%c",ESC,1,ESC,1,187,ESC,4,201);
				fgcolor(6);
				printf("%c%c",220,220);
			} else{
				fgcolor(5);
				printf("%c[%dD%c%c[%dD%c",ESC,1,188,ESC,4,200);
				fgcolor(6);
				printf("%c%c",223,223);
			}}
		if(direction==3 ||direction==4){ //next direction here but same structure for all
				for(i=0;i<size-1;i++){
					printf("%c",220);
				}
				gotoxy(x-1,y);
				for(i=0;i<size-1;i++){
					printf("%c",219);
				}
				gotoxy(x-1,y+1);
				for(i=0;i<size-1;i++){
					printf("%c",223);
				}
				fgcolor(6);
				if (direction==3){
					gotoxy(x-1,y);
					printf("%c",219);
					fgcolor(5);
					printf("%c[%dD%c[%dA%c%c[%dD%c[%dB%c",ESC,1,ESC,1,201,ESC,1,ESC,2,200);
				} else{
					gotoxy(x,y);
					printf("%c",219);
					fgcolor(5);
					printf("%c[%dD%c[%dA%c%c[%dD%c[%dB%c",ESC,1,ESC,1,187,ESC,1,ESC,2,188);
				}}
		if(direction==5 ||direction==6){
				gotoxy(x,y-1);
				for(i=0;i<size-1;i++){
					printf("%c",220);
				}
				gotoxy(x-2,y);
				printf("%c",220);
				for(i=0;i<size-1;i++){
					printf("%c",219);
				}
				printf("%c",223);
				gotoxy(x-2,y+1);
				for(i=0;i<size-1;i++){
					printf("%c",223);
				}
				fgcolor(6);
				if (direction==5){
					gotoxy(x-1,y);
					printf("%c",219);
					fgcolor(5);
					printf("%c[%dA%c%c[%dD%c[%dB%c",ESC,1,201,ESC,3,ESC,1,201);

				} else{
					gotoxy(x,y);
					printf("%c",219);
					fgcolor(5);
					printf("%c%c[%dD%c[%dB%c",188,ESC,3,ESC,1,188);
				}}
		if(direction==7 ||direction==8){
				gotoxy(x-2,y-1);
				for(i=0;i<size-1;i++){
					printf("%c",220);
				}
				gotoxy(x-2,y);
				printf("%c",223);
				for(i=0;i<size-1;i++){
					printf("%c",219);
				}
				printf("%c",220);
				gotoxy(x,y+1);
				for(i=0;i<size-1;i++){
					printf("%c",223);
				}
				fgcolor(6);
					if (direction==7){
					gotoxy(x,y);
					printf("%c",219);
					fgcolor(5);
					printf("%c%c[%dD%c[%dA%c",187,ESC,3,ESC,1,187);

				} else{
					gotoxy(x-1,y);
					printf("%c",219);
					fgcolor(5);
					printf("%c[%dB%c%c[%dD%c[%dA%c",ESC,1,200,ESC,3,ESC,1,200);
		}}}
void drawAsteroid(int x,int y,short style){
	gotoxy(x-1,y-1);
	fgcolor(7);
	if(style==1){
	 printf("%c%c%c%c[%dB%c[%dD%c%c%c%c%c%c[%dD%c[%dB%c%c%c",220,178,220,ESC,1,ESC,4,176,178,178,178,176,ESC,4,ESC,1,223,178,223);
	} else{
		gotoxy(x-3,y-1);
	printf("%c%c%c%c%c[%dB%c[%dD%c%c%c%c%c%c%c[%dB%c[%dD%c%c%c%c%c%c%c[%dB%c[%dD%c%c%c%c",176,177,178,178,ESC,1,ESC,5,176,177,178,219,219,178,ESC,1,ESC,6,176,177,178,219,219,178,ESC,1,ESC,5,176,177,178,178);

	}

}

