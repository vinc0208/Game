/*
 * Score.c
 *
 *  Created on: 17. jan. 2025
 *      Author: Jens
 */


#include "Score.h"
#include <stdlib.h>
#include <unistd.h>

void ScoreTracker(int32_t points){
	int32_t static score = 0;
		score += points;
}

void HighscoreTracker(){
	FILE *Highscore = fopen("Highscore.txt","w+");

	// test for files not existing.
	if (Highscore == NULL){
		printf("Error! Could not open file\n");
		exit(-1); // must include stdlib.h
	}
}
