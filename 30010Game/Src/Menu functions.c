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
#include "Graphics functions.h"


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
		selXY[0].x = 32;
		selXY[0].y = 34;
		selXY[1].x = 89;
		selXY[1].y = 34;
		selXY[2].x = 153;
		selXY[2].y = 34;
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
		mainMenu();
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
			mainMenu();
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
			mainMenu();
			  return 0;
		    break;
		}
	}else{
		return 0;
	}
}

void mainMenu(){
	clrscr();
	fgcolor(15);
	reverse(0);

		//draw stars
		for(uint8_t i = 0; i<75; i++){
			uint8_t x = rand() % 189;
			uint8_t y = rand() % 50;
			gotoxy(x,y);
			printf("%c",250);
		}

		//Start time for spaceship animation
		StopTime();
		StartTime();

		//Create spaceship animation
		int x1 = 2;
		int x2 = 185;
		int y = 23;
		while(1){
			if(TimeMaster15.hsecond % 4 == 0){
				gotoxy(x1-1,y-1);
				printf("      ");
				gotoxy(x1-1,y);
				printf("      ");
				gotoxy(x1-1,y+1);
				printf("      ");
				x1++;
				drawSpaceship(x1,y,1,4);

				gotoxy(x2-1,y-1);
				printf("      ");
				gotoxy(x2-1,y);
				printf("      ");
				gotoxy(x2-1,y+1);
				printf("      ");
				x2--;
				drawSpaceship(x2,y,2,3);

			}

			if(TimeMaster15.second == 2){
				StopTime();
				break;
			}
		}


		//Title print
		gotoxy(40,10);
		printf("     _______  ______      ___       ______  _______      _______      ___       ___  ___   _______ ");
		gotoxy(40,11);
		printf("    /       ||   _  %c    /   %c     /      ||   ____|    /  _____|    /   %c     |   %c/   | |   ____|",92,92,92,92);
		gotoxy(40,12);
		printf("   |   (----`|  |_)  |  /  ^  %c   |  ,----'|  |__      |  |  __     /  ^  %c    |  %c  /  | |  |__   ",92,92,92);
		gotoxy(40,13);
		printf("    %c   %c    |   ___/  /  /_%c  %c  |  |     |   __|     |  | |_ |   /  /_%c  %c   |  |%c/|  | |   __| ",92,92,92,92,92,92,92);
		gotoxy(40,14);
		printf(".----)   |   |  |     /  _____  %c |  `----.|  |____    |  |__| |  /  _____  %c  |  |  |  | |  |___",92,92);
		gotoxy(40,15);
		printf("|_______/    | _|    /__/     %c__%c %c______||_______|    %c______| /__/     %c__%c |__|  |__| |_______|",92,92,92,92,92,92);

		//Start print
		gotoxy(20,28);
		printf(" ____  _             _  ");
		gotoxy(20,29);
		printf("/ ___|| |_ __ _ _ __| |_");
		gotoxy(20,30);
		printf("%c___ %c| __/ _` | '__| __|",92,92);
		gotoxy(20,31);
		printf(" ___) | || %c_| | |  | |_ ",40);
		gotoxy(20,32);
		printf("|____/ %c__%c__,_|_|   %c__|",92,92,92);

		//Help print
		gotoxy(80,28);
		printf(" _   _      _ ");
		gotoxy(80,29);
		printf("| | | | ___| |_ __");
		gotoxy(80,30);
		printf("| |_| |/ _ %c | '_ %c ",92,92);
		gotoxy(80,31);
		printf("|  _  |  __/ | |_%c |",41);
		gotoxy(80,32);
		printf("|_| |_|%c___|_| .__/ ",92);
		gotoxy(80,33);
		printf("             |_|");

		//Mode print
		gotoxy(140,28);
		printf(" __  __           _ ");
		gotoxy(140,29);
		printf("|  %c/  | ___   __| | __",92);
		gotoxy(140,30);
		printf("| |%c/| |/ _ %c / _` |/ _ %c",92,92,92);
		gotoxy(140,31);
		printf("| |  | | %c_%c | %c_| |  __/",40,41,40);
		gotoxy(140,32);
		printf("|_|  |_|%c___/ %c__,_|%c___|",92,92,92);

}
