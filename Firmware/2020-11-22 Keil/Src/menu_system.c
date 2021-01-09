/*
 * menuSystem.c
 *
 *  Created on: Dec 5, 2020
 *      Author: Joel Michaelis
 */

#include "menu_system.h"
#include <stdbool.h>

extern I2C_HandleTypeDef hi2c1;

#define Keypad_IRQ_Pin GPIO_PIN_4
//extern uint16_t Keypad_IRQ_Pin;

#define Wheel_IRQ_Pin GPIO_PIN_5
//extern uint16_t Wheel_IRQ_Pin;

uint8_t mpr121ReadDelayms = 10;
char lastWheelDir = 'X';
char wheelDir = 'X';

Menu_TypeDef MainMenu;
Menu_TypeDef AnimationMenu;
Menu_TypeDef PinMappingMenu;
Menu_TypeDef ActiveAnimation;

//delete for good?
//bool MAIN_MENU_ENABLED = 1;
//bool PIN_MAPPING_ENABLED = 0;
//bool APPLICATION_ENABLED = 0;

bool Keypad_IRQ = false; 	//indicates that keypad must be read when set
bool Wheel_IRQ = false;		//indicates that wheel must be read when set

uint8_t initNumPM = 0;
uint16_t initValPM = 0;
uint16_t stepSizePM = 500;
uint16_t minValPM = 0;
uint16_t maxValPM = 4000;

uint16_t ledNumPM;
int16_t redValPM;
int16_t bluValPM;
int16_t grnValPM;

Menu_TypeDef MenuScrollUp (Menu_TypeDef Menu)
{
	if(Menu.DisplaySelectedRow == Menu.HighestRow) return Menu;
	if(Menu.DisplaySelectedRow == Menu.DisplayTopRow)
	{
		Menu.DisplayTopRow = Menu.DisplayTopRow - MenuRowLength;
		Menu.DisplayBottomRow = Menu.DisplayBottomRow - MenuRowLength;
	}
	Menu.DisplaySelectedRow = Menu.DisplaySelectedRow - MenuRowLength;
	Menu.selectedRowNum--;
	MenuDisplayUpdate(Menu);
	return Menu;
}


Menu_TypeDef MenuScrollDown (Menu_TypeDef Menu)
{
	if(Menu.DisplaySelectedRow == Menu.LowestRow) return Menu;
	if(Menu.DisplaySelectedRow == Menu.DisplayBottomRow)
	{
		Menu.DisplayTopRow = Menu.DisplayTopRow + MenuRowLength;
		Menu.DisplayBottomRow = Menu.DisplayBottomRow + MenuRowLength;
	}
	Menu.DisplaySelectedRow = Menu.DisplaySelectedRow + MenuRowLength;
	Menu.selectedRowNum++;
	MenuDisplayUpdate(Menu);
	return Menu;
}

// The passed in menu is displayed on the LCD
// Nothing is returned because the menu isn't modified
void MenuDisplayUpdate(Menu_TypeDef Menu)
{
	Menu.ArrayPtr = &Menu.Array[0]; //for some reason this array pointer doesn't get passed in appropriately so this is necessary
	char tempStr[MenuRowLength];
	char *tempStrPtr = &tempStr[0];
	lcd20x4_i2c_clear();
	
	lcd20x4_i2c_1stLine();
	MenuStrCpy(tempStrPtr, Menu.ArrayPtr, Menu.DisplayTopRow, MenuRowLength);
	lcd20x4_i2c_printf(tempStr);
	HAL_Delay(10);
	
	lcd20x4_i2c_2ndLine();
	MenuStrCpy(tempStrPtr, Menu.ArrayPtr, (Menu.DisplayTopRow + MenuRowLength),MenuRowLength);
	lcd20x4_i2c_printf(tempStr);
	HAL_Delay(10);
	
	lcd20x4_i2c_3rdLine();
	MenuStrCpy(tempStrPtr, Menu.ArrayPtr, (Menu.DisplayTopRow + 2*MenuRowLength),MenuRowLength);
	lcd20x4_i2c_printf(tempStr);
	HAL_Delay(10);
	
	lcd20x4_i2c_4thLine();
	MenuStrCpy(tempStrPtr, Menu.ArrayPtr, (Menu.DisplayTopRow + 3*MenuRowLength),MenuRowLength);
	lcd20x4_i2c_printf(tempStr);
	lcd20x4_i2c_setCursor(((Menu.DisplaySelectedRow-Menu.DisplayTopRow)/MenuRowLength),0);
	HAL_Delay(10);
}


void MenuStrCpy(char *strPtr, char *arrayPtr, int strCpyStart , int strCpyLength)
{
	int tempIndex=0;
	while(tempIndex<strCpyLength)
	{
		*(strPtr+tempIndex) = *(arrayPtr + strCpyStart + tempIndex);
		tempIndex++;
	}
}


void MenuSetRowText(char* menuPtr, int rowNum, char rowTxt[MenuRowLength])
{
	int rowIndex=0;
	while(rowIndex<MenuRowLength)
	{
		//prevents a peculiar rowTxt is shorter than MenuRowLength. 
		//The extra ununsed length then gets initialized to seemingly random values.
		if(rowIndex>strlen(rowTxt)) 
			*(menuPtr + (MenuRowLength*rowNum) + rowIndex) = 0x00;
		else
			*(menuPtr + (MenuRowLength*rowNum) + rowIndex) = rowTxt[rowIndex];
		rowIndex++;
	}
}

void MainMenuInit(void)
{
	int mainMenuColumnLength = 4;
	MainMenu.active=true;
	MainMenu.ArrayPtr = &MainMenu.Array[0];
	MainMenu.HighestRow=0;
	MainMenu.DisplayTopRow=0;
	MainMenu.DisplaySelectedRow=0;
	MainMenu.DisplayBottomRow = 3*MenuRowLength;
	MainMenu.LowestRow = MenuRowLength*(mainMenuColumnLength - 1);
	
	MenuSetRowText(MainMenu.ArrayPtr, 0, MainMenuName);
	MainMenu.rowAction[0] = ACTION_NOP;
	
	MenuSetRowText(MainMenu.ArrayPtr, 1, " - Animations ");
	MainMenu.rowAction[1] = ACTION_ANIMATION_MENU;
	
	MenuSetRowText(MainMenu.ArrayPtr, 2, " - Pin Mapping");
	MainMenu.rowAction[2] = ACTION_PIN_MAPPING_MENU;
	
	MenuSetRowText(MainMenu.ArrayPtr, 3, " - Options");
	MainMenu.rowAction[3] = ACTION_NOP;
	
	/*
	MenuSetRowText(MainMenu.ArrayPtr, 4, " Row 4");
	MainMenu.rowAction[4] = ACTION_NOP;
	
	MenuSetRowText(MainMenu.ArrayPtr, 5, " Row 5");
	MainMenu.rowAction[5] = ACTION_NOP;
	
	MenuSetRowText(MainMenu.ArrayPtr, 6, " Row 6");
	MainMenu.rowAction[6] = ACTION_NOP;
	
	MenuSetRowText(MainMenu.ArrayPtr, 7, " Row 7");
	MainMenu.rowAction[7] = ACTION_NOP;
	
	MenuSetRowText(MainMenu.ArrayPtr, 8, " Row 8");
	MainMenu.rowAction[8] = ACTION_NOP;
	
	MenuSetRowText(MainMenu.ArrayPtr, 9, " Bottom of Menu");
	MainMenu.rowAction[9] = ACTION_NOP;	
	*/
}

Menu_TypeDef AnimationMenuInit(Menu_TypeDef Menu)
{
	Menu.ArrayPtr = &Menu.Array[0];
	Menu.HighestRow=0;
	Menu.DisplayTopRow=0;
	Menu.DisplaySelectedRow=0;
	Menu.DisplayBottomRow = 3*MenuRowLength;
	Menu.LowestRow = MenuRowLength*(MenuColumnLength - 1);
	
	MenuSetRowText(Menu.ArrayPtr, 0, AnimationMenuName);
	
	MenuSetRowText(Menu.ArrayPtr, 1, " Joel Mode ");
	Menu.rowAction[1] = ACTION_PLAY_ANIMATION_1;
	
	MenuSetRowText(Menu.ArrayPtr, 2, " Halloween");
	Menu.rowAction[2] = ACTION_PLAY_ANIMATION_2;
	
	MenuSetRowText(Menu.ArrayPtr, 3, " Original Fade");
	Menu.rowAction[3] = ACTION_PLAY_ANIMATION_3;
	
	MenuSetRowText(Menu.ArrayPtr, 4, " Merry Christmas");
	Menu.rowAction[4] = ACTION_PLAY_ANIMATION_4;
	
	MenuSetRowText(Menu.ArrayPtr, 5, " Sliding Cubes");
	Menu.rowAction[5] = ACTION_PLAY_ANIMATION_5;
	
	MenuSetRowText(Menu.ArrayPtr, 6, " Row 6");
	MenuSetRowText(Menu.ArrayPtr, 7, " Row 7");
	MenuSetRowText(Menu.ArrayPtr, 8, " Row 8");
	MenuSetRowText(Menu.ArrayPtr, 9, " Back to Main Menu");
	Menu.rowAction[9] = ACTION_MAIN_MENU;
	return Menu;	
}


Menu_TypeDef PinMappingMenuInit(Menu_TypeDef Menu)
{
	int pinMappingMenuLength = 6;
	
	Menu.ArrayPtr = &Menu.Array[0];
	Menu.HighestRow=0;
	Menu.DisplayTopRow=0;
	Menu.DisplaySelectedRow=0;
	Menu.DisplayBottomRow = 3*MenuRowLength;
	Menu.LowestRow = MenuRowLength*(pinMappingMenuLength - 1);
	
	MenuSetRowText(Menu.ArrayPtr, 0, PinMappingMenuName);
	Menu.rowAction[0] = ACTION_NOP;
	
	MenuSetRowText(Menu.ArrayPtr, 1, " LED #0");
	Menu.rowAction[1] = ACTION_NOP;
	
	MenuSetRowText(Menu.ArrayPtr, 2, " RED Val: 4000");
	Menu.rowAction[2] = ACTION_NOP;
	
	MenuSetRowText(Menu.ArrayPtr, 3, " GRN Val: 2000");
	Menu.rowAction[3] = ACTION_NOP;
	
	MenuSetRowText(Menu.ArrayPtr, 4, " BLU Val: 1000");
	Menu.rowAction[4] = ACTION_NOP;
	
	MenuSetRowText(Menu.ArrayPtr, 5, " Back");
	Menu.rowAction[5] = ACTION_MAIN_MENU;

	return Menu;	
}


Menu_TypeDef ActiveAnimationInit(Menu_TypeDef Menu)
{
	Menu.ArrayPtr = &Menu.Array[0];
	Menu.HighestRow=0;
	Menu.DisplayTopRow=0;
	Menu.DisplaySelectedRow=0;
	Menu.DisplayBottomRow = 3*MenuRowLength;
	Menu.LowestRow = Menu.DisplayBottomRow;
	
	MenuSetRowText(Menu.ArrayPtr, 0, AnimationMenuName);
	Menu.rowAction[0] = ACTION_NOP;
	
	MenuSetRowText(Menu.ArrayPtr, 1, " Animation Name");
	Menu.rowAction[1] = ACTION_NOP;
	
	MenuSetRowText(Menu.ArrayPtr, 2, "  ");
	Menu.rowAction[2] = ACTION_NOP;
	
	MenuSetRowText(Menu.ArrayPtr, 3, " Back");
	Menu.rowAction[3] = ACTION_ANIMATION_MENU;
	return Menu;	
}

//The passed in menu is scrutinized to determine what action to perform
//MainMenu, ApplicationMenu, and PinMapping  Menu are global so don't need to be passed in/out
// the display is updated accordingly
//The same menu is passed out in case it was modified (such as Menu.active toggled)
Menu_TypeDef MenuButtonPressed(Menu_TypeDef Menu)
{

	if (Menu.rowAction[Menu.selectedRowNum] == ACTION_NOP) return Menu;
	
	if (Menu.rowAction[Menu.selectedRowNum] == ACTION_MAIN_MENU)
	{
		Menu.active = false;
		MainMenu.active = true;
		MenuDisplayUpdate(MainMenu);
		return Menu;
	}
		
	if (Menu.rowAction[Menu.selectedRowNum] == ACTION_ANIMATION_MENU)
	{
		Menu.active = false;
		AnimationMenu.active = true;
		MenuDisplayUpdate(AnimationMenu);
		return Menu;
	}
	
	if (Menu.rowAction[Menu.selectedRowNum] == ACTION_PIN_MAPPING_MENU)
	{
		Menu.active = false;
		PinMappingMenu.active = true;
		MenuDisplayUpdate(PinMappingMenu);
		return Menu;
	}
	
	if ((Menu.rowAction[Menu.selectedRowNum] >= ACTION_PLAY_ANIMATION_1) & (Menu.rowAction[Menu.selectedRowNum] <= ACTION_PLAY_ANIMATION_50))
	{
		//Menu.active = false; //commented out just for now
		//determine which animation to play
		//Animation_LUT(Menu.rowAction[Menu.selectedRowNum]);
		return Menu;
	}
	return Menu;
}

/**
 * @brief Establishes & verifies connectivity with the LCD & capacitive touch sensors
 **/
void MenuSystemInit(I2C_HandleTypeDef hi2c)
{
	//lcd20x4_i2c_init(&hi2c);
	HAL_Delay(100);
	mpr121_init(&hi2c, (KEYPAD_ADDRESS<<1), &hi2c);	
	HAL_Delay(100);
	mpr121_init(&hi2c, (WHEEL_ADDRESS<<1), &hi2c);
	HAL_Delay(100);
	lcd20x4_i2c_clear();
	HAL_Delay(100);	
	
	lcd20x4_i2c_1stLine();
	lcd20x4_i2c_printf("8x8x8 RGB LED Cube");
	lcd20x4_i2c_2ndLine();
	lcd20x4_i2c_printf("FW Version: v1.0.1.0");
	lcd20x4_i2c_3rdLine();
	lcd20x4_i2c_printf("Designed by:");
	lcd20x4_i2c_4thLine();
	lcd20x4_i2c_printf("Joel Michaelis :^)");
	HAL_Delay(6000);
	lcd20x4_i2c_clear();

	lcd20x4_i2c_2ndLine();
	if(HAL_I2C_IsDeviceReady(&hi2c, (KEYPAD_ADDRESS<<1), 2, 10) == HAL_OK)
		{
			HAL_Delay(50);
			lcd20x4_i2c_printf("Keypad Ready!");
		}
	else lcd20x4_i2c_printf("Keypad Init Failed");
	
	lcd20x4_i2c_3rdLine();		
	if(HAL_I2C_IsDeviceReady(&hi2c, (WHEEL_ADDRESS<<1), 2, 10) == HAL_OK)
		{
			HAL_Delay(50);
			lcd20x4_i2c_printf("Wheel Ready!");
		}
	else lcd20x4_i2c_printf("Wheel Init Failed");
	
		
	
	HAL_Delay(1000);
	lcd20x4_i2c_clear();
	lcd20x4_i2c_1stLine();	
	lcd20x4_i2c_cursorShow(1);
}


/**
 * @brief essentially a wrapper for lcd_20x4_i2c which also ensures MPR121s are read afterward
 **/
void Menu_Printf(const char* str, ...)
{
	lcd20x4_i2c_printf(str);
	if (Keypad_IRQ == 1) Menu_Read_MPR121(hi2c1, Keypad_IRQ_Pin, currentAction); //keypad IRQ was asserted while lcd was being written to.
	if (Wheel_IRQ == 1) Menu_Read_MPR121(hi2c1, Wheel_IRQ_Pin, currentAction); //keypad IRQ was asserted while lcd was being written to.	
}


/**
 * @brief exactly what it sounds like
 **/
uint16_t Menu_Read_MPR121(I2C_HandleTypeDef hi2c, uint16_t GPIO_Pin, uint16_t currentAction)
{
	Keypad_IRQ = false;
	Wheel_IRQ = false;
	
	//ensures that MPR121s aren't read while LCD is being written to
	I2C_HandleTypeDef *phi2c1 = &hi2c;
	if (phi2c1->State != HAL_I2C_STATE_READY)
	{
		if (GPIO_Pin == Keypad_IRQ_Pin) Keypad_IRQ = true;
		if (GPIO_Pin == Wheel_IRQ_Pin) Wheel_IRQ = true;
		return currentAction;
	}
	
	if(GPIO_Pin == Wheel_IRQ_Pin)
	{
		while(HAL_I2C_GetState(&hi2c) != HAL_I2C_STATE_READY)
    {
    }
		
		lastWheelDir = wheelDir;
		wheelDir = mpr121_wheel(&hi2c, (WHEEL_ADDRESS<<1), wheelDir);
		HAL_Delay(mpr121ReadDelayms);
		
		if ((wheelDir == 'C') & (lastWheelDir != 'C'))	//since the program recognizes touch & release
		{	
			if (MainMenu.active == true) 
			{
				MainMenu = MenuButtonPressed(MainMenu);
				currentAction = MainMenu.rowAction[MainMenu.selectedRowNum];
			}
			else if (AnimationMenu.active == true) 
			{
				AnimationMenu = MenuButtonPressed(AnimationMenu);
				currentAction = AnimationMenu.rowAction[AnimationMenu.selectedRowNum];
			}
			else if (PinMappingMenu.active == true) 
			{
				PinMappingMenu = MenuButtonPressed(PinMappingMenu);
				currentAction = PinMappingMenu.rowAction[PinMappingMenu.selectedRowNum];
			}
			wheelDir = 'X';
			lastWheelDir = 'X';
		}
		
		if ((wheelDir=='E'&lastWheelDir=='N')|(wheelDir=='S'&lastWheelDir=='E')|(wheelDir=='W'&lastWheelDir=='S')|(wheelDir=='N'&lastWheelDir=='W'))
		{
			if (MainMenu.active == true) 				MainMenu = MenuScrollUp(MainMenu);
			if (AnimationMenu.active == true)		AnimationMenu = MenuScrollUp(AnimationMenu);
			if (PinMappingMenu.active == true)	PinMappingMenu = MenuScrollUp(PinMappingMenu);
		}

		if ((wheelDir=='W'&lastWheelDir=='N')|(wheelDir=='N'&lastWheelDir=='E')|(wheelDir=='E'&lastWheelDir=='S')|(wheelDir=='S'&lastWheelDir=='W'))
		{
			if (MainMenu.active == true) 				MainMenu = MenuScrollDown(MainMenu);
			if (AnimationMenu.active == true)		AnimationMenu = MenuScrollDown(AnimationMenu);
			if (PinMappingMenu.active == true)	PinMappingMenu = MenuScrollDown(PinMappingMenu);
		}	
		return currentAction;
	}	
	
	//effectively nothing is implemented at the moment for this other than reading the MPR121 to clear the low IRQ line
	if(GPIO_Pin == Keypad_IRQ_Pin)
	{
		uint8_t keypadVal;	
		keypadVal = mpr121_keyPad(&hi2c, (KEYPAD_ADDRESS<<1));
		HAL_Delay(mpr121ReadDelayms);		
		if (keypadVal == 10)
			return ACTION_HALT_ANIMATION;
	}
	return currentAction;
}
