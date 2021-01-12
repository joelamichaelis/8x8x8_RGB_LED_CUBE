/*
 * tlc5940.h
 *
 *  Created Initially On: Nov 5, 2020
 *      Author: Joel Michaelis
 */
 
#ifndef TLC5940_H_
#define TLC5940_H_

//Includes 
#include "main.h"
#include <string.h>
#include <stdbool.h>

//Variable definitions, etc

 #define NUM_TLCS 12
 
extern int redMap[64];
extern int grnMap[64];
extern int bluMap[64];

//Function Prototypes
void tlc_spi_convert(uint16_t *data16, uint8_t *data8);
void tlc_clear(uint16_t *data16);
void tlc_set_led(uint16_t *data16, uint16_t number, uint16_t brightness);
void tlc_set_lyr(uint16_t *data16, uint64_t color, bool mask[64]);
void tlc_update(SPI_HandleTypeDef hspi, uint16_t *data16, uint8_t *data8);
void tlc_intToStr(uint8_t *numVal, uint8_t *strVal);
void tlc_maskCopy(bool *maskPtr, bool *patternPtr);
void tlc_debug_update(SPI_HandleTypeDef hspi, uint16_t *data16Ptr, uint8_t *data8Ptr);
uint16_t tlc_LEtoBE(uint16_t lilEndian);
uint16_t tlc_nibbleSwap(uint16_t originalNibble);
uint16_t tlc_wordBitReversal(uint16_t originalWord);
void tlc_spi16BitConversion(uint16_t *data16Ptr, uint16_t *data12ptr);
#endif /* TLC5940_H_ */									
					
