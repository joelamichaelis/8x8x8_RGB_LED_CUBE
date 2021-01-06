/*
 * Array8x8Functions.c
 *
 *  Created on: Dec 6, 2020
 *      Author: Joel Michaelis
 */

#include "animations.h"

bool HALT_ANIMATION = false;

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
//------------------------------------Color Definition Begin-------------------------------------//

void Animation_LUT(int animationNumber)
{
	switch(animationNumber)
	{
		case 1:
		{
			joel_mode(frame0);
			return;
		}
			
		case 2:
		{
			halloween(frame0);
			return;
		}
	
		case 3:
		{
			original_fade(frame0);
			return;
		}
		
	}
}

void merry_christmas(Frame_TypeDef frame0)
{
	uint16_t maxBrightness = 4000;
	uint16_t minBrightness = 0;
	uint16_t deltaBrightness = 10;
	uint16_t delay = 100;
	
	HALT_ANIMATION = false;
	
	while(HALT_ANIMATION == false)
	{
		dissolve_in_color(frame0.lyr0, mask0, green, maxBrightness, deltaBrightness, delay);
		dissolve_out_color(frame0.lyr0, mask0, green, minBrightness, deltaBrightness, delay);
	}
}

void original_fade(Frame_TypeDef frame0)
{
	uint16_t maxBrightness = 4000;
	uint16_t minBrightness = 0;
	uint16_t deltaBrightness = 10;
	uint16_t delay = 10;
	uint16_t transitionDelay;
	uint64_t colorWheel[12] = {red,orange,yellow,yelgrn,green,seafoam,cyan,lightblu,blue,indigo,purple,pink};	
	int caseNum = 0;
	
	HALT_ANIMATION = false;
	
	while(HALT_ANIMATION == false)
	{
		while (caseNum<12)
		{
			fade_in_color(frame0.lyr0,mask0,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
			fade_out_color(frame0.lyr0,mask0,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
			HAL_Delay(transitionDelay);
			caseNum++;
		
			fade_in_color(frame0.lyr0,mask1,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
			fade_out_color(frame0.lyr0,mask1,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
			HAL_Delay(transitionDelay);
			caseNum++;
			
			fade_in_color(frame0.lyr0,mask2,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
			fade_out_color(frame0.lyr0,mask2,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
			HAL_Delay(transitionDelay);
			caseNum++;
			
			fade_in_color(frame0.lyr0,mask3,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
			fade_out_color(frame0.lyr0,mask3,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
			HAL_Delay(transitionDelay);
			caseNum++;
			
			fade_in_color(frame0.lyr0,mask2,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
			fade_out_color(frame0.lyr0,mask2,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
			HAL_Delay(transitionDelay);
			caseNum++;
			
			fade_in_color(frame0.lyr0,mask1,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
			fade_out_color(frame0.lyr0,mask1,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
			HAL_Delay(transitionDelay);
			caseNum++;
		}
	}
}

void halloween(Frame_TypeDef frame)
{
	uint16_t maxBrightness = 2000;
	uint16_t minBrightness = 0;
	uint16_t deltaBrightness = 10;
	uint16_t delay = 10;
	uint16_t transitionDelay = 500;
	
	while(HALT_ANIMATION == false)
	{
		fade_in_color(frame0.lyr0,maskChessBoardW,purple,maxBrightness,deltaBrightness,delay);
		fade_in_color(frame0.lyr0,maskChessBoardB,orange,maxBrightness,deltaBrightness,delay);
		HAL_Delay(transitionDelay);
		fade_out_color(frame0.lyr0,maskChessBoardW,purple,minBrightness,deltaBrightness,delay);			
		fade_out_color(frame0.lyr0,maskChessBoardB,orange,minBrightness,deltaBrightness,delay);
		HAL_Delay(transitionDelay);
	}
}

void joel_mode(Frame_TypeDef frame)
{
	uint16_t maxBrightness = 2000;
	uint16_t minBrightness = 0;
	uint16_t deltaBrightness = 10;
	uint16_t delay = 10;
	uint16_t transitionDelay = 500;
	
	HALT_ANIMATION = false;
	
	while(HALT_ANIMATION == false)
	{
		fade_in_color(frame0.lyr0,letterJ,blue,maxBrightness,deltaBrightness,delay);
		fade_out_color(frame0.lyr0,letterJ,blue,minBrightness,deltaBrightness,delay);
		fade_in_color(frame0.lyr0,letterO,blue,maxBrightness,deltaBrightness,delay);
		fade_out_color(frame0.lyr0,letterO,blue,minBrightness,deltaBrightness,delay);
		fade_in_color(frame0.lyr0,letterE,blue,maxBrightness,deltaBrightness,delay);
		fade_out_color(frame0.lyr0,letterE,blue,minBrightness,deltaBrightness,delay);
		fade_in_color(frame0.lyr0,letterL,blue,maxBrightness,deltaBrightness,delay);
		fade_out_color(frame0.lyr0,letterL,blue,minBrightness,deltaBrightness,delay);
		HAL_Delay(transitionDelay);
	}
}


void shifting_cubes(Frame_TypeDef frame)
{
	uint16_t brightness = 2000;
	uint16_t transitionDelay = 500;
	
	HALT_ANIMATION = false;
	
	while(HALT_ANIMATION == false)
	{
		lyr_frame_set_color(frame.lyr0,red,mask0);
		lyr_frame_set_color(frame.lyr0,green,mask1);
		lyr_frame_set_color(frame.lyr0,blue,mask2);
		lyr_frame_set_color(frame.lyr0,yellow,mask4);
		HAL_Delay(transitionDelay);
	}
}



void dissolve_in_color(LyrFrame_TypeDef lyrFrame, bool mask[64], uint64_t color, uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay)
{
	bool tempMask[64];
	bool_mask_clear_all(&tempMask[0]);
	int tempIndex = 0;
	for (tempIndex=0;tempIndex<BOOL_MASK_LENGTH;tempIndex++)
	{
		if (mask[tempIndex] == 1)
		{
			tempMask[tempIndex] = 1;
			lyr_frame_set_color(lyrFrame,color,tempMask);
			lyr_frame_convert(frame0.lyr0,data16Ptr);
			UPDATE_FRAME=1;
			HAL_Delay(delay);
		}
	}
}

void dissolve_out_color(LyrFrame_TypeDef lyrFrame, bool mask[64], uint64_t color, uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay)
{
	bool tempMask[64];
	bool_mask_copy(&mask[0],&tempMask[0]);
	int tempIndex = 0;	
	for (tempIndex=0;tempIndex<BOOL_MASK_LENGTH;tempIndex++)
	{
		if ((tempMask[tempIndex] & mask[tempIndex]) == 1)
		{
			tempMask[tempIndex] = 0;
			//lyr_frame_clear_all(lyrFrame);
			lyr_frame_set_color(lyrFrame,color,tempMask);
			lyr_frame_convert(lyrFrame,data16Ptr);
			UPDATE_FRAME=1;
			HAL_Delay(delay);
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
		lyr_frame_set_single_rgb(lyrFrame.redArrPtr, redBrightness, mask);
		lyr_frame_set_single_rgb(lyrFrame.grnArrPtr, grnBrightness, mask);
		lyr_frame_set_single_rgb(lyrFrame.bluArrPtr, bluBrightness, mask);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		HAL_Delay(delay);
		//if(currentBrightness==4000) HAL_Delay(1);
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
		lyr_frame_set_single_rgb(lyrFrame.redArrPtr, redBrightness, mask);
		lyr_frame_set_single_rgb(lyrFrame.grnArrPtr, grnBrightness, mask);
		lyr_frame_set_single_rgb(lyrFrame.bluArrPtr, bluBrightness, mask);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		HAL_Delay(delay);
		currentBrightness = currentBrightness - deltaBrightness;
		redBrightness = redBrightness - redDeltaBrightness;
		grnBrightness = grnBrightness - grnDeltaBrightness;
		bluBrightness = bluBrightness - bluDeltaBrightness;
	}
}

void fade_in_red(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay)
{
	uint16_t currentBrightness = deltaBrightness;
	while (currentBrightness <= maxBrightness)
	{
		lyr_frame_set_single_rgb(lyrFrame.redArrPtr, currentBrightness, mask);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		HAL_Delay(delay);
		currentBrightness = currentBrightness + deltaBrightness;
	}
}

void fade_in_grn(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay)
{
	uint16_t currentBrightness = deltaBrightness;
	while (currentBrightness <= maxBrightness)
	{
		lyr_frame_set_single_rgb(lyrFrame.grnArrPtr, currentBrightness, mask);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		HAL_Delay(delay);
		currentBrightness = currentBrightness + deltaBrightness;
	}
}

void fade_in_blu(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay)
{
	uint16_t currentBrightness = deltaBrightness;
	while (currentBrightness <= maxBrightness)
	{
		lyr_frame_set_single_rgb(lyrFrame.bluArrPtr, currentBrightness, mask);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		HAL_Delay(delay);
		currentBrightness = currentBrightness + deltaBrightness;
	}
}

void fade_out_red(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay)
{
	int16_t currentBrightness = 4000; //hopefully since its signed there's no negative number hard fault.
	while (currentBrightness >= minBrightness)
	{
		lyr_frame_set_single_rgb(lyrFrame.redArrPtr, currentBrightness, mask);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		HAL_Delay(delay);
		currentBrightness = currentBrightness - deltaBrightness;
	}
}

void fade_out_grn(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay)
{
	int16_t currentBrightness = 4000; //hopefully since its signed there's no negative number hard fault.
	while (currentBrightness >= minBrightness)
	{
		lyr_frame_set_single_rgb(lyrFrame.grnArrPtr, currentBrightness, mask);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		HAL_Delay(delay);
		currentBrightness = currentBrightness - deltaBrightness;
	}
}

void fade_out_blu(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay)
{
	int16_t currentBrightness = 4000; //hopefully since its signed there's no negative number hard fault.
	while (currentBrightness >= minBrightness)
	{
		lyr_frame_set_single_rgb(lyrFrame.bluArrPtr, currentBrightness, mask);
		lyr_frame_convert(frame0.lyr0,data16Ptr);
		UPDATE_FRAME=1;
		HAL_Delay(delay);
		currentBrightness = currentBrightness - deltaBrightness;
	}
}

