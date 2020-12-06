/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd20x4_i2c.h"
#include "mpr121.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
Menu_TypeDef MenuInit(Menu_TypeDef Menu);
void MenuDisplayUpdate(Menu_TypeDef Menu);
Menu_TypeDef MenuScrollUp(Menu_TypeDef Menu);
Menu_TypeDef MenuScrollDown(Menu_TypeDef Menu);
void MenuStrCpy(char *strPtr, char *menuPtr, int strCpyStart , int strCpyLength);
void MenuSetRowText(char* menuPtr, int rowNum, char rowTxt[MenuRowLength]);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
	uint16_t touchVal = 0x0000;
	uint16_t *pTouchVal = &touchVal;
	uint8_t reg = 0x00;
	uint8_t data = 0x00;
	uint8_t data2 = 0x00;
	uint8_t i2cData[3];
	
	uint8_t lcdRowIndex = 0;
	uint8_t lcdColIndex = 0;
	uint8_t wheelReadDelayms = 10;
	
	char lastWheelDir = 'X';
	char wheelDir = 'X';
		
	bool MAIN_MENU_ENABLED = 1;	
	bool PIN_MAPPING_ENABLED = 0;
	bool APPLICATION_ENABLED = 0;
	bool KEYPAD_IRQ = 0;
	
	Menu_TypeDef MainMenu;
	
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	i2cData[0] = reg;
	i2cData[1] = data;
	i2cData[2] = data2;
	
//Menu_TypeDef MainMenu;
MainMenu = MenuInit(MainMenu);
MainMenu.ArrayPtr = &MainMenu.Array[0]; // for some reason the Array Ptr doesnt transfer out of MenuInit

	
	
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	
	
	if(lcd20x4_i2c_init(&hi2c1))
	{
		int j=1;
		j++;
	}
	
	
	HAL_Delay(100);
	mpr121_init(&hi2c1, (KEYPAD_ADDRESS<<1), &hi2c1);
	mpr121_init(&hi2c1, (WHEEL_ADDRESS<<1), &hi2c1);	
	//HAL_Delay(100);
	//lcd20x4_i2c_clear();	
	HAL_Delay(100);
	
	
	if(HAL_I2C_IsDeviceReady(&hi2c1, (KEYPAD_ADDRESS<<1), 2, 10) == HAL_OK)
		{
			lcd20x4_i2c_1stLine();
			HAL_Delay(50);
			lcd20x4_i2c_printf("Keypad Ready!");
		}
	else lcd20x4_i2c_printf("Keypad Init Failed");
	lcd20x4_i2c_2ndLine();	
		
	
	if(HAL_I2C_IsDeviceReady(&hi2c1, (WHEEL_ADDRESS<<1), 2, 10) == HAL_OK)
		{
			HAL_Delay(50);
			lcd20x4_i2c_printf("Wheel Ready!");
		}
	else lcd20x4_i2c_printf("Wheel Init Failed");
	lcd20x4_i2c_1stLine();
		
		
	HAL_Delay(1000);
	lcd20x4_i2c_clear();
	lcd20x4_i2c_cursorShow(1);
	
		
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
		
	i2cData[0] = 0x00;
	i2cData[1] = 0x00;
	i2cData[2] = 0x00;
	touchVal=0x000A;
	
  while (1)
  {
		
		if(MAIN_MENU_ENABLED == 1)
		{
			lcd20x4_i2c_clear();
			MenuDisplayUpdate(MainMenu);
			
			
			while(MAIN_MENU_ENABLED == 1)
			{
				HAL_Delay(1);	//Is there anything to do here?
			}
		}

		
		if(APPLICATION_ENABLED == 1)
		{
			lcd20x4_i2c_clear();
			lcd20x4_i2c_1stLine();
			lcd20x4_i2c_printf("Press 1 to go back");

			while(APPLICATION_ENABLED == 1)
			{
				//Is there anything to do here?
			}
		}		
		
		
		if(PIN_MAPPING_ENABLED == 1)
		{
			lcd20x4_i2c_clear();
			lcd20x4_i2c_1stLine();
			lcd20x4_i2c_printf("LED # 123");
			lcd20x4_i2c_2ndLine();
			lcd20x4_i2c_printf("RED: 255");
			lcd20x4_i2c_3rdLine();
			lcd20x4_i2c_printf("GRN: 255");
			lcd20x4_i2c_4thLine();
			lcd20x4_i2c_printf("BLU: 255");
			
			while(PIN_MAPPING_ENABLED == 1)
			{
				//Is there anything to do here?
			}
		}
		
			
		
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : Wheel_IRQ_Pin Keypad_IRQ_Pin */
  GPIO_InitStruct.Pin = Wheel_IRQ_Pin|Keypad_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	KEYPAD_IRQ = 0;
	
	//ensures that MPR121s aren't read while LCD is being written to
	I2C_HandleTypeDef *phi2c1 = &hi2c1;
	if (phi2c1->State != HAL_I2C_STATE_READY)
	{
		KEYPAD_IRQ = 1;
		return;
	}
	
	
	if(GPIO_Pin == Wheel_IRQ_Pin)
	{
		/*
		lcdColIndex++;
		if(lcdColIndex==20) 
		{
			lcdColIndex=0;
			lcdRowIndex++;
		}
		if(lcdRowIndex==4)
		{
			lcdRowIndex=0;
			lcd20x4_i2c_clear();
		*/
		
		while(HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
    {
    }
		lastWheelDir = wheelDir;
		wheelDir = mpr121_wheel(&hi2c1, (WHEEL_ADDRESS<<1), wheelDir);
		HAL_Delay(wheelReadDelayms);
		
		if (wheelDir == 'E' & lastWheelDir == 'N') MainMenu = MenuScrollUp(MainMenu);
		if (wheelDir == 'S' & lastWheelDir == 'E') MainMenu = MenuScrollUp(MainMenu);
		if (wheelDir == 'W' & lastWheelDir == 'S') MainMenu = MenuScrollUp(MainMenu);
		if (wheelDir == 'N' & lastWheelDir == 'W') MainMenu = MenuScrollUp(MainMenu);
		
		if (wheelDir == 'W' & lastWheelDir == 'N') MainMenu = MenuScrollDown(MainMenu);
		if (wheelDir == 'N' & lastWheelDir == 'E') MainMenu = MenuScrollDown(MainMenu);
		if (wheelDir == 'E' & lastWheelDir == 'S') MainMenu = MenuScrollDown(MainMenu);
		if (wheelDir == 'S' & lastWheelDir == 'W') MainMenu = MenuScrollDown(MainMenu);

		/*
		lcd20x4_i2c_1stLine();
		lcd20x4_i2c_setCursor(lcdRowIndex,lcdColIndex);
		lcd20x4_i2c_printf("%c", wheelDir);
		*/
	}	
	
	if(GPIO_Pin == Keypad_IRQ_Pin)
	   {
			
			//lcd20x4_i2c_clear(); 
			
			 uint8_t keypadVal;
			 while(HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
        {

        }
			 keypadVal = mpr121_keyPad(&hi2c1, (KEYPAD_ADDRESS<<1));
			 //lcd20x4_i2c_printf("Keypad value %i, keypadVal");

			 HAL_Delay(10);
			 
			 if(MAIN_MENU_ENABLED){
				 
				if(keypadVal==1)
				{
					APPLICATION_ENABLED = true;
					MAIN_MENU_ENABLED = false;
					return;
				}
					
				if(keypadVal==2) 
				{
					PIN_MAPPING_ENABLED = true;
					MAIN_MENU_ENABLED = false;
					return;
				}	
				return;
			 }
			 
			 if(APPLICATION_ENABLED)
				{
				 if(keypadVal==1)
				 {
					 MAIN_MENU_ENABLED = true;
					 APPLICATION_ENABLED = false;
					 return;
				 }
				 return;
				}
			 
			 if(PIN_MAPPING_ENABLED)
			 {
				 if(keypadVal==10)
				 {
					 MAIN_MENU_ENABLED = true;
					 PIN_MAPPING_ENABLED = false;
					 return;
				 }
				 return;
			 }
			
	   }
	
  
}

Menu_TypeDef MenuInit(Menu_TypeDef Menu)
{
	Menu.ArrayPtr = &Menu.Array[0];
	Menu.HighestRow=0;
	Menu.DisplayTopRow=0;
	Menu.DisplaySelectedRow=0;
	Menu.DisplayBottomRow = 3*MenuRowLength;
	Menu.LowestRow = MenuRowLength*(MenuColumnLength - 1);
	
	MenuSetRowText(Menu.ArrayPtr, 0, " Top of Main Menu");
	MenuSetRowText(Menu.ArrayPtr, 1, " Row 1");
	MenuSetRowText(Menu.ArrayPtr, 2, " Row 2");
	MenuSetRowText(Menu.ArrayPtr, 3, " Row 3");
	MenuSetRowText(Menu.ArrayPtr, 4, " Row 4");
	MenuSetRowText(Menu.ArrayPtr, 5, " Row 5");
	MenuSetRowText(Menu.ArrayPtr, 6, " Row 6");
	MenuSetRowText(Menu.ArrayPtr, 7, " Row 7");
	MenuSetRowText(Menu.ArrayPtr, 8, " Row 8");
	MenuSetRowText(Menu.ArrayPtr, 9, " Bottom of Menu");
	return Menu;	
}

Menu_TypeDef MenuScrollUp (Menu_TypeDef Menu)
{
	if(Menu.DisplaySelectedRow == Menu.HighestRow) return Menu;
	if(Menu.DisplaySelectedRow == Menu.DisplayTopRow)
	{
		Menu.DisplayTopRow = Menu.DisplayTopRow - MenuRowLength;
		Menu.DisplayBottomRow = Menu.DisplayBottomRow - MenuRowLength;
	}
	Menu.DisplaySelectedRow = Menu.DisplaySelectedRow - MenuRowLength;
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
	MenuDisplayUpdate(Menu);
	return Menu;
}

void MenuDisplayUpdate(Menu_TypeDef Menu)
{
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
		*(menuPtr + (MenuRowLength*rowNum) + rowIndex) = rowTxt[rowIndex];
		rowIndex++;
	}
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
