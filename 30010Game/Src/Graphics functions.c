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
#include <stdlib.h>
#include <Hardware interface functions.h>

//draws a window as decribed in the excersises
void window(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2, short style){
	int i; //uses for loops to build a frame based on style
	if (style==1){
		for(i=0;i<y2-y1;i++){
			gotoxy(x1,y1+i);
			printf("%c",186);
			gotoxy(x2,y1+i);
			printf("%c",186);
		}
		for(i=0;i<x2-x1;i++){
			gotoxy(x1+i,y1);
			printf("%c",205);
			gotoxy(x1+i,y2);
			printf("%c",205);
		}
		gotoxy(x1+5,y1); // here corners and the text is added
		printf("%c[%dm", ESC,7);
		printf("%c[%dm", ESC,27);
		gotoxy(x1,y1);
		printf("%c",201);
		gotoxy(x1,y2);
		printf("%c",200);
		gotoxy(x2,y1);
		printf("%c",187);
		gotoxy(x2,y2);
		printf("%c",188);

	} else{
		for(i=0;i<x2-x1;i++){
			gotoxy(x1+i,y1);
			printf("%c",254);
			gotoxy(x1+i,y2);
			printf("%c",254);
		}
		for(i=0;i<y2-y1;i++){
			gotoxy(x1,y1+i);
			printf("%c",254);
			gotoxy(x2,y1+i);
			printf("%c",254);
		}
		printf("%c[%dm", ESC,7);
		gotoxy(x1+5,y1);
		printf("%c[%dm", ESC,27);
		gotoxy(x1,y1);
		printf("%c",254);
		gotoxy(x1,y2);
		printf("%c",254);
		gotoxy(x2,y1);
		printf("%c",254);
		gotoxy(x2,y2);
		printf("%c",254);
	}}



// Checking position of object and returning 1 if object is within screen borders, else return 0
uint8_t CheckOnScr(uint8_t x, uint8_t y) {
	if ((x > 2) && (x < 190-5) && (y > 1) && (y < 50-3)) {
		return 1;
	} else {
		return 0;
	}
}




//bullets require a direction from the player and a "powerup" state from bullet status.
//this function is for FIRING BULLETS ONLY as it places them at the spaceship if they are active.
//consider changing function to take player input and setting bullet status from Powerup array (by searching for an active dmg power with status=1)
//to make it actually fire the bullet rather than initializing its trajectory
void fireBullet(spaceship *ship, bullet*bul, int pp, uint8_t* reload_timer){
	char shoot = uartKeyRead();
	if ((shoot & (1 << 5)) && (ship->bullets > 0)){
		bul[ship->bullets].status = (pp & 0x11101100);

		fgcolor(11);
		char *ud, *ur, *lr;
		if((bul[ship->bullets].status & 0x00100000) || (bul[ship->bullets].status & 0x01000000)){
			ud = "|";
			ur = "/";
			lr = "-";
		} else{
			ud = "o";
			ur = "o";
			lr = "o";
		}
		if(bul->status==0){
		//if it is not active dont draw it
		} else if(bul->status > 0){; //corresponds to 1 dmg
			if(ship->dir==1){				//Up
				bul->dir=ship->dir;
				bul->x=ship->x;
				bul->y=ship->y-2;
				bul->velx=0;
				bul->vely=-1;
				gotoxy(bul->x,bul->y);
				if (!(pp & 0x01000000)){
					printf("%c", *ud);
				} else if (pp & 0x01000000){
					bold(1);
					printf("%c", *ud);
					bold(0);
				}
			}else if(ship->dir==5){			// Down
				bul->x=ship->x,bul->dir=ship->dir;
				bul->y=ship->y+1;
				bul->velx=0;
				bul->vely=1;
				gotoxy(bul->x,bul->y);
				if (!(pp & 0x01000000)){
					printf("%c", *ud);
				} else if (pp & 0x01000000){
					bold(1);
					printf("%c", *ud);
					bold(0);
				}
			}else if(ship->dir==2){			// Up-right
				bul->x=ship->x+1,bul->dir=ship->dir;
				bul->y=ship->y-1;
				bul->velx=3;
				bul->vely=-1;
				gotoxy(bul->x,bul->y);
				if (!(pp & 0x01000000)){
					printf("%c", *ur);
				} else if (pp & 0x01000000){
					bold(1);
					printf("%c", *ur);
					bold(0);
				}
			}else if(ship->dir==3){			// Right
				bul->x=ship->x+2,bul->dir=ship->dir;
				bul->y=ship->y;
				gotoxy(bul->x,bul->y);
				bul->velx=1;
				bul->vely=0;
				if (!(pp & 0x01000000)){
					printf("%c", *lr);
				} else if (pp & 0x01000000){
					bold(1);
					printf("%c", *lr);
					bold(0);
				}
			}else if(ship->dir==7){			// Left
				bul->x=ship->x-2,bul->dir=ship->dir;
				bul->y=ship->y;
				gotoxy(bul->x,bul->y);
				bul->velx=-1;
				bul->vely=0;
				if (!(pp & 0x01000000)){
					printf("%c", *lr);
				} else if (pp & 0x01000000){
					bold(1);
					printf("%c", *lr);
					bold(0);
				}
			}else if(ship->dir==4){			// Down-right
				bul->x=ship->x+1,bul->dir=ship->dir;
				bul->y=ship->y+1;
				gotoxy(bul->x,bul->y);
				bul->velx=3;
				bul->vely=1;
				if (!(pp & 0x01000000)){
					printf("%c", 92);
				} else if (pp & 0x01000000){
					bold(1);
					printf("%c", 92);
					bold(0);
				}
			}else if(ship->dir==6){			// Down-left
				bul->x=ship->x-2,bul->dir=ship->dir;
				bul->y=ship->y+1;
				gotoxy(bul->x,bul->y);
				bul->velx=-3;
				bul->vely=1;
				if (!(pp & 0x01000000)){
					printf("%c", *ur);
				} else if (pp & 0x01000000){
					bold(1);
					printf("%c", *ur);
					bold(0);
				}
			}else if(ship->dir==8){			// Up-left
				bul->x=ship->x-2,bul->dir=ship->dir;
				bul->y=ship->y-1;
				gotoxy(bul->x,bul->y);
				bul->velx=0;
				bul->vely=1;
				if (!(pp & 0x01000000)){
					printf("%c", 92);
				} else if (pp & 0x01000000){
					bold(1);
					printf("%c", 92);
					bold(0);
				}
			}
		}
		ship->bullets -= 1;
	}
	if ((ship->bullets <= 0) && (*reload_timer < 0)) {
		*reload_timer = TimeMaster15.second + 60*TimeMaster15.minute;
	}
	if ((TimeMaster15.second + 60*TimeMaster15.minute) == *reload_timer + 3){
		ship->bullets = ship->maxbullets;
		*reload_timer = -10;
	}
}

//draws the spaceship at a designated location facing a designated angle
void drawSpaceship(spaceship*shp){
	int8_t i=0,size=3; //setup size
	gotoxy(shp->x-1,shp->y-1);
	if(shp->style==1){ //setup coloration based on style
		fgcolor(1);
	} else if(shp->style==0){
		fgcolor(11);
	} else {
		fgcolor(2);
	}
	//based on direction one block is called
	if(shp->dir==1 ||shp->dir==5){
		for(i=0;i<size+1;i++){
			printf("%c",220); //draws base
		}
		gotoxy(shp->x-1,shp->y);
		for(i=0;i<size+1;i++){
			printf("%c",223);
		}
		fgcolor(6); //drawing window color
		if (shp->dir==1){ //drawing window
			gotoxy(shp->x,shp->y-1);
			printf("%c%c",220,220);
		} else{
			gotoxy(shp->x,shp->y);
			printf("%c%c",223,223);
		}}
	if(shp->dir==7 ||shp->dir==3){ //next direction here but same structure for all
		for(i=0;i<size-1;i++){
			printf("%c",220);
		}
		gotoxy(shp->x-1,shp->y);
		for(i=0;i<size-1;i++){
			printf("%c",219);
		}
		gotoxy(shp->x-1,shp->y+1);
		for(i=0;i<size-1;i++){
			printf("%c",223);
		}
		fgcolor(6);
		if (shp->dir==7){
			gotoxy(shp->x-1,shp->y);
		} else{
			gotoxy(shp->x,shp->y);
		} printf("%c",219);
		}
	if(shp->dir==8 ||shp->dir==4){
		gotoxy(shp->x,shp->y-1);
		for(i=0;i<size-1;i++){
			printf("%c",220);
		}
		gotoxy(shp->x-2,shp->y);
		printf("%c",220);
		for(i=0;i<size-1;i++){
			printf("%c",219);
		}
		printf("%c",223);
		gotoxy(shp->x-2,shp->y+1);
		for(i=0;i<size-1;i++){
			printf("%c",223);
		}
		fgcolor(6);
		if (shp->dir==8){
			gotoxy(shp->x-1,shp->y);
			printf("%c",219);
		} else{
			gotoxy(shp->x,shp->y);
			printf("%c",219);

		}}
	if(shp->dir==2 ||shp->dir==6){
		gotoxy(shp->x-2,shp->y-1);
		for(i=0;i<size-1;i++){
			printf("%c",220);
		}
		gotoxy(shp->x-2,shp->y);
		printf("%c",223);
		for(i=0;i<size-1;i++){
			printf("%c",219);
		}
		printf("%c",220);
		gotoxy(shp->x,shp->y+1);
		for(i=0;i<size-1;i++){
			printf("%c",223);
		}
		fgcolor(6);
			if (shp->dir==6){
			gotoxy(shp->x-1,shp->y);
		printf("%c",219);
		} else{
			gotoxy(shp->x,shp->y);
			printf("%c",219);
}}}

//draws an enemy
void drawEnemy(enemy*ene){
	int8_t i=0,size=3; //setup size
		gotoxy(ene->x-1,ene->y-1);
		fgcolor(2);
		if(ene->dir==1 ||ene->dir==5){
			printf("%c%c%c%c%c[%dD%c[%dB%c%c%c%c",220,220,220,220,ESC,4,ESC,1,223,223,223,223);
			if(ene->dir==1){
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
		if(ene->dir==7 ||ene->dir==3){ //next direction here but same structure for all
				for(i=0;i<size-1;i++){
					printf("%c",220);
				}
				gotoxy(ene->x-1,ene->y);
				for(i=0;i<size-1;i++){
					printf("%c",219);
				}
				gotoxy(ene->x-1,ene->y+1);
				for(i=0;i<size-1;i++){
					printf("%c",223);
				}
				fgcolor(6);
				if (ene->dir==7){
					gotoxy(ene->x-1,ene->y);
					printf("%c",219);
					fgcolor(5);
					printf("%c[%dD%c[%dA%c%c[%dD%c[%dB%c",ESC,1,ESC,1,201,ESC,1,ESC,2,200);
				} else{
					gotoxy(ene->x,ene->y);
					printf("%c",219);
					fgcolor(5);
					printf("%c[%dD%c[%dA%c%c[%dD%c[%dB%c",ESC,1,ESC,1,187,ESC,1,ESC,2,188);
				}}
		if(ene->dir==4 ||ene->dir==8){
				gotoxy(ene->x,ene->y-1);
				for(i=0;i<size-1;i++){
					printf("%c",220);
				}
				gotoxy(ene->x-2,ene->y);
				printf("%c",220);
				for(i=0;i<size-1;i++){
					printf("%c",219);
				}
				printf("%c",223);
				gotoxy(ene->x-2,ene->y+1);
				for(i=0;i<size-1;i++){
					printf("%c",223);
				}
				fgcolor(6);
				if (ene->dir==8){
					gotoxy(ene->x-1,ene->y);
					printf("%c",219);
					fgcolor(5);
					printf("%c[%dA%c%c[%dD%c[%dB%c",ESC,1,201,ESC,3,ESC,1,201);

				} else{
					gotoxy(ene->x,ene->y);
					printf("%c",219);
					fgcolor(5);
					printf("%c%c[%dD%c[%dB%c",188,ESC,3,ESC,1,188);
				}}
		if(ene->dir==2 ||ene->dir==6){
				gotoxy(ene->x-2,ene->y-1);
				for(i=0;i<size-1;i++){
					printf("%c",220);
				}
				gotoxy(ene->x-2,ene->y);
				printf("%c",223);
				for(i=0;i<size-1;i++){
					printf("%c",219);
				}
				printf("%c",220);
				gotoxy(ene->x,ene->y+1);
				for(i=0;i<size-1;i++){
					printf("%c",223);
				}
				fgcolor(6);
					if (ene->dir==2){
					gotoxy(ene->x,ene->y);
					printf("%c",219);
					fgcolor(5);
					printf("%c%c[%dD%c[%dA%c",187,ESC,3,ESC,1,187);

				} else{
					gotoxy(ene->x-1,ene->y);
					printf("%c",219);
					fgcolor(5);
					printf("%c[%dB%c%c[%dD%c[%dA%c",ESC,1,200,ESC,3,ESC,1,200);
		}}}

//draws an asteroid
void drawAsteroid(asteroid*ast,short style){
	gotoxy(ast->x-1,ast->y-1);
	char* krater="o";
	fgcolor(7);
	if(style==1){
	 printf("%c%c%c%c[%dB%c[%dD%c%c%c%c%c%c[%dD%c[%dB%c%c%c",220,178,220,ESC,1,ESC,4,176,178,178,178,176,ESC,4,ESC,1,223,178,223);
	} else{
		gotoxy(ast->x-3,ast->y-1);
	printf("%c%c%c%c%c%c[%dB%c[%dD%c%c%c",176,177,178,178,177,ESC,1,ESC,6,176,177,178);
	printf("%s",krater);
	printf("%c%c%c%c[%dB%c[%dD%c%c%c%c%c%c%c%c[%dB%c[%dD%c%c%c%c%c",219,178,177,ESC,1,ESC,7,176,177,178,219,219,178,177,ESC,1,ESC,6,176,177,178,178,177);

	}
}

//draws a random powerup at an intended position
void drawPowerup(powerup *pow){
	//1 speed boost (yellow), 2 Dmg boost (red), 3 Score mult. (purple), 4 Bullet type 1 (light blue), 5 Bullet type 2 (blue), 6 Bullet type 3 (Dark blue)

	gotoxy(pow->x-1,pow->y);
	if(pow->status==0){
		//dont draw if it's not real
	}else if(pow->status==1){
		fgcolor(3);
	} else if(pow->status==2) {
		fgcolor(1);
	}else if(pow->status==3) {
		fgcolor(5);
	}else if(pow->status==4) {
		fgcolor(51);
	}else if(pow->status==5) {
		fgcolor(21);
	}else if(pow->status==6) {
		fgcolor(19);
	} else{
		fgcolor(15); //white is an error color
	} printf("%c%c",219,219);
}

//turns all bullets off and puts them at (0,0)
void initBullet(bullet* bul,int n_bull){
	//x,y and dir for all bullets get a junk value
	//status is turned off as no bullets are fired on game start
	int i;
	for(i=0;i<n_bull;i++){
		bul[i].status=0;
		bul[i].x=0;
		bul[i].y=0;
		bul[i].dir=1;
	}}

//turns all powerups off and puts them at (0,0)
void initPowerup(powerup *pow,int n_pow){
	//x and y for all powerups get a junk value
	//status is turned off as no powerups are present on game start
	int i;
	for(i=0;i<n_pow;i++){
		pow[i].status=0;
		pow[i].x=0;
		pow[i].y=0;
	}}

//initializes spaceship and draws it in the center
void initSpaceship(spaceship* ship, uint8_t difficulty, int style){
	//x,y,hp,status,dir,are set to default values
	ship->x=95;
	ship->y=25;
	ship->hp=6-difficulty;
	ship->dir=1;
	ship->style=style;
	ship->status=1; // indicates that they are active when true
	ship->maxbullets=5-2*(difficulty-1);	// Sets maximum number of bullets
	ship->bullets=5-2*(difficulty-1);	// Sets number of bullets
	drawSpaceship(ship);
}

//generates almost randomly placed enemies and draws them
void initEnemy(enemy* all_enemies,int n_ene, uint8_t difficulty){
	int i,k;
	for(i=0;i<n_ene;i++){
		k=rand() % (3 + 1); // assigns each a random part of the screen in which to appear
		if(k==0){
			all_enemies[i].x=rand() % (185 - 5 + 1)+ 5; // assigns initial coords to each enemy
			all_enemies[i].y=rand() % (18 - 3 + 1)+ 3;
			all_enemies[i].dir=5; // a direction somewhat facing the player
		} else if(k==1){
			all_enemies[i].x=rand() % (185 - 5 + 1)+ 5;
			all_enemies[i].y=rand() % (45 - 30 + 1)+ 30;
			all_enemies[i].dir=1;
		}else if(k==2){
			all_enemies[i].x=rand() % (85 - 5 + 1)+ 5;
			all_enemies[i].y=rand() % (45 - 3 + 1)+ 3;
			all_enemies[i].dir=3;
		}else if(k==3){
			all_enemies[i].x=rand() % (185 - 105 + 1)+ 105;
			all_enemies[i].y=rand() % (45 - 3 + 1)+ 3;
			all_enemies[i].dir=7;
		}

		all_enemies[i].hp=2+difficulty; //setting default values which can be changed later
		all_enemies[i].vely=1;
		all_enemies[i].velx=1;
		all_enemies[i].status=1; // indicates that they are active when true
		drawEnemy(&all_enemies[i]); //finishes by drawing them
		}}

//generates almost randomly placed asteroids and draws them
void initAsteroid(asteroid* all_asteroids,int n_ast){
	int i,k;
	for(i=0;i<n_ast;i++){
		k=rand() % (3 + 1); // assigns each a random part of the screen in which to appear
		if(k==0){
			all_asteroids[i].x=rand() % (185 - 5 + 1)+ 5; // assigns initial coords to each asteroid
			all_asteroids[i].y=rand() % (18 - 3 + 1)+ 3;
		} else if(k==1){
			all_asteroids[i].x=rand() % (185 - 5 + 1)+ 5;
			all_asteroids[i].y=rand() % (45 - 30 + 1)+ 30;
		}else if(k==2){
			all_asteroids[i].x=rand() % (85 - 5 + 1)+ 5;
			all_asteroids[i].y=rand() % (45 - 3 + 1)+ 3;
		}else if(k==3){
			all_asteroids[i].x=rand() % (185 - 105 + 1)+ 105;
			all_asteroids[i].y=rand() % (45 - 3 + 1)+ 3;
		}

		all_asteroids[i].status=1; // indicates that they are active when true
		drawAsteroid(&all_asteroids[i],2); //finishes by drawing them
		}}




// draw a bullet that has already been fired
void drawBullet(bullet* bul){
	fgcolor(11);
	char *ud, *ur, *lr;
	if((bul->status & 0x00100000) || (bul->status & 0x01000000)){
		ud = "|";
		ur = "/";
		lr = "-";
	} else{
		ud = "o";
		ur = "o";
		lr = "o";
	}
	if(bul->status==0){
		//if it is not active dont draw it
	} else if(bul->status > 0){; //corresponds to 1 dmg
		if(bul->dir==1){				//Up
			gotoxy(bul->x,bul->y);
			if (!(bul->status & 0x01000000)){
				printf("%c", *ud);
			} else if (bul->status & 0x01000000){
				bold(1);
				printf("%c", *ud);
				bold(0);
			}
		} else if(bul->dir==5){			// Down
			gotoxy(bul->x,bul->y);
			if (!(bul->status & 0x01000000)){
				printf("%c", *ud);
			} else if (bul->status & 0x01000000){
				bold(1);
				printf("%c", *ud);
				bold(0);
			}
		}else if(bul->dir==2){			// Up-right
			gotoxy(bul->x,bul->y);
			if (!(bul->status & 0x01000000)){
				printf("%c", *ur);
			} else if (bul->status & 0x01000000){
				bold(1);
				printf("%c", *ur);
				bold(0);
			}
		}else if(bul->dir==3){			// Right
			if (!(bul->status & 0x01000000)){
				printf("%c", *lr);
			} else if (bul->status & 0x01000000){
				bold(1);
				printf("%c", *lr);
				bold(0);
			}
		}else if(bul->dir==7){			// Left
			gotoxy(bul->x,bul->y);
			if (!(bul->status & 0x01000000)){
				printf("%c", *lr);
			} else if (bul->status & 0x01000000){
				bold(1);
				printf("%c", *lr);
				bold(0);
			}
		}else if(bul->dir==4){			// Down-right
			gotoxy(bul->x,bul->y);
			if (!(bul->status & 0x01000000)){
				printf("%c", 92);
			} else if (bul->status & 0x01000000){
				bold(1);
				printf("%c", 92);
				bold(0);
			}
		}else if(bul->dir==6){			// Down-left
			gotoxy(bul->x,bul->y);
			if (!(bul->status & 0x01000000)){
				printf("%c", *ur);
			} else if (bul->status & 0x01000000){
				bold(1);
				printf("%c", *ur);
				bold(0);
			}
		}else if(bul->dir==8){			// Up-left
			gotoxy(bul->x,bul->y);
			if (!(bul->status & 0x01000000)){
				printf("%c", 92);
			} else if (bul->status & 0x01000000){
				bold(1);
				printf("%c", 92);
				bold(0);
			}
		}
	}
}


//spawns an enemy near the edge of the screen
void SpawnEnemy(enemy* all_enemies,int n_ene){
	int i,k;
		for(i=0;i<n_ene;i++){
			if((all_enemies[i].status==0) && ((rand() % (3 + 1)) >=2 ) ){ //checks empty enemy slots and
				k=rand() % (3 + 1); // assigns each a random part of the screen in which to appear
				all_enemies[i].status=1; // indicates that they are active when true
				if(k==0){
					all_enemies[i].x=rand() % (185 - 5 + 1)+ 5; // assigns initial coords to each enemy
					all_enemies[i].y=rand() % (10 - 3 + 1)+ 3;
					all_enemies[i].dir=5; // a direction somewhat facing the player
				} else if(k==1){
					all_enemies[i].x=rand() % (185 - 5 + 1)+ 5;
					all_enemies[i].y=rand() % (45 - 37 + 1)+ 37;
					all_enemies[i].dir=1;
				}else if(k==2){
					all_enemies[i].x=rand() % (50 - 5 + 1)+ 5;
					all_enemies[i].y=rand() % (45 - 3 + 1)+ 3;
					all_enemies[i].dir=3;
				}else if(k==3){
					all_enemies[i].x=rand() % (185 - 145 + 1)+ 105;
					all_enemies[i].y=rand() % (45 - 3 + 1)+ 3;
					all_enemies[i].dir=7;
		}}}}

void SpawnAsteroid(asteroid* ast,int n_ast){
	int i,k;
		for(i=0;i<n_ast;i++){
			if((ast[i].status==0) && ((rand() % (3 + 1)) >=2 ) ){
				ast[i].status=1; // indicates that they are active when true
				k=rand() % (3 + 1); // assigns each a random part of the screen in which to appear
				if(k==0){
					ast[i].x=rand() % (185 - 5 + 1)+ 5; // assigns initial coords to each asteroid
					ast[i].y=rand() % (10 - 3 + 1)+ 3;
					drawAsteroid(&ast[i],2); //finishes by drawing them
				} else if(k==1){
					ast[i].x=rand() % (185 - 5 + 1)+ 5;
					ast[i].y=rand() % (45 - 37 + 1)+ 37;
					drawAsteroid(&ast[i],2); //finishes by drawing them
				}else if(k==2){
					ast[i].x=rand() % (85 - 5 + 1)+ 5;
					ast[i].y=rand() % (45 - 3 + 1)+ 3;
					drawAsteroid(&ast[i],2); //finishes by drawing them
				}else if(k==3){
					ast[i].x=rand() % (185 - 105 + 1)+ 105;
					ast[i].y=rand() % (45 - 3 + 1)+ 3;
					drawAsteroid(&ast[i],2); //finishes by drawing them

		}}}}

//draws each active asteroid at their position & delete those near the edge
void updateAsteroid(asteroid* ast, int n_ast){
	short i;
	for(i=0;i<n_ast;i++){
		if(ast[i].status!=0){ //check each active asteroid
			if(CheckOnScr(ast[i].x,ast[i].y)==0){ //check if they are near an edge
				ast[i].status=0;
				gotoxy(ast[i].x-3,ast[i].y-1);
				printf("     ");
				gotoxy(ast[i].x-4,ast[i].y);
				printf("       ");
				gotoxy(ast[i].x-4,ast[i].y+1);
				printf("       ");
				gotoxy(ast[i].x-3,ast[i].y+2);
				printf("      ");
			} else {
			drawAsteroid(&ast[i],2);
		}}}}

//draws each active powerup at their position & delete those near the edge
void updatePowerup(powerup* pow, int n_pow){
	short i;
	for(i=0;i<n_pow;i++){
		if(pow[i].status!=0){ //check each active powerup
			if(CheckOnScr(pow[i].x,pow[i].y)==0){ //check if they are near an edge
				pow[i].status=0;
				gotoxy(pow[i].x-1,pow[i].y-1);
				printf("  ");
			} else { //if not simply draw them
			drawPowerup(&pow[i]);
		}}}}
//simply check all active enemies and draws them at their current internal position
void updateEnemy(enemy* ene, int n_ene){
	short i;
	for(i=0;i<n_ene;i++){
		if(ene[i].status!=0){ //check each active enemy
			 //simply draw them
			drawPowerup(&ene[i]);
		}}}

//deletes the spaceship. should be followed by drawing it again
void eraseSpaceship(spaceship* shp){
	gotoxy(shp->x-2,shp->y-1); //because the ship stands still we can use it's coordinates
	printf("     "); // to go there and just print spaces to delete it
	gotoxy(shp->x-2,shp->y);
	printf("     ");
	gotoxy(shp->x-3,shp->y+1);
	printf("     ");
}

//clrscr() followed by drawing every object
void updateAll(spaceship * shp, enemy * ene, bullet* bul, asteroid* ast, powerup* pow, int n_ene, int n_ast, int n_bul, int n_pow, int *pp){
	uint8_t i;
	clrscr();
	drawSpaceship(shp);
	for(i=0;i<n_ast;i++){
		if(ast[i].status !=0){
			drawAsteroid(&ast[i],2);
		}
	}
	for(i=0;i<n_ene;i++){
		if(ene[i].status !=0){
			drawEnemy(&ene[i]);
		}
	}
	for(i=0;i<n_pow;i++){
		if(pow[i].status !=0){
			drawPowerup(&pow[i]);
		}
	}
	for(i=0;i<n_bul;i++){
		if(bul[n_bul-i].status !=0){
			drawBullet(&bul[n_bul]);
		}
	}
}


/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White      */
