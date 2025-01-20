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
	int16_t bulletTime = 0;
	int16_t playerTime = 0;
	int16_t enemyTime = 0;

	//set the seed
	srand(5);


	//this block initializes the game
	clrscr(); //clear screen and set starting parameters
	uint8_t difficulty=1,n_bul=5-(difficulty-1),style=1,n_ene = 5,n_ast=5,n_pow=5,i,angle=0,prevangle = -1,reload_timer=-10;
	int player_powers = 0x00100000;
	int pp=0x00100000;
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
	int gamestart = 0;
	int speed = 1;


	StopTime();
	StartTime();



	while(1){
		int8_t static t = 0;
		if(TimeMaster15.hsecond != t){
			bulletTime++;
			enemyTime++;
			playerTime++;
			t = TimeMaster15.hsecond;
		}

		if(bulletTime >= 33 ){
			UpdateBulletPos(&playership,&all_bullets, n_bul);
			CheckBulletCollisions(&playership, &all_enemies, &all_bullets, &all_asteroids,&all_powerups, n_ene, n_ast, n_bul, n_pow);
			bulletTime = 0;
		}

		if(enemyTime >= 200){
			UpdateEnemyPos(&playership,&all_enemies,n_ene);
			SpawnEnemy(&all_enemies,n_ene);
			updateEnemy(&all_enemies, n_ene);
			enemyTime = 0;
		}

		if(playerTime >= 50){
			playerMove(&all_bullets, &all_asteroids, &all_enemies, &all_powerups, &playership, speed, n_ene, n_ast, n_bul, n_pow);
			updateAsteroid(&all_asteroids, n_ast);
			updatePowerup(&all_powerups, n_pow);
			CheckSpaceshipCollisions(&playership, &all_enemies, &all_asteroids,&all_powerups, n_ene, n_ast, n_pow, &pp);
			SpawnAsteroid(&all_asteroids,n_ast);
			updateEnemy(&all_enemies, n_ene);
			playerTime = 0;
		}

	}
}

/*For playermovement
 * playerMove()
 * updateAsteroid
 * updatePowerup
 * CheckSpaceshipCollisions
 * SpawnAsteroid
 */

/*For bullet refresh
 * LorentzForce
 * UpdateBulletPos
 * CheckBulletCollisions
 */

/*For enemy refresh
 * UpdateEnemyPos
 * SpawnEnemy
 * UpdateEnemy
 */
