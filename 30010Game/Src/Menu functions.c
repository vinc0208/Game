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
	int static lvl = 0;

	if(first == 1){
		currmenu = menu;
		switch (menu) {
		  case 0:
		    mainMenu();
		    break;
		  case 1:
		    helpMenu();
		    break;
		  case 2:
		    diffMenu();
		    break;
		  case 3:
		    //deathMenu();
		    break;
		  case 4:
		    //pauseMenu();
		    break;
		}
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
	    if((currmenu == 2) && (lvl < 2)){
	    	//increment level
	    	lvl++;
	    	printMode(lvl);
	    }
	    break;
	  case 115: //S
	    if((currmenu == 2) && (lvl > 0)){
	    	//decrement level
	    	lvl--;
	    	printMode(lvl);
	    }
	    break;
	  case 13:
		currmenu = menuConfirm(currmenu, sel);
    	gotoxy(selXY[sel].x, selXY[sel].y);
    	printf(" ");
    	sel = 0;
		break;
	}
	*level = lvl;

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
		    helpMenu();
			  return 1;
		    break;
		  case 2:
		    diffMenu();
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

	return 0;
}

void mainMenu(){

	clrscr();
	fgcolor(15);
	reverse(0);
	srand(5);
		//draw stars
		for(uint8_t i = 0; i<100; i++){
			uint8_t x = rand() % 189;
			uint8_t y = rand() % 50;
			gotoxy(x,y);
			printf("%c",250);
		}

		//Start time for spaceship animation
		StopTime();
		ResetTime();
		StartTime();

		//Create spaceship animation
		int y = 23;
		spaceship shp1;
		shp1.x = 2;
		shp1.y = y;
		shp1.dir = 3;

		spaceship shp2;
		shp2.x = 185;
		shp2.y = y;
		shp2.dir = 7;

		while(1){
			if(TimeMaster15.hsecond % 4 == 0){
				gotoxy(shp1.x-1,y-1);
				printf("      ");
				gotoxy(shp1.x-1,y);
				printf("      ");
				gotoxy(shp1.x-1,y+1);
				printf("      ");
				shp1.x += 1;
				drawSpaceship(&shp1);

				gotoxy(shp2.x-1,y-1);
				printf("      ");
				gotoxy(shp2.x-1,y);
				printf("      ");
				gotoxy(shp2.x-1,y+1);
				printf("      ");
				shp2.x -= 1;
				drawSpaceship(&shp2);

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

		//Controls at bottom of screen
		gotoxy(140,50);
		printf("A for left, D for right, ENTER for select");
}

void helpMenu(){
	clrscr();

	srand(5);
	//draw stars
	for(uint8_t i = 0; i<100; i++){
		uint8_t x = rand() % 189;
		uint8_t y = rand() % 50;
		gotoxy(x,y);
		printf("%c",250);
	}

	//Help print
	gotoxy(80,9);
	printf(" _   _      _ ");
	gotoxy(80,10);
	printf("| | | | ___| |_ __");
	gotoxy(80,11);
	printf("| |_| |/ _ %c | '_ %c ",92,92);
	gotoxy(80,12);
	printf("|  _  |  __/ | |_%c |",41);
	gotoxy(80,13);
	printf("|_| |_|%c___|_| .__/ ",92);
	gotoxy(80,14);
	printf("             |_|");

	//Help text
	gotoxy(50,20);
	printf("Welcome to Space Game! This is a short guide as to how the game is played");
	gotoxy(50,22);
	printf("You are an invasive alien species, and your recent invasion of earth just failed..");
	gotoxy(50,24);
	printf("Millions of your kin are dead, and now the earthlings are launching a counter attack.");
	gotoxy(50,26);
	printf("Filled with sorrow and anger, you must fight back and survive against these monsters!");
	gotoxy(50,30);
	printf("Just use your spaceship controls: A & D to rotate and W & D to go forwards/backwards.");
	gotoxy(50,32);
	printf("Press SPACE to shoot, and don't hesitate!");
	gotoxy(50,34);
	printf("New supply packages and upgrades will be sent to you over time. Good luck");



	//Controls at bottom of screen
	gotoxy(140,50);
	printf("Press ENTER to return to Main Menu");

}

void diffMenu(){
	clrscr();

	//draw stars
	for(uint8_t i = 0; i<100; i++){
		uint8_t x = rand() % 189;
		uint8_t y = rand() % 50;
		gotoxy(x,y);
		printf("%c",250);
	}

	//Mode text
	gotoxy(80,9);
	printf(" __  __           _ ");
	gotoxy(80,10);
	printf("|  %c/  | ___   __| | __",92);
	gotoxy(80,11);
	printf("| |%c/| |/ _ %c / _` |/ _ %c",92,92,92);
	gotoxy(80,12);
	printf("| |  | | %c_%c | %c_| |  __/",40,41,40);
	gotoxy(80,13);
	printf("|_|  |_|%c___/ %c__,_|%c___|",92,92,92);

	//Instructions
	gotoxy(50,20);
	printf("Here you can select the difficulty mode of the game!");
	gotoxy(50,22);
	printf("Just press W for mode increase and S for mode decrease");

	//Controls at bottom of screen
	gotoxy(140,50);
	printf("Press ENTER to return to Main Menu");

}

void printMode(int lvl){
	switch (lvl) {
	  case 0:
		  //Erase old mode
		  gotoxy(75,30);
		  printf("                                     ");
		  gotoxy(75,31);
		  printf("                                     ");
		  gotoxy(75,32);
		  printf("                                     ");
		  gotoxy(75,33);
		  printf("                                     ");
		  gotoxy(75,34);
		  printf("                                     ");
		  gotoxy(75,35);
		  printf("                                     ");

		  //Print mode Easy
		  gotoxy(75,30);
	      printf("      _____  ");
	      gotoxy(75,31);
	      printf("     | ____|__ _ ___ _   _ ");
	      gotoxy(75,32);
	      printf("     |  _| / _` / __| | | |");
	      gotoxy(75,33);
	      printf("     | |__| %c_| %c__ %c |_| |",40,92,92);
	      gotoxy(75,34);
	      printf("     |_____%c__,_|___/%c__, |",92,92);
	      gotoxy(75,35);
	      printf("                     |___/   ");
	    break;
	  case 1:
		  //Erase old mode
		  gotoxy(75,30);
		  printf("                                     ");
		  gotoxy(75,31);
		  printf("                                     ");
		  gotoxy(75,32);
		  printf("                                     ");
		  gotoxy(75,33);
		  printf("                                     ");
		  gotoxy(75,34);
		  printf("                                     ");
		  gotoxy(75,35);
		  printf("                                     ");

		  //Print mode Normal
		  gotoxy(75,30);
	      printf(" _   _                            _");
	      gotoxy(75,31);
	      printf("| %c | | ___  _ __ _ __ ___   __ _| |",92);
	      gotoxy(75,32);
	      printf("|  %c| |/ _ %c| '__| '_ ` _ %c / _` | |",92,92,92);
	      gotoxy(75,33);
	      printf("| |%c  | %c_%c | |  | | | | | | %c_| | |",92,40,41,40);
	      gotoxy(75,34);
	      printf("|_| %c_|%c___/|_|  |_| |_| |_|%c__,_|_|",92,92,92);
	    break;
	  case 2:
		  //Erase old mode
		  gotoxy(75,30);
		  printf("                                     ");
		  gotoxy(75,31);
		  printf("                                     ");
		  gotoxy(75,32);
		  printf("                                     ");
		  gotoxy(75,33);
		  printf("                                     ");
		  gotoxy(75,34);
		  printf("                                     ");
		  gotoxy(75,35);
		  printf("                                     ");

		  //Print mode Hard
		  gotoxy(75,30);
	      printf("     _   _               _");
	      gotoxy(75,31);
	      printf("    | | | | __ _ _ __ __| |");
	      gotoxy(75,32);
	      printf("    | |_| |/ _` | '__/ _` |");
	      gotoxy(75,33);
	      printf("    |  _  | %c_| | | | %c_| |",40,40);
	      gotoxy(75,34);
	      printf("    |_| |_|%c__,_|_|  %c__,_|",92,92);
	    break;
	}

}
