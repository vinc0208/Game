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

void TIM1_BRK_TIM15_IRQHandler(void) {
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

void Timer15Config(void){
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

void StartTime(){

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

