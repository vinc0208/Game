// =====================================================================
//
//	Exported by Cearn's excellut v1.0
//	(comments, kudos, flames to daytshen@hotmail.com)
//
// =====================================================================

#ifndef SINUSOID_H
#define SINUSOID_H
#include <stdint.h> // whatever
#include <stdio.h>
int32_t expand(int32_t i);
void printFix(int32_t i);
// === LUT SIZES ===
#define SIN_SIZE 512

// === LUT DECLARATIONS ===
extern const signed short SIN[512];


#endif	// SINUSOID_H
