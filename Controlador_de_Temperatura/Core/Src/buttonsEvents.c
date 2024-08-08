//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------//
//	buttonsEvent.c
//----------------------------------------------Desciption---------------------------------------------//
//
//	This file implements the usage of the arrows keyboard from the hardware kit, then implements
//	the resourse of debouncing, witch can be usefull to prevent ghosting or double clicking.
//	Was created in this file the function of time pressing event, for 500 ms and for 3 second. 
//	Each function will be explained before it implementation.
//
//	The functions implemented on this file are:
//	-	vButtonsEventsInit			
//	-	vButtonsEventsBtEnter			
//	-	vButtonsEventsBtUp			
//	-	vButtonsEventsBtDown			
//	-	vButtonsEventsBtLeft			
//	-	vButtonsEventsBtRight			
//	-	vButtonsEventsDebouncingCallback			
//	-	vButtonsEventsUpdateEXTI			
//	-	vButtonsEventsBtLeft			
//	-	vButtonsEventsBtLeft			
//
//	There are two _weak functions in this file, ther are:
//	-	vButtonsEventCallbackReleasedEvent
//	-	vButtonsEventCallbackPressedEvent
//	-	vButtonsEventCallback500msPressedEvent
//	-	vButtonsEventCallback3sPressedEvent
//
//-----------------------------------------------Author------------------------------------------------//
//	João Vitor Mendes
//	Vitor Akio Isawa
//-----------------------------------------------Version-----------------------------------------------//
//	Created on :									15/04/24
//	Revised on :									21/04/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//-----------------------------------------------Includes----------------------------------------------//
#include "buttonsEvents.h"
#include "led.h"

//-------------------------------------------Variable and definitions----------------------------------//
TIM_HandleTypeDef *pTimDebouncerPointer, *pTimPressedTimePointer;
char cBtState[5];
char cBtFlag[5];
char cBtState[5];
unsigned int cBtTimer[5];

//----------------------------------------------Functions----------------------------------------------//

//	Function name	: 	vButtonsEventsInit	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Enable all EXTI interruptions in all buttons and inicializes		
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	TIM_HandleTypeDef pTimDebouncer 
//		                TIM_HandleTypeDef pTimPressedTime 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vButtonsEventsInit(TIM_HandleTypeDef *pTimDebouncer,TIM_HandleTypeDef *pTimPressedTime){
	HAL_TIM_Base_Start_IT(pTimPressedTime);
	pTimDebouncerPointer = pTimDebouncer;
	pTimPressedTimePointer = pTimPressedTime;
}

//	Function name	: 	vButtonsEventsBtEnter	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Activate flags, timer zeroing and interruption disable for the 
//		                enter button
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vButtonsEventsBtEnter(){
	vButtonsEventsUpdateEXTI(BTENTER, 0); 
	cBtFlag[BTENTER] = 1;
	HAL_TIM_Base_Start_IT(pTimDebouncerPointer);
	pTimDebouncerPointer->Instance->CNT = 0;
}

//	Function name	: 	vButtonsEventsBtUp	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Activate flags, timer zeroing and interruption disable for 
//		                the up button
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vButtonsEventsBtUp(){
	vButtonsEventsUpdateEXTI(BTUP, 0); 
	cBtFlag[BTUP] = 1;
	HAL_TIM_Base_Start_IT(pTimDebouncerPointer);
	pTimDebouncerPointer->Instance->CNT = 0;
}

//	Function name	: 	vButtonsEventsBtDown	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Activate flags, timer zeroing and interruption disable for 
//		                the Down button
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vButtonsEventsBtDown(){
	vButtonsEventsUpdateEXTI(BTDOWN, 0);
	cBtFlag[BTDOWN] = 1;
	HAL_TIM_Base_Start_IT(pTimDebouncerPointer);
	pTimDebouncerPointer->Instance->CNT = 0;
}

//	Function name	: 	vButtonsEventsBtLeft	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Activate flags, timer zeroing and interruption disable for 
//		                the left button
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vButtonsEventsBtLeft(){
	vButtonsEventsUpdateEXTI(BTLEFT, 0);
	cBtFlag[BTLEFT] = 1;
	HAL_TIM_Base_Start_IT(pTimDebouncerPointer);
	pTimDebouncerPointer->Instance->CNT = 0;
}

//	Function name	: 	vButtonsEventsBtRight	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Activate flags, timer zeroing and interruption disable for 
//		                the Right button
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vButtonsEventsBtRight(){
	cBtFlag[BTRIGHT] = 1;
	vButtonsEventsUpdateEXTI(BTRIGHT, 0);
	HAL_TIM_Base_Start_IT(pTimDebouncerPointer);
	pTimDebouncerPointer->Instance->CNT = 0;
}

//	Function name	: 	vButtonsEventsDebouncingCallback	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	verify if each button has your flag high, meaning that some event happen
//		                to that button then if the button is high level it was pressed and if it
//		                is low level the button was realeased.
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vButtonsEventsDebouncingCallback(){
	HAL_TIM_Base_Stop_IT(pTimDebouncerPointer);
	if (cBtFlag[BTENTER]){
		if(HAL_GPIO_ReadPin(BT_ENTER_GPIO_Port, BT_ENTER_Pin)){
			cBtState[BTENTER] = 1;
			vButtonsEventCallbackPressedEvent(BTENTER);
		}else{
			cBtState[BTENTER] = 0;
			vButtonsEventCallbackReleasedEvent(BTENTER);
		}
		vButtonsEventsUpdateEXTI(BTENTER, 1);
		cBtFlag[BTENTER] = 0;
	}
	if (cBtFlag[BTUP]){
		if(HAL_GPIO_ReadPin(BT_UP_GPIO_Port, BT_UP_Pin)){
			cBtState[BTUP] = 1;
			vButtonsEventCallbackPressedEvent(BTUP);
		}else{
			cBtState[BTUP] = 0;
			vButtonsEventCallbackReleasedEvent(BTUP);
		}
		cBtFlag[BTUP]=0;
		vButtonsEventsUpdateEXTI(BTUP, 1);
	}
	if (cBtFlag[BTDOWN]){
		if(HAL_GPIO_ReadPin(BT_DOWN_GPIO_Port, BT_DOWN_Pin)){
			cBtState[BTDOWN] = 1;
			vButtonsEventCallbackPressedEvent(BTDOWN);
		}else{
			cBtState[BTDOWN] = 0;
			vButtonsEventCallbackReleasedEvent(BTDOWN);
		}
		cBtFlag[BTDOWN]=0;
		vButtonsEventsUpdateEXTI(BTDOWN, 1);
	}
	if (cBtFlag[BTLEFT]){
		if(HAL_GPIO_ReadPin(BT_LEFT_GPIO_Port, BT_LEFT_Pin)){
			cBtState[BTLEFT] = 1;
			vButtonsEventCallbackPressedEvent(BTLEFT);
		}else{
			cBtState[BTLEFT] = 0;
			vButtonsEventCallbackReleasedEvent(BTLEFT);
		}
		cBtFlag[BTLEFT]=0;
		vButtonsEventsUpdateEXTI(BTLEFT, 1);
	}
	if (cBtFlag[BTRIGHT]){
		if(HAL_GPIO_ReadPin(BT_RIGHT_GPIO_Port, BT_RIGHT_Pin)){
			cBtState[BTRIGHT] = 1;
			vButtonsEventCallbackPressedEvent(BTRIGHT);
		}else{
			cBtState[BTRIGHT] = 0;
			vButtonsEventCallbackReleasedEvent(BTRIGHT);
		}
		cBtFlag[BTRIGHT]=0;
		vButtonsEventsUpdateEXTI(BTRIGHT, 1);
	}
}

//	Function name	: 	vButtonsEventsUpdateEXTI	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Disable and enable the interrupt in the NVIC interrupt controller and 
//		                clear the EXTI the EXTI for the selected button and state used.
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	char cButton
//		                char cState
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vButtonsEventsUpdateEXTI(char cButton, char cState){
	if(BTENTER == cButton){
		if (cState == 0){
			HAL_NVIC_DisableIRQ(EXTI0_IRQn);
			__HAL_GPIO_EXTI_CLEAR_IT(BTENTER);
		}
		else{
			HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		}
	}
	else if(BTUP == cButton){
		if (cState == 0){
			HAL_NVIC_DisableIRQ(EXTI1_IRQn);
			__HAL_GPIO_EXTI_CLEAR_IT(BTUP);
		}
		else{
			HAL_NVIC_EnableIRQ(EXTI1_IRQn);
		}
	}
	else if(BTDOWN == cButton){
			if (cState == 0){
				HAL_NVIC_DisableIRQ(EXTI2_IRQn);
				__HAL_GPIO_EXTI_CLEAR_IT(BTDOWN);
			}
			else{
				HAL_NVIC_EnableIRQ(EXTI2_IRQn);
			}
	}
	else if(BTLEFT == cButton){
			if (cState == 0){
				HAL_NVIC_DisableIRQ(EXTI3_IRQn);
				__HAL_GPIO_EXTI_CLEAR_IT(BTLEFT);
			}
			else{
				HAL_NVIC_EnableIRQ(EXTI3_IRQn);
			}
	}
	else if(BTRIGHT == cButton){
			if (cState == 0){
				HAL_NVIC_DisableIRQ(EXTI4_IRQn);
				__HAL_GPIO_EXTI_CLEAR_IT(BTRIGHT);
			}
			else{
				HAL_NVIC_EnableIRQ(EXTI4_IRQn);
			}
	}
}

//	Function name	: 	vButtonsEventsBtEnter	
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Checks how long the button is pressed and call the function set for a 
//		                contiunuous pressing button using the state and time variable
//		                (cbtSate , cBtTimer).
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vButtonsEventsLongPressCallback(){
	int aux;
	for (int i=0; i<5; i++){
		if(cBtState[i]){
			aux++;
			cBtTimer[i] ++;
			if(!(cBtTimer[i]%_HALF_SEC_COUNTS)){
				vButtonsEventCallback500msPressedEvent((char)i);
//				cBtTimer[i]=0;
			}
			if(_THREE_SEC_COUNTS==cBtTimer[i]){
				vButtonsEventCallback3sPressedEvent((char)i);
				cBtTimer[i]=0;
				cBtState[i]=0;
			}
		}
		else{
		cBtTimer[i]=0;
		}

	}
}


//-----------------------------------------Weak Functions----------------------------------------------//

//	Function name	: 	vButtonsEventCallbackReleasedEvent							
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Function called when the button is released  								  
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	buttonsEventsDef xButton													   
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
__weak void vButtonsEventCallbackReleasedEvent(enum buttonsEventsDef xButton){};

//	Function name	: 	vButtonsEventCallbackPressedEvent							
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Function called when the button is pressed  								  
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	buttonsEventsDef xButton
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
__weak void vButtonsEventCallbackPressedEvent(enum buttonsEventsDef xButton){};

//	Function name	: 	vButtonsEventCallback500msPressedEvent							
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Function called when the button is pressed  for 500ms 						  
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	buttonsEventsDef xButton
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//		
__weak void vButtonsEventCallback500msPressedEvent(enum buttonsEventsDef xButton){};


//	Function name	: 	vButtonsEventCallback3sPressedEvent							
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Function called when the button is pressed  for 3s 					  	  
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	buttonsEventsDef xButton
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//		
__weak void vButtonsEventCallback3sPressedEvent(enum buttonsEventsDef xButton){};


//	Function name	: 	vButtonsEventsCleanFlag
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Clean flag for more than one long pressed event
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	n/a
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vButtonsEventsCleanFlag(){
	for(int iRun=0 ; iRun<5 ; iRun++){
		cBtFlag[iRun]=0;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

