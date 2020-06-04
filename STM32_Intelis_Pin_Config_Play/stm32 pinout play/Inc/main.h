/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define NC_Pin GPIO_PIN_13
#define NC_GPIO_Port GPIOC
#define NCH0_Pin GPIO_PIN_0
#define NCH0_GPIO_Port GPIOH
#define NCH1_Pin GPIO_PIN_1
#define NCH1_GPIO_Port GPIOH
#define PMIC_SYNC_Pin GPIO_PIN_2
#define PMIC_SYNC_GPIO_Port GPIOC
#define RADIO_RSTN_ADI_Pin GPIO_PIN_3
#define RADIO_RSTN_ADI_GPIO_Port GPIOC
#define RADIO_GPIO2_ADI_Pin GPIO_PIN_0
#define RADIO_GPIO2_ADI_GPIO_Port GPIOA
#define RADIO_GPIO3_ADI_Pin GPIO_PIN_1
#define RADIO_GPIO3_ADI_GPIO_Port GPIOA
#define RADIO_GPIO4_ADI_Pin GPIO_PIN_2
#define RADIO_GPIO4_ADI_GPIO_Port GPIOA
#define RADIO_GPIO6_ADI_Pin GPIO_PIN_3
#define RADIO_GPIO6_ADI_GPIO_Port GPIOA
#define VB_EN_Pin GPIO_PIN_4
#define VB_EN_GPIO_Port GPIOA
#define RADIO_SPI_SCLK_Pin GPIO_PIN_5
#define RADIO_SPI_SCLK_GPIO_Port GPIOA
#define RADIO_SPI_MISO_Pin GPIO_PIN_6
#define RADIO_SPI_MISO_GPIO_Port GPIOA
#define RADIO_SPI_MOSI_Pin GPIO_PIN_7
#define RADIO_SPI_MOSI_GPIO_Port GPIOA
#define FLASH_PWR_ENB_N_Pin GPIO_PIN_0
#define FLASH_PWR_ENB_N_GPIO_Port GPIOB
#define NCB1_Pin GPIO_PIN_1
#define NCB1_GPIO_Port GPIOB
#define TCXO_PWR_Pin GPIO_PIN_2
#define TCXO_PWR_GPIO_Port GPIOB
#define RADIO_TCXO_ADI_Pin GPIO_PIN_10
#define RADIO_TCXO_ADI_GPIO_Port GPIOB
#define NCB11_Pin GPIO_PIN_11
#define NCB11_GPIO_Port GPIOB
#define FLASH_SPI_CSN_Pin GPIO_PIN_12
#define FLASH_SPI_CSN_GPIO_Port GPIOB
#define FLASH_SPI_SCK_Pin GPIO_PIN_13
#define FLASH_SPI_SCK_GPIO_Port GPIOB
#define FLASH_SPI_MISO_Pin GPIO_PIN_14
#define FLASH_SPI_MISO_GPIO_Port GPIOB
#define FLASH_SPI_MOSI_Pin GPIO_PIN_15
#define FLASH_SPI_MOSI_GPIO_Port GPIOB
#define RL78_SPI_CSN_Pin GPIO_PIN_6
#define RL78_SPI_CSN_GPIO_Port GPIOC
#define RL78_BUSY_ASK_ME_Pin GPIO_PIN_9
#define RL78_BUSY_ASK_ME_GPIO_Port GPIOC
#define PMIC_V1_ADJ_Pin GPIO_PIN_9
#define PMIC_V1_ADJ_GPIO_Port GPIOA
#define RADIO_SPI_CSN_Pin GPIO_PIN_10
#define RADIO_SPI_CSN_GPIO_Port GPIOA
#define PMIC_V3_EN_Pin GPIO_PIN_11
#define PMIC_V3_EN_GPIO_Port GPIOA
#define EN1_Pin GPIO_PIN_12
#define EN1_GPIO_Port GPIOA
#define BSL_TX_Pin GPIO_PIN_12
#define BSL_TX_GPIO_Port GPIOC
#define BSL_RX_Pin GPIO_PIN_2
#define BSL_RX_GPIO_Port GPIOD
#define FW_TST_SIG2_Pin GPIO_PIN_6
#define FW_TST_SIG2_GPIO_Port GPIOB
#define FW_TST_SIG1_Pin GPIO_PIN_7
#define FW_TST_SIG1_GPIO_Port GPIOB
#define FEM_ENABLE_CSD_Pin GPIO_PIN_8
#define FEM_ENABLE_CSD_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
