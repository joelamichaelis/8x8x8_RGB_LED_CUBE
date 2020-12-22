/*
 * menu_system.h
 *
 *  Created on: Dec 5, 2020
 *      Author: Joel Michaelis
 */

#ifndef MENU_SYSTEM_H_
#define MENU_SYSTEM_H_

#include <stdbool.h>
#include "mpr121.h"
#include "lcd20x4_i2c.h"

#define MenuRowLength 20
#define MenuColumnLength 10
#define MenuSize 200

#define MainMenuName " Main Menu:"
#define AnimationMenuName " Animation Menu:"
#define PinMappingMenuName " Pin Mapping:"

//These actions could be made into an ENUM
#define ACTION_HALT_ANIMATION 	 0
#define ACTION_PLAY_ANIMATION_1  1
#define ACTION_PLAY_ANIMATION_2  2
#define ACTION_PLAY_ANIMATION_3  3
#define ACTION_PLAY_ANIMATION_4  4
#define ACTION_PLAY_ANIMATION_5  5
#define ACTION_PLAY_ANIMATION_6  6
#define ACTION_PLAY_ANIMATION_7  7
#define ACTION_PLAY_ANIMATION_8  8
#define ACTION_PLAY_ANIMATION_9  9
#define ACTION_PLAY_ANIMATION_10 10
#define ACTION_PLAY_ANIMATION_50 10 // its going to be quite a while before I exceed this many animations
#define ACTION_NOP 							 51	//No OPeration
#define ACTION_MAIN_MENU 				 52
#define ACTION_ANIMATION_MENU 	 53
#define ACTION_PIN_MAPPING_MENU  54

//delete for good?
//extern bool MAIN_MENU_ENABLED;
//extern bool PIN_MAPPING_ENABLED;
//extern bool APPLICATION_ENABLED;

extern uint16_t currentAction; //global variable defined in main.c but also must be visible in menu_system.c


typedef struct __Menu_TypeDef
{	
	char Array[MenuSize]; 
	char *ArrayPtr;
	int HighestRow;									//as high as the menu can scroll
	int DisplayTopRow;							//the uppermost visible row
	int DisplaySelectedRow;					//where the cursor is pointing
	int DisplayBottomRow;						//the bottommost visible row
	int LowestRow;									//as low as the menu can scroll
	int rowAction[MenuColumnLength];		//every row has a corresponding action when button pressed while selected
	int selectedRowNum;							//counts by 1s unlike DisplaySelectedRow
	bool active;										//dictates whether or not menu is on display
} Menu_TypeDef;

//these menus are basically global variables shared between main & menu system. not ideal but I'll live with it for now.
extern Menu_TypeDef MainMenu;
extern Menu_TypeDef AnimationMenu;
extern Menu_TypeDef PinMappingMenu;
extern Menu_TypeDef ActiveAnimation;

void MenuDisplayUpdate(Menu_TypeDef Menu);
Menu_TypeDef MenuScrollUp(Menu_TypeDef Menu);
Menu_TypeDef MenuScrollDown(Menu_TypeDef Menu);
Menu_TypeDef MenuButtonPressed(Menu_TypeDef Menu);
void MenuStrCpy(char *strPtr, char *menuPtr, int strCpyStart , int strCpyLength);
void MenuSetRowText(char* menuPtr, int rowNum, char rowTxt[MenuRowLength]);

void MainMenuInit(void);
Menu_TypeDef AnimationMenuInit(Menu_TypeDef Menu);
Menu_TypeDef PinMappingMenuInit(Menu_TypeDef Menu);


/**
 * @brief Establishes & verifies connectivity with the LCD & capacitive touch sensors
 **/
void MenuSystemInit(I2C_HandleTypeDef hi2c);

/**
 * @brief essentially a wrapper for lcd_20x4_i2c which also ensures MPR121s are read afterward
 **/
void Menu_Printf(const char* str, ...);


/**
 * @brief exactly what it sounds like
 **/
uint16_t Menu_Read_MPR121(I2C_HandleTypeDef hi2c, uint16_t GPIO_Pin, uint16_t currentAction);

#endif
