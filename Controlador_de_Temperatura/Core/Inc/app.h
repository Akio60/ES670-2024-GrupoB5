//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------// 
//	app.h
//----------------------------------------------Desciption---------------------------------------------//
//
//	This file implements the inicialization and functions used by app given the usage of the
//  features apllied to all screens shown.
//
//-----------------------------------------------Author------------------------------------------------//
//	João Vitor Mendes
//	Vitor Akio Isawa
//-----------------------------------------------Version-----------------------------------------------// 
//	Created on :									01/05/24
//	Revised on :									21/06/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//-----------------------------------------------Library-----------------------------------------------// 
#ifndef INC_APP_H_
#define INC_APP_H_

#include "main.h"

enum configModeValues {
	TEMPERATURE=0,
	SETPOINT,
	HEATER,
	COOLER,
	KP,
	KI,
	KD,
	CONTROL,
	SPEED
};

//----------------------------------------------Functions----------------------------------------------//

//	Function name	: 	vInitApp
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Inicialize the flag who shows the actual screen on app.
//					
//-----------------------------------------------------------------------------------------------------//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vInitApp();

//	Function name	: 	vAppChangeMenu
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Function used by selecting an given value on witch state of menu will be set
//					
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	enum configModeValues value
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppChangeMenu (enum configModeValues value);

//	Function name	: 	vAppGetFromKeyboard
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	"Read" the value obteined by the matrix keyboar by change 
// 						the cKeyboarbuttonpressed to the given character
//					
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	matrixButtons * pMatrixButtons
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppGetFromKeyboard(matrixButtons * pMatrixButtons);

//	Function name	: 	vAppUpdateValue
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	This function is used to update and shape the form of data is shown on display
//					
//-----------------------------------------------------------------------------------------------------//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppUpdateValues();

//	Function name	: 	vAppGetKeyboardValue
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	This function is used to get a value from the interface matrix keyboard
//					
//-----------------------------------------------------------------------------------------------------//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppGetKeyboardValue();

//	Function name	: 	vAppTimeCounter
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	This function count the time up to 100 using usTimeCounter.
//					
//-----------------------------------------------------------------------------------------------------//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppTimeCounter();

//	Function name	: 	vAppInfoToLCD
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Configure what is shown in lcd in the different states of the aplication
//						in each case of the system mostly using the lcd.h library
//					
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	float fTemp, float fHeater, float fCooler, float
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppInfoToLCD (float fTemp, float fHeater, float fCooler, float fSetPointValue);

//	Function name	: 	vAppPIDControl
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	This function calculates the PID controller response fPidUpdateData and update
//						the process variables
//-----------------------------------------------------------------------------------------------------//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppPIDControl();

//	Function name	: 	vAppLedTemperatureStatus
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Set representative leds to show the proportion of temperature reach by the sensor
//					
//-----------------------------------------------------------------------------------------------------//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppLedTemperatureStatus ();

//	Function name	: 	vAppChangeState
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	This function is used to change the state machine actual state
//					
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	enum state xNewState
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
enum state vAppChangeState(enum state xAppState);

#endif /* INC_APP_H_ */
