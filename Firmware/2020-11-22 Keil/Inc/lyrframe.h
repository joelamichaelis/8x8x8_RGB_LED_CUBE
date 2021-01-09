/*
 * lyrframe.h
 *
 *  Created on: Nov 22, 2020
 *      Author: Joel Michaelis
 */
 
 #ifndef LYRFRAME
 #define LYRFRAME
 
 #include <stdbool.h>
 #include "array_8x8.h"

typedef struct __LyrFrame_TypeDef
{	
	uint16_t redArray[64];
	uint16_t *redArrPtr;
	uint16_t grnArray[64];
	uint16_t *grnArrPtr;
	uint16_t bluArray[64];
	uint16_t *bluArrPtr;
} LyrFrame_TypeDef;

extern bool UPDATE_FRAME;
extern uint16_t *data16Ptr;
/**
 * @brief merges the lyrFrame separate R/G/B 8x8 arrays into data16 which is the data transmitted to the TLCs 
 * @param[in] lyrFrame - the lyrFrame of interest
 * @param[in] data16Ptr - a pointer to the array of data which is sent to the TLC
 */
void lyr_frame_convert(LyrFrame_TypeDef lyrFrame,uint16_t *data16Ptr);

/**
 * @brief set either the R,G, or B values of the given layer frame
 * @param[in] arrayPtr - points to the first element of the given RGB array inside a lyrFrame 
 * @param[in] brightness - self-explanitory :^)
 * @param[in] mask - corresponds to an 8x8 array that specifies which LEDs will be set the given color
 * example usage: lyr_frame_set_single_rgb(frame1.lyr0.redArrPtr,0x0FFF,mask2);
 */
void lyr_frame_set_single_rgb(uint16_t *arrayPtr, uint16_t brightness, bool mask[64]);

/**
 * @brief set the layer frame to a special RGB color
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] mask - corresponds to an 8x8 array that specifies which LEDs will be set the given color
 * example usage: lyr_frame_set_color(frame1.lyr0,yellow,mask2);
 */
void lyr_frame_set_color(LyrFrame_TypeDef lyrFrame,uint64_t color, bool mask[64]);

/**
 * @brief clear the given lyrFrame
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 */
void lyr_frame_clear_all(LyrFrame_TypeDef lyrFrame);

/**
 * @brief shift the layer frame in the specified direction, zeros are shifted in
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_shift_right(frame1.lyr0, DIRECTION_RIGHT);
 */
void lyr_frame_shift(LyrFrame_TypeDef lyrFrame, uint8_t direction);

/**
 * @brief shift the layer frame in the specified direction and wrap around
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_rotate_right(frame1.lyr0, DIRECTION_RIGHT);
 */
void lyr_frame_rotate(LyrFrame_TypeDef lyrFrame, uint8_t direction);

/**
 * @brief  inverts the brightness values of all elements of the layer frame arrays
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 **/
 void lyr_frame_invert(LyrFrame_TypeDef lyrFrame); 

/**
 * @brief shift a column of the layer frame in the specified direction, zeros are shifted in
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] colNum - indicates which column is to be shifted (0 - 7)
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_shift_column(frame1.lyr0, 7, DIRECTION_RIGHT);
 */
void lyr_frame_shift_column(LyrFrame_TypeDef lyrFrame, uint8_t colNum, uint8_t direction);

/**
 * @brief shift a column of the layer frame in the specified direction and wrap around
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] colNum - indicates which column is to be rotated (0 - 7)
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_rotate_column(frame1.lyr0, 7, DIRECTION_RIGHT);
 */
void lyr_frame_rotate_column(LyrFrame_TypeDef lyrFrame, uint8_t colNum, uint8_t direction);

/**
 * @brief shift a row of the layer frame in the specified direction, zeros are shifted in
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] rowNum - indicates which row is to be shifted (0 - 7)
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_shift_row(frame1.lyr0, 0, DIRECTION_RIGHT);
 */
void lyr_frame_shift_row(LyrFrame_TypeDef lyrFrame, uint8_t rowNum, uint8_t direction);

/**
 * @brief shift a row of the layer frame in the specified direction and wrap around
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] rowNum - indicates which row is to be shifted (0 - 7)
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_rotate_row(frame1.lyr0, 0, DIRECTION_RIGHT);
 */
void lyr_frame_rotate_row(LyrFrame_TypeDef lyrFrame, uint8_t rowNum, uint8_t direction);

/**
 * @brief rotate the layer frame quadrants either CW or CCW about the +/- z direction 
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * example usage: lyr_frame_rotate_ccw(frame1.lyr0, DIRECTION_CW);
 */
void lyr_frame_quadrant_rotate(LyrFrame_TypeDef lyrFrame, uint8_t direction);


/**
 * @brief increases the intensity of the non-zero elements in the lyrFrame
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] delta - the amount to increase the intensity by
 */
void lyr_frame_brighten(LyrFrame_TypeDef lyrFrame, uint16_t delta);

#endif
