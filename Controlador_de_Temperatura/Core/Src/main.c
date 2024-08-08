/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "matrixKeyboard.h"
//#include <buttonsEvents.h>

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

/* USER CODE BEGIN PV */
	enum state xAppState =INIT;
	long long int var = 0;
	matrixButtons * keyboard;
	char cMenuIndex[_NUMBER_OF_MENUS];
	int iActMenuIndex = TEMPERATURE;

	char cAddresI2c = 0x27;

	unsigned short int usTimeCounter=0;
	float fTemperature = 0;
	float fSetPointValue = 40;
	float fHeaterPWM = 0;
	float fCoolerPWM = 0;
	float fAppKp = 2.7;
	float fAppKi = 0.9;
	float fAppKd = 0;
	char cCtrlOn = 1;
	unsigned short int usCoolerSpeed=0;
	unsigned char ucTimeCounterUART=0;

	unsigned char ucLocalInterfaceLock=0; // 0:unlocked 1:locked



	TIM_HandleTypeDef * pTimer10ms 			= &htim6;
	TIM_HandleTypeDef * pTimerButtonsEventsDebouncing 	= &htim7;
	TIM_HandleTypeDef * pTimerButtonsEventsLongPress 	= &htim16;
	TIM_HandleTypeDef * pTimBuzzer 						= &htim20;
	TIM_HandleTypeDef * pTimCooler						= &htim8;
	TIM_HandleTypeDef * pTimHeater						= &htim1;
	TIM_HandleTypeDef * pTimTachometerPulseCounter		= &htim3;
	TIM_HandleTypeDef * pTimTachometerTimeCounter		= &htim4;
	ADC_HandleTypeDef * pADCTemperature					= &hadc1;

	extern UART_HandleTypeDef hlpuart1;
	UART_HandleTypeDef * pUARTCom = &hlpuart1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void vButtonsEventCallbackPressedEvent(enum buttonsEventsDef xButton){
	switch (xButton) {
		case BTENTER:

			break;
		case BTUP:
			vIncrementCoolerPWMDuty();
			break;
		case BTDOWN:
			vDecrementCoolerPWMDuty();
			break;
		case BTLEFT:
			switch (xAppState) {
				case RUN:
					vDecrementHeaterPWMDuty();
					break;
				case CONFIG:
					if(TEMPERATURE == iActMenuIndex){
						vAppChangeMenu(SPEED);
					}
					else{
						vAppChangeMenu(iActMenuIndex-1);
						}
					break;
				default:
					break;
			}
			break;
		case BTRIGHT:
			switch (xAppState) {
				case RUN:
					vIncrementHeaterPWMDuty();
					break;
				case CONFIG:
					if(SPEED==iActMenuIndex){
						vAppChangeMenu(TEMPERATURE);
					}
					else{
						vAppChangeMenu(iActMenuIndex+1);
						}
					break;
				default:
					break;
			}

			break;
		default:
			break;
	}
}
void vButtonsEventCallback3sPressedEvent(enum buttonsEventsDef xButton){
	switch (xButton) {
		case BTENTER:
			if(xAppState == RUN){
				vAppChangeState(CONFIG);
			}
			else if(xAppState == CONFIG){
				vAppChangeState(RUN);
			}

			break;
		case BTUP:

			break;
		case BTDOWN:

			break;
		case BTLEFT:

			break;
		case BTRIGHT:

			break;
		default:
			break;
		}
 }

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
  MX_DMA_Init();
  MX_LPUART1_UART_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_TIM16_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();
  MX_TIM20_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

  /* Initialize all configured peripherals libs*/
  vLedInitLeds();
  vButtonsInitButtons();
  vMatrixKeyboardInit();
  vButtonsEventsInit(&htim7, &htim16);
  vHeaterAndCoolerInit(pTimCooler, pTimHeater);
  vTachometerInit(pTimTachometerTimeCounter, 1000);
  vBuzzerInit(pTimBuzzer);
  vLcdInitLcd(&hi2c1, 0x27);
  vPidInit(fAppKp,fAppKi,fAppKd,30,1);
  vInitApp();
  vCommunicationInit();
  vCommunicationStateMachineInit(pUARTCom);
  vTemperatureSensorInit(pADCTemperature);
  /* End of libs inicialization */

  /* Tests Code Begin */
  xAppState = vAppChangeState(RUN);
  keyboard = pMatrixKeyboardGetKeys();
  vLcdSendCommand(CMD_CLEAR);
  vBuzzerConfig(1000,500,pTimBuzzer);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	fTemperature = fTemperatureSensorGetTemperature();
	vAppInfoToLCD(fTemperature, fHeaterPWM, fCoolerPWM, fSetPointValue);
	vAppLedTemperatureStatus();
	vHeaterPWMDuty(fHeaterPWM/100);
	vCoolerfanPWMDuty(fCoolerPWM/100);

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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	switch(xAppState){
	case INIT:
		break;

	case RUN:
		if (pTimer10ms == htim){
			vAppTimeCounter();
			vAppPIDControl();
			vMatrixKeyboardUpdateCallback();
			vTachometerUpdate();
		}
		if (pTimerButtonsEventsDebouncing == htim){
			vButtonsEventsDebouncingCallback();
		}
		if (pTimerButtonsEventsLongPress == htim){
			vButtonsEventsLongPressCallback();
		}
		if (pTimTachometerTimeCounter == htim ){
		}
		break;
	case CONFIG:
		if (pTimer10ms == htim){
			vAppTimeCounter();
			vAppPIDControl();
			vMatrixKeyboardUpdateCallback();
			vAppGetFromKeyboard(keyboard);
			vAppGetKeyboardValue();
			vTachometerUpdate();
			vBuzzerPlayingCallback();
		}
		if (pTimerButtonsEventsDebouncing == htim){
			vButtonsEventsDebouncingCallback();
		}
		if (pTimerButtonsEventsLongPress == htim){
			vButtonsEventsLongPressCallback();
		}
		if (pTimTachometerTimeCounter == htim ){
		}
	break;
	case CHANGE:
		if (pTimer10ms == htim){
			vAppTimeCounter();
			vMatrixKeyboardUpdateCallback();
			vAppGetFromKeyboard(keyboard);
			vAppGetKeyboardValue();
			vTachometerUpdate();
			vBuzzerPlayingCallback();

		}

	break;
		default:
			break;
	}
}

void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin){
	switch(xAppState){
		case RUN:
			if(BT_UP_Pin == GPIO_Pin){
				vButtonsEventsBtUp();
			}
			if(BT_DOWN_Pin == GPIO_Pin){
				vButtonsEventsBtDown();
			}
			if(BT_LEFT_Pin == GPIO_Pin){
				vButtonsEventsBtLeft();
			}
			if(BT_RIGHT_Pin == GPIO_Pin){
				vButtonsEventsBtRight();
			}
			if(BT_ENTER_Pin == GPIO_Pin){
				vButtonsEventsBtEnter();
			}

			break;
		case CONFIG:
			if(BT_LEFT_Pin == GPIO_Pin){
				vButtonsEventsBtLeft();
			}
			if(BT_RIGHT_Pin == GPIO_Pin){
				vButtonsEventsBtRight();
			}
			if(BT_ENTER_Pin == GPIO_Pin){
				vButtonsEventsBtEnter();
			}
			break;
		default:
			break;
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
