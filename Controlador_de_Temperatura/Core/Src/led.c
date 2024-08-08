//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------// 
//	led.c
//----------------------------------------------Desciption---------------------------------------------//
//
//	This file implements the inicialization and functions used by leds, the functions are:
//
//	- vLedInitLeds  ,for led inicialization
//	- vLedUp		,for turning on a chosen led
//	- vledDown		,for turning off a chosen led
//	- vLedWrite		,for setting up or down a chosen led with a selected option
//	- vLedToogle   ,for switching the status of a selected led
//
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
#include "led.h"

//----------------------------------------------Functions----------------------------------------------//

//	Function name	: 	vLedInitLeds
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Setting the GPIO interface for using the led as a output port, 
//		                type of the port and the configurations 
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vLedInitLeds(){
	//enable clock in PORT A and B
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	//Set Led pins as output mode

	//set PA5 (GREEN1 led) pin as output
	GPIOA->MODER |= GPIO_MODER_MODE5_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE5_1;

	//set PA4 (YELLOW) pin as output
	GPIOA->MODER |= GPIO_MODER_MODE4_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE4_1;

	//set PB14 (RED) pin as output
	GPIOB->MODER |= GPIO_MODER_MODE14_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE14_1;

	//set PA12 (GREEN2 led) pin as output
	GPIOA->MODER |= GPIO_MODER_MODE12_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE12_1;

	//set PB5 (BLUE) pin as output
	GPIOB->MODER |= GPIO_MODER_MODE5_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE5_1;

	//Set led pins as push-pull mode
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT5;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT4;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT14;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT12;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT5;
}

//	Function name	: 	vLedUp
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Turns to high-state the selected led 
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	cLed - Sort of leds available [0-4] named by colors
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vLedUp(char cLed){
	switch (cLed) {
		case GREEN1:
			GPIOA->ODR |= GPIO_ODR_OD5;
			break;
		case YELLOW:
			GPIOA->ODR |= GPIO_ODR_OD4;
			break;
		case RED:
			GPIOB->ODR |= GPIO_ODR_OD14;
			break;
		case GREEN2:
			GPIOA->ODR |= GPIO_ODR_OD12;
			break;
		case BLUE:
			GPIOB->ODR |= GPIO_ODR_OD5;
			break;
		default:
			break;
	}
}

//	Function name	: 	vLedDown
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Turns to low-state the selected led
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	cLed - Sort of leds available [0-4] named by colors
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vLedDown(char cLed){
	switch (cLed) {
		case GREEN1:
			GPIOA->ODR &= ~GPIO_ODR_OD5;
			break;
		case YELLOW:
			GPIOA->ODR &= ~GPIO_ODR_OD4;
			break;
		case RED:
			GPIOB->ODR &= ~GPIO_ODR_OD14;
			break;
		case GREEN2:
			GPIOA->ODR &= ~GPIO_ODR_OD12;
			break;
		case BLUE:
			GPIOB->ODR &= ~GPIO_ODR_OD5;
			break;
		default:
			break;
	}
}

//	Function name	: 	vLedWrite
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Forces the selected led to a state given 
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	cLed - Sort of leds available [0-4] named by colors
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vLedWrite(char cLed, char cState){
	if (TRUE == cState){
		vLedUp(cLed);
	}
	else{
		vLedDown(cLed);
	}
}

//	Function name	: 	vLedToggle
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Forces the selected led to switch the state 
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	cLed - Sort of leds available [0-4] named by colors
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vLedToggle(char cLed){
	//read actual state of pin
	switch (cLed){
		case GREEN1:
			GPIOA->ODR ^= GPIO_ODR_OD5;
			break;
		case YELLOW:
			GPIOA->ODR ^= GPIO_ODR_OD4;
			break;
		case RED:
			GPIOB->ODR ^= GPIO_ODR_OD14;
			break;
		case GREEN2:
			GPIOA->ODR ^= GPIO_ODR_OD12;
			break;
		case BLUE:
			GPIOB->ODR ^= GPIO_ODR_OD5;
			break;
		default:
			break;

	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
