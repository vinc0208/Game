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
	Highscore coolplayer;
	PrepareFlashIfNeeded();
	ReadHighscores(HighscoreArray);

	//Prepare LED
	LEDprep();

	int gamestart = 0;
	int first = 1;
	int initLCD = 1;
	int speed = 1;
	int menu = 0;
	uint16_t currentscore = 0;
	uint8_t difficulty=1;
	uint8_t buffer[512];
	uint8_t key;
	ResetScore(&currentscore);


	StopTime();
	StartTime();

	while(1){

		while(gamestart == 0){
			menuSelect(menu, &difficulty, &gamestart, &first);
		}
		uint8_t n_bul=6-difficulty,style=1,n_ene = 4+difficulty,n_ast=5,n_pow=5,i,angle=0,prevangle = 10;
		int reload_timer=0;

		//this block initializes the game
		//Set starting parameters
		int pp=0x10000000;

		// make arrays of all objects
		bullet all_bullets[n_bul];
		asteroid all_asteroids[n_ast];
		enemy all_enemies[n_ene];
		powerup all_powerups[n_pow];
		spaceship playership;

		//initialize and draw all objects
		clrscr();
		initSpaceship(&playership,difficulty,style);
		initBullet(all_bullets, n_bul);
		initPowerup(all_powerups, n_pow);
		initEnemy(all_enemies,n_ene,difficulty);
		initAsteroid(all_asteroids,n_ast);

		if(initLCD){
			//initialize LCD
			init_lcd(buffer, playership);
			initLCD = 0;
		}


		//Set enemy starting speed based on chosen difficulty
		switch (difficulty) {
		  case 1:
		    enemyTimeRefresh = 200;
		    break;
		  case 2:
			  enemyTimeRefresh = 180;
		    break;
		  case 3:
			  enemyTimeRefresh = 160;
			break;

		}

		//Set time to 0 and start time for the game
		ResetTime();
		StartTime();

		//This is the beginning of the game loop
		while(playership.hp > 0){
			int8_t static t = 0;
			int static s = 0;
			uint8_t k = uart_get_char();

			if(k != 0){
				key = k;
			}

			//This sets the player movement speed based on which powerups are active
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

			//Adding for the three counters of player movement, enemy movement and bullet, movement
			//These will be updated at refresh rates independent of each other
			if(TimeMaster15.hsecond != t){
				bulletTime++;
				enemyTime++;
				playerTime++;
				s++;
				t = TimeMaster15.hsecond;
			}
			//This is the bullet refresh section
			if(bulletTime >= 33 ){
				fireBullet(&playership, all_bullets, pp, &reload_timer, &key, TimeMaster15.second, TimeMaster15.minute);
				UpdateBulletPos(&playership,all_bullets, n_bul);
				CheckBulletCollisions(&playership, all_enemies, all_bullets, all_asteroids,all_powerups, n_ene, n_ast, n_bul, n_pow, &currentscore, pp);
				bulletTime = 0;
			}
			//This is the enemy refresh section
			if(enemyTime >= enemyTimeRefresh){
				UpdateEnemyPos(&playership,all_enemies,n_ene);
				closestEnemy(&angle, playership, all_enemies, n_ene);
				radar(buffer, angle, &prevangle);
				SpawnEnemy(all_enemies,n_ene,difficulty);
				updateEnemy(all_enemies, n_ene);
				enemyTime = 0;
			}
			//This is the player refresh section
			if(playerTime >= playerTimeRefresh){
				playerMove(all_bullets, all_asteroids, all_enemies, all_powerups, &playership, n_ene, n_ast, n_bul, n_pow, &key);
				updateAsteroid(all_asteroids, n_ast);
				updatePowerup(all_powerups, n_pow);
				CheckSpaceshipCollisions(&playership, all_enemies, all_asteroids,all_powerups, n_ene, n_ast, n_pow, &pp, &currentscore);
				SpawnAsteroid(all_asteroids,n_ast);
				updateEnemy(all_enemies, n_ene);
				update_stats(playership, buffer, &currentscore);
				RGB_life_detector(playership, gamestart);
				playerTime = 0;
			}
			//This last counter s and if statement is for the increase of enemy speed based on progression of game
			if(s>=1000 && (enemyTimeRefresh > 100)){
				enemyTimeRefresh-=5;
				s=0;
			}
		}
		gamestart = 0;
		update_stats(playership, buffer, &currentscore);
		coolplayer.score = currentscore;
		strncpy(coolplayer.name, "ABC", 4);
		HighscoreUpdater(HighscoreArray, coolplayer);
		ResetScore(&currentscore);
		WriteToFlash(HighscoreArray);
		menu = 3;
		first = 1;
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
