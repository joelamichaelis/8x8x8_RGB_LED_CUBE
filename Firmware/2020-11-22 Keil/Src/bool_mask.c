/*
 * bool_mask.c
 *
 *  Created on: Dec 6, 2020
 *      Author: Joel Michaelis
 */

#include "bool_mask.h"

// PRIVATE FUNCTION PROTOTYPES BEGIN

// PRIVATE FUNCTION PROTOTYPES END

//-------------------------------------Bool Mask Defines Begin-------------------------------------
//encoding bool masks saves 56bytes per which is non-trivial given the number of bool masks used and the 32K size limit
// apparently the c language doesn't support binary literals and keil's compiler do the conversion
//EX: uint64_t mask0Encoded = 0b1111111110000001100000011000000110000001100000011000000111111111;


const uint64_t mask0Encoded = 0xFF818181818181FF;	
const uint64_t mask1Encoded = 0x007E424242427E00;		
const uint64_t mask2Encoded = 0x00003C24243C0000;	
const uint64_t mask3Encoded = 0x0000001818000000;	
const uint64_t maskAllEncoded = 0xFFFFFFFFFFFFFFFF;															
const uint64_t maskChessBoardWEncoded = 0xAA55AA55AA55AA55;	
const uint64_t maskChessBoardBEncoded = 0x55AA55AA55AA55AA;										
const uint64_t maskLetterJEncoded = 0xFF0404040484CC78;
const uint64_t maskLetterOEncoded = 0x7EFFC3C3C3C3FF7E;
const uint64_t maskLetterEEncoded = 0xFFFFC0FEFEC0FFFF;	
const uint64_t maskLetterLEncoded = 0xC0C0C0C0C0C0FEFE;
const uint64_t maskEmptyEncoded = 0x0000000000000000;	
const uint64_t maskEncLetterA	= 0x7EFFE7E7FFFFE7E7;			
const uint64_t maskEncLetterB	=	0xFEFFE7FEFEE7FFFE;											
const uint64_t maskEncLetterC = 0x7EFFE7E0E0E7FF7E;
const uint64_t maskEncLetterD = 0xFEFFE7E7E7E7FFFE;
const uint64_t maskEncLetterE = 0xFFFFE0FCFCE0FFFF;
const uint64_t maskEncLetterF = 0xFFFFE0FCFCE0E0E0;		
const uint64_t maskEncLetterG = 0x7EFFE7E0EFE7FF7E;
const uint64_t maskEncLetterH = 0xE7E7E7FFFFE7E7E7;
const uint64_t maskEncLetterI = 0xFFFF18181818FFFF;
const uint64_t maskEncLetterJ = 0xFF0404040484CC78;
const uint64_t maskEncLetterK = 0xE3E7EEFCFCEEE7E3;
const uint64_t maskEncLetterL = 0xE0E0E0E0E0E0FFFF;
const uint64_t maskEncLetterM = 0x82C6EEAABA929282;
const uint64_t maskEncLetterN = 0xE7F7F7FFFFFFEFE7;
const uint64_t maskEncLetterO = 0x7EFFE7E7E7E7FF7E;
const uint64_t maskEncLetterP = 0xFEFFE7FFFEE0E0E0;
const uint64_t maskEncLetterQ = 0x7EFFE7E7E3EDF67B;
const uint64_t maskEncLetterR = 0xFEFFE7FFFEE7E7E7;
const uint64_t maskEncLetterS = 0x7EFFE0FE7F07FF7E;
const uint64_t maskEncLetterT = 0xFFFF181818181818;														
const uint64_t maskEncLetterU = 0xE7E7E7E7E7E7FF7E;	
const uint64_t maskEncLetterV = 0xE7E7E7E7E7E77E3C;
const uint64_t maskEncLetterW = 0x82929292BAEEC682;
const uint64_t maskEncLetterX = 0xE7E77E3C3C7EE7E7;
const uint64_t maskEncLetterY = 0xE7E7E77E3C181818;
const uint64_t maskEncLetterZ = 0xFFFF0F1E78F0FFFF;

bool mask0[64] = {1,1,1,1,1,1,1,1,
									1,0,0,0,0,0,0,1,
									1,0,0,0,0,0,0,1,
									1,0,0,0,0,0,0,1,
									1,0,0,0,0,0,0,1,
									1,0,0,0,0,0,0,1,
									1,0,0,0,0,0,0,1,
									1,1,1,1,1,1,1,1};
									
bool mask1[64] = {0,0,0,0,0,0,0,0,
									0,1,1,1,1,1,1,0,
									0,1,0,0,0,0,1,0,
									0,1,0,0,0,0,1,0,
									0,1,0,0,0,0,1,0,
									0,1,0,0,0,0,1,0,
									0,1,1,1,1,1,1,0,
									0,0,0,0,0,0,0,0};			
																		
bool mask2[64] = {0,0,0,0,0,0,0,0,
									0,0,0,0,0,0,0,0,
									0,0,1,1,1,1,0,0,
									0,0,1,0,0,1,0,0,
									0,0,1,0,0,1,0,0,
									0,0,1,1,1,1,0,0,
									0,0,0,0,0,0,0,0,
									0,0,0,0,0,0,0,0};									

bool mask3[64] = {0,0,0,0,0,0,0,0,
									0,0,0,0,0,0,0,0,
									0,0,0,0,0,0,0,0,
									0,0,0,1,1,0,0,0,
									0,0,0,1,1,0,0,0,
									0,0,0,0,0,0,0,0,
									0,0,0,0,0,0,0,0,
									0,0,0,0,0,0,0,0};	
									
/*
commented out since not used and need to save space
bool mask4[64] = {1,1,1,1,1,1,1,1,
									1,0,0,0,0,0,0,1,
									1,0,1,1,1,1,0,1,
									1,0,1,0,0,1,0,1,
									1,0,1,0,0,1,0,1,
									1,0,1,1,1,1,0,1,
									1,0,0,0,0,0,0,1,
									1,1,1,1,1,1,1,1};

bool mask5[64] = {1,1,1,1,1,1,1,1,
									1,1,0,0,0,0,1,1,
									1,0,1,0,0,1,0,1,
									1,0,0,1,1,0,0,1,
									1,0,0,1,1,0,0,1,
									1,0,1,0,0,1,0,1,
									1,1,0,0,0,0,1,1,
									1,1,1,1,1,1,1,1};

bool mask6[64] = {0,0,0,0,0,0,0,0,
									1,1,1,1,1,1,1,1,
									0,0,0,0,0,0,0,0,
									1,1,1,1,1,1,1,1,
									0,0,0,0,0,0,0,1,
									1,1,1,1,1,1,1,1,
									0,0,0,0,0,0,0,0,
									1,1,1,1,1,1,1,1};
									

bool mask7[64] = {1,1,1,1,1,1,1,1,
									0,0,0,0,0,0,0,0,
									1,1,1,1,1,1,1,1,
									0,0,0,0,0,0,0,0,
									1,1,1,1,1,1,1,1,
									0,0,0,0,0,0,0,0,
									1,1,1,1,1,1,1,1,
									0,0,0,0,0,0,0,0};
*/


bool maskAll[64] = {1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1};
										
bool maskChessBoardW[64] = {1,0,1,0,1,0,1,0,
														0,1,0,1,0,1,0,1,
														1,0,1,0,1,0,1,0,
														0,1,0,1,0,1,0,1,
														1,0,1,0,1,0,1,0,
														0,1,0,1,0,1,0,1,
														1,0,1,0,1,0,1,0,
														0,1,0,1,0,1,0,1};														
														
bool maskChessBoardB[64] = {0,1,0,1,0,1,0,1,
														1,0,1,0,1,0,1,0,
														0,1,0,1,0,1,0,1,
														1,0,1,0,1,0,1,0,
														0,1,0,1,0,1,0,1,
														1,0,1,0,1,0,1,0,
														0,1,0,1,0,1,0,1,
														1,0,1,0,1,0,1,0};									
														
bool letterJ[64] = {1,1,1,1,1,1,1,1,
										0,0,0,0,0,1,0,0,
										0,0,0,0,0,1,0,0,
										0,0,0,0,0,1,0,0,
										0,0,0,0,0,1,0,0,
										1,0,0,0,0,1,0,0,
										1,1,0,0,1,1,0,0,
										0,1,1,1,1,0,0,0};

				
										

bool letterO[64] = {0,1,1,1,1,1,1,0,
										1,1,1,1,1,1,1,1,
										1,1,0,0,0,0,1,1,
										1,1,0,0,0,0,1,1,
										1,1,0,0,0,0,1,1,
										1,1,0,0,0,0,1,1,
										1,1,1,1,1,1,1,1,
										0,1,1,1,1,1,1,0};
				
										

bool letterE[64] = {1,1,1,1,1,1,1,1,
										1,1,1,1,1,1,1,1,
										1,1,0,0,0,0,0,0,
										1,1,1,1,1,1,1,0,
										1,1,1,1,1,1,1,0,
										1,1,0,0,0,0,0,0,
										1,1,1,1,1,1,1,1,
										1,1,1,1,1,1,1,1};

										

bool letterL[64] = {1,1,0,0,0,0,0,0,
										1,1,0,0,0,0,0,0,
										1,1,0,0,0,0,0,0,
										1,1,0,0,0,0,0,0,
										1,1,0,0,0,0,0,0,
										1,1,0,0,0,0,0,0,
										1,1,1,1,1,1,1,0,
										1,1,1,1,1,1,1,0};
	
										
										
bool maskEmpty[64] = {0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0};


											
//-------------------------------------Bool Mask Defines End---------------------------------------


void bool_mask_clear_all(bool* boolMaskPtr)
{
	int tempIndex = 0;
	for(tempIndex=0;tempIndex<BOOL_MASK_LENGTH;tempIndex++)
		*(boolMaskPtr + tempIndex) = false;
}	
										
void bool_mask_copy(bool* originalBoolMaskPtr,bool* copyBoolMaskPtr)		
{
	int tempIndex = 0;
	for(tempIndex=0;tempIndex<BOOL_MASK_LENGTH;tempIndex++)
		*(copyBoolMaskPtr + tempIndex) = *(originalBoolMaskPtr + tempIndex);
}	

void bool_mask_decode(bool* destBoolMaskPtr, uint64_t encodedBoolMask)
{
	uint8_t index = 0;
	uint64_t bitCompare = 0x8000000000000000;
	while(index<BOOL_MASK_LENGTH)
	{
		if ((encodedBoolMask & bitCompare) > 0)
			*(destBoolMaskPtr + index) = true;
		else
			*(destBoolMaskPtr + index) = false;
				
		bitCompare = bitCompare >> 1;
		index++;
		
	}	
}
										
void maskPtrSet (bool *maskPtr, int startVal, int stepVal, int stopVal, uint16_t brightness)
{	
	for (int tempVal=startVal;tempVal<stopVal+1;tempVal=tempVal+stepVal)
	{
		*(maskPtr + tempVal) = brightness;
	}
}

void arraySetRow(bool *maskPtr, int rowNum, uint16_t brightness)
{
	if (rowNum == 0) maskPtrSet(maskPtr,0,1,7,brightness);		//*(maskPtr[0:7])   = brightness;
	if (rowNum == 1) maskPtrSet(maskPtr,8,1,15,brightness);		//*(maskPtr[8:15])  = brightness;
	if (rowNum == 2) maskPtrSet(maskPtr,16,1,23,brightness);	//*(maskPtr[16:23]) = brightness;
	if (rowNum == 3) maskPtrSet(maskPtr,24,1,31,brightness);	//*(maskPtr[24:31]) = brightness;
	if (rowNum == 4) maskPtrSet(maskPtr,32,1,39,brightness);	//*(maskPtr[32:39]) = brightness;
	if (rowNum == 5) maskPtrSet(maskPtr,40,1,47,brightness);	//*(maskPtr[40:47]) = brightness;
	if (rowNum == 6) maskPtrSet(maskPtr,48,1,55,brightness);	//*(maskPtr[48:55]) = brightness;
	if (rowNum == 7) maskPtrSet(maskPtr,56,1,63,brightness);	//*(maskPtr[56:63]) = brightness;
	return;
}

void arraySetCol(bool *maskPtr, int colNum, uint16_t brightness)
{
	if (colNum == 0) maskPtrSet(maskPtr,0,8,56,brightness);		//*(maskPtr[0,8,16,24,32,40,48,56])  = brightness;
	if (colNum == 1) maskPtrSet(maskPtr,1,8,57,brightness);		//*(maskPtr[1,9,17,25,33,41,49,57])  = brightness;
	if (colNum == 2) maskPtrSet(maskPtr,2,8,58,brightness);		//*(maskPtr[2,10,18,26,34,42,50,58]) = brightness;
	if (colNum == 3) maskPtrSet(maskPtr,3,8,59,brightness);		//*(maskPtr[3,11,19,27,35,43,51,59]) = brightness;
	if (colNum == 4) maskPtrSet(maskPtr,4,8,60,brightness);		//*(maskPtr[4,12,20,28,36,44,52,60]) = brightness;
	if (colNum == 5) maskPtrSet(maskPtr,5,8,61,brightness);		//*(maskPtr[5,13,21,29,37,45,53,61]) = brightness;
	if (colNum == 6) maskPtrSet(maskPtr,6,8,62,brightness);		//*(maskPtr[6,14,22,30,38,46,54,62]) = brightness;
	if (colNum == 7) maskPtrSet(maskPtr,7,8,63,brightness);		//*(maskPtr[7,15,23,31,39,47,55,63]) = brightness;
	return;
}

void arraySetRing(bool *maskPtr, int ringNum, uint16_t brightness)
{
	if (ringNum == 0) //outermost ring
	{
		maskPtrSet(maskPtr,0,1,7,brightness);
		maskPtrSet(maskPtr,8,7,15,brightness);
		maskPtrSet(maskPtr,16,7,23,brightness);
		maskPtrSet(maskPtr,24,7,31,brightness);
		maskPtrSet(maskPtr,32,7,39,brightness);
		maskPtrSet(maskPtr,40,7,47,brightness);
		maskPtrSet(maskPtr,48,7,55,brightness);
		maskPtrSet(maskPtr,56,7,63,brightness);
	}
	
	if (ringNum == 1) //1 ring in from outermost
	{
		maskPtrSet(maskPtr,9,1,14,brightness);
		maskPtrSet(maskPtr,17,5,22,brightness);
		maskPtrSet(maskPtr,25,5,30,brightness);
		maskPtrSet(maskPtr,33,5,38,brightness);
		maskPtrSet(maskPtr,41,5,46,brightness);
		maskPtrSet(maskPtr,49,1,54,brightness);
	}
	
	if (ringNum == 2) //2 rings in from outermost, 1 ring from innermost
	{	
		maskPtrSet(maskPtr,18,1,21,brightness);
		maskPtrSet(maskPtr,26,3,29,brightness);
		maskPtrSet(maskPtr,34,3,37,brightness);
		maskPtrSet(maskPtr,42,1,45,brightness);
	}
	
	if (ringNum == 3) //innermost ring
	{	
		maskPtrSet(maskPtr,27,1,28,brightness);
		maskPtrSet(maskPtr,35,1,36,brightness);
	}
}

void arraySetRandom(bool *maskPtr, int nSet, uint16_t brightness)
{
		//rand(RAND_MAX)
}
