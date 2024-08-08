/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "matrixKeyboard.h"
#include "buttonsEvents.h"
#include "led.h"
#include "buttons.h"
#include "lcd.h"
#include "heaterAndCooler.h"
#include "temperatureSensor.h"
#include "communication.h"
#include "pid.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "usart.h"
#include "tim.h"
#include "gpio.h"
#include "app.h"
#include "buzzer.h"
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
#define BT_UP_Pin GPIO_PIN_1
#define BT_UP_GPIO_Port GPIOC
#define BT_UP_EXTI_IRQn EXTI1_IRQn
#define BT_DOWN_Pin GPIO_PIN_2
#define BT_DOWN_GPIO_Port GPIOC
#define BT_DOWN_EXTI_IRQn EXTI2_IRQn
#define BT_LEFT_Pin GPIO_PIN_3
#define BT_LEFT_GPIO_Port GPIOC
#define BT_LEFT_EXTI_IRQn EXTI3_IRQn
#define LPUART1_TX_Pin GPIO_PIN_2
#define LPUART1_TX_GPIO_Port GPIOA
#define LPUART1_RX_Pin GPIO_PIN_3
#define LPUART1_RX_GPIO_Port GPIOA
#define BT_RIGHT_Pin GPIO_PIN_4
#define BT_RIGHT_GPIO_Port GPIOC
#define BT_RIGHT_EXTI_IRQn EXTI4_IRQn
#define BT_ENTER_Pin GPIO_PIN_0
#define BT_ENTER_GPIO_Port GPIOB
#define BT_ENTER_EXTI_IRQn EXTI0_IRQn
#define ROW_4_IN_Pin GPIO_PIN_11
#define ROW_4_IN_GPIO_Port GPIOB
#define ROW_3_IN_Pin GPIO_PIN_12
#define ROW_3_IN_GPIO_Port GPIOB
#define ROW_2_IN_Pin GPIO_PIN_13
#define ROW_2_IN_GPIO_Port GPIOB
#define ROW_1_IN_Pin GPIO_PIN_15
#define ROW_1_IN_GPIO_Port GPIOB
#define COLUMN_4_OUT_Pin GPIO_PIN_7
#define COLUMN_4_OUT_GPIO_Port GPIOC
#define COLUMN_3_OUT_Pin GPIO_PIN_8
#define COLUMN_3_OUT_GPIO_Port GPIOC
#define COLUMN_2_OUT_Pin GPIO_PIN_9
#define COLUMN_2_OUT_GPIO_Port GPIOC
#define COLUMN_1_OUT_Pin GPIO_PIN_10
#define COLUMN_1_OUT_GPIO_Port GPIOA
#define T_SWDIO_Pin GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define T_SWO_Pin GPIO_PIN_3
#define T_SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define LDG1_PIN GPIO_PIN_5
#define LDG1_PORT GPIOA
#define LDY_PIN GPIO_PIN_4
#define LDY_PORT GPIOA
#define LDR_PIN GPIO_PIN_14
#define LDR_PORT GPIOB
#define LDG2_PIN GPIO_PIN_12
#define LDG2_PORT GPIOA
#define LDB_PIN GPIO_PIN_5
#define LDB_PORT GPIOB

#define BT_UP GPIO_PIN_1
#define BT_UP_PORT GPIOC
#define BT_DN GPIO_PIN_2
#define BT_DN_PORT GPIOC
#define BT_LF GPIO_PIN_3
#define BT_LF_PORT GPIOC
#define BT_RT GPIO_PIN_4
#define BT_RT_PORT GPIOC
#define BT_EN GPIO_PIN_0
#define BT_EN_PORT GPIOB

#define _NUMBER_OF_MENUS 9

enum state{
	INIT=0,
	RUN,
	CHANGE,
	CONFIG
};

void appLedByKeyboard (matrixButtons * pMatrixButtons);

void vMatrixKeyboardHalfSecPressedCallback(char cButton);

void vMatrixKeyboardThreeSecPressedCallback(char cButton);

void appLedCounter (int cOperation);

void vAppIncrementCoolerPWMDuty();

void vAppDecrementCoolerPWMDuty();

void vAppIncrementHeaterPWMDuty();

void vAppDecrementHeaterPWMDuty();

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
