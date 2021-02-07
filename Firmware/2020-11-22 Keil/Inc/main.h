/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "menu_system.h"
#include "animations.h"
#include "tlc5940.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */


/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GSCK_3V3_Pin GPIO_PIN_1
#define GSCK_3V3_GPIO_Port GPIOA
#define XLAT_3V3_Pin GPIO_PIN_4
#define XLAT_3V3_GPIO_Port GPIOA
#define SCLK_3V3_Pin GPIO_PIN_5
#define SCLK_3V3_GPIO_Port GPIOA
#define SOUT_3V3_Pin GPIO_PIN_6
#define SOUT_3V3_GPIO_Port GPIOA
#define SIN_3V3_Pin GPIO_PIN_7
#define SIN_3V3_GPIO_Port GPIOA
#define DCPRG_3V3_Pin GPIO_PIN_0
#define DCPRG_3V3_GPIO_Port GPIOB
#define VPRG_3V3_Pin GPIO_PIN_1
#define VPRG_3V3_GPIO_Port GPIOB
#define L3_EN_Pin GPIO_PIN_10
#define L3_EN_GPIO_Port GPIOB
#define L4_EN_Pin GPIO_PIN_11
#define L4_EN_GPIO_Port GPIOB
#define L5_EN_Pin GPIO_PIN_12
#define L5_EN_GPIO_Port GPIOB
#define L6_EN_Pin GPIO_PIN_13
#define L6_EN_GPIO_Port GPIOB
#define L7_EN_Pin GPIO_PIN_14
#define L7_EN_GPIO_Port GPIOB
#define L8_EN_Pin GPIO_PIN_15
#define L8_EN_GPIO_Port GPIOB
#define BLANK_3V3_Pin GPIO_PIN_8
#define BLANK_3V3_GPIO_Port GPIOA
#define ESP8266_RX_STM32_TX_Pin GPIO_PIN_9
#define ESP8266_RX_STM32_TX_GPIO_Port GPIOA
#define ESP8266_TX_STM32_RX_Pin GPIO_PIN_10
#define ESP8266_TX_STM32_RX_GPIO_Port GPIOA
#define ESP8266_EN_Pin GPIO_PIN_15
#define ESP8266_EN_GPIO_Port GPIOA
#define XERR_Pin GPIO_PIN_3
#define XERR_GPIO_Port GPIOB
#define Keypad_IRQ_Pin GPIO_PIN_4
#define Keypad_IRQ_GPIO_Port GPIOB
#define Keypad_IRQ_EXTI_IRQn EXTI4_IRQn
#define Wheel_IRQ_Pin GPIO_PIN_5
#define Wheel_IRQ_GPIO_Port GPIOB
#define Wheel_IRQ_EXTI_IRQn EXTI9_5_IRQn
#define L1_EN_Pin GPIO_PIN_8
#define L1_EN_GPIO_Port GPIOB
#define L2_EN_Pin GPIO_PIN_9
#define L2_EN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
