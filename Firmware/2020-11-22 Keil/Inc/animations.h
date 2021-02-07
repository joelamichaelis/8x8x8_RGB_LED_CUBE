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
void configurable_text(Frame_TypeDef frame);
void original_fade(Frame_TypeDef frame0);
void halloween(Frame_TypeDef frame);
void joel_mode(Frame_TypeDef frame);
void strobe(Frame_TypeDef frame0);
void sliding_cubes(Frame_TypeDef frame0);
void stretchy_cube(Frame_TypeDef frame);

//-------------------------------------------HIGH LEVEL "PUBLIC" ANIMATIONS END----------------------------------------------------//

//----------------------------------------- "PRIVATE" SUB-ANIMATION FUNCTIONS BEGIN----------------------------------------------------//


//---------------------------------------------TRANSITIONS BEGIN----------------------------------------------------------------------//
/**
 * @brief gradually increases or decreases the intensity of the specified boolMask-color pair brightness
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] maskPtr - points to the boolMask being referenced
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] minMaxBrightness - the final brightness value
 * @param[in] deltaBrightness - dictates number of steps
 * @param[in] delay - length of time in ms to wait inbetween
 * @param[in] increaseNdecrease - true increases brightness, false decreases brightness
 */
void transition_fade(LyrFrame_TypeDef lyrFrame, bool *maskPtr, uint64_t color, uint16_t minMaxBrightness, uint16_t deltaBrightness, uint16_t delay, bool increaseNdecrease);

/**
 * @brief one at a time, "punches" in or out LEDs of a given bool mask. 
					"punch out" can be done by setting the color to blank.
					"punch in" can be done by setting to color to whatever is desired.
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] maskPtr - points to the boolMask being referenced
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] delay - length of time in ms to wait inbetween
 * @param[in] punchDirection - currently supports forward and back only. this a quick & easy way to support different punching directions
 * example usage: transition_punch(frame1.lyr0, &mask3[0], white, 27, DIRECTION_FORWARD);
 */
void transition_punch(LyrFrame_TypeDef lyrFrame, bool *maskPtr, uint64_t color, uint16_t delay, uint8_t punchDirection);

/**
 * @brief a combination of punch and fade; each "punch" is individually faded in sequence
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] maskPtr - points to the boolMask being referenced
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] minMaxBrightness - the final brightness value
 * @param[in] deltaBrightness - dictates number of steps
 * @param[in] delay - length of time in ms to wait inbetween
 * @param[in] punchDirection - currently supports forward and back only. this a quick & easy way to support different punching directions
 * @param[in] increaseNdecrease - true increases brightness, false decreases brightness
 */
void transition_punch_fade(LyrFrame_TypeDef lyrFrame, bool *maskPtr, uint64_t color, uint16_t minMaxBrightness, uint16_t deltaBrightness, uint16_t delay, bool increaseNdecrease, uint8_t punchDirection);

//---------------------------------------------TRANSITIONS END-------------------------------------------------------------------------//

//---------------------------------------------SUBANIMATIONS BEGIN-------------------------------------------------------------------------//
/**
 * @brief starts as an 8x8 square outline. The square then retracts into the stopPt corner.
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] stopPt - the corner which the 8x8 square outline collapses into
 * @param[in] delay - length of time in ms to wait inbetween punches
 */
void subanimation_stretch_retract(LyrFrame_TypeDef lyrFrame, int stopPt, uint16_t delay);

/**
 * @brief starts from a single corner of the 8x8 array. This corner then expands out diagonally while retaining 
					a square shape. The initial corner remains fixed until the opposite corner is reached.
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] startPt - the initial corner
 * @param[in] delay - length of time in ms to wait inbetween punches
 */
void subanimation_stretch_expand(LyrFrame_TypeDef lyrFrame, uint64_t color, int startPt, uint16_t delay);


/**
 * @brief flashes the lyrFrame on and off rapidly
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] maskPtr - points to the boolMask being referenced
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] strobeDelay - the amount of time to wait in ms between flashes
 */
void subanimation_strobe(LyrFrame_TypeDef lyrFrame, bool *maskPtr, uint64_t color, uint16_t strobeDelay);

//---------------------------------------------SUBANIMATIONS END----------------------------------------------------------------//

//----------------------------------------- "PRIVATE" SUB-ANIMATION FUNCTIONS END-------------------------------------------------------//

//----------------------------------------- UTILITY FUNCTIONS BEGIN----------------------------------------------------//

/**
 * @brief a wrapper for HAL_Delay(delay) but also enables play/pause functionality
 * @param[in] delay - length of time in ms to wait
 */
void animation_delay(uint32_t delay);

/**
 * @brief receives a color and overwrites either the red, grn, or blue portion of said color to rgbValue depending on the value of rgbChoice
 * @param[in] initialColor - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] rgbValue - the value that will be overwrite either the red, grn, or blue brightness. should be pseudo 12-bit (bounded between 0 & 4095)
 * @param[in] rgbChoice - should be bounded between 0 & 2 where: 0 -> red, 1 -> grn, 2 -> blu
 * @return[out] the resulting color with one of its R/G/B values changed 
 */
uint64_t modify_color_single_rgb_value(uint64_t initialColor, uint16_t rgbValue, uint8_t rgbCoice);

//----------------------------------------- UTILITY FUNCTIONS END----------------------------------------------------//

#endif
