/*
 * tlc5940.c
 *
 *  Created Initially On: Nov 5, 2020
 *      Author: Joel Michaelis
 */
 
#include "tlc5940.h"
#include <string.h>
#include <stdbool.h>
 
 void tlc_spi_convert(uint16_t *data16, uint8_t *data8)
{

	int index8 = 0;
	int index16 = 0;
	int i = 0;

	while (index8 < 24*NUM_TLCS)
	{
		switch (i)
		{
			case 0:
				*(data8 + index8) = (*(data16 + index16)>>4);
				index8++;
        i++;
        break;

      case 1:
				*(data8 + index8) = ( (( (*(data16 + index16)<<4) & 0xF0)) | ( (*(data16 + (index16 + 1))>>8) & 0x0F ));
				index8++;
        i++;
        break;

      case 2:
				*(data8 + index8) = *(data16 + (index16 + 1));
				index8++;
				index16 = index16 + 2;
        i=0;
        break;
		}
	}
}


void tlc_clear(uint16_t *data16Ptr)
{
	for(int i=0; i<24*NUM_TLCS;i++)
	{
		*(data16Ptr + i) = 0;
	}

}

void tlc_set_led(uint16_t *data16, uint16_t number, uint16_t brightness)
{
	if (brightness > 0x0FFF) brightness = 0xFFF;
	*(data16 + number) = brightness;
}


// Function sets the entire TLC data16 array. requires a color and a pattern mask.
void tlc_set_lyr(uint16_t *data16, uint64_t color, bool mask[64])
{
	// color takes form 0x0RRR0GGG0BBB
	uint16_t red = (color>>32);
	uint16_t grn = (color>>16);
	uint16_t blu = (color>>0);

	for(int index=0;index<64;index++)
	{
		if ( mask[index] == 1)
		{
			*(data16 + redMap[index]) = red;
			*(data16 + grnMap[index]) = grn;
			*(data16 + bluMap[index]) = blu;
		}
	}

}

void tlc_update(SPI_HandleTypeDef hspi, uint16_t *data16Ptr, uint8_t *data8Ptr)
{
	tlc_spi_convert(data16Ptr, data8Ptr);
	//tlc_spi16BitConversion(data16Ptr,data12Ptr);
	HAL_SPI_Transmit(&hspi, data8Ptr, 24*NUM_TLCS, 10);
	HAL_GPIO_WritePin(XLAT_3V3_GPIO_Port, XLAT_3V3_Pin, GPIO_PIN_SET);
	// short delay (approx 3us)
	for(uint16_t dummyVar =1;dummyVar<15;dummyVar++);
	HAL_GPIO_WritePin(XLAT_3V3_GPIO_Port, XLAT_3V3_Pin, GPIO_PIN_RESET);
}


//function defined specifically to convert integers 0~192 into strings
void tlc_intToStr(uint8_t *numVal, uint8_t *strVal)
{
	*(strVal) = (*(numVal)/100) + '0';
	*(strVal + 1) = ((*(numVal)%100)/10) + '0';
	*(strVal + 2) = (*(numVal)%10) + '0';
	*(strVal + 3) = '\n';
}


void tlc_maskCopy(bool *maskPtr, bool *patternPtr)
{
	for (int index=0;index<64;index++)
	{
		*(patternPtr + index) = *(maskPtr + index);
	}
}


//This is a function to play with to help for dev purposes
void tlc_debug_update(SPI_HandleTypeDef hspi, uint16_t *data16Ptr, uint8_t *data8Ptr)
{
	tlc_clear(data16Ptr);
	tlc_spi_convert(data16Ptr, data8Ptr);
	*(data8Ptr+0) = 0xF0;
	*(data8Ptr+1) = 0x0F;
	
	HAL_SPI_Transmit(&hspi, data8Ptr, 24*NUM_TLCS, 10);
	HAL_GPIO_WritePin(XLAT_3V3_GPIO_Port, XLAT_3V3_Pin, GPIO_PIN_SET);
	// short delay (approx 3us)
	for(uint16_t dummyVar =1;dummyVar<15;dummyVar++);
	HAL_GPIO_WritePin(XLAT_3V3_GPIO_Port, XLAT_3V3_Pin, GPIO_PIN_RESET);
}

uint16_t tlc_LEtoBE(uint16_t lilEndian)
{
	uint16_t bigEndian = 0x0000;
	bigEndian |= ((lilEndian<<12) & 0xF000);
	bigEndian |= ((lilEndian<<4)  & 0x0F00);
	bigEndian |= ((lilEndian>>4)  & 0x00F0);
	bigEndian |= ((lilEndian>>12) & 0x000F);
	return bigEndian;
}

uint16_t tlc_nibbleSwap(uint16_t originalNibble)
{
	uint16_t reversedNibble = 0x0000;
	switch(originalNibble)
	{
		case 0x0000:
			reversedNibble = 0x0000;
			break;
		case 0x0001:
			reversedNibble = 0x0008;
			break;
		case 0x0002:
			reversedNibble = 0x0004;
			break;
		case 0x0003:
			reversedNibble = 0x000C;
			break;
		case 0x0004:
			reversedNibble = 0x0002;
			break;
		case 0x0005:
			reversedNibble = 0x000A;
			break;
		case 0x0006:
			reversedNibble = 0x0006;
			break;
		case 0x0007:
			reversedNibble = 0x000E;
			break;
		case 0x0008:
			reversedNibble = 0x0001;
			break;
		case 0x0009:
			reversedNibble = 0x0009;
			break;
		case 0x000A:
			reversedNibble = 0x0005;
			break;
		case 0x000B:
			reversedNibble = 0x000D;
			break;
		case 0x000C:
			reversedNibble = 0x0003;
			break;
		case 0x000D:
			reversedNibble = 0x000B;
			break;
		case 0x000E:
			reversedNibble = 0x0007;
			break;
		case 0x000F:
			reversedNibble = 0x000F;
			break;
		default:
			break;
	}
	return reversedNibble;
}

uint16_t tlc_wordBitReversal(uint16_t originalWord)
{
	
	originalWord = tlc_LEtoBE(originalWord);
	
	uint16_t reversedWord = 0x0000;
	uint16_t tempWord = 0x0000;
	
	tempWord = (originalWord & 0x000F);
	reversedWord |= (tlc_nibbleSwap(tempWord)<<12);
	
	tempWord = ((originalWord>>4) & 0x000F);
	reversedWord |= (tlc_nibbleSwap(tempWord)<<8);
	
	tempWord = ((originalWord>>8) & 0x000F);
	reversedWord |= (tlc_nibbleSwap(tempWord)<<4);
	
	tempWord = ((originalWord>>12) & 0x000F);
	reversedWord |= (tlc_nibbleSwap(tempWord));
	
	return reversedWord;
}

void tlc_spi16BitConversion(uint16_t *data16Ptr, uint16_t *data12Ptr)
{
	int index12 = 0;
	int index16 = 0;
	int caseIndex =0;
	
	while (index12 < 12*NUM_TLCS)
	{
		switch (caseIndex)
		{
			case 0:
				*(data12Ptr+index12) = ((tlc_wordBitReversal(*(data16Ptr+index16))) | ((tlc_wordBitReversal(*(data16Ptr+index16+1))>>12) & 0x000F));
				index12++;
				index16++;
        caseIndex++;
        break;
			
			case 1:
				*(data12Ptr+index12) = ((tlc_wordBitReversal(*(data16Ptr+index16))<<4) | ((tlc_wordBitReversal(*(data16Ptr+index16+1))>>8) & 0x00FF));
				index12++;
				index16++;
        caseIndex++;
        break;
			
			case 2:
				*(data12Ptr+index12) = ((tlc_wordBitReversal(*(data16Ptr+index16))<<8) | ((tlc_wordBitReversal(*(data16Ptr+index16+1))>>4) & 0x0FFF)); //case 2
				index12++;
				index16++;
				caseIndex=0;
				break;
		}
	}
}	
