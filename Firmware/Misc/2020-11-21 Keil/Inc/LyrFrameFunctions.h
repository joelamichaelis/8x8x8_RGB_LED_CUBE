/*
 * LyrFrameFunctions.h
 *
 *  Created on: Nov 22, 2020
 *      Author: Joel Michaelis
 */
 
 #include "main.h"
 #include <stdbool.h>
 #include "Array8x8Functions.h"
 
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
 * @brief shift the layer frame to the right N times
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] nTimes - The number of times to perform the operation
 * example usage: lyr_frame_shift_right(frame1.lyr0,1);
 */
void lyr_frame_shift_right(LyrFrame_TypeDef lyrFrame, uint16_t nTimes);

/**
 * @brief shift the layer frame to the left N times
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] nTimes - The number of times to perform the operation
 * example usage: lyr_frame_shift_left(frame1.lyr0,1);
 */
void lyr_frame_shift_left(LyrFrame_TypeDef lyrFrame, uint16_t nTimes);

/**
 * @brief shift the layer frame to the forward N times
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] nTimes - The number of times to perform the operation
 * example usage: lyr_frame_shift_forward(frame1.lyr0,1);
 */
void lyr_frame_shift_forward(LyrFrame_TypeDef lyrFrame, uint16_t nTimes);

/**
 * @brief shift the layer frame to the back N times
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] nTimes - The number of times to perform the operation
 * example usage: lyr_frame_shift_back(frame1.lyr0,1);
 */
void lyr_frame_shift_back(LyrFrame_TypeDef lyrFrame, uint16_t nTimes);
