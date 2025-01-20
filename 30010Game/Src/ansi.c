#define ESC 0x1B
#include "stdint.h"
#include "stdio.h"
#include "string.h"


void underline(uint8_t on) {

	if(on == 1) {
		printf("%c[%dm", ESC, 04);
	}
	else {
		printf("%c[%dm", ESC, 24);
	}

}

void reverse(uint8_t on) {

	if(on == 1) {
		printf("%c[%dm", ESC, 07);
	}
	else {
		printf("%c[%dm", ESC, 27);
	}

}

void bold(uint8_t on) {

	if(on == 1) {
		printf("%c[%dm", ESC, 01);
	}
	else {
		printf("%c[%dm", ESC, 22);
	}

}

void clrreol() {
	printf("%c[K", ESC);
}

void clrscr() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[2J", ESC);
}

void gotoxy(uint8_t y, uint8_t x) {
// gray on black text, no underline, no blink, no reverse
  printf("%c[%d;%dH",ESC,x,y);
}



void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}


