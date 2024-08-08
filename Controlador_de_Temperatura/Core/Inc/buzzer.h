//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------//
//	buzzer.h
//----------------------------------------------Desciption---------------------------------------------//
//
//	This header file indentify the functions there will be used to execute the requisits of the keyboard
//	sofware. Here we create the struct used to define the state of each button of the keyboard and a
//	struct with almost the same form used before to count the time that the button has been pressed.
//
//-----------------------------------------------Author------------------------------------------------//
//	João Vitor Mendes
//	Vitor Akio Isawa
//-----------------------------------------------Version-----------------------------------------------//
//	Created on :									09/05/24
//	Revised on :									17/05/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------Defines-----------------------------------------------//
#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_
#define _TIMER_CLOCK 170000000


//-----------------------------------------------Includes----------------------------------------------//
#include "tim.h"


//----------------------------------------------Functions----------------------------------------------//

//	Function name	: 	vBuzzerInit
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Inicializa o as funcoes do buzzer
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	TIM_HandleTypeDef *pTimBuzzer
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vBuzzerInit(TIM_HandleTypeDef *pTimBuzzer);

//	Function name	: 	vBuzzerConfig
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Setting the GPIO interface for using the led as a output port,
//		                type of the port and the configurations
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	unsigned short int usFrequency ,freq do buzzer vai variar entre 100 e 10 000
//		                unsigned short int usPeriod    ,tempo que o buzzer vai tocar
//		                TIM_HandleTypeDef *htim 	, modulo timer para contabilizar
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vBuzzerConfig(unsigned short int usFrequency, unsigned short int usPeriod, TIM_HandleTypeDef *htim);

//	Function name	: 	vBuzzerPlay
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Deve executar o buzzer de acordo com as configurações definidas em vBuzzerConfig
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vBuzzerPlay(void);

//	Function name	: 	vBuzzerPlayingCallback
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Conta o tempo em que o buzzer se mantem tocando
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vBuzzerPlayingCallback(void);


#endif /* INC_BUZZER_H_ */
