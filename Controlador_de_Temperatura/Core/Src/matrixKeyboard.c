//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------//
//	matrixKeyboard.c
//----------------------------------------------Desciption---------------------------------------------//
//
//	This file implements the functions for the usage of the matrix keybord, beeing able to read a  
//	pressed button and register that information.
//	The code relies on the description of the hardware described, so, in order to scam the values, the 
//	code turns to enable one column per time, in witch is scaned if there are any 
//	row receiving the signal. With this we can specificate witch button is pressed.
//	Another function set on this file is to scan if there are any continuous pressing buttons by at least
//	4 cycles, then turning on the info Led
//
//	The functions implemented on this file are:
//	-	vMatrixKeyboardInit		
//	-	vMatrixKeyboardReset	
//	-	vMatrixKeyboardTimeReset
//	-	vMatrixKeyboardUpdateCallback
//	-	vMatrixKeyboardSetPort	
//	-	vMatrixKeyboardReadPorts
//	-	vMatrixKeyboardUpdateTimePressed	
//	-	vMatrixKeyboardIncrementTimePressed	
//
//	There are two _weak functions in this file, ther are:
//	-	vMatrixKeyboardThreeSecPressedCallback
//	-	vMatrixKeyboardHalfSecPressedCallback
//
//-----------------------------------------------Author------------------------------------------------//
//	João Vitor Mendes
//	Vitor Akio Isawa
//-----------------------------------------------Version-----------------------------------------------//
//	Created on :									05/04/24
//	Revised on :									21/04/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------Library-----------------------------------------------//
#include "stm32g4xx_hal.h"
#include "matrixKeyboard.h"
#include "tim.h"

//-------------------------------------------Variable and definitions----------------------------------//
char cActColumn =-1;
char cFourCycleCounter=1;
matrixButtons xMatrixState;
matrixButtonsTime xMatrixTimePressed;

//----------------------------------------------Functions----------------------------------------------//

//	Function name	: 	vMatrixKeyboardInit
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Function to enable clock on the Matrixkeyboard, setting up the variables  
//		                used to  collect data from the inputs and timers used on this file
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vMatrixKeyboardInit(){
	HAL_TIM_Base_Start_IT(&htim6);
	vMatrixKeyboardReset();
	vMatrixKeyboardTimeReset();
}

//	Function name	: 	pMatrixKeyboardGetKeys
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Function that returns the pointer of xMatrixState  
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
matrixButtons * pMatrixKeyboardGetKeys(){
	return &xMatrixState;
}

//	Function name	: 	vMatrixKeyboardReset
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	This function is used to set all variables on the matrix   
//		                keyboard , meaning turning all the states into 0
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vMatrixKeyboardReset(){
	xMatrixState.cBt1 = 0;			// row :1 	Column: 1
	xMatrixState.cBt2 = 0;			// row :1 	Column: 2
	xMatrixState.cBt3 = 0;			// row :1 	Column: 3
	xMatrixState.cBt4 = 0;			// row :2 	Column: 1
	xMatrixState.cBt5 = 0;			// row :2 	Column: 2
	xMatrixState.cBt6 = 0;			// row :2 	Column: 3
	xMatrixState.cBt7 = 0;			// row :3 	Column: 1
	xMatrixState.cBt8 = 0;			// row :3 	Column: 2
	xMatrixState.cBt9 = 0;			// row :3	Column: 3
	xMatrixState.cBt0 = 0;			// row :4 	Column: 2
	xMatrixState.cBtA = 0;			// row :1 	Column: 4
	xMatrixState.cBtB = 0;			// row :2 	Column: 4
	xMatrixState.cBtC = 0;			// row :3 	Column: 4
	xMatrixState.cBtD = 0;			// row :4 	Column: 4
	xMatrixState.cBtHash = 0;	 	// row :4 	Column: 3
	xMatrixState.cBtAsterisk = 0;	// row :4 	Column: 1
}


//	Function name	: 	vMatrixKeyboardTimeReset
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	This function is used to reset the time variable of all buttons of   
//		                the keyboard
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vMatrixKeyboardTimeReset(){
	xMatrixTimePressed.usBt1 = 0;			// row :1 	Column: 1
	xMatrixTimePressed.usBt2 = 0;			// row :1 	Column: 2
	xMatrixTimePressed.usBt3 = 0;			// row :1 	Column: 3
	xMatrixTimePressed.usBt4 = 0;			// row :2 	Column: 1
	xMatrixTimePressed.usBt5 = 0;			// row :2 	Column: 2
	xMatrixTimePressed.usBt6 = 0;			// row :2 	Column: 3
	xMatrixTimePressed.usBt7 = 0;			// row :3 	Column: 1
	xMatrixTimePressed.usBt8 = 0;			// row :3 	Column: 2
	xMatrixTimePressed.usBt9 = 0;			// row :3	Column: 3
	xMatrixTimePressed.usBt0 = 0;			// row :4 	Column: 2
	xMatrixTimePressed.usBtA = 0;			// row :1 	Column: 4
	xMatrixTimePressed.usBtB = 0;			// row :2 	Column: 4
	xMatrixTimePressed.usBtC = 0;			// row :3 	Column: 4
	xMatrixTimePressed.usBtD = 0;			// row :4 	Column: 4
	xMatrixTimePressed.usBtHash = 0;	 		// row :4 	Column: 3
	xMatrixTimePressed.usBtAsterisk = 0;		// row :4 	Column: 1
	xMatrixTimePressed.cTimerThreeSec =0;
}


//	Function name	: 	vMatrixKeyboardUpdateCallback
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	By using the next functions, this function will update the port state ,
//		                read any new input and verify if the button is pressed by 4 cycles 
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vMatrixKeyboardUpdateCallback(){
	vMatrixKeyboardSetPort();
	vMatrixKeyboardReadPorts();
	if (4==cFourCycleCounter){
		cFourCycleCounter =1;
		vMatrixKeyboardUpdateTimePressed();
	}
	else{
		cFourCycleCounter ++;
	}
}


//	Function name	: 	vMatrixKeyboardSetPort
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Looks for the column in high level and toogles it and the next    
//		                pin to high level
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vMatrixKeyboardSetPort(){
	if (HAL_GPIO_ReadPin( COLUMN_1_OUT_GPIO_Port, COLUMN_1_OUT_Pin))
	{
		HAL_GPIO_WritePin(COLUMN_1_OUT_GPIO_Port, COLUMN_1_OUT_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(COLUMN_2_OUT_GPIO_Port, COLUMN_2_OUT_Pin, GPIO_PIN_SET);
		cActColumn = 2;
	}
	else if(HAL_GPIO_ReadPin(COLUMN_2_OUT_GPIO_Port, COLUMN_2_OUT_Pin))
	{
		HAL_GPIO_WritePin(COLUMN_2_OUT_GPIO_Port, COLUMN_2_OUT_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(COLUMN_3_OUT_GPIO_Port, COLUMN_3_OUT_Pin, GPIO_PIN_SET);
		cActColumn = 3;
	}
	else if(HAL_GPIO_ReadPin(COLUMN_3_OUT_GPIO_Port, COLUMN_3_OUT_Pin))
	{
		HAL_GPIO_WritePin(COLUMN_3_OUT_GPIO_Port, COLUMN_3_OUT_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(COLUMN_4_OUT_GPIO_Port, COLUMN_4_OUT_Pin, GPIO_PIN_SET);
		cActColumn = 4;
	}
	else if(HAL_GPIO_ReadPin(COLUMN_4_OUT_GPIO_Port, COLUMN_4_OUT_Pin))
	{
		HAL_GPIO_WritePin(COLUMN_4_OUT_GPIO_Port, COLUMN_4_OUT_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(COLUMN_1_OUT_GPIO_Port, COLUMN_1_OUT_Pin, GPIO_PIN_SET);
		cActColumn = 1;
	}
	else {
		HAL_GPIO_TogglePin(COLUMN_1_OUT_GPIO_Port, COLUMN_1_OUT_Pin); //case for initialization
		cActColumn = 1;
	}
}


//	Function name	: 	vMatrixKeyboardReadPorts
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Reading the signal by crossing the data of collums and rows, 
//		                one row per time
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vMatrixKeyboardReadPorts(){
	if (1 == cActColumn){
		if(HAL_GPIO_ReadPin(ROW_1_IN_GPIO_Port, ROW_1_IN_Pin)){
			xMatrixState.cBtAsterisk = 0;
			xMatrixState.cBt1 = 1;
			xMatrixState.cBt4 = 0;
			xMatrixState.cBt7 = 0;
		}
		else if (HAL_GPIO_ReadPin(ROW_2_IN_GPIO_Port, ROW_2_IN_Pin)){
			xMatrixState.cBtAsterisk = 0;
			xMatrixState.cBt1 = 0;
			xMatrixState.cBt4 = 1;
			xMatrixState.cBt7 = 0;
		}
		else if (HAL_GPIO_ReadPin(ROW_3_IN_GPIO_Port, ROW_3_IN_Pin)){
			xMatrixState.cBtAsterisk = 0;
			xMatrixState.cBt1 = 0;
			xMatrixState.cBt4 = 0;
			xMatrixState.cBt7 = 1;
		}
		else if (HAL_GPIO_ReadPin(ROW_4_IN_GPIO_Port, ROW_4_IN_Pin)){
			xMatrixState.cBtAsterisk = 1;
			xMatrixState.cBt1 = 0;
			xMatrixState.cBt4 = 0;
			xMatrixState.cBt7 = 0;
		}
		else{
			xMatrixState.cBtAsterisk = 0;
			xMatrixState.cBt1 = 0;
			xMatrixState.cBt4 = 0;
			xMatrixState.cBt7 = 0;
		}
	}
	if (2 == cActColumn){
			if(HAL_GPIO_ReadPin(ROW_1_IN_GPIO_Port, ROW_1_IN_Pin)){
				xMatrixState.cBt0 = 0;
				xMatrixState.cBt2 = 1;
				xMatrixState.cBt5 = 0;
				xMatrixState.cBt8 = 0;
			}
			else if (HAL_GPIO_ReadPin(ROW_2_IN_GPIO_Port, ROW_2_IN_Pin)){
				xMatrixState.cBt0 = 0;
				xMatrixState.cBt2 = 0;
				xMatrixState.cBt5 = 1;
				xMatrixState.cBt8 = 0;
			}
			else if (HAL_GPIO_ReadPin(ROW_3_IN_GPIO_Port, ROW_3_IN_Pin)){
				xMatrixState.cBt0 = 0;
				xMatrixState.cBt2 = 0;
				xMatrixState.cBt5 = 0;
				xMatrixState.cBt8 = 1;
			}
			else if (HAL_GPIO_ReadPin(ROW_4_IN_GPIO_Port, ROW_4_IN_Pin)){
				xMatrixState.cBt0 = 1;
				xMatrixState.cBt2 = 0;
				xMatrixState.cBt5 = 0;
				xMatrixState.cBt8 = 0;
			}
			else{
				xMatrixState.cBt0 = 0;
				xMatrixState.cBt2 = 0;
				xMatrixState.cBt5 = 0;
				xMatrixState.cBt8 = 0;
			}
		}
	if (3 == cActColumn){
			if(HAL_GPIO_ReadPin(ROW_1_IN_GPIO_Port, ROW_1_IN_Pin)){
				xMatrixState.cBtHash = 0;
				xMatrixState.cBt3 = 1;
				xMatrixState.cBt6 = 0;
				xMatrixState.cBt9 = 0;
			}
			else if (HAL_GPIO_ReadPin(ROW_2_IN_GPIO_Port, ROW_2_IN_Pin)){
				xMatrixState.cBtHash = 0;
				xMatrixState.cBt3 = 0;
				xMatrixState.cBt6 = 1;
				xMatrixState.cBt9 = 0;
			}
			else if (HAL_GPIO_ReadPin(ROW_3_IN_GPIO_Port, ROW_3_IN_Pin)){
				xMatrixState.cBtHash = 0;
				xMatrixState.cBt3 = 0;
				xMatrixState.cBt6 = 0;
				xMatrixState.cBt9 = 1;
			}
			else if (HAL_GPIO_ReadPin(ROW_4_IN_GPIO_Port, ROW_4_IN_Pin)){
				xMatrixState.cBtHash = 1;
				xMatrixState.cBt3 = 0;
				xMatrixState.cBt6 = 0;
				xMatrixState.cBt9 = 0;
			}
			else{
				xMatrixState.cBtHash = 0;
				xMatrixState.cBt3 = 0;
				xMatrixState.cBt6 = 0;
				xMatrixState.cBt9 = 0;
			}
		}
	if (4 == cActColumn){
			if(HAL_GPIO_ReadPin(ROW_1_IN_GPIO_Port, ROW_1_IN_Pin)){
				xMatrixState.cBtA = 1;
				xMatrixState.cBtB = 0;
				xMatrixState.cBtC = 0;
				xMatrixState.cBtD = 0;
			}
			else if (HAL_GPIO_ReadPin(ROW_2_IN_GPIO_Port, ROW_2_IN_Pin)){
				xMatrixState.cBtA = 0;
				xMatrixState.cBtB = 1;
				xMatrixState.cBtC = 0;
				xMatrixState.cBtD = 0;
			}
			else if (HAL_GPIO_ReadPin(ROW_3_IN_GPIO_Port, ROW_3_IN_Pin)){
				xMatrixState.cBtA = 0;
				xMatrixState.cBtB = 0;
				xMatrixState.cBtC = 1;
				xMatrixState.cBtD = 0;
			}
			else if (HAL_GPIO_ReadPin(ROW_4_IN_GPIO_Port, ROW_4_IN_Pin)){
				xMatrixState.cBtA = 0;
				xMatrixState.cBtB = 0;
				xMatrixState.cBtC = 0;
				xMatrixState.cBtD = 1;
			}
			else{
				xMatrixState.cBtA = 0;
				xMatrixState.cBtB = 0;
				xMatrixState.cBtC = 0;
				xMatrixState.cBtD = 0;
			}
		}
}


//	Function name	: 	vMatrixKeyboardUpdateTimePressed
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Verify if some button stay pressed for more than one cycle and update its  
//		                time pressed in xMatrixTimePressed by using the function 
//		                vMatrixKeyboardIncrementTimePressed
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vMatrixKeyboardUpdateTimePressed(){
	unsigned short int usTimePressed=0;
	char cButtonPressed=0;
	if (xMatrixState.cBt1){ //if pressed
		xMatrixTimePressed.usBt1 ++;
		usTimePressed = xMatrixTimePressed.usBt1;
		cButtonPressed = BT1;
	}
	else if (0 != xMatrixTimePressed.usBt1){
		xMatrixTimePressed.usBt1 = 0;
	}

	if (xMatrixState.cBt2){
	    xMatrixTimePressed.usBt2 ++;
	    usTimePressed = xMatrixTimePressed.usBt2;
	    cButtonPressed = BT2;
	}
	else if (0 != xMatrixTimePressed.usBt2){
		xMatrixTimePressed.usBt2 = 0;
	}

	if (xMatrixState.cBt3){
	    xMatrixTimePressed.usBt3 ++;
	    usTimePressed = xMatrixTimePressed.usBt3;
	    cButtonPressed = BT3;
	}
	else if (0 != xMatrixTimePressed.usBt3){
		xMatrixTimePressed.usBt3 = 0;
	}

	if (xMatrixState.cBt4){
	    xMatrixTimePressed.usBt4 ++;
	    usTimePressed = xMatrixTimePressed.usBt4;
	    cButtonPressed = BT4;
	}
	else if (0 != xMatrixTimePressed.usBt4){
		xMatrixTimePressed.usBt4 = 0;
	}

	if (xMatrixState.cBt5){
	    xMatrixTimePressed.usBt5 ++;
	    usTimePressed = xMatrixTimePressed.usBt5;
	    cButtonPressed = BT5;
	}
	else if (0 != xMatrixTimePressed.usBt5){
		xMatrixTimePressed.usBt5 = 0;
	}

	if (xMatrixState.cBt6){
	    xMatrixTimePressed.usBt6 ++;
	    usTimePressed = xMatrixTimePressed.usBt6;
	    cButtonPressed = BT6;
	}
	else if (0 != xMatrixTimePressed.usBt6){
		xMatrixTimePressed.usBt6 = 0;
	}

	if (xMatrixState.cBt7){
	    xMatrixTimePressed.usBt7 ++;
	    usTimePressed = xMatrixTimePressed.usBt7;
	    cButtonPressed = BT7;
	}
	else{
	    if (0 != xMatrixTimePressed.usBt7){
	        xMatrixTimePressed.usBt7 = 0;
	    }
	}

	if (xMatrixState.cBt8){
	    xMatrixTimePressed.usBt8 ++;
	    usTimePressed = xMatrixTimePressed.usBt8;
	    cButtonPressed = BT8;
	}
	else if (0 != xMatrixTimePressed.usBt8){
		xMatrixTimePressed.usBt8 = 0;
	}

	if (xMatrixState.cBt9){
	    xMatrixTimePressed.usBt9 ++;
	    usTimePressed = xMatrixTimePressed.usBt9;
	    cButtonPressed = BT9;
	}
	else if (0 != xMatrixTimePressed.usBt9){
		xMatrixTimePressed.usBt9 = 0;
	}

	if (xMatrixState.cBt0){
	    xMatrixTimePressed.usBt0 ++;
	    usTimePressed = xMatrixTimePressed.usBt0;
	    cButtonPressed = BT0;
	}
	else if (0 != xMatrixTimePressed.usBt0){
		xMatrixTimePressed.usBt0 = 0;
	}
	if (xMatrixState.cBtA){
	    xMatrixTimePressed.usBtA ++;
	    usTimePressed = xMatrixTimePressed.usBtA;
	    cButtonPressed = BTA;
	}
	else if (0 != xMatrixTimePressed.usBtA){
		xMatrixTimePressed.usBtA = 0;
	}
	if (xMatrixState.cBtB){
	    xMatrixTimePressed.usBtB ++;
	    usTimePressed = xMatrixTimePressed.usBtB;
	    cButtonPressed = BTB;
	}
	else if (0 != xMatrixTimePressed.usBtB){
		xMatrixTimePressed.usBtB = 0;
	}

	if (xMatrixState.cBtC){
	    xMatrixTimePressed.usBtC ++;
	    usTimePressed = xMatrixTimePressed.usBtC;
	    cButtonPressed = BTC;
	}
	else if (0 != xMatrixTimePressed.usBtC){
		xMatrixTimePressed.usBtC = 0;
	}

	if (xMatrixState.cBtD){
	    xMatrixTimePressed.usBtD ++;
	    usTimePressed = xMatrixTimePressed.usBtD;
	    cButtonPressed = BTD;
	}
	else if (0 != xMatrixTimePressed.usBtD){
		xMatrixTimePressed.usBtD = 0;
	}

	if (xMatrixState.cBtAsterisk){
	    xMatrixTimePressed.usBtAsterisk ++;
	    usTimePressed = xMatrixTimePressed.usBtAsterisk;
	    cButtonPressed = BTAsterisk;
	}
	else if (0 != xMatrixTimePressed.usBtAsterisk){
		xMatrixTimePressed.usBtAsterisk = 0;
	}

	if (xMatrixState.cBtHash){
	    xMatrixTimePressed.usBtHash ++;
	    usTimePressed = xMatrixTimePressed.usBtHash;
	    cButtonPressed = BTHash;
	}
	else if (0 != xMatrixTimePressed.usBtHash){
		xMatrixTimePressed.usBtHash = 0;
	}
	vMatrixKeyboardIncrementTimePressed(usTimePressed,cButtonPressed);

}


//	Function name	: 	vMatrixKeyboardIncrementTimePressed
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Check if the button is pressed by 500 ms
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	usTimePressed,
//		                cButtonPressed.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vMatrixKeyboardIncrementTimePressed(unsigned short int usTimePressed, char cButtonPressed){
//	if(!((!usTimePressed)&&(usTimePressed))){ //se ambos não forem 0
	if((usTimePressed!=0) && (cButtonPressed != 0)){ //se ambos não forem 0
		if (!(usTimePressed % 12)){
			vMatrixKeyboardHalfSecPressedCallback(cButtonPressed);
		}
		if (75 == usTimePressed){
			xMatrixTimePressed.cTimerThreeSec = 1;
			vMatrixKeyboardThreeSecPressedCallback(cButtonPressed);
		}
	}
}

//-----------------------------------------Weak Functions----------------------------------------------//

//	Function name	: 	vMatrixKeyboardThreeSecPressedCallback
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Function called when the button is pressed for three seconds
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	cButton
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
__weak void vMatrixKeyboardThreeSecPressedCallback(char cButton){};

//	Function name	: 	vMatrixKeyboardHalfSecPressedCallback
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Function called when the button is pressed for half second 
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	cButton
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
__weak void vMatrixKeyboardHalfSecPressedCallback(char cButton){};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
