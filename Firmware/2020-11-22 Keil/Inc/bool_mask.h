/*
 * bool_mask.h
 *
 *  Created on: Dec 6, 2020
 *      Author: Joel Michaelis
 */
 
#ifndef BOOL_MASK_H_
#define BOOL_MASK_H_
 
#include <stdbool.h>
#include "stdint.h"

#define BOOL_MASK_LENGTH 64

// bool mask declarations here allow them to be visible when this library is included
// bool mask definitions are made in bool_mask.c
// I don't understand why I had to make the declarations extern to avoid linker errors with the src definitions
extern bool mask0[64];
extern bool mask1[64];
extern bool mask2[64];
extern bool mask3[64];
extern bool mask4[64];
extern bool mask5[64];
extern bool mask6[64];
extern bool mask7[64];
extern bool maskChessBoardW[64];
extern bool maskChessBoardB[64];
extern bool letterJ[64];
extern bool letterO[64];
extern bool letterE[64];
extern bool letterL[64];


void bool_mask_clear_all(bool* boolMaskPtr);
void bool_mask_copy(bool* originalBoolMaskPtr,bool* copyBoolMaskPtr);
void maskPtrSet (bool *maskPtr, int startVal, int stepVal, int stopVal, uint16_t brightness);
void arraySetRow(bool *maskPtr, int rowNum, uint16_t brightness);
void arraySetCol(bool *maskPtr, int colNum, uint16_t brightness);
void arraySetRing(bool *maskPtr, int ringNum, uint16_t brightness);
void arraySetRandom(bool *maskPtr, int nSet, uint16_t brightness);

#endif
