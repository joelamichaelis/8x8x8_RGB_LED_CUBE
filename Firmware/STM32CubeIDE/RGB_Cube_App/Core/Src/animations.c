/*
 * Array8x8Functions.c
 *
 *  Created on: Dec 6, 2020
 *      Author: Joel Michaelis
 */

#include "animations.h"

bool HALT_ANIMATION = false;
bool PAUSE_ANIMATION = false;

//------------------------------------Color Definition Begin-------------------------------------//
uint64_t null =				0x000000000000;
uint64_t red = 				0x0fff00000000;
uint64_t yellow = 		0x0fff0fff0000;
uint64_t green = 			0x00000fff0000;
uint64_t cyan = 			0x00000fff0fff;
uint64_t blue = 			0x000000000fff;
uint64_t purple = 		0x0fff00000fff;
uint64_t white = 			0x0fff0fff0fff;

uint64_t orange = 		0x0fff08000000;
uint64_t yelgrn = 		0x08000fff0000;
uint64_t seafoam = 		0x00000fff0800;
uint64_t lightblu = 	0x000008000fff;
uint64_t indigo = 		0x080000000fff;
uint64_t pink = 			0x0fff00000800;

uint64_t whiteRed = 	0x0fff08000800;
uint64_t whiteGrn = 	0x08000fff0800;
uint64_t whiteBlu = 	0x080008000fff;
//------------------------------------Color Definition End-------------------------------------//

//-------------------------------------------HIGH LEVEL "PUBLIC" ANIMATIONS BEGIN----------------------------------------------------//

void merry_christmas(Frame_TypeDef frame)
{
	uint16_t maxBrightness = 4000;
	uint16_t minBrightness = 0;
	uint16_t deltaBrightness = 10;
	uint16_t delay = 100;
	
	HALT_ANIMATION = false;
	
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
	
	while(HALT_ANIMATION == false)
	{
		//dissolve_in_color(frame.lyr0, mask0, green, maxBrightness, deltaBrightness, delay);
		//dissolve_out_color(frame.lyr0, mask0, green, minBrightness, deltaBrightness, delay);
	}
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
}

void original_fade(Frame_TypeDef frame)
{
	uint16_t maxBrightness = 4000;
	uint16_t minBrightness = 0;
	uint16_t deltaBrightness = 10;
	uint16_t delay = 40;
	uint16_t transitionDelay = 4;
	uint64_t colorWheel[12] = {red,orange,yellow,yelgrn,green,seafoam,cyan,lightblu,blue,indigo,purple,pink};	
	uint8_t directionA = DIRECTION_FORWARD;
	uint8_t directionB = DIRECTION_BACK;
	
	HALT_ANIMATION = false;
	
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
	
	while(HALT_ANIMATION == false)
	{
		int caseNum = 0;
		while (caseNum<12)
		{
			transition_punch(frame.lyr0,&mask0[0],colorWheel[caseNum],delay,directionA);	
			transition_punch(frame.lyr0,&mask0[0],null,delay,directionB);
			animation_delay(transitionDelay);
			caseNum++;
		
			transition_punch(frame.lyr0,&mask1[0],colorWheel[caseNum],delay,directionA);	
			transition_punch(frame.lyr0,&mask1[0],null,delay,directionB);
			//dissolve_in_color(frame.lyr0,mask1,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
			//dissolve_out_color(frame.lyr0,mask1,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
			animation_delay(transitionDelay);
			caseNum++;
			
			transition_punch(frame.lyr0,&mask2[0],colorWheel[caseNum],delay,directionA);	
			transition_punch(frame.lyr0,&mask2[0],null,delay,directionB);
			//dissolve_in_color(frame.lyr0,mask2,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
			//dissolve_out_color(frame.lyr0,mask2,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
			animation_delay(transitionDelay);
			caseNum++;
			
			transition_punch(frame.lyr0,&mask3[0],colorWheel[caseNum],delay,directionA);	
			transition_punch(frame.lyr0,&mask3[0],null,delay,directionB);
			//dissolve_in_color(frame.lyr0,mask3,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
			//dissolve_out_color(frame.lyr0,mask3,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
			animation_delay(transitionDelay);
			caseNum++;
			
			transition_punch(frame.lyr0,&mask2[0],colorWheel[caseNum],delay,directionA);	
			transition_punch(frame.lyr0,&mask2[0],null,delay,directionB);
			//dissolve_in_color(frame.lyr0,mask2,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
			//dissolve_out_color(frame.lyr0,mask2,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
			animation_delay(transitionDelay);
			caseNum++;
			
			transition_punch(frame.lyr0,&mask1[0],colorWheel[caseNum],delay,directionA);	
			transition_punch(frame.lyr0,&mask1[0],null,delay,directionB);
			//dissolve_in_color(frame.lyr0,mask1,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
			//dissolve_out_color(frame.lyr0,mask1,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
			animation_delay(transitionDelay);
			caseNum++;
		}
	}
	
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
}

void halloween(Frame_TypeDef frame)
{
	uint16_t maxBrightness = 2000;
	uint16_t minBrightness = 0;
	uint16_t deltaBrightness = 10;
	uint16_t delay = 10;
	uint16_t transitionDelay = 500;
	
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
	
	while(HALT_ANIMATION == false)
	{
		fade_in_color(frame.lyr0,maskChessBoardW,purple,maxBrightness,deltaBrightness,delay);
		fade_in_color(frame.lyr0,maskChessBoardB,orange,maxBrightness,deltaBrightness,delay);
		animation_delay(transitionDelay);
		fade_out_color(frame.lyr0,maskChessBoardW,purple,minBrightness,deltaBrightness,delay);			
		fade_out_color(frame.lyr0,maskChessBoardB,orange,minBrightness,deltaBrightness,delay);
		animation_delay(transitionDelay);
	}
	
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
}

void joel_mode(Frame_TypeDef frame)
{
	
	uint16_t maxBrightness = 2000;
	uint16_t minBrightness = 0;
	uint16_t deltaBrightness = 10;
	uint16_t delay = 10;
	uint16_t transitionDelay = 500;
	
	HALT_ANIMATION = false;
	
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
	
	while(HALT_ANIMATION == false)
	{
		fade_in_color(frame.lyr0,letterJ,blue,maxBrightness,deltaBrightness,delay);
		fade_out_color(frame.lyr0,letterJ,blue,minBrightness,deltaBrightness,delay);
		fade_in_color(frame.lyr0,letterO,blue,maxBrightness,deltaBrightness,delay);
		fade_out_color(frame.lyr0,letterO,blue,minBrightness,deltaBrightness,delay);
		fade_in_color(frame.lyr0,letterE,blue,maxBrightness,deltaBrightness,delay);
		fade_out_color(frame.lyr0,letterE,blue,minBrightness,deltaBrightness,delay);
		fade_in_color(frame.lyr0,letterL,blue,maxBrightness,deltaBrightness,delay);
		fade_out_color(frame.lyr0,letterL,blue,minBrightness,deltaBrightness,delay);
		HAL_Delay(transitionDelay);
	}
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
}


void sliding_cubes(Frame_TypeDef frame)
{
	uint64_t colorWheel[12] = {red,orange,yellow,yelgrn,green,seafoam,cyan,lightblu,blue,indigo,purple,pink};	
	int colorIndex = 0;
	uint16_t transitionDelay = 400;
	bool maskCube0189[64];
	bool_mask_copy(&maskCube0189[0],&maskEmpty[0]);
	maskCube0189[0] = 1;
	maskCube0189[1] = 1;
	maskCube0189[8] = 1;
	maskCube0189[9] = 1;
	//maskCube0189[58] = 0;
	HALT_ANIMATION = false;
	PAUSE_ANIMATION = false;
	lyr_frame_clear_all(frame.lyr0);
	
	while(HALT_ANIMATION == false)
	{
		if(HALT_ANIMATION == true) break;
		
		lyr_frame_set_color(frame.lyr0,colorWheel[colorIndex],maskCube0189);
		colorIndex++;
		if(colorIndex==12) colorIndex=0;
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		animation_delay(transitionDelay);
		
		if(HALT_ANIMATION == true) break;
		for(int repIndex=0;repIndex<3;repIndex++)
		{
			lyr_frame_shift_column(frame0.lyr0, 0, DIRECTION_FORWARD);
			lyr_frame_shift_column(frame0.lyr0, 0, DIRECTION_FORWARD);
			lyr_frame_shift_column(frame0.lyr0, 1, DIRECTION_FORWARD);
			lyr_frame_shift_column(frame0.lyr0, 1, DIRECTION_FORWARD);
			lyr_frame_convert(frame0.lyr0,data16Ptr);
			UPDATE_FRAME=1;
			animation_delay(transitionDelay);
			if(HALT_ANIMATION == true) break;
		}
		
		if(HALT_ANIMATION == true) break;
		lyr_frame_set_color(frame.lyr0,colorWheel[colorIndex],maskCube0189);
		colorIndex++;
		if(colorIndex==12) colorIndex=0;
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		animation_delay(transitionDelay);		
		
		if(HALT_ANIMATION == true) break;
		for(int repIndex=0;repIndex<3;repIndex++)
		{
			lyr_frame_shift_row(frame0.lyr0, 6, DIRECTION_RIGHT);
			lyr_frame_shift_row(frame0.lyr0, 6, DIRECTION_RIGHT);
			lyr_frame_shift_row(frame0.lyr0, 7, DIRECTION_RIGHT);
			lyr_frame_shift_row(frame0.lyr0, 7, DIRECTION_RIGHT);
			lyr_frame_shift_column(frame0.lyr0, 0, DIRECTION_FORWARD);
			lyr_frame_shift_column(frame0.lyr0, 0, DIRECTION_FORWARD);
			lyr_frame_shift_column(frame0.lyr0, 1, DIRECTION_FORWARD);
			lyr_frame_shift_column(frame0.lyr0, 1, DIRECTION_FORWARD);
			lyr_frame_convert(frame0.lyr0,data16Ptr);
			UPDATE_FRAME=1;
			animation_delay(transitionDelay);
			if(HALT_ANIMATION == true) break;
		}
		
		if(HALT_ANIMATION == true) break;
		lyr_frame_set_color(frame.lyr0,colorWheel[colorIndex],maskCube0189);
		colorIndex++;
		if(colorIndex==12) colorIndex=0;
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		animation_delay(transitionDelay);	

		
		for(int repIndex=0;repIndex<3;repIndex++)
		{
			if(HALT_ANIMATION == true) break;
			lyr_frame_shift_column(frame0.lyr0, 6, DIRECTION_BACK);
			lyr_frame_shift_column(frame0.lyr0, 6, DIRECTION_BACK);
			lyr_frame_shift_column(frame0.lyr0, 7, DIRECTION_BACK);
			lyr_frame_shift_column(frame0.lyr0, 7, DIRECTION_BACK);
			lyr_frame_shift_row(frame0.lyr0, 6, DIRECTION_RIGHT);
			lyr_frame_shift_row(frame0.lyr0, 6, DIRECTION_RIGHT);
			lyr_frame_shift_row(frame0.lyr0, 7, DIRECTION_RIGHT);
			lyr_frame_shift_row(frame0.lyr0, 7, DIRECTION_RIGHT);
			lyr_frame_shift_column(frame0.lyr0, 0, DIRECTION_FORWARD);
			lyr_frame_shift_column(frame0.lyr0, 0, DIRECTION_FORWARD);
			lyr_frame_shift_column(frame0.lyr0, 1, DIRECTION_FORWARD);
			lyr_frame_shift_column(frame0.lyr0, 1, DIRECTION_FORWARD);
			lyr_frame_convert(frame0.lyr0,data16Ptr);
			lyr_frame_convert(frame0.lyr0,data16Ptr);
			UPDATE_FRAME=1;
			animation_delay(transitionDelay);
		}	
		
		if(HALT_ANIMATION == true) break;
		lyr_frame_set_color(frame.lyr0,colorWheel[colorIndex],maskCube0189);
		colorIndex++;
		if(colorIndex==12) colorIndex=0;
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		animation_delay(transitionDelay);	
		
		if(HALT_ANIMATION == true) break;
		lyr_frame_shift_row(frame0.lyr0, 0, DIRECTION_INWARD);
		lyr_frame_shift_row(frame0.lyr0, 1, DIRECTION_INWARD);
		lyr_frame_shift_row(frame0.lyr0, 2, DIRECTION_INWARD);
		lyr_frame_shift_row(frame0.lyr0, 3, DIRECTION_INWARD);
		lyr_frame_shift_row(frame0.lyr0, 4, DIRECTION_INWARD);
		lyr_frame_shift_row(frame0.lyr0, 5, DIRECTION_INWARD);
		lyr_frame_shift_row(frame0.lyr0, 6, DIRECTION_INWARD);
		lyr_frame_shift_row(frame0.lyr0, 7, DIRECTION_INWARD);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		animation_delay(2*transitionDelay);	
		
		if(HALT_ANIMATION == true) break;
		lyr_frame_shift_column(frame0.lyr0, 0, DIRECTION_INWARD);
		lyr_frame_shift_column(frame0.lyr0, 1, DIRECTION_INWARD);
		lyr_frame_shift_column(frame0.lyr0, 2, DIRECTION_INWARD);
		lyr_frame_shift_column(frame0.lyr0, 3, DIRECTION_INWARD);
		lyr_frame_shift_column(frame0.lyr0, 4, DIRECTION_INWARD);
		lyr_frame_shift_column(frame0.lyr0, 5, DIRECTION_INWARD);
		lyr_frame_shift_column(frame0.lyr0, 6, DIRECTION_INWARD);
		lyr_frame_shift_column(frame0.lyr0, 7, DIRECTION_INWARD);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		animation_delay(2*transitionDelay);	
		
		if(HALT_ANIMATION == true) break;
		lyr_frame_shift_row(frame0.lyr0, 0, DIRECTION_INWARD);
		lyr_frame_shift_row(frame0.lyr0, 1, DIRECTION_INWARD);
		lyr_frame_shift_row(frame0.lyr0, 2, DIRECTION_INWARD);
		lyr_frame_shift_row(frame0.lyr0, 3, DIRECTION_INWARD);
		lyr_frame_shift_row(frame0.lyr0, 4, DIRECTION_INWARD);
		lyr_frame_shift_row(frame0.lyr0, 5, DIRECTION_INWARD);
		lyr_frame_shift_row(frame0.lyr0, 6, DIRECTION_INWARD);
		lyr_frame_shift_row(frame0.lyr0, 7, DIRECTION_INWARD);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		animation_delay(2*transitionDelay);	
		
		if(HALT_ANIMATION == true) break;
		lyr_frame_shift_column(frame0.lyr0, 0, DIRECTION_INWARD);
		lyr_frame_shift_column(frame0.lyr0, 1, DIRECTION_INWARD);
		lyr_frame_shift_column(frame0.lyr0, 2, DIRECTION_INWARD);
		lyr_frame_shift_column(frame0.lyr0, 3, DIRECTION_INWARD);
		lyr_frame_shift_column(frame0.lyr0, 4, DIRECTION_INWARD);
		lyr_frame_shift_column(frame0.lyr0, 5, DIRECTION_INWARD);
		lyr_frame_shift_column(frame0.lyr0, 6, DIRECTION_INWARD);
		lyr_frame_shift_column(frame0.lyr0, 7, DIRECTION_INWARD);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		animation_delay(2*transitionDelay);	
		
	}
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
}

void stretchy_cube(Frame_TypeDef frame)
{
	lyr_frame_clear_all(frame.lyr0);
	
	uint16_t delay = 250;
	uint64_t randColor = 0;
	uint16_t randBrightnessValue = 0;
	uint8_t randRgbChoice = 0;
	uint8_t startPt = 0;
	
	startPt = rand_32bit_modulus(rngCount, 3);
	randRgbChoice = rand_32bit_modulus(rngCount, 2);
	randBrightnessValue = rand_32bit_modulus(rngCount, 4095);
	randColor = modify_color_single_rgb_value(randColor, randBrightnessValue, randRgbChoice);
	
	
	//if (startPt == 0) startPt = 0;
	if (startPt == 1) startPt = 7;
	if (startPt == 2) startPt = 56;
	if (startPt == 3) startPt = 63;
	
	while(HALT_ANIMATION == false)
	{				
		animation_stretch_out(frame.lyr0, randColor, startPt, delay);
		
		startPt = rand_32bit_modulus(rngCount, 3);
		randRgbChoice = rand_32bit_modulus(rngCount, 2);
		randBrightnessValue = rand_32bit_modulus(rngCount, 4095);
		randColor = modify_color_single_rgb_value(randColor, randBrightnessValue, randRgbChoice);
		
		//if (startPt = 0) startPt = 0;
		if (startPt == 1) startPt = 7;
		if (startPt == 2) startPt = 56;
		if (startPt == 3) startPt = 63;
				
		animation_stretch_in(frame.lyr0, startPt, delay); // still need to implement this
	}
}

//-------------------------------------------HIGH LEVEL "PUBLIC" ANIMATIONS END----------------------------------------------------//

//----------------------------------------- "PRIVATE" SUB-ANIMATION FUNCTIONS BEGIN----------------------------------------------------//

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
void transition_punch(LyrFrame_TypeDef lyrFrame, bool *maskPtr, uint64_t color, uint16_t delay, uint8_t direction)
{
		
	if(direction == DIRECTION_FORWARD)
	{
		for(uint8_t tempIndex=0;tempIndex<BOOL_MASK_LENGTH;tempIndex++)
		{
			if(*(maskPtr + tempIndex) == 1)
			{
				lyr_frame_set_single_color(lyrFrame,color,tempIndex);
				lyr_frame_convert(frame0.lyr0,data16Ptr);
				UPDATE_FRAME=1;
				animation_delay(delay);
				if(HALT_ANIMATION == true) break;
			}
		}
	}
	
	if(direction == DIRECTION_BACK)
	{
		for(uint8_t tempIndex=BOOL_MASK_LENGTH;tempIndex>0;tempIndex--)
		{
			if(*(maskPtr + tempIndex-1) == 1)
			{
				lyr_frame_set_single_color(lyrFrame,color,tempIndex-1);
				lyr_frame_convert(frame0.lyr0,data16Ptr);
				UPDATE_FRAME=1;
				animation_delay(delay);
				if(HALT_ANIMATION == true) break;
			}
		}
	}
	
}

void dissolve_color(LyrFrame_TypeDef lyrFrame, bool mask[64], uint64_t color, uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay)
{
	int tempIndex = 0;	
	for (tempIndex=0;tempIndex<BOOL_MASK_LENGTH;tempIndex++)
	{
		if (mask[tempIndex] == 1)
		{
			lyr_frame_set_single_color(lyrFrame,0,tempIndex);
			lyr_frame_convert(frame0.lyr0,data16Ptr);
			UPDATE_FRAME=1;
			animation_delay(delay);
			if(HALT_ANIMATION == true) break;
		}
	}
}

void fade_in_color(LyrFrame_TypeDef lyrFrame, bool mask[64], uint64_t color, uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay)
{	
	int16_t redBrightness = (color>>32);
	int16_t grnBrightness = (color>>16);
	int16_t bluBrightness = (color>>0);
	int16_t redDeltaBrightness = 0x0000;
	int16_t grnDeltaBrightness = 0x0000;
	int16_t bluDeltaBrightness = 0x0000;
	int16_t currentBrightness = 0; //hopefully since its signed there's no negative number hard fault.
	
	if (redBrightness >= 4000)
	{
		redBrightness = 0;
		redDeltaBrightness = deltaBrightness;
	}
	
	if ((redBrightness < 4000) & (redBrightness > 0)) 
	{
		redBrightness = 0;
		redDeltaBrightness = (deltaBrightness/2);
	}
	
	
	if (grnBrightness >= 4000)
	{
		grnBrightness = 0;
		grnDeltaBrightness = deltaBrightness;
	}
	
	if ((grnBrightness < 4000) & (grnBrightness > 0)) 
	{
		grnBrightness = 0;
		grnDeltaBrightness = (deltaBrightness/2);
	}	
	
	if (bluBrightness >= 4000)
	{
		bluBrightness = 0;
		bluDeltaBrightness = deltaBrightness;
	}
	
	if ((bluBrightness < 4000) & (bluBrightness > 0)) 
	{
		bluBrightness = 0;
		bluDeltaBrightness = (deltaBrightness/2);
	}
		
	while (currentBrightness <= maxBrightness)
	{
		if(HALT_ANIMATION == true) break;
		lyr_frame_set_single_rgb(lyrFrame.redArrPtr, redBrightness, mask);
		lyr_frame_set_single_rgb(lyrFrame.grnArrPtr, grnBrightness, mask);
		lyr_frame_set_single_rgb(lyrFrame.bluArrPtr, bluBrightness, mask);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		animation_delay(delay);
		currentBrightness = currentBrightness + deltaBrightness;
		redBrightness = redBrightness + redDeltaBrightness;
		grnBrightness = grnBrightness + grnDeltaBrightness;
		bluBrightness = bluBrightness + bluDeltaBrightness;
	}
}

void fade_out_color(LyrFrame_TypeDef lyrFrame, bool mask[64], uint64_t color, uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay)
{
	int16_t redBrightness = (color>>32);
	int16_t grnBrightness = (color>>16);
	int16_t bluBrightness = (color>>0);
	int16_t redDeltaBrightness = 0x0000;
	int16_t grnDeltaBrightness = 0x0000;
	int16_t bluDeltaBrightness = 0x0000;
	int16_t currentBrightness = 4000; //hopefully since its signed there's no negative number hard fault.
	
	if (redBrightness >= 4000)
	{
		redBrightness = 4000;
		redDeltaBrightness = deltaBrightness;
	}
	
	if ((redBrightness < 4000) & (redBrightness > 0)) 
	{
		redBrightness = 2000;
		redDeltaBrightness = (deltaBrightness/2);
	}
	
	
	if (grnBrightness >= 4000)
	{
		grnBrightness = 4000;
		grnDeltaBrightness = deltaBrightness;
	}
	
	if ((grnBrightness < 4000) & (grnBrightness > 0)) 
	{
		grnBrightness = 2000;
		grnDeltaBrightness = (deltaBrightness/2);
	}	
	
	if (bluBrightness >= 4000)
	{
		bluBrightness = 4000;
		bluDeltaBrightness = deltaBrightness;
	}
	
	if ((bluBrightness < 4000) & (bluBrightness > 0)) 
	{
		bluBrightness = 2000;
		bluDeltaBrightness = (deltaBrightness/2);
	}
	
	while (currentBrightness >= minBrightness)
	{
		if(HALT_ANIMATION == true) break;
		lyr_frame_set_single_rgb(lyrFrame.redArrPtr, redBrightness, mask);
		lyr_frame_set_single_rgb(lyrFrame.grnArrPtr, grnBrightness, mask);
		lyr_frame_set_single_rgb(lyrFrame.bluArrPtr, bluBrightness, mask);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		animation_delay(delay);
		currentBrightness = currentBrightness - deltaBrightness;
		redBrightness = redBrightness - redDeltaBrightness;
		grnBrightness = grnBrightness - grnDeltaBrightness;
		bluBrightness = bluBrightness - bluDeltaBrightness;
	}
}

/**
 * @brief starts as an 8x8 square outline. The square then collapses into the stopPt corner.
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] stopPt - the corner which the 8x8 square outline collapses into
 * @param[in] delay - length of time in ms to wait inbetween punches
 */
void animation_stretch_in(LyrFrame_TypeDef lyrFrame, int stopPt, uint16_t delay)
{

}

/**
 * @brief starts from a single corner of the 8x8 array. This corner then "stretches out" or expands out diagonally while retaining 
					a square shape. The initial corner remains fixed until the opposite corner is reached.
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] startPt - the initial corner
 * @param[in] delay - length of time in ms to wait inbetween punches
 */
void animation_stretch_out(LyrFrame_TypeDef lyrFrame, uint64_t color, int startPt, uint16_t delay)
{
	if ((startPt != 0)&(startPt != 7)&(startPt != 56)&(startPt != 63)) return;
	
	lyr_frame_clear_all(lyrFrame);
	
	int stopPt = startPt;
	int limitPt = 0;
	int ptStepSize = 0;
	
	if ((startPt == 0)|(startPt == 7))
	{
		if (startPt == 0) // rear left of array
		{
			limitPt = 63; //front right of array
			ptStepSize = 9;
		}
	
		if (startPt == 7) //rear right of array
		{
			limitPt = 56; //front left of array
			ptStepSize = 7;
		}
	
		while(stopPt<=limitPt)
		{
			stopPt+=ptStepSize;
			lyr_frame_clear_all(lyrFrame);
			lyrframe_set_square(lyrFrame, color, startPt, stopPt);
			lyr_frame_convert(frame0.lyr0,data16Ptr);
			UPDATE_FRAME = 1;
			animation_delay(delay);
		}
	}
	
	if ((startPt == 56) | (startPt == 63))
	{
		if (startPt == 56) // front left of array
		{
			limitPt = 7; //front left of array
			ptStepSize = 7;
		}
	
		if (startPt == 63)
		{
			limitPt = 0; //front left of array
			ptStepSize = 9;
		}
		
		while(stopPt>=limitPt)
		{
			stopPt-=ptStepSize;
			lyr_frame_clear_all(lyrFrame);
			lyrframe_set_square(lyrFrame, color, startPt, stopPt);
			lyr_frame_convert(frame0.lyr0,data16Ptr);
			UPDATE_FRAME = 1;
			animation_delay(delay);	
		}
	}
}

/**
 * @brief clears the specified lyrframe by sliding its existing values out in the specified direction
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * @param[in] delay - length of time in ms to wait inbetween punches
 */
void transition_slide_out (LyrFrame_TypeDef lyrframe, uint8_t direction, uint16_t delay)
{
	for(uint8_t reps=0;reps<8;reps++)
	{
		lyr_frame_shift(lyrframe, direction);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME = 1;
		animation_delay(delay);
	}	
}

/**
 * @brief sets the specified lyrframe to the given mask-color pair by sliding it in from the specified direction
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] maskPtr - points to the first element of the boolMask which indicates what LEDs to set
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 * @param[in] delay - length of time in ms to wait inbetween punches
 */
void transition_slide_in (LyrFrame_TypeDef lyrframe, bool *maskPtr, uint64_t color, uint8_t direction, uint16_t delay)
{

	if(direction==DIRECTION_RIGHT)
	{	
		//proposed function to copy & paste row:
		//lyrframe_set_row(LyrFrame_Typedef lyrframe, uint8_t rowNum, bool *maskPtr);
		
		//set lyrframe's col0 to mask's col7
		//delay, update
		
		//shift lyrframe right
		//set lyrframe's col0 to mask's col6
		//delay, update
		
		//shift lyrframe right
		//set lyrframe's col0 to mask's col5
		//delay, update
		
		//shift lyrframe right
		//set lyrframe's col0 to mask's col4
		//delay, update
		
		//shift lyrframe right
		//set lyrframe's col0 to mask's col3
		//delay, update
		
		//shift lyrframe right
		//set lyrframe's col0 to mask's col2
		//delay, update
		
		//shift lyrframe right
		//set lyrframe's col0 to mask's col1
		//delay, update
		
		//shift lyrframe right
		//set lyrframe's col0 to mask's col0
		//delay, update
	}
}

//----------------------------------------- "PRIVATE" SUB-ANIMATION FUNCTIONS END----------------------------------------------------//

//----------------------------------------- UTILITY FUNCTIONS BEGIN----------------------------------------------------//

/**
 * @brief a wrapper for HAL_Delay(delay) but also enables play/pause functionality
 * @param[in] delay - length of time in ms to wait
 */
void animation_delay(uint32_t delay)
{
	HAL_Delay(delay);
	while(PAUSE_ANIMATION == true)
	{
		 HAL_Delay(delay);
	}
}

/**
 * @brief receives a color and overwrites either the red, grn, or blue portion of said color to rgbValue depending on the value of rgbChoice
 * @param[in] initialColor - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] rgbValue - the value that will be overwrite either the red, grn, or blue brightness. should be pseudo 12-bit (bounded between 0 & 4095)
 * @param[in] rgbChoice - should be bounded between 0 & 2 where: 0 -> red, 1 -> grn, 2 -> blu
 * @return[out] the resulting color with one of its R/G/B values changed 
 */
uint64_t modify_color_single_rgb_value(uint64_t initialColor, uint16_t rgbValue, uint8_t rgbCoice)
{
	//need to look at this in debug mode to ensure the logic makes sense for recombining the individual brightnesses
	uint64_t redBrightness = 0;
	uint64_t grnBrightness = 0;
	uint64_t bluBrightness = 0;
	
	redBrightness = (0x0000000000001111 && (initialColor>>32));
	grnBrightness = (0x0000000000001111 && (initialColor>>16));
	bluBrightness = (0x0000000000001111 && (initialColor>>0));
	
	if(rgbCoice == 0) redBrightness = rgbValue;
	if(rgbCoice == 1) grnBrightness = rgbValue;
	if(rgbCoice == 2) bluBrightness = rgbValue;
	
	initialColor = (0x0000000000001111 && redBrightness);
	initialColor = ((initialColor<<16) && grnBrightness);
	initialColor = ((initialColor<<16) && bluBrightness);
		
	return initialColor;	
}

//----------------------------------------- UTILITY FUNCTIONS END----------------------------------------------------//
