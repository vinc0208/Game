#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include <Graphics functions.h>
#include "Hardware interface functions.h"
#include <stdlib.h>
int main(void)
{

	uart_init(9600);

	Timer15Config(); //Initialize time


	while(1){

	}
}
