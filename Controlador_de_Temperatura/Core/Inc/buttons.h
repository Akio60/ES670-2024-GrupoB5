//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------//  
//	buttons.h
//----------------------------------------------Desciption---------------------------------------------//
//
//	This file implemesnts the inicialization of the buttons functions used by interface, 
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
//-----------------------------------------------Defines-----------------------------------------------//
#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

//-----------------------------------------------Includes----------------------------------------------//

//-----------------------------------------------Structs-----------------------------------------------//
enum buttonsDef {
	UP=1,
	DOWN=2,
	LEFT=3,
	RIGHT=4,
	ENTER=5
};

//----------------------------------------------Functions----------------------------------------------//

//	Function name	: 	vButtonsInitButtons
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Setting the GPIO interface for using the buttons as a output   
//		                port, the type of the port, clock and the configurations 
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	none
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vButtonsInitButtons();

//	Function name	: 	cButtonsRead
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Identify if a button is pressed, it only checks one button per   
//		                time set by cDir 
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	cDir - Sort of buttons available [0-4] named by their orientation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
char cButtonsRead(char dir);

//-----------------------------------------------------------------------------------------------------//

#endif /* INC_BUTTONS_H_ */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//