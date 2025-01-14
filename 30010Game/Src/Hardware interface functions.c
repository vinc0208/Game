/*
 * Hardware interface functions.c
 *
 *  Created on: 13 Jan 2025
 *      Author: vince
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include <Graphics functions.h>
#include <ansi.h>
#define ESC 0x1B
#include <stdint.h> // whatever
#include <stdio.h>
#include "Hardware interface functions.h"
#include "charset.h"
#include <string.h>


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
	return uart_get_char();
}

/*uint8_t menuSelect(char menuName[]){
	uint8_t static sel = 1;
	uint8_t static options = 2;
	point static sellocations[3];


	if(menuName == "Main Menu"){
		options = 3;

	}else if(menuName == "Help"){
		options = 1;
	}else if(menuName == "Difficulty"){
		options = 1;
	}



}*/

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
}

//Work in progress (Jens)
/*void IncreasingSpeed(){
	int32_t static speed = 1;
	TimeFormat SpeedIncrease; //Maybe use global variable instead?
	SpeedIncrease = TimeMaster15;

	if ((TimeMaster15.second % 10) == 0){
		speed += 1;
		SpeedIncrease.second *= (speed/2);
	}
}*/

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

void menuSelect(int menu, int* level){
	//For menu input: 0 = main menu, 1 = help, 2 = difficulty, 3 = death, 4 = pause
	uint8_t static sel = 0;
	uint8_t static options;
	point static selXY[5];
	char static c = 0;
	int static currmenu;
	int static first = 1;

	if(first == 1){
		currmenu = menu;
		first = 0;
	}

	c = uartKeyRead();


	switch (currmenu) {
	  case 0:
		selXY[0].x = 1;
		selXY[0].y = 1;
		selXY[1].x = 10;
		selXY[1].y = 1;
		selXY[2].x = 20;
		selXY[2].y = 1;
		options = 3;
		break;
	  case 1:
		selXY[0].x = 5;
		selXY[0].y = 1;
		options = 1;
		break;
	  case 2:
		selXY[0].x = 5;
		selXY[0].y = 1;
		options = 1;
		break;
	  case 3:
		selXY[0].x = 5;
		selXY[0].y = 1;
		selXY[1].x = 15;
		selXY[1].y = 1;
		options = 2;
		break;
	  case 4:
		selXY[0].x = 5;
		selXY[0].y = 1;
		selXY[1].x = 15;
		selXY[1].y = 1;
		options = 2;
		break;
		}

	switch (c) {
	  case 97: //A
	    if(sel > 0){
	    	gotoxy(selXY[sel].x, selXY[sel].y);
	    	printf(" ");
	    	sel--;
	    	gotoxy(selXY[sel].x, selXY[sel].y);
	    	printf("%c", 205);
	    }
	    break;
	  case 100: //D
	    if(sel < options-1){
	    	gotoxy(selXY[sel].x, selXY[sel].y);
	    	printf(" ");
	    	sel++;
	    	gotoxy(selXY[sel].x, selXY[sel].y);
	    	printf("%c", 205);
	    }
	    break;
	  case 119: //W
	    if(currmenu == 2){
	    	//increment level
	    	*level++;
	    	printf("Level++\n");
	    }
	    break;
	  case 115: //S
	    if(currmenu == 2){
	    	//decrement level
	    	*level--;
	    	printf("Level--\n");
	    }
	    break;
	  case 13:
		currmenu = menuConfirm(currmenu, sel);
    	gotoxy(selXY[sel].x, selXY[sel].y);
    	printf(" ");
    	sel = 0;
		break;
	}

}

int menuConfirm(int menu, uint8_t sel){
	if(menu == 0){
		switch (sel) {
		  case 0:
		    //initGame()
			  printf("\n");
			  printf("INITGAME");
			  return 0;
		    break;
		  case 1:
		    //help()
			  printf("\n");
			  printf("help");
			  return 1;
		    break;
		  case 2:
		    //difficulty
			  printf("\n");
			  printf("difficulty");
			  return 2;
		    break;
		}
	}else if((menu == 1) || (menu == 2)){
		//main menu
		printf("\n");
		printf("Main menu");
		return 0;
	}else if(menu == 3){
		switch (sel) {
		  case 0:
		    //initGame()
			  printf("\n");
			  printf("initgame");
			  return 0;
		    break;
		  case 1:
		    //mainMenu()
			  printf("\n");
			  printf("mainMenu");
			  return 0;
		    break;
		}
	}else if(menu == 4){
		switch (sel) {
		  case 0:
		    //resume()
			  printf("\n");
			  printf("resume");
			  return 0;
		    break;
		  case 1:
		    //mainMenu()
			  printf("\n");
			  printf("mainMenu");
			  return 0;
		    break;
		}
	}else{
		return 0;
	}

}



/*****************************/
/* Joystick Control Functions*/
/*****************************/
void initJoystick() {
	// Exercise 5
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC;

	// Set pin PA0 to input
	GPIOA->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOA->MODER |=  (0x00000000 << (0 * 2)); // Set mode register (0x00 –Input, 0x01 -Output, 0x02 -Alternate Function, 0x03 -Analog in/out)
	GPIOA->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOA->PUPDR |=  (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -No pull, 0x01 -Pull-up, 0x02 -Pull-down)

	uint16_t val = GPIOA->IDR & (0x0001 << 2); //Read from pin PA0

	// Set pin PA1 to output
	GPIOA->OSPEEDR &= ~(0x00000003 << (1 * 2)); // Clear speed register
	GPIOA->OSPEEDR |=  (0x00000002 << (1 * 2)); // set speed register (0x01 -10 MHz, 0x02 -2 MHz, 0x03 -50 MHz)
	GPIOA->OTYPER &= ~(0x0001 << (1 * 1)); // Clear output type register
	GPIOA->OTYPER |=  (0x0000 << (1)); // Set output type register (0x00 -Push pull, 0x01 -Open drain)

	GPIOA->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
	GPIOA->MODER |=  (0x00000001 << (1 * 2)); // Set mode register (0x00 –Input, 0x01 -Output, 0x02 -Alternate Function, 0x03 -Analog in/out)

	GPIOA->ODR |= (0x0001 << 1); //Set pin PA1 to high



	//Set PA9, PB4, PC7 to outputs
	GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2));
	GPIOA->OSPEEDR |=  (0x00000002 << (9 * 2));
	GPIOA->OTYPER &= ~(0x0001 << (9 * 1));
	GPIOA->OTYPER |=  (0x0000 << (9));

	GPIOA->MODER &= ~(0x00000003 << (9 * 2));
	GPIOA->MODER |=  (0x00000001 << (9 * 2));


	GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2));
	GPIOB->OSPEEDR |=  (0x00000002 << (4 * 2));
	GPIOB->OTYPER &= ~(0x0001 << (4 * 1));
	GPIOB->OTYPER |=  (0x0000 << (4));

	GPIOB->MODER &= ~(0x00000003 << (4 * 2));
	GPIOB->MODER |=  (0x00000001 << (4 * 2));


	GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2));
	GPIOC->OSPEEDR |=  (0x00000002 << (7 * 2));
	GPIOC->OTYPER &= ~(0x0001 << (7 * 1));
	GPIOC->OTYPER |=  (0x0000 << (7));

	GPIOC->MODER &= ~(0x00000003 << (7 * 2));
	GPIOC->MODER |=  (0x00000001 << (7 * 2));

	GPIOA->ODR |= (0x0001 << 9);
	GPIOB->ODR |= (0x0001 << 4);
	GPIOC->ODR |= (0x0001 << 7);
}

uint8_t readJoystick() {

	uint8_t X = 00000000;
	uint8_t lval = GPIOC -> IDR & (0x0001 << 1);
	uint8_t cval = GPIOB -> IDR & (0x0001 << 5);
	uint8_t upval = GPIOA -> IDR & (0x0001 << 4);
	uint8_t nval = GPIOB -> IDR & (0x0001 << 0);
	uint8_t rval = GPIOC -> IDR & (0x0001 << 0);

	X|= upval >> 4;		//00000001	Up
	X|= nval << 1;		//00000010	Down
	X|= lval << 1;		//00000100	Left
	X|= rval << 3;		//00001000	Right
	X|= cval >> 1;		//00010000	Center

		return X;
}



/*****************************/
/** Radar Control Functions **/
/*****************************/
void init_radar(uint8_t *buffer) {
	uint8_t i;
	uint8_t slice = 106;
	uint8_t line;
	for (line=0; line<2; line++) {
		for (i=0; i<15; i++) {
			buffer[line*128 + slice + i] = game_char_data[0][1];
		}
	}
	line = 2, slice = 113;
	buffer[(line-1)*128 + slice] = 0x01;
	lcd_push_buffer(buffer);
}

void init_lcd(uint8_t* buffer) {
	uint8_t i;
	uint8_t j;
	for (j=0; j<2; j++) {
		for (i=0; i<4; i++) {
			buffer[128*i + 93 +j*2] = game_char_data[24][0];
		}
	}
	for (uint8_t l=0; l<2; l++) {
		for (i=0; i<5; i++) {
			for (j=0; j<5; j++) {
				uint8_t n = 19 + i - 5*l;
				buffer[(l+2)*128 + i*6 + 99 + j] = game_char_data[n][j];
			}
		}
	}
	init_radar(buffer);

}

void radar(uint8_t* buffer) {
	uint8_t X = readJoystick();
	uint8_t slice, line;

	while (0 == X) {
		init_radar(buffer);
		break;
	}
	while (((0x0001 << 3) & X) && !((0x0001 << 0) & X) && !((0x0001 << 1) & X)) {	//Right
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
		X = readJoystick();
		if (!((0x0001 << 3) & X) || ((0x0001 << 0) & X) || ((0x0001 << 1) & X)) { 	//If not pointing right or pointing up or down: break
			init_radar(buffer);
			break;
		}
	}

	while (((0x0001 << 0) & X) && !((0x0001 << 3) & X) && !((0x0001 << 2) & X)) {	//Up
		slice = 111;
		line = 1;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[5][j];
		}
		lcd_push_buffer(buffer);
		X = readJoystick();
		if (!((0x0001 << 0) & X) || ((0x0001 << 0) & X) || ((0x0001 << 1) & X)) {
			init_radar(buffer);
			break;
		}
	}

	while (((0x0001 << 2) & X) && !((0x0001 << 0) & X) && !((0x0001 << 1) & X)) {	//Left
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
		X = readJoystick();
		if (!((0x0001 << 2) & X) || ((0x0001 << 0) & X) || ((0x0001 << 1) & X)) {
			init_radar(buffer);
			break;
		}
	}

	while (((0x0001 << 1) & X) && !((0x0001 << 3) & X) && !((0x0001 << 2) & X)) {	//Down
		slice = 111;
		line = 2;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[12][j];
		}
		lcd_push_buffer(buffer);
		X = readJoystick();
		if (!((0x0001 << 1) & X) || ((0x0001 << 3) & X) || ((0x0001 << 2) & X)) {
			init_radar(buffer);
			break;
		}
	}

	while (((0x0001 << 0) & X) && ((0x0001 << 3) & X)) {		// Up-right
		slice = 116;
		line = 1;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[6][j];
		}
		if (!((0x0001 << 0) & X) || !((0x0001 << 3) & X)) {
			init_radar(buffer);
			break;
		}
	}

	while (((0x0001 << 0) & X) && ((0x0001 << 2) & X)) {		//Up-left
		slice = 106;
		line = 1;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[4][j];
		}
		if (!((0x0001 << 0) & X) || !((0x0001 << 2) & X)) {
			init_radar(buffer);
			break;
		}
	}

	while (((0x0001 << 1) & X) && ((0x0001 << 3) & X)) {		//Down-right
		slice = 116;
		line = 1;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[13][j];
		}
		if (!((0x0001 << 1) & X) || !((0x0001 << 3) & X)) {
			init_radar(buffer);
			break;
		}
	}

	while (((0x0001 << 1) & X) && ((0x0001 << 2) & X)) {		//Down-left
		slice = 106;
		line = 1;
		for (uint8_t j=0; j<5; j++) {
			buffer[(line-1)*128+slice+j] = game_char_data[11][j];
		}
		if (!((0x0001 << 1) & X) || !((0x0001 << 2) & X)) {
			init_radar(buffer);
			break;
		}
	}
}

