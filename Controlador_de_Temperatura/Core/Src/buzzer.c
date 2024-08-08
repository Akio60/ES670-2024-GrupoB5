//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------//
//	buzzer.c
//----------------------------------------------Desciption---------------------------------------------//
//
//
//-----------------------------------------------Author------------------------------------------------//
//	João Vitor Mendes
//	Vitor Akio Isawa
//-----------------------------------------------Version-----------------------------------------------//
//	Created on :									10/05/24
//	Revised on :									14/05/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------Library-----------------------------------------------// 
#include "buzzer.h"

//-------------------------------------------Variable and definitions----------------------------------//
struct buzzerTarget {
  char cPlaying;
  unsigned short int usTimePlaying;
  unsigned short int usPeriod;
  TIM_HandleTypeDef * pTimBuzzer;
};
struct buzzerTarget buzzer;

//----------------------------------------------Functions----------------------------------------------//

//	Function name	: 	vBuzzerInit
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Inicializa o as funcoes do buzzer
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	TIM_HandleTypeDef *pTimBuzzer , pointer to a struct buzzer
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vBuzzerInit(TIM_HandleTypeDef *pTimBuzzer){
	HAL_TIM_PWM_Start(pTimBuzzer, TIM_CHANNEL_1);
	buzzer.pTimBuzzer = pTimBuzzer;
	buzzer.cPlaying=0;
	buzzer.usPeriod = 300;
	buzzer.usTimePlaying = 0;
}


//	Function name	: 	vBuzzerConfig
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Setting the GPIO interface for using the led as a output port,
//		                type of the port and the configurations
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	unsigned short int usFrequency ,freq do buzzer vai variar entre 100 e 10 000
//		                unsigned short int usPeriod    ,tempo que o buzzer vai tocar
//		                TIM_HandleTypeDef *htim 	, modulo timer para contabilizar
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vBuzzerConfig(unsigned short int usFrequency, unsigned short int usPeriod, TIM_HandleTypeDef *htim){
	if (0 != usFrequency){
		htim->Init.Prescaler = (_TIMER_CLOCK / (htim->Init.Period * usFrequency));
		htim->Init.Period = 9999;
	}
	buzzer.usPeriod = usPeriod/10;
}


//	Function name	: 	vBuzzerPlay
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Deve executar o buzzer de acordo com as configurações definidas em vBuzzerConfig
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vBuzzerPlay(void){
	buzzer.cPlaying = 1;
	buzzer.pTimBuzzer->Instance->CCR1=5000;

}


//	Function name	: 	vBuzzerPlayingCallback
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Conta o tempo em que o buzzer se mantem tocando
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vBuzzerPlayingCallback(void){
	buzzer.usTimePlaying += 1 ;
	if(buzzer.usTimePlaying >= buzzer.usPeriod){
		buzzer.pTimBuzzer->Instance->CCR1=0;
		buzzer.cPlaying = 0;
		buzzer.usTimePlaying = 0;
	}
}
