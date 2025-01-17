#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include <Graphics functions.h>
#include "Hardware interface functions.h"
#include "Menu functions.h"
#include <stdlib.h>
#include <string.h>
#include "ansi.h"
#include "sinusoid.h"
int main(void) {

	uart_init(115200);
	//Initialize time
	Timer15Config();
	//set the seed
	srand(2);


	//initialize LCD
	uint8_t buffer[512];
	init_lcd(buffer);

	initJoystick();
	uint8_t X = readJoystick();
	uint8_t angle = 0;
	uint8_t prevangle = -1;

	int level = 10;



	 //this block initializes the game
		clrscr(); //clear screen and set starting parameters
		uint8_t n_bul=5, difficulty=2,style=1,n_ene = -2+difficulty,n_ast=18,n_pow=5,i;
		bullet all_bullets[n_bul]; // make arrays of all objects
		asteroid all_asteroids[n_ast];
		enemy all_enemies[n_ene];
		powerup all_powerups[n_pow];
		spaceship playership;

		initSpaceship(&playership,difficulty,style); //initialize and draw all objects
		initBullet(&all_bullets, n_bul);
		initPowerup(&all_powerups,n_pow);
		initEnemy(&all_enemies,n_ene);
		initAsteroid(&all_asteroids,n_ast);


		all_asteroids[1].x=95;
		all_asteroids[1].y=10;
		drawAsteroid(&all_asteroids[1],n_ene);
		all_bullets[1].status=1;
		fireBullet(&playership,&all_bullets[1]);

	while(1){
		//joystick_2_radar(buffer, X, angle, prevangle);
		//menuSelect(0, &level);


		UpdateObjPos(&playership,&all_enemies,&all_bullets,n_ene, n_bul);
		CheckBulletCollisions(&playership,&all_enemies,&all_bullets,&all_asteroids, n_ene, n_ast, n_bul);
		for(i=0;i<n_ene;i++){
			drawEnemy(&all_enemies[i]);
		}

	}
}
