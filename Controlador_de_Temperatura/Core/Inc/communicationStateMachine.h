//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//
//----------------------------------------------File Name----------------------------------------------//
//
//	communication.h
//
//----------------------------------------------Desciption---------------------------------------------//
//
//	This file shows the headers of all functions implemented on CommunicationStateMachine.c, each state
// shows up as the iddle state, while nothings happens, and the functional form, using some states to 
// interact with any kinds of inputs that can be used in the heater controller system
//-----------------------------------------------Author------------------------------------------------//
//
//	João Vitor Mendes
//	Vitor Akio Isawa
//
//-----------------------------------------------Version-----------------------------------------------//
//
//	Created on :									29/04/24
//	Revised on :									03/05/24
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------Defines-----------------------------------------------//
#define _MAX_NUMBER_OF_CHARS 100
//-----------------------------------------------Includes----------------------------------------------//
#include "main.h"
#include <strings.h>
#include <stdio.h>
//----------------------------------------------Functions----------------------------------------------//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void vCommunicationStateMachineSetParam(unsigned char ucParam, unsigned char ucValue);
void vCommunicationStateMachineReturnParam(unsigned char ucParam);

//-----------------------------------------------------------------------------------------------------//
void vCommunicationStateMachineFloatToString(float fInputNumber, int iDigits, unsigned char * ucOutputNumber);

//float fCommunicationStateMachineStringToFloat(unsigned char * ucInputNumber);
float fCommunicationStateMachineStringToFloat();
void vCommunicationStateMachineSendMessage (UART_HandleTypeDef * huart, unsigned char* ucMessage);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
