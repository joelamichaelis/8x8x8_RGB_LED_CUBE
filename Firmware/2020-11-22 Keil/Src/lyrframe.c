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
			//don't clear existing stuff out!
			//*(lyrFrame.redArrPtr + index) = 0x0000;
			//*(lyrFrame.grnArrPtr + index) = 0x0000;
			//*(lyrFrame.bluArrPtr + index) = 0x0000;
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
 * @brief shift the layer frame in the specified direction, zeros are shifted in
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_shift_right(frame1.lyr0, DIRECTION_RIGHT);
 */
void lyr_frame_shift(LyrFrame_TypeDef lyrFrame, uint8_t direction)
{
	array_8x8_shift(lyrFrame.redArrPtr, direction);
	array_8x8_shift(lyrFrame.grnArrPtr, direction);
	array_8x8_shift(lyrFrame.bluArrPtr, direction);
}

/**
 * @brief shift the layer frame in the specified direction and wrap around
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_rotate_right(frame1.lyr0, DIRECTION_RIGHT);
 */
void lyr_frame_rotate(LyrFrame_TypeDef lyrFrame, uint8_t direction)
{
	array_8x8_rotate(lyrFrame.redArrPtr, direction);
	array_8x8_rotate(lyrFrame.grnArrPtr, direction);
	array_8x8_rotate(lyrFrame.bluArrPtr, direction);
}

/**
 * @brief  inverts the brightness values of all elements of the layer frame arrays
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 **/
void lyr_frame_invert(LyrFrame_TypeDef lyrFrame)
{
	array_8x8_invert(lyrFrame.redArrPtr);
	array_8x8_invert(lyrFrame.grnArrPtr);
	array_8x8_invert(lyrFrame.bluArrPtr);
}

/**
 * @brief shift a column of the layer frame in the specified direction, zeros are shifted in
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] colNum - indicates which column is to be shifted (0 - 7)
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_shift_column(frame1.lyr0, 7, DIRECTION_RIGHT);
 */
void lyr_frame_shift_column(LyrFrame_TypeDef lyrFrame, uint8_t colNum, uint8_t direction)
{
	array_8x8_shift_column(lyrFrame.redArrPtr, colNum, direction);
	array_8x8_shift_column(lyrFrame.grnArrPtr, colNum, direction);
	array_8x8_shift_column(lyrFrame.bluArrPtr, colNum, direction);
}

/**
 * @brief shift a column of the layer frame in the specified direction and wrap around
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] colNum - indicates which column is to be rotated (0 - 7)
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_rotate_column(frame1.lyr0, 7, DIRECTION_RIGHT);
 */
void lyr_frame_rotate_column(LyrFrame_TypeDef lyrFrame, uint8_t colNum, uint8_t direction)
{
	array_8x8_rotate_column(lyrFrame.redArrPtr, colNum, direction);
	array_8x8_rotate_column(lyrFrame.grnArrPtr, colNum, direction);
	array_8x8_rotate_column(lyrFrame.bluArrPtr, colNum, direction);
}

/**
 * @brief shift a row of the layer frame in the specified direction, zeros are shifted in
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] rowNum - indicates which row is to be shifted (0 - 7)
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_shift_row(frame1.lyr0, 0, DIRECTION_RIGHT);
 */
void lyr_frame_shift_row(LyrFrame_TypeDef lyrFrame, uint8_t rowNum, uint8_t direction)
{
	array_8x8_shift_row(lyrFrame.redArrPtr, rowNum, direction);
	array_8x8_shift_row(lyrFrame.grnArrPtr, rowNum, direction);
	array_8x8_shift_row(lyrFrame.bluArrPtr, rowNum, direction);
}

/**
 * @brief shift a row of the layer frame in the specified direction and wrap around
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] rowNum - indicates which row is to be shifted (0 - 7)
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_rotate_row(frame1.lyr0, 0, DIRECTION_RIGHT);
 */
void lyr_frame_rotate_row(LyrFrame_TypeDef lyrFrame, uint8_t rowNum, uint8_t direction)
{
	array_8x8_rotate_row(lyrFrame.redArrPtr, rowNum, direction);
	array_8x8_rotate_row(lyrFrame.grnArrPtr, rowNum, direction);
	array_8x8_rotate_row(lyrFrame.bluArrPtr, rowNum, direction);
}



/**
 * @brief rotate the layer frame quadrants counter-clockwise about the +z upward direction 
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_rotate(frame1.lyr0, DIRECTION_CW);
 */

/*
void lyr_frame_quadrant_rotate_ccw(LyrFrame_TypeDef lyrFrame, uint8_t direction)
{
	array_8x8_quadrant_rotate(lyrFrame.redArrPtr, direction);
	array_8x8_quadrant_rotate(lyrFrame.grnArrPtr, direction);
	array_8x8_quadrant_rotate(lyrFrame.bluArrPtr, direction);
}

*/

/**
 * @brief rotate the layer frame quadrantsclockwise about the -z downward direction 
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_rotate(frame1.lyr0, DIRECTION_CCW);
 */
 
 /*
 
void lyr_frame_quadrant_rotate_cw(LyrFrame_TypeDef lyrFrame, uint8_t direction)
{
	array_8x8_quadrant_rotate(lyrFrame.redArrPtr, direction);
	array_8x8_quadrant_rotate(lyrFrame.grnArrPtr, direction);
	array_8x8_quadrant_rotate(lyrFrame.bluArrPtr, direction);
}

*/

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
