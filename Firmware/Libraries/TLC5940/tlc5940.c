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
				*(data8 + index8) = *(data16 + index16);
				index8++;
        i++;
        break;

      case 1:
				*(data8 + index8) = ( (( (*(data16 + (index16 + 1))<<4) & 0xF0) >> 4) | ( ((*(data16 + index16)>>8) & 0x0F ) << 4));
				index8++;
        i++;
        break;

      case 2:
				*(data8 + index8) = (*(data16 + (index16 + 1))>>4);
				index8++;
				index16 = index16 + 2;
        i=0;
        break;
		}
	}
}


void tlc_clear(uint16_t *data16)
{
	for(int i=0; i<24*NUM_TLCS;i++)
	{
		*(data16Ptr + i) = 0;
	}

}

void tlc_set_led(uint16_t *data16, int number, uint16_t brightness)
{
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

void tlc_update(uint16_t *data16, uint8_t *data8)
{
	tlc_spi_convert(data16Ptr, data8Ptr);

	HAL_SPI_Transmit(&hspi1, data8, 24*NUM_TLCS, 10);
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