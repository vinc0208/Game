#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course

int main(void)
{
	uart_init(9600);
	while(1){
		printf("Bøh");
	}
}
