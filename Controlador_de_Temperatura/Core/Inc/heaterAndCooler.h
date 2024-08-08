//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------//
//	heaterAndCooler.h
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
//	Created on :									05/04/24
//	Revised on :									13/04/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------Defines-----------------------------------------------//
#ifndef INC_HEATERANDCOOLER_H_
#define INC_HEATERANDCOOLER_H_
#include "tim.h"

//----------------------------------------------Functions----------------------------------------------//

//	Function name	: 	vHeaterAndCoolerInit
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Inicialize the aplication, starts the PWM signal generation
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	TIM_HandleTypeDef *pTimcooler , pointer to cooler tim
//		                TIM_HandleTypeDef *pTimheater , pointer to heater tim
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vHeaterAndCoolerInit(TIM_HandleTypeDef *pTimCooler,TIM_HandleTypeDef *pTimHeater);

//	Function name	: 	vCoolerfanPWMDuty
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Set the range of the power of the cooler fan, given  the % of duty cycle
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	float fCoolerDuty , value of % of duty cycle of cooler, in range 0 to 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vCoolerfanPWMDuty(float fCoolerDuty);

//	Function name	: 	vHeaterPWMDuty
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Set the power of the heater, given  the % of duty cycle
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	float fCoolerDuty , value of % of duty cycle of heater, in range 0 to 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vHeaterPWMDuty(float fHeaterDuty);

//	Function name	: 	vIncrementHeaterPWMDuty
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Increment 10% of Heater duty cycle
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	n/a
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vIncrementHeaterPWMDuty();

//	Function name	: 	vDecrementHeaterPWMDuty
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Decrement 10% of Heater duty cycle
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	n/a
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vDecrementHeaterPWMDuty();

//	Function name	: 	vIncrementCoolerPWMDuty
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Increment 10% of Heater duty cycle
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	n/a
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vIncrementCoolerPWMDuty();

//	Function name	: 	vDecrementCoolerPWMDuty
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Decrement 10% of Cooler duty cycle
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	n/a
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vDecrementCoolerPWMDuty();



#endif /* INC_HEATERANDCOOLER_H_ */
