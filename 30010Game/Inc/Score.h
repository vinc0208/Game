/*
 * Score.h
 *
 *  Created on: 17. jan. 2025
 *      Author: Jens
 */

#ifndef SCORE_H_
#define SCORE_H_

#include <stdio.h>
#include <stdint.h>

typedef struct {
    char name[4];   // Fixed-length name (3 characters + '\0')
    uint16_t score;  // Score
} Highscore;

uint16_t ScoreTracker(uint16_t points, uint16_t* currentscore);
void ResetScore(uint16_t* currentscore);
uint16_t ReadFlashLastPage(uint16_t offset);
void PrepareFlashIfNeeded();
void ReadHighscores(Highscore* data);
void HighscoreUpdater(Highscore* array, Highscore player);
void WriteToFlash(Highscore* data);
void EraseMemoryLastPage();

#endif /* SCORE_H_ */
