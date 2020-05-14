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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define NUM_TLCS    12
//#include "arrayFunctions.h"
//#include "usbd_cdc_if.h"
#include <string.h>
#include <stdbool.h>
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
void spi_convert(uint16_t *data16, uint8_t *data8);
void tlc_clear(uint16_t *data16);
void tlc_set_led(uint16_t *data16, int number, uint16_t brightness);
void tlc_update(uint16_t *data16, uint8_t *data8);
void intToStr(uint8_t *numVal, uint8_t *strVal);
void maskCopy(bool *maskPtr, bool *patternPtr);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

typedef struct __Frame_TypeDef{
	bool lyr0Mask[64];
	bool lyr1Mask[64];
	bool lyr2Mask[64];
	bool lyr3Mask[64];
	bool lyr4Mask[64];
	bool lyr5Mask[64];
	bool lyr6Mask[64];
	bool lyr7Mask[64];
	uint64_t lyr0Color;
	uint64_t lyr1Color;
	uint64_t lyr2Color;
	uint64_t lyr3Color;
	uint64_t lyr4Color;
	uint64_t lyr5Color;
	uint64_t lyr6Color;
	uint64_t lyr7Color;
} Frame_TypeDef;

Frame_TypeDef frame1;

//lyr global variable indicates active cube layer.
//Needs to be global so timer IRQ can access value
uint8_t activeLyr = 0;

//Data Arrays&Pointers Need to be global for a reason. I will specify why once I remember.
// Data Arrays
uint16_t data16[16*NUM_TLCS];
uint8_t data8[24*NUM_TLCS];
// Data Pointers
uint8_t *data8Ptr = &data8[0];
uint16_t *data16Ptr = &data16[0];

// Current mapping. Reconfigure as needed :^)
// Needs to be global for convenient timer IRQ access

int redMap[64] = {154,145,176,185,179,188,182,191,158,149,128,137,131,140,134,143,113,122,116,125,119,108,102,111,161,170,164,173,167,104,98,107,33,42,36,45,39,12,6,15,81,90,84,93,87,8,2,11,49,58,52,61,55,19,25,16,65,74,68,77,71,23,29,20};
int grnMap[64] = {147,153,144,177,186,180,189,183,151,157,148,129,138,132,141,135,120,114,123,117,126,100,109,103,168,162,171,165,174,96,105,99,40,34,43,37,46,4,13,7,88,82,91,85,94,0,9,3,56,50,59,53,62,27,18,24,72,66,75,69,78,31,22,28};;
int bluMap[64] = {155,146,152,184,178,187,181,190,159,150,156,136,130,139,133,142,112,121,115,124,118,127,101,110,160,169,163,172,166,175,97,106,32,41,35,44,38,47,5,14,80,89,83,92,86,95,1,10,48,57,51,60,54,63,26,17,64,73,67,76,70,79,30,21};

//Color Definition Begin
uint64_t red = 				0x0fff00000000;
uint64_t green = 			0x00000fff0000;
uint64_t blue = 			0x000000000fff;
uint64_t yellow = 		0x0fff0fff0000;
uint64_t purple = 		0x0fff00000fff;
uint64_t cyan = 			0x00000fff0fff;
uint64_t orange = 		0x0fff08000000;
uint64_t pink = 			0x0fff0c0f0cbf;
uint64_t seafoam = 		0x071f0eef0b8f;
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

bool *mask0Ptr = &mask0[0];
bool *mask1Ptr = &mask1[0];
bool *mask2Ptr = &mask2[0];
bool *mask3Ptr = &mask3[0];
bool *mask4Ptr = &mask4[0];
bool *mask5Ptr = &mask5[0];
bool *mask6Ptr = &mask6[0];
bool *mask7Ptr = &mask7[0];

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

	frame1.lyr0Color = cyan;

	//set indicates power off (pin is open drain); reset indicates power on (pin is grounded)
	// This pin referencing is slightly redundant. L8 needs to be reset since it's toggled during tim5ocstart (158)
	HAL_GPIO_WritePin(L8_EN_GPIO_Port, L8_EN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(L7_EN_GPIO_Port, L7_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(L6_EN_GPIO_Port, L6_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(L5_EN_GPIO_Port, L5_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(L4_EN_GPIO_Port, L4_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(L3_EN_GPIO_Port, L3_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(L2_EN_GPIO_Port, L2_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(L1_EN_GPIO_Port, L1_EN_Pin, GPIO_PIN_RESET);


	HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_2);	//
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_1);	//


	//HAL_SPI_Init(&hspi1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	HAL_Delay(100);
	//maskCopy(maskPtr,testPtr);

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
  if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM2;
  sConfigOC.Pulse = 16383;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
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
  HAL_GPIO_WritePin(GPIOA, XLAT_3V3_Pin|ESP8266_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DCPRG_3V3_Pin|VPRG_3V3_Pin|L3_EN_Pin|L4_EN_Pin 
                          |L5_EN_Pin|L6_EN_Pin|L7_EN_Pin|L8_EN_Pin 
                          |L1_EN_Pin|L2_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : XLAT_3V3_Pin ESP8266_EN_Pin */
  GPIO_InitStruct.Pin = XLAT_3V3_Pin|ESP8266_EN_Pin;
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
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void maskCopy(bool *maskPtr, bool *patternPtr)
{
	for (int index=0;index<64;index++)
	{
		*(patternPtr + index) = *(maskPtr + index);
	}
};

void tlc_set_led(uint16_t *data16, int number, uint16_t brightness){

	*(data16 + number) = brightness;

}

// Function sets the entire TLC data16 array. requires a color and a pattern mask.
void tlc_set_lyr(uint16_t *data16, uint64_t color, bool mask[64])
{
	// color takes form 0x0RRR0GGG0BBB
	uint16_t red = (color>>32);
	uint16_t grn = (color>>16);
	uint16_t blu = (color>>0);

	for(int index=0;index<64;index++)
	{
		if ( mask[index] == 1)
		{
			*(data16 + redMap[index]) = red;
			*(data16 + grnMap[index]) = grn;
			*(data16 + bluMap[index]) = blu;
		}
	}

}


void tlc_clear(uint16_t *data16){

		for(int i=0; i<24*NUM_TLCS;i++){
		*(data16Ptr + i) = 0;
	}

}

void tlc_update(uint16_t *data16, uint8_t *data8){

	spi_convert(data16Ptr, data8Ptr);

	HAL_SPI_Transmit(&hspi1, data8, 24*NUM_TLCS, 10);
	HAL_GPIO_WritePin(XLAT_3V3_GPIO_Port, XLAT_3V3_Pin, GPIO_PIN_SET);
	// short delay (approx 3us)
	for(uint16_t dummyVar =1;dummyVar<15;dummyVar++);
	HAL_GPIO_WritePin(XLAT_3V3_GPIO_Port, XLAT_3V3_Pin, GPIO_PIN_RESET);

}

void spi_convert(uint16_t *data16, uint8_t *data8){

	int index8 = 0;
	int index16 = 0;
	int i = 0;

 while (index8 < 24*NUM_TLCS){
 switch (i) {

      case 0:
				*(data8 + index8) = *(data16 + index16);
				index8++;
        i++;
        break;

      case 1:
				*(data8 + index8) = ( (( (*(data16 + (index16 + 1))<<4) & 0xF0) >> 4) | ( ((*(data16 + index16)>>8) & 0x0F ) << 4));
				index8++;
        i++;
        break;

      case 2:
				*(data8 + index8) = (*(data16 + (index16 + 1))>>4);
				index8++;
				index16 = index16 + 2;
        i=0;
        break;}
			}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
//I think blank should be toggled in this callback for improved synchronization


	if(activeLyr==0){
		HAL_GPIO_TogglePin(L8_EN_GPIO_Port, L8_EN_Pin);
		tlc_clear(data16Ptr);
		tlc_set_lyr(data16Ptr,seafoam,mask5);
		tlc_update(data16Ptr,data8Ptr);
		HAL_GPIO_TogglePin(L1_EN_GPIO_Port, L1_EN_Pin);}

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
		tlc_set_lyr(data16Ptr,yellow,mask5);
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

	activeLyr++;
	if(activeLyr==8) activeLyr = 0;
}

//void CDC_ReceiveCallBack(uint8_t *buf, uint32_t len){
//	CDC_Transmit_FS(buf, len);
//}

//function defined specifically to convert integers 0~192 into strings
void intToStr(uint8_t *numVal, uint8_t *strVal)
{
	*(strVal) = (*(numVal)/100) + '0';
	*(strVal + 1) = ((*(numVal)%100)/10) + '0';
	*(strVal + 2) = (*(numVal)%10) + '0';
	*(strVal + 3) = '\n';
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
