//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------// 
//	buttons.c
//----------------------------------------------Desciption---------------------------------------------//
//
//	This file implements the inicialization and functions used by  buttons on interface, 
//	the functions are:
//
//	-	vButtonsInitButtons	,for Buttons inicialization
//	-	cButtonsRead		,for Reading a state of a button
//
//-----------------------------------------------Author------------------------------------------------//
//	João Vitor Mendes
//	Vitor Akio Isawa
//-----------------------------------------------Version-----------------------------------------------// 
//	Created on :									04/04/24
//	Revised on :									21/06/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------Library-----------------------------------------------// 
#include "stm32g4xx_hal.h"
#include "buttons.h"

//----------------------------------------------Functions----------------------------------------------//

//	Function name	: 	vButtonsInitButtons
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Setting the GPIO interface for using the buttons as a output   
//		                port, the type of the port, clock and the configurations 
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vButtonsInitButtons(){
	//enable clock in PORT B and C
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	//Set Led pins as input mode

	//set PC1 (up Button) pin as input
	GPIOC->MODER &= ~GPIO_MODER_MODE1_0;
	GPIOC->MODER &= ~GPIO_MODER_MODE1_1;

	//set PC2 (down button) pin as input
	GPIOC->MODER &= ~GPIO_MODER_MODE2_0;
	GPIOC->MODER &= ~GPIO_MODER_MODE2_1;

	//set PC3 (left Button) pin as input
	GPIOC->MODER &= ~GPIO_MODER_MODE3_0;
	GPIOC->MODER &= ~GPIO_MODER_MODE3_1;

	//set PC4 (right Button) pin as input
	GPIOC->MODER &= ~GPIO_MODER_MODE4_0;
	GPIOC->MODER &= ~GPIO_MODER_MODE4_1;

	//set PB0 (enter Button) pin as input
	GPIOB->MODER &= ~GPIO_MODER_MODE0_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE0_1;
}

//	Function name	: 	cButtonsRead
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Identify if a button is pressed, it only checks one button per   
//		                time set by cDir 
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	cDir - Sort of buttons available [0-4] named by their orientation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
char cButtonsRead(char cDir){
	char status=0;
	if ((GPIOC->IDR & 0x00000002) && UP == cDir){
		status = 1;
	}
	else if ((GPIOC->IDR & 0x00000004) && DOWN==cDir){
		status = 1;
	}
	else if ((GPIOC->IDR & 0x00000008) && LEFT == cDir) {
		status = 1;
	}
	else if((GPIOC->IDR & 0x00000010) && RIGHT == cDir){
		status = 1;
	}
	else if ((GPIOB->IDR & 0x00000001) && ENTER == cDir){
		status = 1;
	}
	return status;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//