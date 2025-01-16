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


	//The commented code below is simply for showing LCD things, not needed atm, but uncomment to see
	/*
	//Prepare byte array and strings to be updated
	uint8_t byteArray[512];
	char life[] = "Lives: ";
	char score[] = "Score: ";
	char bullets[] = "Ammo : ";

	//initialize LCD
	lcd_init();

	//Update byte array with strings (These will frequently give warnings, however it should still work)
	lcd_write_string(life, 1, 1, &byteArray);
	lcd_write_string(score, 1, 2, &byteArray);
	lcd_write_string(bullets, 1, 3, &byteArray);

	//Transmit byte array
	lcd_push_buffer(byteArray);
	*/


	/*lcd_init();
	uint8_t buffer[512];
	memset(buffer,0x00,512);
	initJoystick();
	init_lcd(buffer);
	init_radar(buffer);*/
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



	while(1){
		menuSelect(0, &level);
	}
}
