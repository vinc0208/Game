/*
 * Menu functions.c
 *
 *  Created on: 15 Jan 2025
 *      Author: vince
 */

#include <ansi.h>
#define ESC 0x1B
#include <stdint.h> // whatever
#include <stdio.h>
#include <stdlib.h>
#include "Movement and math functions.h"
#include "Menu functions.h"
#include "Hardware interface functions.h"


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
