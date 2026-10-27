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
#define NUM_TLCS    12
//#include "usbd_cdc_if.h"
#include <string.h>
#include <stdbool.h>
#include "lcd20x4_i2c.h"
#include "mpr121.h"
#include "tlc5940.h"
#include "Array8x8Functions.h"
#include "LyrFrameFunctions.h"
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

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_RTC_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void fade_in_color(LyrFrame_TypeDef lyrFrame, bool mask[64], uint64_t color, uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_out_color(LyrFrame_TypeDef lyrFrame, bool mask[64], uint64_t color, uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_in_red(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_in_grn(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_in_blu(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t maxBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_out_red(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_out_grn(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay);
void fade_out_blu(LyrFrame_TypeDef lyrFrame, bool mask[64], uint16_t minBrightness, uint16_t deltaBrightness, uint16_t delay);
void previous_lyr_off(uint16_t activeLyr);
uint16_t current_lyr_on(uint16_t activeLyr);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

bool MAIN_MENU_ENABLED = 1;	
bool PIN_MAPPING_ENABLED = 0;
bool APPLICATION_ENABLED = 0;
bool KEYPAD_IRQ = 0; //when this is set, indicates that the keypad must be read
bool DONT_BLANK = 0;
bool UPDATE_FRAME = 0;

Frame_TypeDef frame0;

//lyr global variable indicates active cube layer.
//Needs to be global so timer IRQ can access value
uint8_t activeLyr = 0;

//Data Arrays & Pointers shese should probably not be global
// Data Arrays
uint16_t data16[16*NUM_TLCS];
uint8_t data8[24*NUM_TLCS];

// Data Pointers
uint16_t *data16Ptr = &data16[0];
uint8_t *data8Ptr = &data8[0];

// Needs to be global for convenient timer IRQ access
uint8_t initNumPM = 0;
uint16_t initValPM = 0;
uint16_t stepSizePM = 500;
uint16_t minValPM = 0;
uint16_t maxValPM = 4000;

uint16_t ledNumPM;
int16_t redValPM;
int16_t bluValPM;
int16_t grnValPM;

//Color Definition Begin
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

//Color Definition End

// This is how I'm manually specifying layer patterns for now!
bool mask0[64] = {1,1,1,1,1,1,1,1,
									1,0,0,0,0,0,0,1,
									1,0,0,0,0,0,0,1,
									1,0,0,0,0,0,0,1,
									1,0,0,0,0,0,0,1,
									1,0,0,0,0,0,0,1,
									1,0,0,0,0,0,0,1,
									1,1,1,1,1,1,1,1};

bool mask1[64] = {0,0,0,0,0,0,0,0,
									0,1,1,1,1,1,1,0,
									0,1,0,0,0,0,1,0,
									0,1,0,0,0,0,1,0,
									0,1,0,0,0,0,1,0,
									0,1,0,0,0,0,1,0,
									0,1,1,1,1,1,1,0,
									0,0,0,0,0,0,0,0};

bool mask2[64] = {0,0,0,0,0,0,0,0,
									0,0,0,0,0,0,0,0,
									0,0,1,1,1,1,0,0,
									0,0,1,0,0,1,0,0,
									0,0,1,0,0,1,0,0,
									0,0,1,1,1,1,0,0,
									0,0,0,0,0,0,0,0,
									0,0,0,0,0,0,0,0};

bool mask3[64] = {0,0,0,0,0,0,0,0,
									0,0,0,0,0,0,0,0,
									0,0,0,0,0,0,0,0,
									0,0,0,1,1,0,0,0,
									0,0,0,1,1,0,0,0,
									0,0,0,0,0,0,0,0,
									0,0,0,0,0,0,0,0,
									0,0,0,0,0,0,0,0};

bool mask4[64] = {1,1,1,1,1,1,1,1,
									1,0,0,0,0,0,0,1,
									1,0,1,1,1,1,0,1,
									1,0,1,0,0,1,0,1,
									1,0,1,0,0,1,0,1,
									1,0,1,1,1,1,0,1,
									1,0,0,0,0,0,0,1,
									1,1,1,1,1,1,1,1};

bool mask5[64] = {1,1,1,1,1,1,1,1,
									1,1,0,0,0,0,1,1,
									1,0,1,0,0,1,0,1,
									1,0,0,1,1,0,0,1,
									1,0,0,1,1,0,0,1,
									1,0,1,0,0,1,0,1,
									1,1,0,0,0,0,1,1,
									1,1,1,1,1,1,1,1};

bool mask6[64] = {0,0,0,0,0,0,0,0,
									1,1,1,1,1,1,1,1,
									0,0,0,0,0,0,0,0,
									1,1,1,1,1,1,1,1,
									0,0,0,0,0,0,0,1,
									1,1,1,1,1,1,1,1,
									0,0,0,0,0,0,0,0,
									1,1,1,1,1,1,1,1};

bool mask7[64] = {1,1,1,1,1,1,1,1,
									0,0,0,0,0,0,0,0,
									1,1,1,1,1,1,1,1,
									0,0,0,0,0,0,0,0,
									1,1,1,1,1,1,1,1,
									0,0,0,0,0,0,0,0,
									1,1,1,1,1,1,1,1,
									0,0,0,0,0,0,0,0};

bool maskAll[64] = {1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1};									

bool *mask0Ptr = &mask0[0];
bool *mask1Ptr = &mask1[0];
bool *mask2Ptr = &mask2[0];
bool *mask3Ptr = &mask3[0];
bool *mask4Ptr = &mask4[0];
bool *mask5Ptr = &mask5[0];
bool *mask6Ptr = &mask6[0];
bool *mask7Ptr = &mask7[0];
										
// pin mapping - this should never need to be reconfigured now that all the cabling as been eliminated :^)
int redMap[64] = {178,181,160,163,166,145,148,151,189,186,175,172,169,158,155,152,130,133,112,115,118,97,100,103,141,138,127,124,121,110,107,104,82,85,64,67,70,49,52,55,93,90,79,76,73,62,59,56,34,37,16,19,22,1,4,7,45,42,31,28,25,14,11,8};
int grnMap[64] = {177,180,183,162,165,144,147,150,190,187,184,173,170,159,156,153,129,132,135,114,117,96,99,102,142,139,136,125,122,111,108,105,81,84,87,66,69,48,51,54,94,91,88,77,74,63,60,57,33,36,39,18,21,0,3,6,46,43,40,29,26,15,12,9};
int bluMap[64] = {176,179,182,161,164,167,146,149,191,188,185,174,171,168,157,154,128,131,134,113,116,119,98,101,143,140,137,126,123,120,109,106,80,83,86,65,68,71,50,53,95,92,89,78,75,72,61,58,32,35,38,17,20,23,2,5,47,44,41,30,27,24,13,10};
	
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_RTC_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	
	//have to manually set the pointers
	frame0.lyr0.redArrPtr = &frame0.lyr0.redArray[0];
	frame0.lyr0.grnArrPtr = &frame0.lyr0.grnArray[0];
	frame0.lyr0.bluArrPtr = &frame0.lyr0.bluArray[0];
	
	// This pin referencing is slightly redundant. L8 needs to be set since it's toggled during timXocstart (158)
	HAL_GPIO_WritePin(L8_EN_GPIO_Port, L8_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(L7_EN_GPIO_Port, L7_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(L6_EN_GPIO_Port, L6_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(L5_EN_GPIO_Port, L5_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(L4_EN_GPIO_Port, L4_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(L3_EN_GPIO_Port, L3_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(L2_EN_GPIO_Port, L2_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(L1_EN_GPIO_Port, L1_EN_Pin, GPIO_PIN_RESET);


	HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_2);	//
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_4);	//this was working with ch1 even though thats set as a gpio!

	// LCD & MPR121 INIT BEGIN
	lcd20x4_i2c_init(&hi2c1);
	HAL_Delay(100);
	mpr121_init(&hi2c1, (KEYPAD_ADDRESS<<1), &hi2c1);	
	HAL_Delay(100);
	mpr121_init(&hi2c1, (WHEEL_ADDRESS<<1), &hi2c1);
	HAL_Delay(100);
	lcd20x4_i2c_clear();
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
		
	HAL_GPIO_WritePin(L8_EN_GPIO_Port, L8_EN_Pin, GPIO_PIN_SET);	
	
	//LCD & MPR121 INIT END
	
	HAL_SPI_Init(&hspi1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    
		if(MAIN_MENU_ENABLED == 1)
		{
			
			tlc_clear(data16Ptr);
			tlc_update(hspi1,data16Ptr,data8Ptr);
			lcd20x4_i2c_clear();
			lcd20x4_i2c_1stLine();
			lcd20x4_i2c_printf("Main Menu");
			lcd20x4_i2c_2ndLine();
			lcd20x4_i2c_printf("1 - Application");
			lcd20x4_i2c_3rdLine();
			lcd20x4_i2c_printf("2 - Pin Mapping");	
			
			while(MAIN_MENU_ENABLED == 1)
			{
				HAL_Delay(50);
			}
		}
		
		if(APPLICATION_ENABLED == 1)
		{
			lcd20x4_i2c_clear();
			lcd20x4_i2c_1stLine();
			lcd20x4_i2c_printf("Press 3 to go back");
						

			while(APPLICATION_ENABLED == 1)
			{
				
				uint16_t maxBrightness = 4000;
				uint16_t minBrightness = 0;
				uint16_t deltaBrightness = 100;
				uint16_t delay = 10;
				
				
				uint64_t colorWheel[12] = {red,orange,yellow,yelgrn,green,seafoam,cyan,lightblu,blue,indigo,purple,pink};	
				int caseNum = 0;
		
				while (caseNum<12)
				{
					fade_in_color(frame0.lyr0,mask0,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
					fade_out_color(frame0.lyr0,mask0,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
					HAL_Delay(500);
					caseNum++;
					
					fade_in_color(frame0.lyr0,mask1,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
					fade_out_color(frame0.lyr0,mask1,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
					HAL_Delay(500);
					caseNum++;
					
					fade_in_color(frame0.lyr0,mask2,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
					fade_out_color(frame0.lyr0,mask2,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
					HAL_Delay(500);
					caseNum++;
					
					fade_in_color(frame0.lyr0,mask3,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
					fade_out_color(frame0.lyr0,mask3,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
					HAL_Delay(500);
					caseNum++;
					
					fade_in_color(frame0.lyr0,mask2,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
					fade_out_color(frame0.lyr0,mask2,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
					HAL_Delay(500);
					caseNum++;
					
					fade_in_color(frame0.lyr0,mask1,colorWheel[caseNum],maxBrightness,deltaBrightness,delay);					
					fade_out_color(frame0.lyr0,mask1,colorWheel[caseNum],minBrightness,deltaBrightness,delay);
					HAL_Delay(500);
					caseNum++;
					
				}
				
				
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
			
			ledNumPM = initNumPM;
			redValPM = initValPM;
			bluValPM = initValPM;
			grnValPM = initValPM;

			
			while(PIN_MAPPING_ENABLED == 1)
			{
				tlc_clear(data16Ptr);
				tlc_set_led(data16Ptr,redMap[ledNumPM],redValPM);
				tlc_set_led(data16Ptr,grnMap[ledNumPM],grnValPM);
				tlc_set_led(data16Ptr,bluMap[ledNumPM],bluValPM);
				tlc_update(hspi1, data16Ptr,data8Ptr);
				
				lcd20x4_i2c_clear();
				lcd20x4_i2c_1stLine();
				lcd20x4_i2c_printf("LED # %d", ledNumPM);
				lcd20x4_i2c_2ndLine();
				lcd20x4_i2c_printf("RED: %d", redValPM);
				lcd20x4_i2c_3rdLine();
				lcd20x4_i2c_printf("GRN: %d", grnValPM);
				lcd20x4_i2c_4thLine();
				lcd20x4_i2c_printf("BLU: %d", bluValPM);				

			}
		}
	}
}		
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  
  /* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 16383;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */
	sConfigOC.OCMode = TIM_OCMODE_PWM2;
  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
  sConfigOC.Pulse = 1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */
	sConfigOC.Pulse = 1;
  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, XLAT_3V3_Pin|BLANK_3V3_Pin|ESP8266_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DCPRG_3V3_Pin|VPRG_3V3_Pin|L3_EN_Pin|L4_EN_Pin 
                          |L5_EN_Pin|L6_EN_Pin|L7_EN_Pin|L8_EN_Pin 
                          |L1_EN_Pin|L2_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : XLAT_3V3_Pin BLANK_3V3_Pin ESP8266_EN_Pin */
  GPIO_InitStruct.Pin = XLAT_3V3_Pin|BLANK_3V3_Pin|ESP8266_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DCPRG_3V3_Pin VPRG_3V3_Pin L3_EN_Pin L4_EN_Pin 
                           L5_EN_Pin L6_EN_Pin L7_EN_Pin L8_EN_Pin 
                           L1_EN_Pin L2_EN_Pin */
  GPIO_InitStruct.Pin = DCPRG_3V3_Pin|VPRG_3V3_Pin|L3_EN_Pin|L4_EN_Pin 
                          |L5_EN_Pin|L6_EN_Pin|L7_EN_Pin|L8_EN_Pin 
                          |L1_EN_Pin|L2_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : XERR_Pin */
  GPIO_InitStruct.Pin = XERR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(XERR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Keypad_IRQ_Pin Wheel_IRQ_Pin */
  GPIO_InitStruct.Pin = Keypad_IRQ_Pin|Wheel_IRQ_Pin;
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
	
	uint8_t keypadVal;	
	

	keypadVal = mpr121_keyPad(&hi2c1, (KEYPAD_ADDRESS<<1));
	HAL_Delay(50);
	if(GPIO_Pin == Keypad_IRQ_Pin)
	{
		if(MAIN_MENU_ENABLED == true)
		{
			if(keypadVal == 1)
			{
				APPLICATION_ENABLED = true;
				MAIN_MENU_ENABLED = false;
				return;
			}
			
			if(keypadVal == 2)
			{
				PIN_MAPPING_ENABLED = true;
				MAIN_MENU_ENABLED = false;
				return;
			}
			return;
		}
		
		if(APPLICATION_ENABLED == true)
		{
			if(keypadVal == 3)
			{
				//MAIN_MENU_ENABLED = true;
				//APPLICATION_ENABLED = false;
				return;
			}
			return;
		}

		if(PIN_MAPPING_ENABLED == true)
		{
			if(keypadVal == 1)
				redValPM=redValPM + stepSizePM;
				if (redValPM > maxValPM) redValPM = 0;
			if(keypadVal == 2)
				bluValPM=grnValPM + stepSizePM;
				if (bluValPM > maxValPM) bluValPM = 0;
			if(keypadVal == 3)
				grnValPM=bluValPM + stepSizePM;
				if (grnValPM > maxValPM) grnValPM = 0;
			if(keypadVal == 4)
			{
				if (ledNumPM==0) ledNumPM = 64;
				ledNumPM--;
			}
			if(keypadVal == 6)
			{
				ledNumPM++;
				if (ledNumPM==64) ledNumPM = 0;
			}
			if(keypadVal == 7)
				redValPM=redValPM - stepSizePM;
				if (redValPM < minValPM) redValPM = maxValPM;
			if(keypadVal == 8)
				grnValPM=grnValPM - stepSizePM;
				if (grnValPM < minValPM) grnValPM = maxValPM;
			if(keypadVal == 9)
				bluValPM=bluValPM - stepSizePM;
				if (bluValPM < minValPM) bluValPM = maxValPM;
			if(keypadVal == 10)
			{
				MAIN_MENU_ENABLED = true;
				PIN_MAPPING_ENABLED = false;
				return;
			}
			return;
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{	
	if(UPDATE_FRAME==0)
	{
		previous_lyr_off(activeLyr);
		HAL_GPIO_WritePin(BLANK_3V3_GPIO_Port, BLANK_3V3_Pin, GPIO_PIN_SET);
		for(uint16_t dummyVar =1;dummyVar<15;dummyVar++); // short delay (approx 3us)
		HAL_GPIO_WritePin(BLANK_3V3_GPIO_Port, BLANK_3V3_Pin, GPIO_PIN_RESET);
		activeLyr =  current_lyr_on(activeLyr);
		return;
	}
	
	if(UPDATE_FRAME==1)
	{
		previous_lyr_off(activeLyr);
		tlc_spi_convert(data16Ptr, data8Ptr);
		HAL_SPI_Transmit(&hspi1, data8Ptr, 24*NUM_TLCS, 10);
		HAL_GPIO_WritePin(BLANK_3V3_GPIO_Port, BLANK_3V3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(XLAT_3V3_GPIO_Port, XLAT_3V3_Pin, GPIO_PIN_SET);
		for(uint16_t dummyVar =1;dummyVar<15;dummyVar++); // short delay (approx 3us)
		HAL_GPIO_WritePin(XLAT_3V3_GPIO_Port, XLAT_3V3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BLANK_3V3_GPIO_Port, BLANK_3V3_Pin, GPIO_PIN_RESET);
		UPDATE_FRAME=0;
		activeLyr =  current_lyr_on(activeLyr);
		return;
	}
}
	
	
	//I think blank should be toggled in this callback for improved synchronization
	/*
	if(activeLyr==0)
	{
		HAL_GPIO_TogglePin(L8_EN_GPIO_Port, L8_EN_Pin); //turn off previous layer
		tlc_clear(data16Ptr);
		tlc_set_lyr(data16Ptr,seafoam,mask5);
		tlc_update(data16Ptr,data8Ptr);
		HAL_GPIO_TogglePin(L1_EN_GPIO_Port, L1_EN_Pin);	//turn on current layer
	}

	if(activeLyr==1){
		HAL_GPIO_TogglePin(L1_EN_GPIO_Port, L1_EN_Pin);
		tlc_clear(data16Ptr);
		tlc_set_lyr(data16Ptr,red,mask5);
		tlc_update(data16Ptr,data8Ptr);
		HAL_GPIO_TogglePin(L2_EN_GPIO_Port, L2_EN_Pin);}

	if(activeLyr==2){
		HAL_GPIO_TogglePin(L2_EN_GPIO_Port, L2_EN_Pin);
		tlc_clear(data16Ptr);
		tlc_set_lyr(data16Ptr,cyan,mask5);
		tlc_update(data16Ptr,data8Ptr);
		HAL_GPIO_TogglePin(L3_EN_GPIO_Port, L3_EN_Pin);}

	if(activeLyr==3){
		HAL_GPIO_TogglePin(L3_EN_GPIO_Port, L3_EN_Pin);
		tlc_clear(data16Ptr);
		tlc_set_lyr(data16Ptr,purple,mask5);
		tlc_update(data16Ptr,data8Ptr);
		HAL_GPIO_TogglePin(L4_EN_GPIO_Port, L4_EN_Pin);}

	if(activeLyr==4){
		HAL_GPIO_TogglePin(L4_EN_GPIO_Port, L4_EN_Pin);
		tlc_clear(data16Ptr);
		tlc_set_lyr(data16Ptr,pink,mask5);
		tlc_update(data16Ptr,data8Ptr);
		HAL_GPIO_TogglePin(L5_EN_GPIO_Port, L5_EN_Pin);}

	if(activeLyr==5){
		HAL_GPIO_TogglePin(L5_EN_GPIO_Port, L5_EN_Pin);
		tlc_clear(data16Ptr);
		tlc_set_lyr(data16Ptr,frameColor,mask5);
		tlc_update(data16Ptr,data8Ptr);
		HAL_GPIO_TogglePin(L6_EN_GPIO_Port, L6_EN_Pin);}

	if(activeLyr==6){
		HAL_GPIO_TogglePin(L6_EN_GPIO_Port, L6_EN_Pin);
		tlc_clear(data16Ptr);
		tlc_set_lyr(data16Ptr,blue,mask5);
		tlc_update(data16Ptr,data8Ptr);
		HAL_GPIO_TogglePin(L7_EN_GPIO_Port, L7_EN_Pin);}

	if(activeLyr==7){
		HAL_GPIO_TogglePin(L7_EN_GPIO_Port, L7_EN_Pin);
		tlc_clear(data16Ptr);
		tlc_set_lyr(data16Ptr,green,mask5);
		tlc_update(data16Ptr,data8Ptr);
		HAL_GPIO_TogglePin(L8_EN_GPIO_Port, L8_EN_Pin);}

	
	if(activeLyr==8) activeLyr = 0;
	*/
	
void previous_lyr_off(uint16_t activeLyr)
{
	if(activeLyr == 0) HAL_GPIO_TogglePin(L8_EN_GPIO_Port, L8_EN_Pin);
	if(activeLyr == 1) HAL_GPIO_TogglePin(L1_EN_GPIO_Port, L1_EN_Pin);
	if(activeLyr == 2) HAL_GPIO_TogglePin(L2_EN_GPIO_Port, L2_EN_Pin);
	if(activeLyr == 3) HAL_GPIO_TogglePin(L3_EN_GPIO_Port, L3_EN_Pin);
	if(activeLyr == 4) HAL_GPIO_TogglePin(L4_EN_GPIO_Port, L4_EN_Pin);
	if(activeLyr == 5) HAL_GPIO_TogglePin(L5_EN_GPIO_Port, L5_EN_Pin);
	if(activeLyr == 6) HAL_GPIO_TogglePin(L6_EN_GPIO_Port, L6_EN_Pin);
	if(activeLyr == 7) HAL_GPIO_TogglePin(L7_EN_GPIO_Port, L7_EN_Pin);
}
	
uint16_t current_lyr_on(uint16_t activeLyr)
{
	if(activeLyr == 0) HAL_GPIO_TogglePin(L1_EN_GPIO_Port, L1_EN_Pin);
	if(activeLyr == 1) HAL_GPIO_TogglePin(L2_EN_GPIO_Port, L2_EN_Pin);
	if(activeLyr == 2) HAL_GPIO_TogglePin(L3_EN_GPIO_Port, L3_EN_Pin);
	if(activeLyr == 3) HAL_GPIO_TogglePin(L4_EN_GPIO_Port, L4_EN_Pin);
	if(activeLyr == 4) HAL_GPIO_TogglePin(L5_EN_GPIO_Port, L5_EN_Pin);
	if(activeLyr == 5) HAL_GPIO_TogglePin(L6_EN_GPIO_Port, L6_EN_Pin);
	if(activeLyr == 6) HAL_GPIO_TogglePin(L7_EN_GPIO_Port, L7_EN_Pin);
	if(activeLyr == 7) HAL_GPIO_TogglePin(L8_EN_GPIO_Port, L8_EN_Pin);
	activeLyr++;
	if(activeLyr==8) activeLyr = 0;
	return activeLyr;
}

	
//void CDC_ReceiveCallBack(uint8_t *buf, uint32_t len){
//	CDC_Transmit_FS(buf, len);
//}

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
		if(currentBrightness==4000) HAL_Delay(1);
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
