//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------//
//	communications.c
//----------------------------------------------Desciption---------------------------------------------//
//
//	This file implements the usage of the arrows keyboard from the hardware kit, then implements the resourse
//	of debouncing, witch can be usefull to prevent ghosting or double clicking. Therefore, was
//	created in this file the time pressing event, for 500 ms and for 3 second. Each function will 
//	be explained before it implementation.
//
//	The functions implemented on this file are:
//	-	vButtonsEventsInit						
//
//	There are two _weak functions in this file, ther are:
//	-	vButtonsEventCallbackReleasedEvent
//
//-----------------------------------------------Author------------------------------------------------//
//	João Vitor Mendes
//	Vitor Akio Isawa
//-----------------------------------------------Version-----------------------------------------------//
//	Created on :									19/04/24
//	Revised on :									03/05/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------Includes----------------------------------------------//
#include "communication.h"
#include <strings.h>
#include <stdio.h>

//----------------------------------------Variable and definitions-------------------------------------//

float fInputNumber;
char cMessage[_MAX_NUMBER_OF_CHARS];
char ucMaxNumberMessage[_MAX_NUMBER_OF_CHARS];
unsigned char ucInPos;
unsigned char ucInput;
unsigned char ucMessage[_MAX_NUMBER_OF_CHARS];
unsigned char ucInputNumber[_MAX_NUMBER_LENGHT];
unsigned char ucOutputNumber[_MAX_NUMBER_LENGHT];
UART_HandleTypeDef * huart_func;
//-----------------------------------------------Functions---------------------------------------------//

//	Function name	: 	vCommunicationInit	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Inicializes the variables used setting up to zero and set the UART port 		
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vCommunicationInit(){
	HAL_UART_Receive_IT(&hlpuart1, &ucInput, 1);
	ucInPos = 0;
	ucInput = 0;
	for (int i =0; i<=_MAX_NUMBER_LENGHT;  i++){
		ucInputNumber [i] = 0;
	}
}

//	Function name	: 	HAL_UART_RxCpltCallback	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Setting the correct use when indentify a income message. Verifing if it is 
//		                between the limits and store the value. each step is described in the code 
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	TIM_HandleTypeDef pTimDebouncer 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void HAL_UART_RxCpltCallback_COM(UART_HandleTypeDef * huart){
	if (huart == &hlpuart1){
		// Caso seja um caracter de finalização de comando
		if(ucInput == '\r'){

			//se o usuário digitar apenas enter, sem nenhum dígito
			if(0 == ucInPos){
				sprintf((char *)ucMessage, "\r\n");
				vCommunicationSendMessage(huart, ucMessage);
			}

			//Caso haja algum valor coletado
			else{
				ucInputNumber[ucInPos] = '\000';

				sprintf((char *)ucMessage, "O Número digitado foi: \r\n");
				vCommunicationSendMessage(huart, ucMessage);
				vCommunicationSendMessage(huart, ucInputNumber);
				sprintf((char *)ucMessage, "\r\n");
				vCommunicationSendMessage(huart, ucMessage);
				fInputNumber = fCommunicationStringToFloat(ucInputNumber);

				//Verifica se o valor digitado esta entre os limites toleráveis e calcula o invero dele
				if(fInputNumber>= -1000 && fInputNumber<= 1000 ){
					sprintf((char *)ucMessage, "Número digitado com a troca do ponto pela vírgula: \r\n");
					vCommunicationSendMessage(huart, ucMessage);
					vCommunicationSendMessage(huart, ucInputNumber);
					sprintf((char *)ucMessage, "\r\n");
					vCommunicationSendMessage(huart, ucMessage);

					sprintf((char *)ucMessage, "O inverso do número digitado com 3 casas decimais é: \r\n");
					vCommunicationSendMessage(huart, ucMessage);
					fInputNumber = 1/fInputNumber;
					vCommunicationFloatToString(fInputNumber, ucInPos, ucOutputNumber);

					vCommunicationSendMessage(huart, ucOutputNumber);
					sprintf((char *)ucMessage, "\r\n");
					vCommunicationSendMessage(huart, ucMessage);
				}
				//caso esteja fora dos limites
				else{
					sprintf((char *)ucMessage, "\r\n");
					vCommunicationSendMessage(huart, ucMessage);
					sprintf((char *)ucMessage, "Número fora do intervalo! \r\n");
					vCommunicationSendMessage(huart, ucMessage);
				}
				vCommunicationClearInput();
			}
		}
		//Armazena o valor digitadp
		else {
			//identifica se o número vai extrapolar a quantidade máxima de elementos
			if(ucInPos <= _MAX_NUMBER_LENGHT - 1){
			ucInputNumber[ucInPos] = ucInput;
			ucInPos ++;
			}
		}
		HAL_UART_Receive_IT(&hlpuart1, &ucInput, 1);
		}
}

//	Function name	: 	vCommunicationClearInput	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Clean all vectors that holds the inputs and outputs	
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vCommunicationClearInput(){
	for (int i =0; i<=_MAX_NUMBER_LENGHT;  i++){
		ucInputNumber [i] = 0;
	}
	for (int i =0; i<=_MAX_NUMBER_LENGHT;  i++){
		ucOutputNumber [i] = 0;
	}
	ucInPos =0 ;

}

//	Function name	: 	vCommunicationSendMessage	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Send message to putty from HAL_UART_Transmit		
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	UART_HandleTypeDef * huart 
//		                unsigned char* ucMessage 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vCommunicationSendMessage (UART_HandleTypeDef * huart, unsigned char* ucMessage){
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

//	Function name	: 	fCommunicationStringToFloat	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Turns Strings to float using atof functon and set a "." instead a ","		
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	unsigned char * ucInputNumber
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
float fCommunicationStringToFloat(unsigned char * ucInputNumber){
	float fInputNumber=0;
	int iPos=0;
	while (iPos >= 0){
		if ('\0'!=ucInputNumber[iPos]){
			if (ucInputNumber[iPos] == ','){ucInputNumber[iPos] = '.';}
			iPos++;
		}
		else{
			iPos = -1;
		}
	}
	fInputNumber = atof ((char *) ucInputNumber);
	return fInputNumber;
}

//	Function name	: 	vCommunicationFloatToString	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Turns Float to Strings using atof functon and set a "." instead a ","		
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	float fInputNumber
//		                int iDigits 
//		                unsigned char * ucOutputNumber 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vCommunicationFloatToString(float fInputNumber, int iDigits, unsigned char * ucOutputNumber){
	gcvt(fInputNumber, iDigits, ucOutputNumber);
	ucOutputNumber[_MAX_NUMBER_LENGHT-1] = '\000';
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

//---------------------------------------------Weak Functions------------------------------------------//
