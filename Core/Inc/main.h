/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define AD_BLDC_CUR1_Pin GPIO_PIN_0
#define AD_BLDC_CUR1_GPIO_Port GPIOA
#define AD_BLDC_CUR2_Pin GPIO_PIN_1
#define AD_BLDC_CUR2_GPIO_Port GPIOA
#define AD_BLDC_CUR3_Pin GPIO_PIN_2
#define AD_BLDC_CUR3_GPIO_Port GPIOA
#define GPE3_BLDC_HU_Pin GPIO_PIN_3
#define GPE3_BLDC_HU_GPIO_Port GPIOA
#define GPE3_BLDC_HU_EXTI_IRQn EXTI3_IRQn
#define GPE4_BLDC_HV_Pin GPIO_PIN_4
#define GPE4_BLDC_HV_GPIO_Port GPIOA
#define GPE4_BLDC_HV_EXTI_IRQn EXTI4_IRQn
#define GPE5_BLDC_HW_Pin GPIO_PIN_5
#define GPE5_BLDC_HW_GPIO_Port GPIOA
#define GPE5_BLDC_HW_EXTI_IRQn EXTI9_5_IRQn
#define AD_PRESS_SEN_Pin GPIO_PIN_6
#define AD_PRESS_SEN_GPIO_Port GPIOA
#define AD_LINK_CURR_Pin GPIO_PIN_7
#define AD_LINK_CURR_GPIO_Port GPIOA
#define LIMIT_SEN_1_Pin GPIO_PIN_0
#define LIMIT_SEN_1_GPIO_Port GPIOB
#define LIMIT_SEN_2_Pin GPIO_PIN_1
#define LIMIT_SEN_2_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOB
#define LINK_DC_EN_Pin GPIO_PIN_12
#define LINK_DC_EN_GPIO_Port GPIOB
#define BLDC_EN_Pin GPIO_PIN_13
#define BLDC_EN_GPIO_Port GPIOB
#define T15C1_BLDC_PWM_WH_Pin GPIO_PIN_14
#define T15C1_BLDC_PWM_WH_GPIO_Port GPIOB
#define T15C2_BLDC_PWM_WL_Pin GPIO_PIN_15
#define T15C2_BLDC_PWM_WL_GPIO_Port GPIOB
#define T1C1_BLDC_PWM_UH_Pin GPIO_PIN_8
#define T1C1_BLDC_PWM_UH_GPIO_Port GPIOA
#define T1C2_BLDC_PWM_UL_Pin GPIO_PIN_9
#define T1C2_BLDC_PWM_UL_GPIO_Port GPIOA
#define T1C3_BLDC_PWM_VH_Pin GPIO_PIN_10
#define T1C3_BLDC_PWM_VH_GPIO_Port GPIOA
#define T1C4_BLDC_PWM_VL_Pin GPIO_PIN_11
#define T1C4_BLDC_PWM_VL_GPIO_Port GPIOA
#define BLDC_FAULT_Pin GPIO_PIN_12
#define BLDC_FAULT_GPIO_Port GPIOA
#define BLDC_CAL_Pin GPIO_PIN_15
#define BLDC_CAL_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_3
#define LED2_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_4
#define LED3_GPIO_Port GPIOB
#define USART1_DE_Pin GPIO_PIN_5
#define USART1_DE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
