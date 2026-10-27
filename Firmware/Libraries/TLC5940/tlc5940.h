/*
 * tlc5940.h
 *
 *  Created Initially On: Nov 5, 2020
 *      Author: Joel Michaelis
 */
 


//Includes 
#include "main.h"
#include <string.h>
#include <stdbool.h>

//Variable definitions, etc

 #define NUM_TLCS    12

typedef struct __Frame_TypeDef{
	bool lyr0Mask[64];
	bool lyr1Mask[64];
	bool lyr2Mask[64];
	bool lyr3Mask[64];
	bool lyr4Mask[64];
	bool lyr5Mask[64];
	bool lyr6Mask[64];
	bool lyr7Mask[64];
	uint64_t lyr0Color;
	uint64_t lyr1Color;
	uint64_t lyr2Color;
	uint64_t lyr3Color;
	uint64_t lyr4Color;
	uint64_t lyr5Color;
	uint64_t lyr6Color;
	uint64_t lyr7Color;
} Frame_TypeDef;

Frame_TypeDef frame1;

//lyr global variable indicates active cube layer.
//Needs to be global so timer IRQ can access value
uint8_t activeLyr = 0;

//Data Arrays&Pointers Need to be global for a reason. I will specify why once I remember.
// Data Arrays
uint16_t data16[16*NUM_TLCS];
uint8_t data8[24*NUM_TLCS];
// Data Pointers
uint8_t *data8Ptr = &data8[0];
uint16_t *data16Ptr = &data16[0];

// Current mapping. Reconfigure as needed :^)
// Needs to be global for convenient timer IRQ access

int redMap[64] = {178,181,160,163,166,145,148,151,189,186,175,172,169,158,155,152,130,133,112,115,118,97,100,103,141,138,127,124,121,110,107,104,82,85,64,67,70,49,52,55,93,90,79,76,73,62,59,56,34,37,16,19,22,1,4,7,45,42,31,28,25,14,11,8};
int grnMap[64] = {177,180,183,162,165,144,147,150,190,187,184,173,170,159,156,153,129,132,135,114,117,96,99,102,142,139,136,125,122,111,108,105,81,84,87,66,69,48,51,54,94,91,88,77,74,63,60,57,33,36,39,18,21,0,3,6,46,43,40,29,26,15,12,9};
int bluMap[64] = {176,179,182,161,164,167,146,149,191,188,185,174,171,168,157,154,128,131,134,113,116,119,98,101,143,140,137,126,123,120,109,106,80,83,86,65,68,71,50,53,95,92,89,78,75,72,61,58,32,35,38,17,20,23,2,5,47,44,41,30,27,24,13,10};

uint8_t ledNumPM = 64;
uint16_t redValPM = 2000;
uint16_t bluValPM = 2000;
uint16_t grnValPM = 2000;
	
//Color Definition Begin
uint64_t red = 				0x0fff00000000;
uint64_t green = 			0x00000fff0000;
uint64_t blue = 			0x000000000fff;
uint64_t yellow = 		0x0fff0fff0000;
uint64_t purple = 		0x0fff00000fff;
uint64_t cyan = 			0x00000fff0fff;
uint64_t orange = 		0x0fff08000000;
uint64_t pink = 			0x0fff0c0f0cbf;
uint64_t seafoam = 		0x071f0eef0b8f;
//Color Definition End

// This is how I'm manually specifying layer patterns for now!
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

bool *mask0Ptr = &mask0[0];
bool *mask1Ptr = &mask1[0];
bool *mask2Ptr = &mask2[0];
bool *mask3Ptr = &mask3[0];
bool *mask4Ptr = &mask4[0];
bool *mask5Ptr = &mask5[0];
bool *mask6Ptr = &mask6[0];
bool *mask7Ptr = &mask7[0];
									
bool MAIN_MENU_ENABLED = 1;	
bool PIN_MAPPING_ENABLED = 0;
bool APPLICATION_ENABLED = 0;

//Function Prototypes
void tlc_spi_convert(uint16_t *data16, uint8_t *data8);
void tlc_clear(uint16_t *data16);
void tlc_set_led(uint16_t *data16, int number, uint16_t brightness);
void tlc_set_lyr(uint16_t *data16, uint64_t color, bool mask[64]);
void tlc_update(uint16_t *data16, uint8_t *data8);
void tlc_intToStr(uint8_t *numVal, uint8_t *strVal);
void tlc_maskCopy(bool *maskPtr, bool *patternPtr);