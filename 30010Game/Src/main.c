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

	all_enemies[1].x=95;
	all_enemies[1].y=10;
	drawEnemy(&all_enemies[1]);
	all_bullets[1].status=1;


	//initialize LCD
	uint8_t buffer[512];
	init_lcd(buffer, playership);


	int level = 1;


	StopTime();
	StartTime();

	while(1){
		//menuSelect(0, &level);
		/*while(1){
			menuSelect(4, &level);
			if(gamestart == 1){
				break;
			}
		}*/

		if(TimeMaster15.hsecond %  50 == 0){
			uint8_t updateAst = playerMove(all_bullets,all_asteroids, all_enemies, all_powerups, &playership, 1);
			eraseSpaceship(&playership);
			drawSpaceship(&playership);
			fireBullet(&playership, all_bullets, player_powers, &reload_timer);
			if(updateAst == 1){
				updateAsteroid(all_asteroids, n_ast);
				updatePowerup(all_powerups, n_pow);
			}

			UpdateEnemyPos(&playership,all_enemies, n_ene);
			UpdateBulletPos(&playership,all_bullets, n_bul);
			CheckBulletCollisions(&playership,all_enemies,all_bullets,all_asteroids,all_powerups, n_ene, n_ast, n_bul,n_pow);
			CheckSpaceshipCollisions(&playership, all_enemies,all_asteroids,all_powerups,n_ene, n_ast, n_pow, &player_powers);
			for(i=0;i<n_ene;i++){
				if(all_enemies[i].status!=0){
					drawEnemy(&all_enemies[i]);
					}}
			SpawnEnemy(all_enemies,n_ene);
			SpawnAsteroid(all_asteroids,n_ast);
		}
		update_stats(playership, buffer);
	}
}
