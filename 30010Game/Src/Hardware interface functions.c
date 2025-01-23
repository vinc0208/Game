/*
 * Hardware interface functions.c
 *
 *  Created on: 13 Jan 2025
 *      Author: vince
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "Graphics functions.h"
#include "ansi.h"
#define ESC 0x1B
#include <stdint.h> // whatever
#include <stdio.h>
#include "Hardware interface functions.h"
#include "charset.h"
#include <string.h>
#include "Gamechar.h"
#include "Score.h"


void uartStringModifier(char arr[]){
	int static n = 0;
	char static i = 0;

	i = uart_get_char();

	if(i == 0x0D){
		printf("\n");
		printf("%s\n", arr);
		for(int h = 0; h<sizeof(arr); h++){
			arr[h] = 0;
		}
		n = 0;
	} else if(i != 0){
		arr[n] = i;
		arr[n+1] = 0;
		printf("%c", arr[n]);
		n++;
	}

}

char uartKeyRead(){
	char key=uart_get_char();
	uart_clear();
	return key;
}


void TIM1_BRK_TIM15_IRQHandler(void) { //Needed to count the time
	TimeMaster15.msecond += 1;
	if (TimeMaster15.msecond >= 10){
		TimeMaster15.msecond %= 10;
		TimeMaster15.hsecond += 1;
	}
	if (TimeMaster15.hsecond >= 100){
		TimeMaster15.hsecond %= 100;
		TimeMaster15.second += 1;
	}
	if (TimeMaster15.second >= 60){
		TimeMaster15.second %= 60;
		TimeMaster15.minute += 1;
	}
	if (TimeMaster15.minute >= 60){
		TimeMaster15.minute %= 60;
		TimeMaster15.hour += 1;
	}

	TIM15->SR &= ~0x0001; // Clear interrupt bit
 }

void Timer15Config(void){ //Needed to have time
	RCC->APB2ENR |= RCC_APB2Periph_TIM15; // Enable clock line to timer 15;
	TIM15->CR1 &= ~(0x0001<<0); // Configure timer 15
	TIM15->CR1 &= ~(0x0001<<1);
	TIM15->CR1 &= ~(0x0001<<2);
	TIM15->CR1 &= ~(0x0001<<3);
	TIM15->CR1 &= ~(0x0001<<7);
	TIM15->CR1 &= ~(0x0003<<8);
	TIM15->CR1 &= ~(0x0001<<11);

	TIM15->ARR = 64000; // Set reload value
	TIM15->PSC = 0x0000; // Set prescale value

	TIM15->CR1 |= (0x0001<<0);

	TIM15->DIER |= 0x0001; // Enable timer 15 interrupts
	NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 1); // Set interrupt priority
	NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn); // Enable interrupt

}

void StartTime(){ //Starts time
	NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn); // Enable interrupt
}

void StopTime(){ //Stops time
	NVIC_DisableIRQ(TIM1_BRK_TIM15_IRQn); // Disable interrupt
}

void ResetTime(){ //Resets the time
	NVIC_DisableIRQ(TIM1_BRK_TIM15_IRQn); // Disable interrupt
	TimeMaster15.hour = 0;
	TimeMaster15.minute = 0;
	TimeMaster15.second = 0;
	TimeMaster15.hsecond = 0;
	TimeMaster15.msecond = 0;

	SpeedIncrease = TimeMaster15;
}

void lcd_write_string(char* string, uint8_t slice, uint16_t line, uint8_t* buffer){
	uint8_t strleng = strlen(string);
	uint8_t temp1[strleng]; //We make an array with the length of string to hold the individual values of each character
	uint16_t u;
	u = (line-1)*128; //Fordi der er 128 pr linje

	for (uint8_t i=0; i<strleng; i++){ //We put all characters of the string into temp1
		temp1[i] = (int)string[i];
	}

	for (uint8_t i=0; i<strleng; i++){ //We take all the numbers we got from the string pointer and reduce them by 32
		temp1[i] -= 0x20;
	}

	for (uint8_t i=0; i<strleng; i++){ //We have two for loops so we can for each character put the 5 values needed to make that character on the LCD
		uint8_t z = temp1[i];
		for (uint8_t j=0; j<5; j++){
			buffer[u+(i*6)+slice+j] = character_data[z][j];
		}
	}
}

void lcd_update(char* string, char* tbu, uint8_t slice, uint16_t line, uint8_t* buffer){
	uint8_t strleng = strlen(string);
	uint8_t tbuleng = strlen(tbu);

	char temp2[strleng+tbuleng+1];

	for (uint8_t i=0; i<=strleng; i++){
		temp2[i] = (int)string[i];
	}
	for (uint8_t i=0; i<=tbuleng; i++){
		temp2[i+strleng] = (int)tbu[i];
	}

	lcd_write_string(temp2, slice, line, buffer);
}


/*****************************/
/******* LCD Functions *******/
/*****************************/
void init_radar(uint8_t *buffer) {
	uint8_t i;
	uint8_t slice = 106;
	uint8_t line;
	for (line=0; line<2; line++) {
		for (i=0; i<15; i++) {
			buffer[line*128 + slice + i] = game_char_data[0][0];		//Clears radar
		}
	}
	line = 2, slice = 113;
	buffer[(line-1)*128 + slice] = 0x01;								//Adds radar center
	lcd_push_buffer(buffer);
}


void init_lcd(uint8_t* buffer, spaceship ship) {
	//Prepare byte array and strings to be updated (buffer)
	memset(buffer,0x00,512);
	char score[] = "Score: 0    ";
	char life[] = "Lives: ";
	char bullets[] = "Ammo : ";

	//initialize LCD
	lcd_init();

	//Update byte array with strings (These will frequently give warnings, however it should still work)
	lcd_write_string(score, 1, 1, buffer);
	lcd_write_string(life, 1, 2, buffer);
	lcd_write_string(bullets, 1, 3, buffer);

	uint8_t n;
	uint8_t i;
	uint8_t j;
	for (n=0; n<ship.hp; n++) {
		for (i=0; i<2; i++) {
			for (j=0; j<5; j++) {
				buffer[(1)*128 + 37 + n*11 + i*5 + j] = game_char_data[2+i][j];	//Prints hearts
			}
		}
	}

	for (n=0; n<ship.bullets; n++) {
		for (j=0; j<5; j++) {
			buffer[(2)*128 + 38 + n*11 + j] = game_char_data[1][j];				//Prints bullets
		}
	}


	for (j=0; j<2; j++) {
		for (i=0; i<4; i++) {
			buffer[128*i + 93 +j*2] = game_char_data[24][0];				//Draw two vert lines
		}
	}
	for (uint8_t l=0; l<2; l++) {
		for (i=0; i<5; i++) {
			for (j=0; j<5; j++) {
				n = 19 + i - 5*l;
				buffer[(l+2)*128 + i*6 + 99 + j] = game_char_data[n][j];	//Prints radar text
			}
		}
	}
	init_radar(buffer);

}


void radar(uint8_t* buffer, uint8_t angle, uint8_t* prevangle) {
	uint8_t slice, line;

	if (*prevangle == angle){

	}else{
		init_radar(buffer);
	}
	if (angle == 0) {						//No input

	}else if (angle == 3) {					//Right
		slice = 116;
		line = 1;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[9][j];
		}
		line = 2;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[10][j];
		}
		lcd_push_buffer(buffer);

	}	else if (angle == 1) {				//Up
		slice = 111;
		line = 1;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[5][j];
		}
		lcd_push_buffer(buffer);

	} else if (angle == 7) {				//Left
		slice = 106;
		line = 1;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[7][j];
		}
		line = 2;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[8][j];
		}
		lcd_push_buffer(buffer);

	} else if (angle == 5) {				//Down
		slice = 111;
		line = 2;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[12][j];
		}
		lcd_push_buffer(buffer);

	} else if (angle == 2) {				//Up-right
		slice = 116;
		line = 1;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[6][j];
		}
		lcd_push_buffer(buffer);

	} else if (angle == 8) {				//Up-left
		slice = 106;
		line = 1;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[4][j];
		}
		lcd_push_buffer(buffer);

	} else if (angle == 4) {				//Down-right
		slice = 116;
		line = 2;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[13][j];
		}
		lcd_push_buffer(buffer);

	} else if (angle == 6) {				//Down-left
		slice = 106;
		line = 2;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[11][j];
		}
		lcd_push_buffer(buffer);
	}
	prevangle = angle;
}


void RGB_life_detector(spaceship ship, int gamestart){
	if (ship.hp > 3 && gamestart == 1){ //Set blue
		GPIOA->ODR &= ~(0x0001 << 9);

		GPIOC->ODR |= (0x0001 << 7);
		GPIOB->ODR |= (0x0001 << 4);
	}
	else if (ship.hp == 3 && gamestart == 1){ //Set green
		GPIOC->ODR &= ~(0x0001 << 7);

		GPIOB->ODR |= (0x0001 << 4);
		GPIOA->ODR |= (0x0001 << 9);
	}

	else if (ship.hp == 2 && gamestart == 1){ //Set yellow
		GPIOC->ODR &= ~(0x0001 << 7);
		GPIOB->ODR &= ~(0x0001 << 4);

		GPIOA->ODR |= (0x0001 << 9);
	}

	else if (ship.hp == 1 && gamestart == 1){ //Set red
		GPIOB->ODR &= ~(0x0001 << 4);

		GPIOC->ODR |= (0x0001 << 7);
		GPIOA->ODR |= (0x0001 << 9);
	}
	else if (ship.hp <= 0 && gamestart == 1){ //Turn off LED
		GPIOB->ODR |= (0x0001 << 4);
		GPIOC->ODR |= (0x0001 << 7);
		GPIOA->ODR |= (0x0001 << 9);
	}
	else{
		GPIOA->ODR |= (0x0001 << 9);
		GPIOC->ODR |= (0x0001 << 7);
		GPIOB->ODR |= (0x0001 << 4);
	}
}


void update_stats(spaceship ship, uint8_t* buffer, uint16_t* currentscore){
	uint8_t n;
	uint8_t i;
	uint8_t j;
	for (n=0; n<ship.hp; n++) {
		for (i=0; i<2; i++) {
			for (j=0; j<5; j++) {
				buffer[(1)*128 + 37 + n*11 + i*5 + j] = game_char_data[2+i][j];	//Prints hearts
			}
		}
	}
	for (n=0; n<(5-ship.hp); n++) {
		for (i=0; i<2; i++) {
			for (j=0; j<5; j++) {
				buffer[(1)*128 + 81 - n*11 + i*5 + j] = game_char_data[0][0];	//Clears hearts
			}
		}
	}

	for (n=0; n<ship.bullets; n++) {
		for (j=0; j<5; j++) {
			buffer[(2)*128 + 38 + n*11 + j] = game_char_data[1][j];			//Prints bullets
		}
	}
	for (n=0; n<(5-ship.bullets); n++) {
		for (j=0; j<5; j++) {
			buffer[(2)*128 + 81 - n*11 + j] = game_char_data[0][0];			//Clears bullets
		}
	}
	char temp[6];
	sprintf(temp,"%d",ScoreTracker(0, &*currentscore));
	lcd_update("Score: ", temp, 1, 1, buffer);

	lcd_push_buffer(buffer);
}

void LEDprep(){
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000001 << (4 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

	GPIOC->MODER &= ~(0x00000003 << (7 * 2));
	GPIOC->MODER |= (0x00000001 << (7 * 2));

	GPIOA->MODER &= ~(0x00000003 << (9 * 2));
	GPIOA->MODER |= (0x00000001 << (9 * 2));

	GPIOB->ODR |= (0x0001 << 4);
	GPIOC->ODR |= (0x0001 << 7);
	GPIOA->ODR |= (0x0001 << 9);
}
