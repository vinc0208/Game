#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include <Graphics functions.h>
#include "Hardware interface functions.h"
int main(void)
{

	uart_init(9600);

	Timer15Config(); //Initialize time

	if(0){
		clrscr();
		int x=1,y=1,X=20,Y=10,dire=1;
		short style=1;
		gotoxy(x,y);
		drawSpaceship(X,Y,style,dire);
		drawSpaceship(X+5,Y,style,dire+2);
		drawSpaceship(X,Y+3,style+1,dire+1);
		drawSpaceship(X+5,Y+3,style+1,dire+3);
		drawSpaceship(X+10,Y+3,style-1,dire+5);
		drawSpaceship(X+10,Y,style,dire+4);
		drawSpaceship(X+15,Y+3,style-1,dire+7);
		drawSpaceship(X+15,Y,style-1,dire+6);
		drawEnemy(X,Y-3, dire);
		drawEnemy(X,Y-6, dire+1);
		drawEnemy(X+5,Y-3, dire+2);
		drawEnemy(X+5,Y-6, dire+3);
		drawEnemy(X+10,Y-3, dire+4);
		drawEnemy(X+10,Y-6, dire+5);
		drawEnemy(X+15,Y-3, dire+6);
		drawEnemy(X+15,Y-6, dire+7);
		drawAsteroid(X+20,Y-6,dire);
		drawAsteroid(X+22,Y,dire+1);
		gotoxy(x,y);
	}
	while(1){

	}
}
