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
	srand(5);



	//Initialyze LCD
	uint8_t buffer[512];
	init_lcd(buffer);

	//Initialyze joystick to test radar
	uint8_t X = readJoystick();
	uint8_t prevangle = -1;
	uint8_t angle = 0;



	/* //this block initializes the game
		clrscr(); //clear screen and set starting parameters
		uint8_t n_bul=5, difficulty=2,style=1,n_ene = 20+difficulty,n_ast=5,n_pow=5,i;
		bullet all_bullets[n_bul]; // make arrays of all objects
		asteroid all_asteroids[n_ast];
		enemy all_enemies[n_ene];
		powerup all_powerups[n_pow];
		uint8_t player_powers = 0x00000000;
		spaceship playership;

		initSpaceship(&playership,difficulty,style); //initialize and draw all objects
		initBullet(&all_bullets, n_bul);
		initPowerup(&all_powerups,n_pow);
		initEnemy(&all_enemies,n_ene);
		initAsteroid(&all_asteroids,n_ast);*/


	int level = 10;


	while(1){
		joystick_2_radar(buffer, X, prevangle, angle);
		menuSelect(0, &level);


		/*UpdateObjPos(&playership,&all_enemies,&all_bullets,n_ene, n_bul);
		for(i=0;i<n_ene;i++){
			drawEnemy(&all_enemies[i]);
		}*/

	}
}
