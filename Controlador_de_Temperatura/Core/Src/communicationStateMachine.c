//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------//
//	communicationStateMachine.c
//----------------------------------------------Desciption---------------------------------------------//
//
//	This file explains the funcion os the state machine used on the communicantion system,
//	using the RxCpltCallback function to interrupt the system and treat these interruptions.
//	the other functions are made to set and return parameters.
//
//	The functions implemented on this file are:
//	-	HAL_UART_RxCpltCallback
//	-	vCommunicationStateMachineReturnParam
//	-	vCommunicationStateMachineSetParam
//
//
//-----------------------------------------------Author------------------------------------------------//
//	João Vitor Mendes
//	Vitor Akio Isawa
//-----------------------------------------------Version-----------------------------------------------//
//	Created on :									29/04/24
//	Revised on :									03/05/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//-----------------------------------------------Defines-----------------------------------------------//
#define _IDDLE   '0'
#define _READY   '1'
#define _GET     '2'
#define _SET     '3'
#define _PARAM   '4'
#define _VALUE   '5'

#define MAX_VALUE_LENGTH 7

//-----------------------------------------------Includes----------------------------------------------//
#include "communicationStateMachine.h"

//----------------------------------------Variable and definitions-------------------------------------//
extern float fTemperature ;
extern float fSetPointValue ;
extern float fHeaterPWM ;
extern float fCoolerPWM ;
extern float fAppKp ;
extern float fAppKi ;
extern float fAppKd ;
extern char cCtrlOn;
extern unsigned short int usCoolerSpeed;
extern unsigned char ucLocalInterfaceLock;

static unsigned char ucValue[MAX_VALUE_LENGTH+1];

unsigned char ucState = _IDDLE;
unsigned char ucValueCount;
unsigned char ucDigit;
unsigned char ucTransmitVector[_MAX_NUMBER_OF_CHARS];
UART_HandleTypeDef *pCommunicationStateMachinePointer;

//-----------------------------------------------Functions---------------------------------------------//


void vCommunicationStateMachineInit(UART_HandleTypeDef *huart){
    pCommunicationStateMachinePointer = huart;
}


//	Function name	: 	HAL_UART_RxCpltCallback
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Makes the treatment when recieve one byte from the uart, making a
//		                state machine to pass trought any input
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	ucByte
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    static unsigned char ucParam;


    if (huart == pCommunicationStateMachinePointer){
        HAL_UART_Receive_IT(huart, &ucDigit, 1);

        if('#' == ucDigit){
            ucState = _READY;
        }

        else{
			if (ucState != _IDDLE){
				switch (ucState){
				case _READY:
					switch (ucDigit){
					case 'g':
						ucState = _GET;
						break;
					case 's':
						ucState = _SET;
						break;
					default:
						ucState = _IDDLE;
					}
					break;

				case _GET:
					if ('t' == ucDigit || 'r' == ucDigit || 'h' == ucDigit || 'c' == ucDigit || 'p' == ucDigit || 'i' == ucDigit
							|| 'd' == ucDigit || 's' == ucDigit || 'l' == ucDigit || 'o' == ucDigit){
					ucParam = ucDigit;
					ucState = _PARAM;
					}
					else
					ucState = _IDDLE;
					break;

				case _SET:
					if ('r' == ucDigit || 'h' == ucDigit || 'c' == ucDigit || 'p' == ucDigit || 'i' == ucDigit || 'd' == ucDigit
							|| 'l' == ucDigit || 'o' == ucDigit){
					ucParam = ucDigit;
					ucValueCount = 0;
					ucState = _VALUE;
					}
					else
					ucState = _IDDLE;
					break;

				case _PARAM:
					if (';' == ucDigit){
						vCommunicationStateMachineReturnParam(ucParam);
					}
					ucState = _IDDLE;
					break;

				case _VALUE:
					if ((ucDigit >= '0' && ucDigit <= '9') || ',' == ucDigit){
						if (ucValueCount < MAX_VALUE_LENGTH){
							ucValue[ucValueCount++] = ucDigit;
						}
					}
					else{
						if (';' == ucDigit){
							ucValue[ucValueCount] = '\0';
							vCommunicationStateMachineSetParam(ucParam, ucValue);
						}
						ucState = _IDDLE;
					}
					break;
				}
			}
		}
    }
}


//	Function name	: 	vCommunicationStateMachineReturnParam
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Returns the parameter indicated by the ucParam variable
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	ucParam
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vCommunicationStateMachineReturnParam(unsigned char ucParam){
	unsigned char ucValue[MAX_VALUE_LENGTH];
    switch (ucParam){
        case 't': //temp
        	vCommunicationStateMachineFloatToString(fTemperature, 4, ucValue);
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucValue);
            sprintf(ucTransmitVector, "\r\n");
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucTransmitVector);
            break;
        case 'r': //temp reference
        	vCommunicationStateMachineFloatToString(fSetPointValue, 4, ucValue);
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucValue);
            sprintf(ucTransmitVector, "\r\n");
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucTransmitVector);
            break;
        case 'h': //heater duty cycle
        	vCommunicationStateMachineFloatToString(fHeaterPWM, 3, ucValue);
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucValue);
            sprintf(ucTransmitVector, "\r\n");
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucTransmitVector);
            break;
        case 'c': //cooler duty dycle
        	vCommunicationStateMachineFloatToString(fCoolerPWM, 3, ucValue);
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucValue);
            sprintf(ucTransmitVector, "\r\n");
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucTransmitVector);
            break;
        case 'p': //kp
        	vCommunicationStateMachineFloatToString(fAppKp, 4, ucValue);
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucValue);
            sprintf(ucTransmitVector, "\r\n");
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucTransmitVector);
            break;
        case 'i': //ki
        	vCommunicationStateMachineFloatToString(fAppKi, 4, ucValue);
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucValue);
            sprintf(ucTransmitVector, "\r\n");
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucTransmitVector);
            break;
        case 'd': //kd
        	vCommunicationStateMachineFloatToString(fAppKd, 4, ucValue);
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucValue);
            sprintf(ucTransmitVector, "\r\n");
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucTransmitVector);
            break;
        case 's': //cooler speed
        	snprintf(ucValue,5, "%d", usCoolerSpeed);
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucValue);
            sprintf(ucTransmitVector, "\r\n");
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucTransmitVector);
            break;
        case 'l': //interface lock
        	snprintf(ucValue,1, "%d", ucLocalInterfaceLock);
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucValue);
            sprintf(ucTransmitVector, "\r\n");
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucTransmitVector);
            break;
        case 'o': //control operation
        	snprintf(ucValue,1, "%d", cCtrlOn);
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucValue);
            sprintf(ucTransmitVector, "\r\n");
            vCommunicationStateMachineSendMessage(pCommunicationStateMachinePointer, &ucTransmitVector);
            break;

    }
}
//	Function name	: 	vCommunicationStateMachineSetParam
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	set the parameter indicated by the ucParam by ucValue
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	ucParam
//		                ucValue
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vCommunicationStateMachineSetParam(unsigned char ucParam, unsigned char ucValue){
	float fValue;
    switch (ucParam){
        case 'r': //temp reference
            fValue=fCommunicationStateMachineStringToFloat(&ucValue);
    		if (fValue >= 25 && fValue <= 90){
    			fSetPointValue = fValue;
    		}
            break;
        case 'h': //heater duty cycle
        	fValue=fCommunicationStateMachineStringToFloat(&ucValue);
    		if (fValue >= 0 && fValue <= 100){
    			fHeaterPWM = fValue;
    		}
            break;
        case 'c': //cooler duty dycle
        	fValue=fCommunicationStateMachineStringToFloat(&ucValue);
    		if (fValue >= 0 && fValue <= 100){
    			fCoolerPWM = fValue;
    		}
        	break;
        case 'p': //kp
        	fAppKp=fCommunicationStateMachineStringToFloat(&ucValue);
            break;
        case 'i': //ki
        	fAppKi=fCommunicationStateMachineStringToFloat(&ucValue);
            break;
        case 'd': //kd
        	fAppKd=fCommunicationStateMachineStringToFloat(&ucValue);
            break;
        case 'l': //interface lock
            ucLocalInterfaceLock= fCommunicationStateMachineStringToFloat(&ucValue);
            break;
        case 'o': //control operation
        	fValue=fCommunicationStateMachineStringToFloat(&ucValue);
    		if (0 == fValue){
    			cCtrlOn = 0;
    		}
    		else if(1 == fValue){
    			cCtrlOn = 1;
    		}
            break;
    }
}

//	Function name	: 	fCommunicationStateMachineStringToFloat
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Turns Strings to float using atof functon and set a "." instead a ","
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	unsigned char * ucInputNumber
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//float fCommunicationStateMachineStringToFloat(unsigned char * ucValue){
float fCommunicationStateMachineStringToFloat(){
	float fInputNumber=0;
	int iPos=0;
	while (iPos >= 0){
		if ('\0'!=ucValue[iPos]){
			if (ucValue[iPos] == ','){
				ucValue[iPos] = '.';
			}
			iPos++;
		}
		else{
			iPos = -1;
		}
	}
	fInputNumber = atof (ucValue);
	return fInputNumber;
}

//	Function name	: 	vCommunicationStateMachineFloatToString
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Turns Float to Strings using atof functon and set a "." instead a ","
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	float fInputNumber
//		                int iDigits
//		                unsigned char * ucOutputNumber
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vCommunicationStateMachineFloatToString(float fInputNumber, int iDigits, unsigned char * ucOutputNumber){
	gcvt(fInputNumber, iDigits, ucOutputNumber);
	ucOutputNumber[MAX_VALUE_LENGTH-1] = '\000';
	int iPos =0;
	while (iPos >= 0){
			if ('\000'!=ucOutputNumber[iPos]){
				if (ucOutputNumber[iPos] == '.'){
					ucOutputNumber[iPos] = ',';
					ucOutputNumber[iPos+4]= '\000';
				}
				iPos++;
			}
			else{
				iPos = -1;
			}
	}
}

//	Function name	: 	vCommunicationStateMachineSendMessage
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Send message to putty from HAL_UART_Transmit
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	UART_HandleTypeDef * huart
//		                unsigned char* ucMessage
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vCommunicationStateMachineSendMessage (UART_HandleTypeDef * huart, unsigned char* ucMessage){
	if(huart == &hlpuart1){
		int iPos = 0;
		while(iPos >= 0 && iPos < _MAX_NUMBER_OF_CHARS){
			if(ucMessage[iPos] =='\000'){
				iPos = -1;
			}
			else if(ucMessage[iPos] =='\n'){
				HAL_UART_Transmit(&hlpuart1, &ucMessage[iPos], 1, 100);
				iPos = -1;
			}
			else{
				HAL_UART_Transmit(&hlpuart1, &ucMessage[iPos], 1, 100);
				iPos ++;
			}
		}
	}
}

//---------------------------------------------Weak Functions------------------------------------------//
