/*
 * LyrFrameFunctions.h
 *
 *  Created on: Nov 22, 2020
 *      Author: Joel Michaelis
 */
 
 #include "main.h"
 #include <stdbool.h>
 #include "Array8x8Functions.h"

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
 * @brief shift the layer frame to the right
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_shift_right(frame1.lyr0);
 */
void lyr_frame_shift_right(LyrFrame_TypeDef lyrFrame);

/**
 * @brief shift the layer frame to the right and wrap around
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_rotate_right(frame1.lyr0);
 */
void lyr_frame_rotate_right(LyrFrame_TypeDef lyrFrame);

/**
 * @brief shift the layer frame to the left
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_shift_left(frame1.lyr0);
 */
void lyr_frame_shift_left(LyrFrame_TypeDef lyrFrame);

/**
 * @brief shift the layer frame to the left and wrap around
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_rotate_left(frame1.lyr0);
 */
void lyr_frame_rotate_left(LyrFrame_TypeDef lyrFrame);

/**
 * @brief shift the layer frame to the forward
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_shift_forward(frame1.lyr0);
 */
void lyr_frame_shift_forward(LyrFrame_TypeDef lyrFrame);

/**
 * @brief shift the layer frame forward and wrap around
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_rotate_forward(frame1.lyr0);
 */
void lyr_frame_rotate_forward(LyrFrame_TypeDef lyrFrame);

/**
 * @brief shift the layer frame to the back
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_shift_back(frame1.lyr0);
 */
void lyr_frame_shift_back(LyrFrame_TypeDef lyrFrame);

/**
 * @brief shift the layer frame backward and wrap around
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * example usage: lyr_frame_rotate_back(frame1.lyr0);
 */
void lyr_frame_rotate_back(LyrFrame_TypeDef lyrFrame);

/**
 * @brief increases the intensity of the non-zero elements in the lyrFrame
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] delta - the amount to increase the intensity by
 */
void lyr_frame_brighten(LyrFrame_TypeDef lyrFrame, uint16_t delta);

/**
 * @brief a multi-frame animation that fades a lyrFrame in & out in steps
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] color - the color :^)
 * @param[in] color - number of steps between off & on
 */
void lyr_frame_fade_in_and_out(LyrFrame_TypeDef lyrFrame, uint64_t color, uint16_t stepSize);

/**
 * @brief fades in blu in steps and waits at each step
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] mask - the specific leds to perform the operation to
 * @param[in] maxBrightness - the brightness to stop fading in at
 * @param[in] deltaBrightness - step size
 * @param[in] delay - amount of time to stay at each step for
 **/
void lyr_frame_fade_in_blu(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay);

/**
 * @brief fades out blu in steps and waits at each step
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] mask - the specific leds to perform the operation to
 * @param[in] maxBrightness - the brightness to stop fading in at
 * @param[in] deltaBrightness - step size
 * @param[in] delay - amount of time to stay at each step for
 **/
void lyr_frame_fade_out_blu(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay);
