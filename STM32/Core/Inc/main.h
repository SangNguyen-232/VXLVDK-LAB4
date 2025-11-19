/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MOD_1_Pin GPIO_PIN_2
#define MOD_1_GPIO_Port GPIOA
#define MOD_2_Pin GPIO_PIN_3
#define MOD_2_GPIO_Port GPIOA
#define MOD_3_Pin GPIO_PIN_4
#define MOD_3_GPIO_Port GPIOA
#define DO_D_Pin GPIO_PIN_5
#define DO_D_GPIO_Port GPIOA
#define VANG_D_Pin GPIO_PIN_6
#define VANG_D_GPIO_Port GPIOA
#define XANH_D_Pin GPIO_PIN_7
#define XANH_D_GPIO_Port GPIOA
#define D_1_Pin GPIO_PIN_0
#define D_1_GPIO_Port GPIOB
#define D_2_Pin GPIO_PIN_1
#define D_2_GPIO_Port GPIOB
#define D_3_Pin GPIO_PIN_2
#define D_3_GPIO_Port GPIOB
#define N_4_Pin GPIO_PIN_10
#define N_4_GPIO_Port GPIOB
#define N_5_Pin GPIO_PIN_11
#define N_5_GPIO_Port GPIOB
#define N_6_Pin GPIO_PIN_12
#define N_6_GPIO_Port GPIOB
#define N_7_Pin GPIO_PIN_13
#define N_7_GPIO_Port GPIOB
#define DO_N_Pin GPIO_PIN_8
#define DO_N_GPIO_Port GPIOA
#define VANG_N_Pin GPIO_PIN_9
#define VANG_N_GPIO_Port GPIOA
#define XANH_N_Pin GPIO_PIN_10
#define XANH_N_GPIO_Port GPIOA
#define EN0_Pin GPIO_PIN_11
#define EN0_GPIO_Port GPIOA
#define EN1_Pin GPIO_PIN_12
#define EN1_GPIO_Port GPIOA
#define EN2_Pin GPIO_PIN_13
#define EN2_GPIO_Port GPIOA
#define EN3_Pin GPIO_PIN_14
#define EN3_GPIO_Port GPIOA
#define D_4_Pin GPIO_PIN_3
#define D_4_GPIO_Port GPIOB
#define D_5_Pin GPIO_PIN_4
#define D_5_GPIO_Port GPIOB
#define D_6_Pin GPIO_PIN_5
#define D_6_GPIO_Port GPIOB
#define D_7_Pin GPIO_PIN_6
#define D_7_GPIO_Port GPIOB
#define N_1_Pin GPIO_PIN_7
#define N_1_GPIO_Port GPIOB
#define N_2_Pin GPIO_PIN_8
#define N_2_GPIO_Port GPIOB
#define N_3_Pin GPIO_PIN_9
#define N_3_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
