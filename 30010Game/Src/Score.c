/*
 * Score.c
 *
 *  Created on: 17. jan. 2025
 *      Author: Jens
 */


#include "Score.h"
#include <stdlib.h>
#include "30010_io.h"
#include "stm32f30x_conf.h"
#include "string.h"

uint16_t ScoreTracker(uint16_t points){
	uint16_t static score = 0;
	score += points;
	return score;
}

void PrepareFlashIfNeeded(){
	uint32_t address = 0x0800F800;
	int Unprepared = 1;

	for (uint16_t i = 0; i < 10; i++){
		char firstChar = *(char*) address;
		if (firstChar != 0xFF){
			Unprepared = 0;
		}
		else{
			Unprepared = 1;
			break;
		}
		address += sizeof(Highscore);
	}
	if (Unprepared == 1) {
		Highscore defaultScores[10];
		for (int i = 0; i < 10; i++) {
			strncpy(defaultScores[i].name, "AAA", 4);
			defaultScores[i].score = 0;
		}

		// We write the default scores to the FLASH memory
		FLASH_Unlock();
		FLASH_ClearFlag( FLASH_FLAG_EOP | FLASH_FLAG_PGERR |FLASH_FLAG_WRPERR );
		FLASH_ErasePage(0x0800F800);

		address = 0x0800F800;
		for (int i = 0; i < 10; i++) {
			// Write the name into the memory
			for (int j = 0; j < 5; j++) {
				if (j < 4){
					FLASH_ProgramHalfWord(address + (i*5+j)*2, defaultScores[i].name[j]);
				}
				else{
					FLASH_ProgramHalfWord(address + (i*5+j)*2, defaultScores[i].score);
				}
			}
		}

		FLASH_Lock();

	}
}

void ReadHighscores(Highscore* data) {
    uint32_t address = 0x0800F800;

    for (int i = 0; i < 10; i++) {
    	for (int j = 0; j < 5; j++) {
    		if (j < 4){
    			data[i].name[j] = *(char*) (address + (i*5+j)*2);
    		}
    		else{
    			data[i].score = *(uint16_t*) (address + (i*5+j)*2);
    		}
    	}
    }
}

void HighscoreUpdater(Highscore* array, Highscore player){
	Highscore larger[11];
	for (int i = 0; i < 10; i++){
		larger[i] = array[i];
	}
	larger[10] = player;
	Highscore tempval;

	for (int i = 0; i < 10; i++){
		if (larger[10-i].score > larger[10-1-i].score){
			tempval = larger[10-i];
			larger[10-i] = larger[10-1-i];
			larger[10-1-i] = tempval;
		}
	}

	for (int i = 0; i < 9; i++){
		array[i] = larger[i];
	}
}


//offset is the location we write to, and data is a byte array
void WriteToFlash(Highscore* data){
	uint32_t address = 0x0800F800;

	FLASH_Unlock();
	FLASH_ClearFlag( FLASH_FLAG_EOP | FLASH_FLAG_PGERR |FLASH_FLAG_WRPERR );
	FLASH_ErasePage(address);

	for (int i = 0; i < 10; i++) {
		// Write the name into the memory
		for (int j = 0; j < 5; j++) {
			if (j < 4){
				FLASH_ProgramHalfWord(address + (i*5+j)*2, data[i].name[j]);
			}
			else{
				FLASH_ProgramHalfWord(address + (i*5+j)*2, data[i].score);
			}
		}
	}

	FLASH_Lock();
}


/*******************************************/
/*                                         */
/*         FOR DEBUGGING PURPOSES          */
/*                                         */
/*******************************************/

//Function that erases last page of flash memory so i can test if "PrepareFlashIfNeeded" works
void EraseMemoryLastPage(){
	FLASH_Unlock();
	FLASH_ClearFlag( FLASH_FLAG_EOP | FLASH_FLAG_PGERR |FLASH_FLAG_WRPERR );
	FLASH_ErasePage(0x0800F800);
	FLASH_Lock();
}

//Function that read values from 0x0800F800 and forward (0x0800F800 is the beginning of the last page)
uint16_t ReadFlashLastPage(uint16_t offset) {

	// Calculate the address in flash memory
    uint32_t address = 0x0800F800 + (offset * 2); // Offset is multiplied by 2 for 16-bit alignment

    // Read the value at the calculated address
    uint16_t value = *(uint16_t *)address;

    return value;
}

