/*
 * Menu functions.c
 *
 *  Created on: 15 Jan 2025
 *      Author: vince
 */

#include "ansi.h"
#define ESC 0x1B
#include <stdint.h> // whatever
#include <stdio.h>
#include <stdlib.h>
#include "30010_io.h"
#include "Movement and math functions.h"
#include "Menu functions.h"
#include "Hardware interface functions.h"
#include "Graphics functions.h"

//Menu master function, intended to be run in a loop (therefore the use of static variables)
//int's should also be int8_t, but I forgot.
void menuSelect(int8_t menu, int8_t* level, int8_t* gamestart, int8_t* first){
	//For menu input: 0 = main menu, 1 = help, 2 = difficulty, 3 = death, 4 = pause, 5 = boss
	uint8_t static sel = 0;
	uint8_t static options;
	point static selXY[5];
	char static c = 0;
	int static currmenu;
	int static lvl = 1;

	//Initialize the starting menu (draw menu)
	if(*first == 1){
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
		    deathMenu();
		    break;
		  case 4:
		    pauseMenu();
		    break;
		  case 5:
			bossMenu();
		}
		*first = 0;
	}


	//Set the marker coordinates and number of options according to the current menu
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
		selXY[1].x = 114+18;
		selXY[1].y = 33;
		selXY[0].x = 39+25;
		selXY[0].y = 33;
		options = 2;
		break;
	  case 4:
		selXY[1].x = 114+18;
		selXY[1].y = 33;
		selXY[0].x = 39+25;
		selXY[0].y = 33;
		options = 2;
		break;
	}


	//Choose what to do based on user keyboard input
	c = uartKeyRead();

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
	    if((currmenu == 2) && (lvl < 3)){
	    	//increment level
	    	lvl++;
	    	printMode(lvl);
	    }
	    break;
	  case 115: //S
	    if((currmenu == 2) && (lvl > 1)){
	    	//decrement level
	    	lvl--;
	    	printMode(lvl);
	    }
	    break;
	  case 13:
		currmenu = menuConfirm(currmenu, sel, gamestart);
    	gotoxy(selXY[sel].x, selXY[sel].y);
    	sel = 0;
		break;
	  case 27:
		currmenu = menuConfirm(currmenu, sel, gamestart);
		break;
	  case 98:
		currmenu = menuConfirm(currmenu, sel, gamestart);
		break;
	}
	*level = lvl;

}

//menuConfirm is just an extension to the menuSelect function to make it more manageble
//Is only called when enter is hit in menuSelect (hence (menu)Confirm)
//This function returns the value of the menu that is being initiated, so that currmenu in menuSelect is being updated,
//and the menuSelect function can keep track of what menu we are in
int menuConfirm(int8_t menu, uint8_t sel, int8_t* gamestart){
	//If statement for each menu containing switch statement switching between actions based on what
	//options are currently selected
	if(menu == 0){
		switch (sel) {
		  case 0:
		    *gamestart = 1;
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
		  case 1:
			  *gamestart = 1;
			  return 0;
		    break;
		  case 0:
		    //mainMenu()
			mainMenu();
			  return 0;
		    break;
		}
	}else if(menu == 4){
		switch (sel) {
		  case 1:
			  clrscr();
			  StartTime();
			  *gamestart = 1;
			  return 0;
			  break;
		  case 0:
			  //mainMenu()
			  mainMenu();
			  return 0;
			  break;
		}
	}else if(menu == 5){
		clrscr();
		StartTime();
		*gamestart = 1;
		return 0;

	}else{
		return 0;
	}

	return 0;
}

//Draw mainMenu function
void mainMenu(){

	clrscr();
	fgcolor(15);
	reverse(0);
		//draw stars
		for(uint8_t i = 0; i<100; i++){
			uint8_t x = rand() % 189;
			uint8_t y = rand() % 50;
			gotoxy(x,y);
			printf("%c",250);
		}


		//Create spaceships for animation
		int y = 23;
		spaceship shp1;
		shp1.x = 13;
		shp1.y = y;
		shp1.dir = 3;
		shp1.style = 0;

		spaceship shp2;
		shp2.x = 173;
		shp2.y = y;
		shp2.dir = 7;
		shp2.style = 1;

		//Draw the space stations
		fgcolor(15);
		gotoxy(4,21);
		printf("%c%c%c%c%c%c%c%c[%dD%c[%dB%c%c%c%c%c%c%c%c%c%c[%dD%c[%dB",220,219,219,219,219,219,220,ESC,8,ESC,1,   219,219,219,219,219,219,219,219,223,ESC,9,ESC,1);
		printf("%c%c%c%c%c%c%c%c%c[%dD%c[%dB%c%c%c%c%c%c%c%c%c%c[%dD%c[%dB %c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,ESC,8,ESC,1,   219,219,219,219,219,219,219,219,220,ESC,9,ESC,1,223,219,219,219,219,219,223);
		gotoxy(175,21);
		printf("%c%c%c%c%c%c%c%c[%dD%c[%dB%c%c%c%c%c%c%c%c%c%c[%dD%c[%dB",220,219,219,219,219,219,220,ESC,8,ESC,1,   223,219,219,219,219,219,219,219,219,ESC,8,ESC,1);
		printf("%c%c%c%c%c%c%c%c%c[%dD%c[%dB%c%c%c%c%c%c%c%c%c%c[%dD%c[%dB %c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,ESC,9,ESC,1,   220,219,219,219,219,219,219,219,219,ESC,9,ESC,1,223,219,219,219,219,219,223);

		//Animation of the two spaceships
		for(int i = 0; i < 2000000; i++){
			if(i % 50000 == 0){
				//Update ship 1
				gotoxy(shp1.x-1,y-1);
				printf("   ");
				gotoxy(shp1.x-2,y);
				printf("    ");
				gotoxy(shp1.x-1,y+1);
				printf("   ");
				shp1.x += 1;
				drawSpaceship(&shp1);
				if(i < 1000000){
					fgcolor(15);
					gotoxy(shp1.x-2, shp1.y);
					printf("%c", 219);
				}

				//Update ship 2
				gotoxy(shp2.x-1,y-1);
				printf("  ");
				gotoxy(shp2.x-1,y);
				printf("   ");
				gotoxy(shp2.x-1,y+1);
				printf("  ");
				shp2.x -= 1;
				drawSpaceship(&shp2);
				if(i < 1000000){
					fgcolor(15);
					gotoxy(shp2.x+1, shp2.y);
					printf("%c", 219);
				}
			}
		}

		fgcolor(15);
		//Title print
		gotoxy(43,10);
		printf("     _______  ______      ___       ______  _______      _______      ___       ___  ___   _______ ");
		gotoxy(43,11);
		printf("    /       ||   _  %c    /   %c     /      ||   ____|    /  _____|    /   %c     |   %c/   | |   ____|",92,92,92,92);
		gotoxy(43,12);
		printf("   |   (----`|  |_)  |  /  ^  %c   |  ,----'|  |__      |  |  __     /  ^  %c    |  %c  /  | |  |__   ",92,92,92);
		gotoxy(43,13);
		printf("    %c   %c    |   ___/  /  /_%c  %c  |  |     |   __|     |  | |_ |   /  /_%c  %c   |  |%c/|  | |   __| ",92,92,92,92,92,92,92);
		gotoxy(43,14);
		printf(".----)   |   |  |     /  _____  %c |  `----.|  |____    |  |__| |  /  _____  %c  |  |  |  | |  |___",92,92);
		gotoxy(43,15);
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

//Draw the help menu
void helpMenu(){
	clrscr();

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
	printf("Just use your spaceship controls: A & D to rotate and W to go forwards.");
	gotoxy(50,32);
	printf("You've been supplied with a state of the art enemy detection radar and a laser rifle.");
	gotoxy(50,34);
	printf("Press SPACE to fire away, but watch your ammo! it's prone to overheating.");
	gotoxy(50,36);
	printf("New supply packages and upgrades can be looted from your enemies. Good luck!");
	gotoxy(87,43);
	printf("Powerups:");
	gotoxy(63,46);
	printf("Dmg boost:          Speed boost:        Score multiplier:");
	gotoxy(74,46);
	fgcolor(1);
	printf("%c%c",219,219);
	gotoxy(96,46);
	fgcolor(3);
	printf("%c%c",219,219);
	gotoxy(121,46);
	fgcolor(5);
	printf("%c%c",219,219);
	gotoxy(63,48);
	fgcolor(15);
	printf("Weapon type 1:      Weapon type 2:      Weapon type 3:");
	gotoxy(78,48);
	fgcolor(6);
	printf("%c%c",219,219);
	gotoxy(98,48);
	fgcolor(12);
	printf("%c%c",219,219);
	gotoxy(118,48);
	fgcolor(4);
	printf("%c%c",219,219);
	fgcolor(15);



	//Controls at bottom of screen
	gotoxy(140,50);
	printf("Press ENTER to return to Main Menu");

}

//Draw the mode or difficulty menu
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
	gotoxy(67,20);
	printf("Here you can select the difficulty mode of the game!");
	gotoxy(67,22);
	printf("Just press W for mode increase and S for mode decrease");

	//Window print
	window(61,29,125,36,1);

	//Changing parameters
	gotoxy(70, 39);
	printf("Player HP:");
	gotoxy(70, 41);
	printf("# bullets:");
	gotoxy(100, 39);
	printf("Enemy  HP:");
	gotoxy(100, 41);
	printf("# enemies:");

	//Controls at bottom of screen
	gotoxy(140,50);
	printf("Press ENTER to confirm and return to Main Menu");

}

//printMode is an extension of the diffMenu, and prints the mode according to what the level/difficulty variable is set to
void printMode(int lvl){
	switch (lvl) {
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

		  //Print mode Easy
		  gotoxy(77,30);
	      printf("      _____  ");
	      gotoxy(77,31);
	      printf("     | ____|__ _ ___ _   _ ");
	      gotoxy(77,32);
	      printf("     |  _| / _` / __| | | |");
	      gotoxy(77,33);
	      printf("     | |__| %c_| %c__ %c |_| |",40,92,92);
	      gotoxy(77,34);
	      printf("     |_____%c__,_|___/%c__, |",92,92);
	      gotoxy(77,35);
	      printf("                     |___/   ");

	      //Changing parameters
		  gotoxy(81, 39);
		  printf("5");
		  gotoxy(81, 41);
		  printf("5");
		  gotoxy(111, 39);
		  printf("3");
		  gotoxy(111, 41);
		  printf("5");
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

	      //Changing parameters
		  gotoxy(81, 39);
		  printf("4");
		  gotoxy(81, 41);
		  printf("3");
		  gotoxy(111, 39);
		  printf("4");
		  gotoxy(111, 41);
		  printf("6");
	    break;
	  case 3:
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
		  gotoxy(78,30);
	      printf("     _   _               _");
	      gotoxy(78,31);
	      printf("    | | | | __ _ _ __ __| |");
	      gotoxy(78,32);
	      printf("    | |_| |/ _` | '__/ _` |");
	      gotoxy(78,33);
	      printf("    |  _  | %c_| | | | %c_| |",40,40);
	      gotoxy(78,34);
	      printf("    |_| |_|%c__,_|_|  %c__,_|",92,92);

	      //Changing parameters
		  gotoxy(81, 39);
		  printf("3");
		  gotoxy(81, 41);
		  printf("1");
		  gotoxy(111, 39);
		  printf("5");
		  gotoxy(111, 41);
		  printf("7");
	    break;
	}

}

//Death menu for when the player dies
void deathMenu() {

	clrscr();
	fgcolor(15);
	reverse(0);
	srand(5);
	//draw stars
	for(uint8_t i = 0; i<75; i++){
		uint8_t x = rand() % 189;
		uint8_t y = rand() % 50;
		gotoxy(x,y);
		printf("%c",250);
	}

	//Death print
	gotoxy(50,10);
	printf("  _______      ___       ___  ___   _______        ______   ____      ____  _______   ______   ");
	gotoxy(50,11);
	printf(" /  _____|    /   %c     |   %c/   | |   ____|      /  __  %c  %c   %c    /   / |   ____| |   _  %c  ",92,92,92,92,92,92);
	gotoxy(50,12);
	printf("|  |  __     /  ^  %c    |  %c  /  | |  |__        |  |  |  |  %c   %c  /   /  |  |__    |  |_)  | ",92,92,92,92);
	gotoxy(50,13);
	printf("|  | |_ |   /  /_%c  %c   |  |%c/|  | |   __|       |  |  |  |   %c   %c/   /   |   __|   |      /  ",92,92,92,92,92);
	gotoxy(50,14);
	printf("|  |__| |  /  _____  %c  |  |  |  | |  |____      |  `--'  |    %c      /    |  |___   |  |%c  %c_ ",92,92,92,92);
	gotoxy(50,15);
	printf(" %c______| /__/     %c__%c |__|  |__| |_______|      %c______/      %c____/     |_______| |__| %c___|",92,92,92,92,92,92);

	//Main Menu print
	gotoxy(39,28);
	printf(" __  __       _         __  __");
	gotoxy(39,29);
	printf("|  %c/  | __ _(_)_ __   |  %c/  | ___ _ __  _   _ ",92,92);
	gotoxy(39,30);
	printf("| |%c/| |/ _` | | '_ %c  | |%c/| |/ _ %c '_ %c| | | |",92,92,92,92,92);
	gotoxy(39,31);
	printf("| |  | | (_| | | | | | | |  | |  __/ | | | |_| |");
	gotoxy(39,32);
	printf("|_|  |_|%c__,_|_|_| |_| |_|  |_|%c___|_| |_|%c__,_|",92,92,92);

	//Restart print
	gotoxy(114,28);
	printf(" ____           _             _   ");
	gotoxy(114,29);
	printf("|  _ %c ___  ___| |_ __ _ _ __| |_ ",92);
	gotoxy(114,30);
	printf("| |_) / _ %c/ __| __/ _` | '__| __|",92);
	gotoxy(114,31);
	printf("|  _ <  __/%c__ %c || (_| | |  | |_ ",92,92);
	gotoxy(114,32);
	printf("|_| %c_%c___||___/%c__%c__,_|_|   %c__|",92,92,92,92,92);

	//Highscore print
	window(2, 28, 23, 38, 1);
	gotoxy(3,28);
	printf(" Highscore ");

	uint32_t address = 0x0800F800;
	for (int i = 0; i < 9; i++) {
		gotoxy(3,29+i);
		printf("%d  ", (i+1));

		for (int j = 0; j < 5; j++) {
			if (j < 4){
				printf("%c", *(char*) (address + (i*5+j)*2));
			}
			else{
				printf("  %d", *(uint16_t*) (address + (i*5+j)*2));
			}
		}
	}

	//Controls at bottom of screen
	gotoxy(140,50);
	printf("A for left, D for right, ENTER for select");

}

//Pause menu - drawing the pause menu
void pauseMenu() {

	clrscr();
	fgcolor(15);
	reverse(0);
	srand(5);
	//draw stars
	for(uint8_t i = 0; i<75; i++){
		uint8_t x = rand() % 189;
		uint8_t y = rand() % 50;
		gotoxy(x,y);
		printf("%c",250);
	}

	//Pause print
	gotoxy(60,10);
	printf(".______      ___      __    __       _______. _______  _______");
	gotoxy(60,11);
	printf("|   _  %c    /   %c    |  |  |  |     /       ||   ____||       %c",92,92,92);
	gotoxy(60,12);
	printf("|  |_%c  |  /  ^  %c   |  |  |  |    |   %c----`|  |__   |  .--.  |",41,92,40);
	gotoxy(60,13);
	printf("|   ___/  /  /_%c  %c  |  |  |  |     %c   %c    |   __|  |  |  |  |",92,92,92,92);
	gotoxy(60,14);
	printf("|  |     /  _____  %c |  `--'  | .----%c   |   |  |____ |  '--'  |",92,41);
	gotoxy(60,15);
	printf("| _|    /__/     %c__%c %c______/  |_______/    |_______||_______/",92,92,92);

	//Main Menu print
	gotoxy(39,28);
	printf(" __  __       _         __  __");
	gotoxy(39,29);
	printf("|  %c/  | __ _(_)_ __   |  %c/  | ___ _ __  _   _ ",92,92);
	gotoxy(39,30);
	printf("| |%c/| |/ _` | | '_ %c  | |%c/| |/ _ %c '_ %c| | | |",92,92,92,92,92);
	gotoxy(39,31);
	printf("| |  | | (_| | | | | | | |  | |  __/ | | | |_| |");
	gotoxy(39,32);
	printf("|_|  |_|%c__,_|_|_| |_| |_|  |_|%c___|_| |_|%c__,_|",92,92,92);

	//Resume print
	gotoxy(114,28);
	printf(" ____ ");
	gotoxy(114,29);
	printf("|  _ %c ___  ___ _   _ _ __ ___   ___",92);
	gotoxy(114,30);
	printf("| |_%c / _ %c/ __| | | | '_ ` _ %c / _ %c",41,92,92,92);
	gotoxy(114,31);
	printf("|  _ <  __/%c__ %c |_| | | | | | |  __/",92,92);
	gotoxy(114,32);
	printf("|_| %c_%c___||___/%c__,_|_| |_| |_|%c___|",92,92,92,92);

	//Controls at bottom of screen
	gotoxy(140,50);
	printf("A for left, D for right, ENTER for select");

}

//Draw the boss menu
void bossMenu() {
	clrscr();
	fgcolor(15);
	window(85, 22, 105, 30, 1);
	gotoxy(89, 24);
	printf("Working hard,");
	gotoxy(94, 26);
	printf("or");
	gotoxy(89, 28);
	printf("hardly working");
	gotoxy(84, 50);
	printf("B to continue working");
}

//This is the pause/unpause function, which starts/stops and prints the pause menu
//by using the gamestart variable and input key from the gameloop
void pause_unpause(int8_t *gamestart, int8_t *menu, uint8_t *key, int8_t *level, int8_t *first){
	if (*key == 27){

		StopTime();
		*menu = 4;
		*gamestart = 0;
		*key = 0;
		*first = 1;

		while(*gamestart == 0){
			menuSelect(*menu, level, gamestart, first);
		}
		clrscr();
	}
}

//Similar to the pause function, just with the boss menu instead
void boss_screen(int8_t *gamestart, int8_t *menu, uint8_t *key, int8_t *level, int8_t *first){
	if (*key == 98){
		StopTime();
		*menu = 5;
		*gamestart = 0;
		*key = 0;
		*first = 1;

		while(*gamestart == 0){
			menuSelect(*menu, level, gamestart, first);
		}
		clrscr();
	}
}
