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

void configurable_text(Frame_TypeDef frame)
{
		
	uint16_t maxBrightness = 2000;
	uint16_t minBrightness = 0;
	uint16_t deltaBrightness = 10;
	uint16_t delay = 10;
	uint16_t transitionDelay = 500;
	
	bool tempBoolMask[64];
	
	
	HALT_ANIMATION = false;
	
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
	uint8_t alphabetIndex=0;
	
	uint64_t alphabetArr [26] = { maskEncLetterA, maskEncLetterB, maskEncLetterC, maskEncLetterD, maskEncLetterE, maskEncLetterF, 
																maskEncLetterG, maskEncLetterH, maskEncLetterI, maskEncLetterJ, maskEncLetterK, maskEncLetterL, 
																maskEncLetterM, maskEncLetterN, maskEncLetterO, maskEncLetterP, maskEncLetterQ, maskEncLetterR, 
																maskEncLetterS, maskEncLetterT, maskEncLetterU, maskEncLetterV, maskEncLetterW, maskEncLetterX, 
																maskEncLetterY, maskEncLetterZ};
	
																
	while(HALT_ANIMATION == false)
	{
		bool_mask_decode(&tempBoolMask[0],alphabetArr[alphabetIndex]);
		
		transition_fade(frame.lyr0,&tempBoolMask[0],blue,maxBrightness,deltaBrightness,delay,true);
		transition_fade(frame.lyr0,&tempBoolMask[0],blue,minBrightness,deltaBrightness,delay,false);
		alphabetIndex++;
		if(alphabetIndex==26) alphabetIndex=0;	
		HAL_Delay(transitionDelay);
	}
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
}

void strobe(Frame_TypeDef frame)
{
	//uint16_t maxBrightness = 4000;
	uint16_t delay = 150;
	
	HALT_ANIMATION = false;
	
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
	

	while(HALT_ANIMATION == false)
	{
		subanimation_strobe(frame.lyr0, &maskAll[0], red, delay);
		subanimation_strobe(frame.lyr0, &maskAll[0], white, delay);
		subanimation_strobe(frame.lyr0, &maskAll[0], blue, delay);
	}
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
}

void original_fade(Frame_TypeDef frame)
{
	//uint16_t maxBrightness = 4000;
	//uint16_t minBrightness = 0;
	//uint16_t deltaBrightness = 10;
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
			animation_delay(transitionDelay);
			caseNum++;
			
			transition_punch(frame.lyr0,&mask2[0],colorWheel[caseNum],delay,directionA);	
			transition_punch(frame.lyr0,&mask2[0],null,delay,directionB);
			animation_delay(transitionDelay);
			caseNum++;
			
			transition_punch(frame.lyr0,&mask3[0],colorWheel[caseNum],delay,directionA);	
			transition_punch(frame.lyr0,&mask3[0],null,delay,directionB);
			animation_delay(transitionDelay);
			caseNum++;
			
			transition_punch(frame.lyr0,&mask2[0],colorWheel[caseNum],delay,directionA);	
			transition_punch(frame.lyr0,&mask2[0],null,delay,directionB);
			animation_delay(transitionDelay);
			caseNum++;
			
			transition_punch(frame.lyr0,&mask1[0],colorWheel[caseNum],delay,directionA);	
			transition_punch(frame.lyr0,&mask1[0],null,delay,directionB);
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
	
	HALT_ANIMATION = false;
	
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
	
	while(HALT_ANIMATION == false)
	{
		
		transition_fade(frame.lyr0,&maskChessBoardW[0],purple,maxBrightness,deltaBrightness,delay,true);
		transition_fade(frame.lyr0,&maskChessBoardB[0],orange,maxBrightness,deltaBrightness,delay,true);
		//fade_in_color(frame.lyr0,maskChessBoardW,purple,maxBrightness,deltaBrightness,delay);
		//fade_in_color(frame.lyr0,maskChessBoardB,orange,maxBrightness,deltaBrightness,delay);
		animation_delay(transitionDelay);
		
		transition_fade(frame.lyr0,&maskChessBoardW[0],purple,minBrightness,deltaBrightness,delay,false);
		transition_fade(frame.lyr0,&maskChessBoardB[0],orange,minBrightness,deltaBrightness,delay,false);
		//fade_out_color(frame.lyr0,maskChessBoardW,purple,minBrightness,deltaBrightness,delay);			
		//fade_out_color(frame.lyr0,maskChessBoardB,orange,minBrightness,deltaBrightness,delay);
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
	
	bool tempBoolMask[64];
	
	HALT_ANIMATION = false;
	
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;
	
	uint8_t joelIndex = 0;
	uint64_t joelArr[4] = {maskEncLetterJ, maskEncLetterO, maskEncLetterE, maskEncLetterL}; 
	
	while(HALT_ANIMATION == false)
	{
		bool_mask_decode(&tempBoolMask[0],joelArr[joelIndex]);
		transition_fade(frame.lyr0,&tempBoolMask[0],blue,maxBrightness,deltaBrightness,delay,true);		
		transition_fade(frame.lyr0,&tempBoolMask[0],blue,minBrightness,deltaBrightness,delay,false);
		//fade_in_color(frame.lyr0,&tempBoolMask[0],blue,maxBrightness,deltaBrightness,delay);
		//fade_out_color(frame.lyr0,&tempBoolMask[0],blue,minBrightness,deltaBrightness,delay);
		joelIndex++;
		if(joelIndex == 4) joelIndex = 0;
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
	maskCube0189[42] = 0; // why is this necessary?
	maskCube0189[58] = 0; // why is this necessary?
	HALT_ANIMATION = false;
	PAUSE_ANIMATION = false;
	lyr_frame_clear_all(frame.lyr0);
	
	while(HALT_ANIMATION == false)
	{
		if(HALT_ANIMATION == true) break;
		
		lyr_frame_set_color(frame.lyr0,colorWheel[colorIndex],maskCube0189);
		colorIndex++;
		if(colorIndex==12) colorIndex=0;
		UPDATE_FRAME=1;
		animation_delay(transitionDelay);
		
		if(HALT_ANIMATION == true) break;
		for(int repIndex=0;repIndex<3;repIndex++)
		{
			lyr_frame_shift_column(frame0.lyr0, 0, DIRECTION_FORWARD);
			lyr_frame_shift_column(frame0.lyr0, 0, DIRECTION_FORWARD);
			lyr_frame_shift_column(frame0.lyr0, 1, DIRECTION_FORWARD);
			lyr_frame_shift_column(frame0.lyr0, 1, DIRECTION_FORWARD);
			UPDATE_FRAME=1;
			animation_delay(transitionDelay);
			if(HALT_ANIMATION == true) break;
		}
		
		if(HALT_ANIMATION == true) break;
		lyr_frame_set_color(frame.lyr0,colorWheel[colorIndex],maskCube0189);
		colorIndex++;
		if(colorIndex==12) colorIndex=0;
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
			UPDATE_FRAME=1;
			animation_delay(transitionDelay);
			if(HALT_ANIMATION == true) break;
		}
		
		if(HALT_ANIMATION == true) break;
		lyr_frame_set_color(frame.lyr0,colorWheel[colorIndex],maskCube0189);
		colorIndex++;
		if(colorIndex==12) colorIndex=0;
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
			UPDATE_FRAME=1;
			animation_delay(transitionDelay);
		}	
		
		if(HALT_ANIMATION == true) break;
		lyr_frame_set_color(frame.lyr0,colorWheel[colorIndex],maskCube0189);
		colorIndex++;
		if(colorIndex==12) colorIndex=0;
		UPDATE_FRAME=1;
		animation_delay(transitionDelay);	
		
		if(HALT_ANIMATION == true) break;
		
		for(uint8_t tempIndex=0;tempIndex<8;tempIndex++)
		{
			lyr_frame_shift_row(frame0.lyr0, tempIndex, DIRECTION_INWARD);
		}
		
		UPDATE_FRAME=1;
		animation_delay(2*transitionDelay);	
		
		if(HALT_ANIMATION == true) break;
		
		for(uint8_t tempIndex=0;tempIndex<8;tempIndex++)
		{
			lyr_frame_shift_column(frame0.lyr0, tempIndex, DIRECTION_INWARD);
		}
		
		UPDATE_FRAME=1;
		animation_delay(2*transitionDelay);	
		
		if(HALT_ANIMATION == true) break;
		
		for(uint8_t tempIndex=0;tempIndex<8;tempIndex++)
		{
			lyr_frame_shift_row(frame0.lyr0, tempIndex, DIRECTION_INWARD);
		}
				
		UPDATE_FRAME=1;
		animation_delay(2*transitionDelay);	
		
		if(HALT_ANIMATION == true) break;
		
		for(uint8_t tempIndex=0;tempIndex<8;tempIndex++)
		{
			lyr_frame_shift_column(frame0.lyr0, tempIndex, DIRECTION_INWARD);
		}
		
		
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
	
	uint16_t delay = 1000;
	uint64_t randColor = 0;
	uint16_t randBrightnessValue = 0;
	uint8_t randRgbChoice = 0;
	uint8_t startPt = 0;
	
	startPt = rand_32bit_modulus(rngCount, 3);
	randRgbChoice = rand_32bit_modulus(rngCount, 2);
	randBrightnessValue = rand_32bit_modulus(rngCount, 4095);
	randColor = modify_color_single_rgb_value(randColor, randBrightnessValue, randRgbChoice);
	
	HALT_ANIMATION = false;
	
	//if (startPt == 0) startPt = 0;
	if (startPt == 1) startPt = 7;
	if (startPt == 2) startPt = 56;
	if (startPt == 3) startPt = 63;
	
	while(HALT_ANIMATION == false)
	{				
		subanimation_stretch_expand(frame.lyr0, randColor, startPt, delay);
		
		
		startPt = rand_32bit_modulus(rngCount, 3);
		randRgbChoice = rand_32bit_modulus(rngCount, 2);
		randBrightnessValue = rand_32bit_modulus(rngCount, 4095);
		randColor = modify_color_single_rgb_value(randColor, randBrightnessValue, randRgbChoice);		
		
		//if (startPt = 0) startPt = 0;
		if (startPt == 1) startPt = 7;
		if (startPt == 2) startPt = 56;
		if (startPt == 3) startPt = 63;
				
		subanimation_stretch_retract(frame.lyr0, randColor, startPt, delay); // still need to implement this
	}
	lyr_frame_clear_all(frame.lyr0);
	lyr_frame_convert(frame.lyr0,data16Ptr);
	UPDATE_FRAME=1;	
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
void transition_punch(LyrFrame_TypeDef lyrFrame, bool *maskPtr, uint64_t color, uint16_t delay, uint8_t punchDirection)
{
	if(punchDirection == DIRECTION_FORWARD)
	{
		for(uint8_t tempIndex=0;tempIndex<BOOL_MASK_LENGTH;tempIndex++)
		{
			if(*(maskPtr + tempIndex) == 1)
			{
				lyr_frame_set_single_color(lyrFrame,color,tempIndex);
				UPDATE_FRAME=1;
				animation_delay(delay);
				if(HALT_ANIMATION == true) break;
			}
		}
	}
	
	if(punchDirection == DIRECTION_BACK)
	{
		for(uint8_t tempIndex=BOOL_MASK_LENGTH;tempIndex>0;tempIndex--)
		{
			if(*(maskPtr + tempIndex-1) == 1)
			{
				lyr_frame_set_single_color(lyrFrame,color,tempIndex-1);
				UPDATE_FRAME=1;
				animation_delay(delay);
				if(HALT_ANIMATION == true) break;
			}
		}
	}
}

void transition_fade(LyrFrame_TypeDef lyrFrame, bool *maskPtr, uint64_t color, uint16_t minMaxBrightness, uint16_t deltaBrightness, uint16_t delay, bool increaseNdecrease)
{
	int16_t redBrightness = (color>>32);
	int16_t grnBrightness = (color>>16);
	int16_t bluBrightness = (color>>0);
	int16_t redDeltaBrightness = 0x0000;
	int16_t grnDeltaBrightness = 0x0000;
	int16_t bluDeltaBrightness = 0x0000;
	int16_t currentBrightness ;	//hopefully since its signed there's no negative number hard fault.
	
	if(increaseNdecrease == true) //incease brightness
	{
		currentBrightness = 0;

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
		
		while (currentBrightness <= minMaxBrightness)
		{
			if(HALT_ANIMATION == true) break;
			lyr_frame_set_single_rgb(lyrFrame.redArrPtr, redBrightness, maskPtr);
			lyr_frame_set_single_rgb(lyrFrame.grnArrPtr, grnBrightness, maskPtr);
			lyr_frame_set_single_rgb(lyrFrame.bluArrPtr, bluBrightness, maskPtr);
			UPDATE_FRAME=1;
			animation_delay(delay);
			currentBrightness = currentBrightness + deltaBrightness;
			redBrightness = redBrightness + redDeltaBrightness;
			grnBrightness = grnBrightness + grnDeltaBrightness;
			bluBrightness = bluBrightness + bluDeltaBrightness;
		}
	}
	
	if(increaseNdecrease == false) //decrease brightness
	{	
		currentBrightness = 4000;
	
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
		
		while (currentBrightness >= minMaxBrightness)
		{
			if(HALT_ANIMATION == true) break;
			lyr_frame_set_single_rgb(lyrFrame.redArrPtr, redBrightness, maskPtr);
			lyr_frame_set_single_rgb(lyrFrame.grnArrPtr, grnBrightness, maskPtr);
			UPDATE_FRAME=1;
			animation_delay(delay);
			currentBrightness = currentBrightness - deltaBrightness;
			redBrightness = redBrightness - redDeltaBrightness;
			grnBrightness = grnBrightness - grnDeltaBrightness;
			bluBrightness = bluBrightness - bluDeltaBrightness;
		}
	}
}

void transition_punch_fade(LyrFrame_TypeDef lyrFrame, bool *maskPtr, uint64_t color, uint16_t minMaxBrightness, uint16_t deltaBrightness, uint16_t delay, bool increaseNdecrease, uint8_t punchDirection)
{
	// unfinished work
}

/**
 * @brief starts as an 8x8 square outline. The square then collapses into the stopPt corner.
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] stopPt - the corner which the 8x8 square outline collapses into
 * @param[in] delay - length of time in ms to wait inbetween punches
 */
void subanimation_stretch_retract(LyrFrame_TypeDef lyrFrame, uint64_t color, int stopPt, uint16_t delay)
{
	if ((stopPt != 0)&(stopPt != 7)&(stopPt != 56)&(stopPt != 63)) return;
	
	//lyr_frame_clear_all(lyrFrame);
	
	int startPt = 0;
	int ptStepSize = 0;
	
	if((stopPt == 56) || (stopPt == 63))
	{
		if(stopPt == 63)
		{
			startPt = 0;
			ptStepSize = 9;
		}
		
		if(stopPt == 56)
		{
			startPt = 7;
			ptStepSize = 7;
		}
		
		while(stopPt>startPt)
		{
			if(HALT_ANIMATION == true) break;
			startPt+=ptStepSize;
			lyr_frame_clear_all(lyrFrame);
			lyrframe_set_square(lyrFrame, color, startPt, stopPt);
			UPDATE_FRAME = 1;
			animation_delay(delay);
		}
	}
	
	if((stopPt == 0) || (stopPt == 7))
	{
		if(stopPt == 0)
		{
			startPt = 63;
			ptStepSize = 9;
		}
		
		if(stopPt == 7)
		{
			startPt = 56;
			ptStepSize = 7;
		}
	
		while(startPt>stopPt)
		{
			if(HALT_ANIMATION == true) break;
			startPt-=ptStepSize;
			lyr_frame_clear_all(lyrFrame);
			lyrframe_set_square(lyrFrame, color, startPt, stopPt);
			UPDATE_FRAME = 1;
			animation_delay(delay);
		}		
	}
}

/**
 * @brief starts from a single corner of the 8x8 array. This corner then "stretches out" or expands out diagonally while retaining 
					a square shape. The initial corner remains fixed until the opposite corner is reached.
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] startPt - the initial corner
 * @param[in] delay - length of time in ms to wait inbetween punches
 */
void subanimation_stretch_expand(LyrFrame_TypeDef lyrFrame, uint64_t color, int startPt, uint16_t delay)
{
	if ((startPt != 0)&(startPt != 7)&(startPt != 56)&(startPt != 63)) return;
	
	//lyr_frame_clear_all(lyrFrame);
	
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
			if(HALT_ANIMATION == true) break;
			stopPt+=ptStepSize;
			lyr_frame_clear_all(lyrFrame);
			lyrframe_set_square(lyrFrame, color, startPt, stopPt);
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
			if(HALT_ANIMATION == true) break;
			stopPt-=ptStepSize;
			lyr_frame_clear_all(lyrFrame);
			lyrframe_set_square(lyrFrame, color, startPt, stopPt);
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

/**
 * @brief flashes the lyrFrame on and off rapidly
 * @param[in] lyrFrame - a struct of the RGB values for a horizontal slice of the 3D frame
 * @param[in] maskPtr - points to the boolMask being referenced
 * @param[in] color - an RGB color in the format 0x00000RRR0GGG0BBB
 * @param[in] strobeDelay - the amount of time to wait in ms between flashes
 */
void subanimation_strobe(LyrFrame_TypeDef lyrFrame, bool *maskPtr, uint64_t color, uint16_t strobeDelay)
{
	lyr_frame_clear_all(lyrFrame);
	UPDATE_FRAME = 1;
	animation_delay(strobeDelay);
	
	lyr_frame_set_color(lyrFrame, color, maskPtr);
	UPDATE_FRAME = 1;
	animation_delay(strobeDelay);
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
	
	redBrightness = (0x0000000000001111 & (initialColor>>32));
	grnBrightness = (0x0000000000001111 & (initialColor>>16));
	bluBrightness = (0x0000000000001111 & (initialColor>>0));
	
	if(rgbCoice == 0) redBrightness = rgbValue;
	if(rgbCoice == 1) grnBrightness = rgbValue;
	if(rgbCoice == 2) bluBrightness = rgbValue;
	
	initialColor = (0x0000000000001111 & redBrightness);
	initialColor = ((initialColor<<16) | grnBrightness);
	initialColor = ((initialColor<<16) | bluBrightness);
		
	return initialColor;	
}

//----------------------------------------- UTILITY FUNCTIONS END----------------------------------------------------//
