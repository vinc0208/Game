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

	//Allow LED light to work
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	//Allow red color
	GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000001 << (4 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

	//Allow green color
	GPIOC->MODER &= ~(0x00000003 << (7 * 2));
	GPIOC->MODER |= (0x00000001 << (7 * 2));

	//Allow blue color
	GPIOA->MODER &= ~(0x00000003 << (9 * 2));
	GPIOA->MODER |= (0x00000001 << (9 * 2));

	//Turn all lights off to begin with
	GPIOA->ODR |= (0x0001 << 9);
	GPIOC->ODR |= (0x0001 << 7);
	GPIOB->ODR |= (0x0001 << 4);


	//Transmit byte array
		uint8_t buffer[512];
		init_lcd(buffer);


		int level = 10;



		/* //this block initializes the game
			clrscr(); //clear screen and set starting parameters
			uint8_t n_bul=5, difficulty=2,style=1,n_ene = 2+difficulty,n_ast=5,n_pow=5;
			bullet testbul[n_bul]; // make arrays of all objects
			asteroid all_asteroids[n_ast];
			enemy all_enemies[n_ene];
			powerup all_powerups[n_pow];
			spaceship playership;

			initSpaceship(&playership,difficulty,style); //initialize and draw all objects
			initBullet(&testbul, n_bul);
			initPowerup(&all_powerups,n_pow);
			initEnemy(&all_enemies,n_ene);
			initAsteroid(&all_asteroids,n_ast);
			*/

		//For testing radar
		/*
		initJoystick();
		uint8_t prevangle = -1;
		uint8_t angle = 0;
		 */



	/* //this block initializes the game
		clrscr(); //clear screen and set starting parameters
		uint8_t n_bul=5, difficulty=2,style=1,n_ene = 2+difficulty,n_ast=5,n_pow=5;
		bullet testbul[n_bul]; // make arrays of all objects
		asteroid all_asteroids[n_ast];
		enemy all_enemies[n_ene];
		powerup all_powerups[n_pow];
		spaceship playership;

		initSpaceship(&playership,difficulty,style); //initialize and draw all objects
		initBullet(&testbul, n_bul);
		initPowerup(&all_powerups,n_pow);
		initEnemy(&all_enemies,n_ene);
		initAsteroid(&all_asteroids,n_ast);
		*/



	while(1){
		//joystick_2_radar(uint8_t* buffer);
		menuSelect(0, &level);
	}
}
