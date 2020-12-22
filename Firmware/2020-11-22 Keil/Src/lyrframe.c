/*
 * LyrFrameFunctions.c
 *
 *  Created on: Nov 22, 2020
 *      Author: Joel Michaelis
 */
  
#include "lyrframe.h"

extern int redMap[64];
extern int grnMap[64];
extern int bluMap[64];

/**
 * @brief merges the lyrFrame separate R/G/B 8x8 arrays into data16 which is the data transmitted to the TLCs 
 * @param[in] lyrFrame - the lyrFrame of interest
 * @param[in] data16Ptr - a pointer to the array of data which is sent to the TLC
 */
void lyr_frame_convert(LyrFrame_TypeDef lyrFrame,uint16_t *data16Ptr)
{
	for(int index=0;index<64;index++)
	{
		*(data16Ptr + redMap[index]) = lyrFrame.redArray[index];
		*(data16Ptr + grnMap[index]) = lyrFrame.grnArray[index];
		*(data16Ptr + bluMap[index]) = lyrFrame.bluArray[index];
	}
}

/**
 * @brief set either the R,G, or B values of the given layer frame
 * @param[in] arrayPtr - points to the first element of the given RGB array inside a lyrFrame 
 * @param[in] brightness - self-explanitory :^)
 * @param[in] mask - corresponds to an 8x8 array that specifies which LEDs will be set the given color
 * example usage: lyr_frame_set_single_rgb(frame1.lyr0.redArrPtr,0x0FFF,mask2);
 */
void lyr_frame_set_single_rgb(uint16_t *arrayPtr, uint16_t brightness, bool mask[64])
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
		
		if ( mask[index] == 0)
		{
			*(lyrFrame.redArrPtr + index) = 0x0000;
			*(lyrFrame.grnArrPtr + index) = 0x0000;
			*(lyrFrame.bluArrPtr + index) = 0x0000;
		}
		
	}
}

/**
 * @brief clear the given lyrFrame
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 */
void lyr_frame_clear_all(LyrFrame_TypeDef lyrFrame)
{
	for(int index=0;index<64;index++)
	{
		*(lyrFrame.redArrPtr + index) = 0x0000;
		*(lyrFrame.grnArrPtr + index) = 0x0000;
		*(lyrFrame.bluArrPtr + index) = 0x0000;
	}
}

/**
 * @brief shift the layer frame to the right N times
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] nTimes - The number of times to perform the operation
 * example usage: lyr_frame_shift_right(frame1.lyr0,1);
 */
void lyr_frame_shift_right(LyrFrame_TypeDef lyrFrame)
{
	array_8x8_shift_right(lyrFrame.redArrPtr);
	array_8x8_shift_right(lyrFrame.grnArrPtr);
	array_8x8_shift_right(lyrFrame.bluArrPtr);
}

/**
 * @brief shift the layer frame to the right and wrap around
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_rotate_right(frame1.lyr0);
 */
void lyr_frame_rotate_right(LyrFrame_TypeDef lyrFrame)
{
	array_8x8_rotate_right(lyrFrame.redArrPtr);
	array_8x8_rotate_right(lyrFrame.grnArrPtr);
	array_8x8_rotate_right(lyrFrame.bluArrPtr);
}

/**
 * @brief shift the layer frame to the left
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_shift_left(frame1.lyr0);
 */
void lyr_frame_shift_left(LyrFrame_TypeDef lyrFrame)
{
	array_8x8_shift_left(lyrFrame.redArrPtr);
	array_8x8_shift_left(lyrFrame.grnArrPtr);
	array_8x8_shift_left(lyrFrame.bluArrPtr);
}

/**
 * @brief shift the layer frame to the left and wrap around
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_rotate_left(frame1.lyr0);
 */
void lyr_frame_rotate_left(LyrFrame_TypeDef lyrFrame)
{
	array_8x8_rotate_left(lyrFrame.redArrPtr);
	array_8x8_rotate_left(lyrFrame.grnArrPtr);
	array_8x8_rotate_left(lyrFrame.bluArrPtr);
}

/**
 * @brief shift the layer frame to the forward
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_shift_forward(frame1.lyr0);
 */
void lyr_frame_shift_forward(LyrFrame_TypeDef lyrFrame)
{
	array_8x8_shift_forward(lyrFrame.redArrPtr);
	array_8x8_shift_forward(lyrFrame.grnArrPtr);
	array_8x8_shift_forward(lyrFrame.bluArrPtr);
}

/**
 * @brief shift the layer frame forward and wrap around
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_rotate_forward(frame1.lyr0);
 */
void lyr_frame_rotate_forward(LyrFrame_TypeDef lyrFrame)
{
	array_8x8_rotate_forward(lyrFrame.redArrPtr);
	array_8x8_rotate_forward(lyrFrame.grnArrPtr);
	array_8x8_rotate_forward(lyrFrame.bluArrPtr);
}

/**
 * @brief shift the layer frame to the back
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_shift_back(frame1.lyr0);
 */
void lyr_frame_shift_back(LyrFrame_TypeDef lyrFrame)
{
	array_8x8_shift_back(lyrFrame.redArrPtr);
	array_8x8_shift_back(lyrFrame.grnArrPtr);
	array_8x8_shift_back(lyrFrame.bluArrPtr);
}

/**
 * @brief shift the layer frame backward and wrap around
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_rotate_back(frame1.lyr0);
 */
void lyr_frame_rotate_back(LyrFrame_TypeDef lyrFrame)
{
	array_8x8_rotate_back(lyrFrame.redArrPtr);
	array_8x8_rotate_back(lyrFrame.grnArrPtr);
	array_8x8_rotate_back(lyrFrame.bluArrPtr);
}

/**
 * @brief increases the intensity of the non-zero elements in the lyrFrame
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] lyrFrame - the amount to increase the intensity by
 */
void lyr_frame_brighten(LyrFrame_TypeDef lyrFrame, uint16_t delta)
{
	array_8x8_brighten(lyrFrame.redArrPtr, delta);
	array_8x8_brighten(lyrFrame.grnArrPtr, delta);
	array_8x8_brighten(lyrFrame.bluArrPtr, delta);
}

/**
 * @brief a multi-frame animation that fades a lyrFrame in & out in steps
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] color - the color :^)
 * @param[in] color - number of steps between off & on
 */
void lyr_frame_fade_in_and_out(LyrFrame_TypeDef lyrFrame, uint64_t color, uint16_t stepSize)
{
	// color takes form 0x00000RRR0GGG0BBB
	uint16_t redMax = (color>>32);
	uint16_t grnMax = (color>>16);
	uint16_t bluMax = (color>>0);
	uint16_t brightest;
	uint16_t darkest;
	uint16_t redRatio;
	uint16_t grnRatio;
	uint16_t bluRatio;
	uint16_t minDelta;

	if ((redMax >= grnMax) & (redMax >= bluMax)) brightest = redMax;
	if ((grnMax >= redMax) & (grnMax >= bluMax)) brightest = grnMax;
	if ((bluMax >= redMax) & (bluMax >= grnMax)) brightest = bluMax;
	
	if ((redMax <= grnMax) & (redMax <= bluMax)) darkest = redMax;
	if ((grnMax <= redMax) & (grnMax <= bluMax)) darkest = grnMax;
	if ((bluMax <= redMax) & (bluMax <= grnMax)) darkest = bluMax;
	
	redRatio = redMax/darkest;
	grnRatio = grnMax/darkest;
	bluRatio = bluMax/darkest;
	
	minDelta = darkest/stepSize;
	
	/*

	for(int index=0;index<=stepSize;index++)
	{
		if ( mask[index] == 1)
		{
			*(lyrFrame.redArrPtr + index) = redBrightness;
			*(lyrFrame.grnArrPtr + index) = grnBrightness;
			*(lyrFrame.bluArrPtr + index) = bluBrightness;
		}
	}
	*/
}

/**
 * @brief fades in blu in steps and waits at each step
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] mask - the specific leds to perform the operation to
 * @param[in] maxBrightness - the brightness to stop fading in at
 * @param[in] deltaBrightness - step size
 * @param[in] delay - amount of time to stay at each step for
 **/
void lyr_frame_fade_in_blu(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay)
{
	uint16_t currentBrightness = deltaBrightness;
	while (currentBrightness <= maxBrightness)
	{
		//lyr_frame_clear_all(lyrFrame);
		lyr_frame_set_single_rgb(lyrFrame.bluArrPtr, currentBrightness, mask);
		lyr_frame_convert(lyrFrame,data16Ptr);
		UPDATE_FRAME=1;
		HAL_Delay(delay);
		currentBrightness = currentBrightness + deltaBrightness;
	}
}

/**
 * @brief fades out blu in steps and waits at each step
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] mask - the specific leds to perform the operation to
 * @param[in] maxBrightness - the brightness to stop fading in at
 * @param[in] deltaBrightness - step size
 * @param[in] delay - amount of time to stay at each step for
 **/
void lyr_frame_fade_out_blu(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay)
{
	int16_t currentBrightness = 4000; //hopefully since its signed there's no negative number hard fault.
	while (currentBrightness >= minBrightness)
	{
		lyr_frame_clear_all(lyrFrame);
		lyr_frame_set_single_rgb(lyrFrame.bluArrPtr, currentBrightness, &mask[0]);
		lyr_frame_convert(lyrFrame,data16Ptr);
		UPDATE_FRAME=1;
		HAL_Delay(delay);
		currentBrightness = currentBrightness - deltaBrightness;
	}
}
