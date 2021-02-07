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

extern const uint64_t mask0Encoded;
extern const uint64_t mask1Encoded;		
extern const uint64_t mask2Encoded;
extern const uint64_t mask3Encoded;
extern const uint64_t maskAllEncoded;													
extern const uint64_t maskChessBoardWEncoded;
extern const uint64_t maskChessBoardBEncoded;										
extern const uint64_t maskLetterJEncoded;
extern const uint64_t maskLetterOEncoded;
extern const uint64_t maskLetterEEncoded;	
extern const uint64_t maskLetterLEncoded;
extern const uint64_t maskEmptyEncoded;
extern const uint64_t maskEncLetterA;	
extern const uint64_t maskEncLetterB;										
extern const uint64_t maskEncLetterC;
extern const uint64_t maskEncLetterD;
extern const uint64_t maskEncLetterE;
extern const uint64_t maskEncLetterF;		
extern const uint64_t maskEncLetterG;
extern const uint64_t maskEncLetterH;
extern const uint64_t maskEncLetterI;
extern const uint64_t maskEncLetterJ;
extern const uint64_t maskEncLetterK;
extern const uint64_t maskEncLetterL;
extern const uint64_t maskEncLetterM;
extern const uint64_t maskEncLetterN;
extern const uint64_t maskEncLetterO;
extern const uint64_t maskEncLetterP;
extern const uint64_t maskEncLetterQ;
extern const uint64_t maskEncLetterR;
extern const uint64_t maskEncLetterS;
extern const uint64_t maskEncLetterT;														
extern const uint64_t maskEncLetterU;
extern const uint64_t maskEncLetterV;
extern const uint64_t maskEncLetterW;
extern const uint64_t maskEncLetterX;
extern const uint64_t maskEncLetterY;
extern const uint64_t maskEncLetterZ;

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
extern bool maskEmpty[64];


void bool_mask_clear_all(bool* boolMaskPtr);
void bool_mask_copy(bool* originalBoolMaskPtr,bool* copyBoolMaskPtr);
void maskPtrSet (bool *maskPtr, int startVal, int stepVal, int stopVal, uint16_t brightness);
void bool_mask_decode(bool* destBoolMaskPtr, uint64_t encodedBoolMask);
void arraySetRow(bool *maskPtr, int rowNum, uint16_t brightness);
void arraySetCol(bool *maskPtr, int colNum, uint16_t brightness);
void arraySetRing(bool *maskPtr, int ringNum, uint16_t brightness);
void arraySetRandom(bool *maskPtr, int nSet, uint16_t brightness);

#endif
