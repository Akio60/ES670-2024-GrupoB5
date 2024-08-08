//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------//
//	buttonsEvents.h
//----------------------------------------------Desciption---------------------------------------------//
//
//	This file shows the headers of all functions implemented on buttonsEvents.c, and will be set up a
//	variable to indicate witch button was pressed.
//
//-----------------------------------------------Author------------------------------------------------//
//	João Vitor Mendes
//	Vitor Akio Isawa
//-----------------------------------------------Version-----------------------------------------------//
//	Created on :									15/04/24
//	Revised on :									21/04/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------Defines-----------------------------------------------//
#ifndef INC_BUTTONSEVENTS_H_
#define INC_BUTTONSEVENTS_H_

#define _HALF_SEC_COUNTS 50
#define _THREE_SEC_COUNTS 300

//-----------------------------------------------Includes----------------------------------------------//
#include <tim.h>
#include <buttons.h>
#include <main.h>

//-----------------------------------------------Structs-----------------------------------------------//
enum buttonsEventsDef {
	BTENTER=0,
	BTUP=1,
	BTDOWN=2,
	BTLEFT=3,
	BTRIGHT=4,
};

//----------------------------------------------Functions----------------------------------------------//
void vButtonsEventsInit(TIM_HandleTypeDef *pTimDebouncer,TIM_HandleTypeDef *pTimPressedTime);
void vButtonsEventsBtUp();
void vButtonsEventsBtDown();
void vButtonsEventsBtLeft();
void vButtonsEventsBtRight();
void vButtonsEventsBtEnter();
void vButtonsEventsBtPressed();
void vButtonsEventsUpdateEXTI(char cButton, char cState);
void vButtonsEventsDebouncingCallback();
void vButtonsEventsLongPressCallback();
void vButtonsEventCallbackReleasedEvent(enum buttonsEventsDef xButton);
void vButtonsEventCallbackPressedEvent(enum buttonsEventsDef xButton);
void vButtonsEventCallback500msPressedEvent(enum buttonsEventsDef xButton);
void vButtonsEventCallback3sPressedEvent(enum buttonsEventsDef xButton);
void vButtonsEventsCleanFlag();

//-----------------------------------------------------------------------------------------------------//

#endif /* INC_BUTTONSEVENTS_H_ */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
