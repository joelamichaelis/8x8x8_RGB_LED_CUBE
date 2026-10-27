/*
 * LyrFrameFunctions.c
 *
 *  Created on: Nov 22, 2020
 *      Author: Joel Michaelis
 */
  
/**
 * @brief set either the R,G, or B values of the given layer frame
 * @param[in] arrayPtr - points to the first element of the given RGB array inside a lyrFrame 
 * @param[in] brightness - self-explanitory :^)
 * @param[in] mask - corresponds to an 8x8 array that specifies which LEDs will be set the given color
 * example usage: lyr_frame_set_single_rgb(frame1.lyr0.redArrPtr,0x0FFF,mask2);
 */
void lyr_frame_set_single_rgb(uint16_t arrayPtr, uint16_t brightness, bool mask[64]);
{
	for(int index=0;index<64;index++)
	{
		if ( mask[index] == 1)
		{
			*(arrayPtr + index) = brightness;
		}
	}
}


/**
 * @brief set the layer frame to a special RGB color
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] mask - corresponds to an 8x8 array that specifies which LEDs will be set the given color
 * example usage: lyr_frame_set_color(frame1.lyr0,yellow,mask2);
 */
void lyr_frame_set_color(LyrFrame_TypeDef lyrFrame,uint64_t color, bool mask[64])
{
	// color takes form 0x00000RRR0GGG0BBB
	uint16_t redBrightness = (color>>32);
	uint16_t grnBrightness = (color>>16);
	uint16_t bluBrightness = (color>>0);

	for(int index=0;index<64;index++)
	{
		if ( mask[index] == 1)
		{
			*(lyrFrame.redArrPtr + index) = redBrightness;
			*(lyrFrame.grnArrPtr + index) = grnBrightness;
			*(lyrFrame.bluArrPtr + index) = bluBrightness;
		}
	}
}


/**
 * @brief shift the layer frame to the right N times
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] nTimes - The number of times to perform the operation
 * example usage: lyr_frame_shift_right(frame1.lyr0,1);
 */
void lyr_frame_shift_right(LyrFrame_TypeDef lyrFrame, uint16_t nTimes)
{
	array_shift_right(lyrFrame.redArrPtr);
	
	void array_shift_right(uint16_t *arrayPtr)
	{
		*(arrayPtr + 0) =0x0000;
		*(arrayPtr + 1) = *(arrayPtr + 0);
		*(arrayPtr + 2) = *(arrayPtr + 1);
		*(arrayPtr + 3) = *(arrayPtr + 2);
		*(arrayPtr + 4) = *(arrayPtr + 3);
		*(arrayPtr + 5) = *(arrayPtr + 4);
		*(arrayPtr + 6) = *(arrayPtr + 5);
		*(arrayPtr + 7) = *(arrayPtr + 6);
		
		for (int index=63;index>0;index--)
		{
			*(arrayPtr + index) = *(arrayPtr + index - 1);
		}
	}
}