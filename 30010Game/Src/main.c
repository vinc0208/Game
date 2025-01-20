#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include <Graphics functions.h>
#include "Hardware interface functions.h"
#include "Menu functions.h"
#include <stdlib.h>
#include <string.h>
#include "ansi.h"
#include "sinusoid.h"
#include "Score.h"
int main(void) {

	uart_init(115200);

	//Initialize time
	Timer15Config();
	ResetTime(); //We dont want time to start counting up when we havent started the game yet

	//set the seed
	srand(5);


	//this block initializes the game
	clrscr(); //clear screen and set starting parameters
	uint8_t difficulty=1,n_bul=5-(difficulty-1),style=1,n_ene = 0,n_ast=5,n_pow=5,i,angle=0,prevangle = -1,reload_timer=-10;
	int player_powers = 0x00100000;
	bullet all_bullets[n_bul]; // make arrays of all objects
	asteroid all_asteroids[n_ast];
	enemy all_enemies[n_ene];
	powerup all_powerups[n_pow];
	spaceship playership;


	initSpaceship(&playership,difficulty,style); //initialize and draw all objects
	initBullet(all_bullets, n_bul);
	initPowerup(all_powerups, n_pow);
	initEnemy(all_enemies,n_ene,difficulty);
	initAsteroid(all_asteroids,n_ast);




	//initialize LCD
	uint8_t buffer[512];
	init_lcd(buffer, playership);


	int level = 1;


	StopTime();
	StartTime();

	while(1){

	}
}
