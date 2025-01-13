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

