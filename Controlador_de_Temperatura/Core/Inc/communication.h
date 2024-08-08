//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//
//----------------------------------------------File Name----------------------------------------------//
//
//	communication.h
//
//----------------------------------------------Desciption---------------------------------------------//
//
//	This file shows the headers of all functions implemented on buttonsEvents.c, and will be set up a
//	variable to indicate witch button was pressed.
//
//
//-----------------------------------------------Author------------------------------------------------//
//
//	João Vitor Mendes
//	Vitor Akio Isawa
//
//-----------------------------------------------Version-----------------------------------------------//
//
//	Created on :									19/04/24
//	Revised on :									26/04/24
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------Defines-----------------------------------------------//
#ifndef INC_COMMUNICATION_H_
#define INC_COMMUNICATION_H_

#define _MAX_NUMBER_OF_CHARS 100
#define _MAX_NUMBER_LENGHT 10

//-----------------------------------------------Includes----------------------------------------------//
#include <stdlib.h>
#include <string.h>
#include "usart.h"
#include "light_printf.h"
#include <stdio.h>


//----------------------------------------------Functions----------------------------------------------//
void vCommunicationInit();
void vCommunicationClearInput();
void vCommunicationSendMessage (UART_HandleTypeDef * huart, unsigned char ucMessage[]);
void vCommunicationFloatToString(float fInputNumber, int iDigits, unsigned char * ucOutputNumber);
float fCommunicationStringToFloat(unsigned char  * ucInputNumber);

//-----------------------------------------------------------------------------------------------------//

#endif /* INC_COMMUNICATION_H_ */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//