//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------//
//	tacometer.c
//----------------------------------------------Desciption---------------------------------------------//
//
//
//-----------------------------------------------Author------------------------------------------------//
//	João Vitor Mendes
//	Vitor Akio Isawa
//-----------------------------------------------Version-----------------------------------------------//
//	Created on :									14/05/24
//	Revised on :									17/05/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------Library-----------------------------------------------// 
#include "tachometer.h"
#include "tim.h"
#include "main.h"
#include "lcd.h"
#include "stdio.h"
#include "communication.h"

//-------------------------------------------Variable and definitions----------------------------------//
unsigned char ucCoolerSpeed[5];
extern unsigned short int usCoolerSpeed;
static TIM_HandleTypeDef *htim_window;
char cTachometerTimeCounter=0;
unsigned short int usPeriodCoolerSpeed = 0;


//----------------------------------------------Functions----------------------------------------------//

//	Function name	: 	vTachometerInit
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Inicialize and set the timers and variables of tachometer
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	TIM_HandleTypeDef *htim , pointer to a timer
//		                unsigned int uPeriod    ,
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vTachometerInit(TIM_HandleTypeDef *pTimTachometerTimeCounter, unsigned int uiPeriod)
{
    // Configurar o período da janela em milissegundos
    // Iniciar o timer para gerar a interrupção a cada uiPeriod
    // Iniciar o TIM3 no modo external clock

	htim_window = pTimTachometerTimeCounter;
    __HAL_TIM_SET_AUTORELOAD(htim_window, (uiPeriod * (HAL_RCC_GetHCLKFreq() / 1000)) - 1);
    HAL_TIM_Base_Start_IT(htim_window);

    extern TIM_HandleTypeDef htim3;
    HAL_TIM_Base_Start(&htim3);
}


//	Function name	: 	vTachometerUpdate
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Refresh the data input in tachometer
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	TIM_HandleTypeDef *htim , pointer to a timer
//		                unsigned int uPeriod    ,
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vTachometerUpdate(void)
{
    extern TIM_HandleTypeDef htim3;
    
    // Ler o valor de contagem do TIM3
    // Calcular a velocidade em RPM (considerando 1 pulso por revolução)
    // Reiniciar o contador do TIM3

    unsigned int uiTachometerPulseCount = __HAL_TIM_GET_COUNTER(&htim3);
    usCoolerSpeed = (uiTachometerPulseCount * 60000) / (__HAL_TIM_GET_AUTORELOAD(htim_window) + 1);
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    usPeriodCoolerSpeed=usPeriodCoolerSpeed + usCoolerSpeed;
    cTachometerTimeCounter += 1;
    if (10 == cTachometerTimeCounter){
    	cTachometerTimeCounter = 0;
    	usPeriodCoolerSpeed = usPeriodCoolerSpeed/10;
    	usPeriodCoolerSpeed = usPeriodCoolerSpeed * 60; // rps to RPM
		snprintf(ucCoolerSpeed,5, "%d", usPeriodCoolerSpeed);
		usPeriodCoolerSpeed = 0;

    }

}
