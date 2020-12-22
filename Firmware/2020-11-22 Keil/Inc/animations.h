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
extern uint16_t *data16Ptr;		//declared in main.c but needs visibility into animations.c
extern Frame_TypeDef frame0;	//declared in main.c but needs visibility into animations.c

void fade_in_color(LyrFrame_TypeDef lyrFrame, bool mask[64], uint64_t color, uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_out_color(LyrFrame_TypeDef lyrFrame, bool mask[64], uint64_t color, uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_in_red(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_in_grn(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_in_blu(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_out_red(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_out_grn(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_out_blu(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay);

void dissolve_in_color(LyrFrame_TypeDef lyrFrame, bool mask[64], uint64_t color, uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay);
void dissolve_out_color(LyrFrame_TypeDef lyrFrame, bool mask[64], uint64_t color, uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay);


// decides which specific animation to play based off its assigned number
extern void Animation_LUT(int animationNumber);

void original_fade(Frame_TypeDef frame0);
void halloween(Frame_TypeDef frame);
void joel_mode(Frame_TypeDef frame);
void merry_christmas(Frame_TypeDef frame0);

#endif
