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
	TimeMaster.msecond += 1;
	if (TimeMaster.msecond >= 10){
		TimeMaster.msecond %= 10;
		TimeMaster.hsecond += 1;
	}
	if (TimeMaster.hsecond >= 100){
		TimeMaster.hsecond %= 100;
		TimeMaster.second += 1;
	}
	if (TimeMaster.second >= 60){
		TimeMaster.second %= 60;
		TimeMaster.minute += 1;
	}
	if (TimeMaster.minute >= 60){
		TimeMaster.minute %= 60;
		TimeMaster.hour += 1;
	}
	TIM15->SR &= ~0x0001; // Clear interrupt bit
 }

void configt15(void){
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

