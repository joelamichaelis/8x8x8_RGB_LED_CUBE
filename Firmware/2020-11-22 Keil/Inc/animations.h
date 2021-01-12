/*
 * Array8x8Functions.h
 *
 *  Created on: Dec 6, 2020
 *      Author: Joel Michaelis
 */

#ifndef ANIMATIONS_H_
#define ANIMATIONS_H_

#include "bool_mask.h"
#include "frame.h"
#include "stm32f1xx_hal.h"

extern bool UPDATE_FRAME; 		//declared in main.c but needs visibility into animations.c
extern bool HALT_ANIMATION;
extern bool PAUSE_ANIMATION;
extern uint16_t *data16Ptr;		//declared in main.c but needs visibility into animations.c
extern Frame_TypeDef frame0;	//declared in main.c but needs visibility into animations.c

//-------------------------------------------HIGH LEVEL "PUBLIC" ANIMATIONS BEGIN----------------------------------------------------//

void original_fade(Frame_TypeDef frame0);
void halloween(Frame_TypeDef frame);
void joel_mode(Frame_TypeDef frame);
void merry_christmas(Frame_TypeDef frame0);
void sliding_cubes(Frame_TypeDef frame0);
void stretchy_cube(Frame_TypeDef frame);

//-------------------------------------------HIGH LEVEL "PUBLIC" ANIMATIONS END----------------------------------------------------//

//----------------------------------------- "PRIVATE" SUB-ANIMATION FUNCTIONS BEGIN----------------------------------------------------//

void fade_in_color(LyrFrame_TypeDef lyrFrame, bool mask[64], uint64_t color, uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_out_color(LyrFrame_TypeDef lyrFrame, bool mask[64], uint64_t color, uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay);

/**
 * @brief one at a time, "punches" in or out LEDs of a given bool mask. 
					"punch out" can be done by setting the color to blank.
					"punch in" can be done by setting to color to whatever is desired.
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] maskPtr - points to the boolMask being referenced for the punch pattern
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] delay - length of time in ms to wait inbetween punches
 * @param[in] direction - currently supports forward and back only. this a quick & easy way to support different punching directions
 * example usage: transition_punch(frame1.lyr0, &mask3[0], white, 27, DIRECTION_FORWARD);
 */
void transition_punch(LyrFrame_TypeDef lyrFrame, bool *maskPtr, uint64_t color, uint16_t delay, uint8_t direction);

void dissolve_color(LyrFrame_TypeDef lyrFrame, bool mask[64], uint64_t color, uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay);

/**
 * @brief starts as an 8x8 square outline. The square then collapses into the stopPt corner.
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] stopPt - the corner which the 8x8 square outline collapses into
 * @param[in] delay - length of time in ms to wait inbetween punches
 */
void animation_stretch_in(LyrFrame_TypeDef lyrFrame, int stopPt, uint16_t delay);

/**
 * @brief starts from a single corner of the 8x8 array. This corner then "stretches out" or expands out diagonally while retaining 
					a square shape. The initial corner remains fixed until the opposite corner is reached.
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] startPt - the initial corner
 * @param[in] delay - length of time in ms to wait inbetween punches
 */
void animation_stretch_out(LyrFrame_TypeDef lyrFrame, uint64_t color, int startPt, uint16_t delay);

/**
 * @brief clears the specified lyrframe by sliding its existing values out in the specified direction
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * @param[in] delay - length of time in ms to wait inbetween punches
 */
void transition_slide_out (LyrFrame_TypeDef lyrframe, uint8_t direction, uint16_t delay);


/**
 * @brief sets the specified lyrframe to the given mask-color pair by sliding it in from the specified direction
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] maskPtr - points to the first element of the boolMask which indicates what LEDs to set
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * @param[in] delay - length of time in ms to wait inbetween punches
 */
void transition_slide_in (LyrFrame_TypeDef lyrframe, bool *maskPtr, uint64_t color, uint8_t direction, uint16_t delay);

//----------------------------------------- "PRIVATE" SUB-ANIMATION FUNCTIONS END----------------------------------------------------//

//----------------------------------------- UTILITY FUNCTIONS BEGIN----------------------------------------------------//

/**
 * @brief a wrapper for HAL_Delay(delay) but also enables play/pause functionality
 * @param[in] delay - length of time in ms to wait
 */
void animation_delay(uint32_t delay);

//----------------------------------------- UTILITY FUNCTIONS END----------------------------------------------------//

#endif
