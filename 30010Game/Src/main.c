#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include <Graphics functions.h>
#include "Hardware interface functions.h"
#include "Menu functions.h"
#include <stdlib.h>
#include <string.h>

int main(void) {

	uart_init(115200);

	//Initialize time
	Timer15Config();

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

	while(1){
		menuSelect(0, &level);
	}
}
