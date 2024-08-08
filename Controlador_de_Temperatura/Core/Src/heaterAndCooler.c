//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------//
//	heaterAndCooler.c
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
//	Revised on :									17/04/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------Library-----------------------------------------------// 
#include "heaterAndCooler.h"
#include "tim.h"

//-------------------------------------------Variable and definitions----------------------------------//
extern float fHeaterPWM;
extern float fCoolerPWM;

//----------------------------------------------Functions----------------------------------------------//

//	Function name	: 	vHeaterAndCoolerInit
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Inicialize the aplication, starts the PWM signal generation
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	TIM_HandleTypeDef *pTimcooler , pointer to cooler tim
//		                TIM_HandleTypeDef *pTimheater , pointer to heater tim
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vHeaterAndCoolerInit(TIM_HandleTypeDef *pTimCooler,TIM_HandleTypeDef *pTimHeater){
	HAL_TIM_PWM_Start(pTimCooler, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(pTimHeater, TIM_CHANNEL_1);
}


//	Function name	: 	vCoolerfanPWMDuty
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Set the range of the power of the cooler fan, given  the % of duty cycle
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	float fCoolerDuty , value of % of duty cycle of cooler, in range 0 to 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vCoolerfanPWMDuty(float fCoolerDuty){
	TIM8->CCR1=fCoolerDuty*10000;
	fCoolerPWM = fCoolerDuty*100;
}


//	Function name	: 	vHeaterPWMDuty
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Set the power of the heater, given  the % of duty cycle
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	float fCoolerDuty , value of % of duty cycle of heater, in range 0 to 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vHeaterPWMDuty(float fHeaterDuty){
	TIM1->CCR1=fHeaterDuty*10000;
	fHeaterPWM = fHeaterDuty*100;
}

//	Function name	: 	vIncrementHeaterPWMDuty
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Increment 10% of Heater duty cycle
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	n/a
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vIncrementHeaterPWMDuty(){
	if ((fHeaterPWM + 10) <= 100 ){
		fHeaterPWM = fHeaterPWM + 10;
	}
	else {
		fHeaterPWM = 100;
	}
	vHeaterPWMDuty(fHeaterPWM/100);
}

//	Function name	: 	vDecrementHeaterPWMDuty
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Decrement 10% of Heater duty cycle
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	n/a
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vDecrementHeaterPWMDuty(){
	if ((fHeaterPWM - 10) >= 0 ){
		fHeaterPWM = fHeaterPWM - 10;
	}
	else {
		fHeaterPWM = 0;
	}
	vHeaterPWMDuty(fHeaterPWM/100);
}

//	Function name	: 	vIncrementCoolerPWMDuty
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Increment 10% of Heater duty cycle
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	n/a
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vIncrementCoolerPWMDuty(){
	if ((fCoolerPWM + 10.0) <= 100.0 ){
		fCoolerPWM = fCoolerPWM + 10.0;
	}
	else {
		fCoolerPWM = 100.0;
	}
	vCoolerfanPWMDuty(fCoolerPWM/100);
}

//	Function name	: 	vDecrementCoolerPWMDuty
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Decrement 10% of Cooler duty cycle
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	n/a
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vDecrementCoolerPWMDuty(){
	if ((fCoolerPWM - 10) >= 0 ){
		fCoolerPWM = fCoolerPWM - 10;
	}
	else {
		fCoolerPWM = 0;
	}
	vCoolerfanPWMDuty(fCoolerPWM/100);
}

