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
	int16_t enemyTimeRefresh = 200;
	int16_t playerTimeRefresh = 50;


	//set the seed
	srand(5);

	//Prepare Highscores
	Highscore HighscoreArray[10];
	Highscore player;
	PrepareFlashIfNeeded();
	ReadHighscores(HighscoreArray);

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

	//initialize LCD
	uint8_t buffer[512];
	init_lcd(buffer, playership);


	int level = 1;
	int gamestart = 0;
	int first = 1;
	int speed = 1;
	int menu = 0;


	StopTime();
	StartTime();

	while(1){

		while(gamestart == 0){
			menuSelect(menu, &level, &gamestart, &first);
		}

		clrscr();
		initSpaceship(&playership,difficulty,style); //initialize and draw all objects
		initBullet(all_bullets, n_bul);
		initPowerup(all_powerups, n_pow);
		initEnemy(all_enemies,n_ene,difficulty);
		initAsteroid(all_asteroids,n_ast);

		ResetTime();
		StartTime();

		while(playership.hp > 0){
			int8_t static t = 0;
			int static s = 0;

			switch (pp & 0x00000011) {
			  case 1:
			    playerTimeRefresh = 40;
			    break;
			  case 17:
				playerTimeRefresh = 32;
			    break;
			  case 0:
				playerTimeRefresh = 50;
				break;

			}

			if(TimeMaster15.hsecond != t){
				bulletTime++;
				enemyTime++;
				playerTime++;
				s++;
				t = TimeMaster15.hsecond;
			}

			if(bulletTime >= 33 ){
				UpdateBulletPos(&playership,&all_bullets, n_bul);
				CheckBulletCollisions(&playership, &all_enemies, &all_bullets, &all_asteroids,&all_powerups, n_ene, n_ast, n_bul, n_pow);
				bulletTime = 0;
			}

			if(enemyTime >= enemyTimeRefresh){
				UpdateEnemyPos(&playership,&all_enemies,n_ene);
				SpawnEnemy(&all_enemies,n_ene,difficulty);
				updateEnemy(&all_enemies, n_ene);
				enemyTime = 0;
			}

			if(playerTime >= playerTimeRefresh){
				playerMove(&all_bullets, &all_asteroids, &all_enemies, &all_powerups, &playership, speed, n_ene, n_ast, n_bul, n_pow);
				updateAsteroid(&all_asteroids, n_ast);
				updatePowerup(&all_powerups, n_pow);
				CheckSpaceshipCollisions(&playership, &all_enemies, &all_asteroids,&all_powerups, n_ene, n_ast, n_pow, &pp);
				SpawnAsteroid(&all_asteroids,n_ast);
				updateEnemy(&all_enemies, n_ene);
				update_stats(playership, &buffer);
				playerTime = 0;
			}
			if(s>=1000 && (enemyTimeRefresh > 80)){
				enemyTimeRefresh-=10;
				s=0;
			}
		}
		gamestart = 0;
		menu = 3;
		first = 1;
		speed = 1;
		StopTime();




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
