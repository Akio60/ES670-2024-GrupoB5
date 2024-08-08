//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------// 
//	app.c
//----------------------------------------------Desciption---------------------------------------------//
//
//	This file implements the inicialization and functions used by app given the usage of the
//  features apllied to all screens shown.
//
//-----------------------------------------------Author------------------------------------------------//
//	João Vitor Mendes
//	Vitor Akio Isawa
//-----------------------------------------------Version-----------------------------------------------// 
//	Created on :									01/05/24
//	Revised on :									21/06/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//-----------------------------------------------Library-----------------------------------------------// 
#include "main.h"

//-------------------------------------------Variable and definitions----------------------------------//
	extern float fTemperature ;
	extern float fHeaterPWM ;
	extern float fCoolerPWM ;
	extern float fSetPointValue ;
	extern float fAppKp ;
	extern float fAppKi ;
	extern float fAppKd ;
	extern char cCtrlOn ;
	extern unsigned short int usCoolerSpeed;
	extern unsigned short int usTimeCounterLCD ;
	extern unsigned short int usTimeCounter;
	extern unsigned char ucTimeCounterUART;
	extern enum state xAppState;	//used to know when update the lcd in while loop

	extern char cMenuIndex[_NUMBER_OF_MENUS];
	extern int iActMenuIndex ;

	char cKeyboardButtonPressed = 0;
	char cKeyPressedProtect = 0;
	unsigned char ucValue[16];
	unsigned char numberOfDigits=0;

	extern TIM_HandleTypeDef * pTimBuzzer ;

	char cComma=0;

//----------------------------------------------Functions----------------------------------------------//

//	Function name	: 	vInitApp
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Inicialize the flag who shows the actual screen on app.
//					
//-----------------------------------------------------------------------------------------------------//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vInitApp (){
	for (int i=1; i< _NUMBER_OF_MENUS;i++){
		cMenuIndex[i]=0;

	}
	cMenuIndex[TEMPERATURE]=1;
	iActMenuIndex = TEMPERATURE;
}

//	Function name	: 	vAppChangeMenu
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Function used by selecting an given value on witch state of menu will be set
//					
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	enum configModeValues value
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppChangeMenu (enum configModeValues value){
	cMenuIndex[iActMenuIndex] = 0;
	iActMenuIndex = value;
	cMenuIndex[iActMenuIndex]=1;
}

//	Function name	: 	vAppGetFromKeyboard
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	"Read" the value obteined by the matrix keyboard by change
// 						the cKeyboarbuttonpressed to the given character
//					
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	matrixButtons * pMatrixButtons
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppGetFromKeyboard(matrixButtons * pMatrixButtons){
		if(pMatrixButtons->cBt1){
			cKeyboardButtonPressed = '1';
		}
		else if (pMatrixButtons->cBt2){
			cKeyboardButtonPressed = '2';
		}
		else if (pMatrixButtons->cBt3){
			cKeyboardButtonPressed = '3';
		}
		else if (pMatrixButtons->cBt4){
			cKeyboardButtonPressed = '4';
		}
		else if (pMatrixButtons->cBt5){
			cKeyboardButtonPressed = '5';
		}
		else if (pMatrixButtons->cBt6){
			cKeyboardButtonPressed = '6';
		}
		else if (pMatrixButtons->cBt7){
			cKeyboardButtonPressed = '7';
		}
		else if (pMatrixButtons->cBt8){
			cKeyboardButtonPressed = '8';
		}
		else if (pMatrixButtons->cBt9){
			cKeyboardButtonPressed = '9';
		}
		else if (pMatrixButtons->cBt0){
			cKeyboardButtonPressed = '0';
		}
		else if (pMatrixButtons->cBtA){ //10
			cKeyboardButtonPressed = 'A';
		}
		else if (pMatrixButtons->cBtB){ //11
			cKeyboardButtonPressed = 'B';
		}
		else if (pMatrixButtons->cBtC){ //12
			cKeyboardButtonPressed = 'C';
		}
		else if (pMatrixButtons->cBtD){ //13
			cKeyboardButtonPressed = 'D';
		}
		else if (pMatrixButtons->cBtAsterisk){ //14
			cKeyboardButtonPressed = '*';
		}
		else if (pMatrixButtons->cBtHash){ //15
			cKeyboardButtonPressed = '#';
		}
		else{
			cKeyboardButtonPressed = ' ';
		}
}

//	Function name	: 	vAppUpdateValue
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	This function is used to update and shape the form of data is shown on display
//					
//-----------------------------------------------------------------------------------------------------//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppUpdateValue(){
	cComma = 0;
	float fValue;
	for (int i=0; i<16;i++){
		if(',' == ucValue[i]){
			ucValue[i]='.';
		}
	}
	fValue = atof ((char *)ucValue);
	if(cMenuIndex[SETPOINT]){
		if (fValue >= 25 && fValue <= 90){
			fSetPointValue = fValue;
		}else{
			//fazer estado de erro se der tempo
		}
	}
	else if(cMenuIndex[HEATER]){
		if (fValue >= 0 && fValue <= 100){
			fHeaterPWM = fValue;
		}else{
			//fazer estado de erro se der tempo
		}
	}
	else if(cMenuIndex[COOLER]){
		if (fValue >= 0 && fValue <= 100){
			fCoolerPWM = fValue;
		}else{
			//fazer estado de erro se der tempo
		}
	}
	else if(cMenuIndex[KP]){
		fAppKp = fValue;
	}
	else if(cMenuIndex[KI]){
		fAppKi = fValue;
	}
	else if(cMenuIndex[KD]){
		fAppKd = fValue;
	}
	else if(cMenuIndex[CONTROL]){
		if (0 == fValue){
			cCtrlOn = 0;
		}
		else if(1 == fValue){
			cCtrlOn = 1;
		}
	}
	vBuzzerConfig(1000,100,pTimBuzzer);
	vBuzzerPlay();
}

//	Function name	: 	vAppGetKeyboardValue
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	This function is used to get a value from the interface matrix keyboard
//					
//-----------------------------------------------------------------------------------------------------//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppGetKeyboardValue(){
if(!cKeyPressedProtect){

	switch (cKeyboardButtonPressed) {
		case '#':
			switch (xAppState) {
				case CONFIG:
					if (iActMenuIndex==SETPOINT || iActMenuIndex==HEATER  || iActMenuIndex==COOLER  || iActMenuIndex==KP || iActMenuIndex == KI ||iActMenuIndex ==KD || iActMenuIndex ==CONTROL ){
						vAppChangeState(CHANGE);

					}
					break;
				case CHANGE:
					vAppUpdateValue();
					for (int i = 0; i<numberOfDigits ; i ++){
						ucValue[i]=0;
					}
					numberOfDigits=0;
					vAppChangeState(CONFIG);
					break;
				default:
					break;
			}
			cKeyPressedProtect=1;
			usTimeCounter=0;
			break;
		case '1':
			if(xAppState == CHANGE  && numberOfDigits<16){
			ucValue[numberOfDigits]='1';
			numberOfDigits+=1;
			cKeyPressedProtect=1;
			usTimeCounter=0;
			}
			break;
		case '2':
			if(xAppState == CHANGE  && numberOfDigits<16){
			ucValue[numberOfDigits]='2';
			numberOfDigits+=1;
			cKeyPressedProtect=1;
			usTimeCounter=0;
			}
			break;
		case '3':
			if(xAppState == CHANGE  && numberOfDigits<16){
			ucValue[numberOfDigits]='3';
			numberOfDigits+=1;
			cKeyPressedProtect=1;
			usTimeCounter=0;
			}
			break;
		case '4':
			if(xAppState == CHANGE  && numberOfDigits<16){
			ucValue[numberOfDigits]='4';
			numberOfDigits+=1;
			cKeyPressedProtect=1;
			usTimeCounter=0;
			}
			break;
		case '5':
			if(xAppState == CHANGE  && numberOfDigits<16) {
			ucValue[numberOfDigits]='5';
			numberOfDigits+=1;
			cKeyPressedProtect=1;
			usTimeCounter=0;
			}
			break;
		case '6':
			if(xAppState == CHANGE && numberOfDigits<16){
			ucValue[numberOfDigits]='6';
			numberOfDigits+=1;
			cKeyPressedProtect=1;
			usTimeCounter=0;
			}
			break;
		case '7':
			if(xAppState == CHANGE && numberOfDigits<16){
			ucValue[numberOfDigits]='7';
			numberOfDigits+=1;
			cKeyPressedProtect=1;
			usTimeCounter=0;
			}
			break;
		case '8':
			if(xAppState == CHANGE && numberOfDigits<16){
			ucValue[numberOfDigits]='8';
			numberOfDigits+=1;
			cKeyPressedProtect=1;
			usTimeCounter=0;
			}
			break;
		case '9':
			if(xAppState == CHANGE && numberOfDigits<16){
			ucValue[numberOfDigits]='9';
			numberOfDigits+=1;
			cKeyPressedProtect=1;
			usTimeCounter=0;
			}
			break;
		case '0':
			if(xAppState == CHANGE && numberOfDigits<16){
			ucValue[numberOfDigits]='0';
			numberOfDigits+=1;
			cKeyPressedProtect=1;
			usTimeCounter=0;
			}
			break;
		case 'C':
			if(xAppState == CHANGE && numberOfDigits<16){
				if(!cComma){
					ucValue[numberOfDigits]=',';
					cComma = 1;
					numberOfDigits+=1;
					cKeyPressedProtect=1;
					usTimeCounter=0;
					}
			}
			break;

		default:
			break;
	}
}
else
{
	if(!(usTimeCounter%70)){
		cKeyPressedProtect=0;
	}
}
}

//	Function name	: 	vAppTimeCounter
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	This function count the time up to 100 using usTimeCounter.
//					
//-----------------------------------------------------------------------------------------------------//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppTimeCounter(){
	usTimeCounter += 1;
	if(100 == usTimeCounter){
		usTimeCounter = 0;
	}
}

//	Function name	: 	vAppInfoToLCD
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Configure what is shown in lcd in the different states of the aplication
//						in each case of the system mostly using the lcd.h library
//					
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	float fTemp, float fHeater, float fCooler, float
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppInfoToLCD (float fTemp, float fHeater, float fCooler, float fSetPointValue){
if (!(usTimeCounter%100)){
	switch (xAppState){
		case RUN:
			vLcdSendCommand(CMD_CLEAR);
			vLcdSetCursor(1,8);
			vLcdWriteString("T:");
			vLcdSetCursor(1,10);
			unsigned char ucString [16];
			vLcdFloatToString(fTemp, 4, ucString);
			vLcdWriteString((char *)ucString);

			vLcdSetCursor(1,0);
			vLcdWriteString("R:");
			vLcdSetCursor(1,2);
			vLcdFloatToString(fSetPointValue, 4, ucString);
			vLcdWriteString((char *)ucString);

			vLcdSetCursor(0,8);
			vLcdWriteString("H:");
			vLcdSetCursor(0,10);
			if(100==fHeater){
				vLcdFloatToString(fHeater, 3, ucString);
				vLcdWriteString((char *)ucString);
				vLcdSetCursor(0,13);
				vLcdWriteString("%");
			}else{
				vLcdFloatToString(fHeater, 2, ucString);
				vLcdWriteString((char *)ucString);
				vLcdSetCursor(0,12);
				vLcdWriteString("% ");
			}

			vLcdSetCursor(0,0);
			vLcdWriteString("C:");
			vLcdSetCursor(0,2);
			if(100==fCooler){
				vLcdFloatToString(fCooler, 3, ucString);
				vLcdWriteString((char *)ucString);
				vLcdSetCursor(0,5);
				vLcdWriteString("%");
			}
			else{
				vLcdFloatToString(fCooler, 2, ucString);
				vLcdWriteString((char *)ucString);
				vLcdSetCursor(0,4);
				vLcdWriteString("% ");
				}
			break;
		case CONFIG:
			if(cMenuIndex[TEMPERATURE]){
				vLcdSendCommand(CMD_CLEAR);
				vLcdSetCursor(0,0);
				vLcdWriteString("Temperature:");
				vLcdSetCursor(1,0);
				unsigned char ucString [16];
				vLcdFloatToString(fTemp, 4, ucString);
				vLcdWriteString((char *)ucString);
			}
			else if(cMenuIndex[SETPOINT]){
				vLcdSendCommand(CMD_CLEAR);
				vLcdSetCursor(0,0);
				vLcdWriteString("Reference:");
				vLcdSetCursor(1,0);
				unsigned char ucString [16];
				vLcdFloatToString(fSetPointValue, 2, ucString);
				vLcdWriteString((char *)ucString);

			}
			else if(cMenuIndex[HEATER]){
				vLcdSendCommand(CMD_CLEAR);
				vLcdSetCursor(0,0);
				vLcdWriteString("Heater PWM:");
				vLcdSetCursor(1,0);
				unsigned char ucString [16];

				if(100==fHeaterPWM){
					vLcdFloatToString(fHeater, 3, ucString);
					vLcdWriteString((char *)ucString);
					vLcdSetCursor(1,3);
					vLcdWriteString("%");
				}else{
					vLcdFloatToString(fHeater, 2, ucString);
					vLcdWriteString((char *)ucString);
					vLcdSetCursor(1,2);
					vLcdWriteString("% ");
				}
			}
			else if(cMenuIndex[COOLER]){
				vLcdSendCommand(CMD_CLEAR);
				vLcdSetCursor(0,0);
				vLcdWriteString("Cooler PWM:");
				vLcdSetCursor(1,0);
				unsigned char ucString [16];

				if(100==fCoolerPWM){
					vLcdFloatToString(fCooler, 3, ucString);
					vLcdWriteString((char *)ucString);
					vLcdSetCursor(1,3);
					vLcdWriteString("%");
				}else{
					vLcdFloatToString(fCooler, 2, ucString);
					vLcdWriteString((char *)ucString);
					vLcdSetCursor(1,2);
					vLcdWriteString("% ");
				}
			}
			else if(cMenuIndex[KP]){
				vLcdSendCommand(CMD_CLEAR);
				vLcdSetCursor(0,0);
				vLcdWriteString("Kp:");
				vLcdSetCursor(1,0);
				unsigned char ucString [16];
				vLcdFloatToString(fAppKp, 5, ucString);
				vLcdWriteString((char *)ucString);
			}
			else if(cMenuIndex[KI]){
				vLcdSendCommand(CMD_CLEAR);
				vLcdSetCursor(0,0);
				vLcdWriteString("Ki:");
				vLcdSetCursor(1,0);
				unsigned char ucString [16];
				vLcdFloatToString(fAppKi, 5, ucString);
				vLcdWriteString((char *)ucString);
			}
			else if(cMenuIndex[KD]){
				vLcdSendCommand(CMD_CLEAR);
				vLcdSetCursor(0,0);
				vLcdWriteString("Kd:");
				vLcdSetCursor(1,0);
				unsigned char ucString [16];
				vLcdFloatToString(fAppKd, 5, ucString);
				vLcdWriteString((char *)ucString);
			}
			else if(cMenuIndex[CONTROL]){
				vLcdSendCommand(CMD_CLEAR);
				vLcdSetCursor(0,0);
				vLcdWriteString("Control:");
				vLcdSetCursor(1,0);
				unsigned char ucString [16];
				if(cCtrlOn){
					sprintf((char *)ucString, "On");
				}
				else{
					sprintf((char *)ucString, "Off");
				}
				vLcdWriteString((char *)ucString);
			}
			else if(cMenuIndex[SPEED]){
				vLcdSendCommand(CMD_CLEAR);
				vLcdSetCursor(0,0);
				vLcdWriteString("Cooler Speed:");
				vLcdSetCursor(1,0);
				unsigned char ucString [16];
				vLcdFloatToString(usCoolerSpeed, 5, ucString);
				vLcdWriteString((char *)ucString);
			}
			else
			{
				vLcdSendCommand(CMD_CLEAR);
				vLcdSetCursor(0,0);
				vLcdWriteString("Erro");
			}
			break;
		case CHANGE:
			if(cMenuIndex[TEMPERATURE]){
				vLcdSendCommand(CMD_CLEAR);
				vLcdSetCursor(0,0);
				vLcdWriteString("Erro");
//				vBuzzerConfig(300, 50, pTimBuzzer);
				vBuzzerPlay();
			}
			else if(cMenuIndex[SETPOINT]){
				vLcdSetCursor(0,0);
				vLcdWriteString("Reference->Set");
				vLcdSetCursor(1,0);
				vLcdWriteString("                ");
				vLcdSetCursor(1,0);
				vLcdWriteString((char *)ucValue);
			}
			else if(cMenuIndex[HEATER]){
				vLcdSetCursor(0,0);
				vLcdWriteString("Heater PWM->Set");
				vLcdSetCursor(1,0);
				vLcdWriteString("                ");
				vLcdSetCursor(1,0);
				vLcdWriteString((char *)ucValue);
			}
			else if(cMenuIndex[COOLER]){
				vLcdSetCursor(0,0);
				vLcdWriteString("Cooler PWM->Set");
				vLcdSetCursor(1,0);
				vLcdWriteString("                ");
				vLcdSetCursor(1,0);
				vLcdWriteString((char *)ucValue);
			}
			else if(cMenuIndex[KP]){
				vLcdSetCursor(0,0);
				vLcdWriteString("Kp->Set");
				vLcdSetCursor(1,0);
				vLcdWriteString("                ");
				vLcdSetCursor(1,0);
				vLcdWriteString((char *)ucValue);
			}
			else if(cMenuIndex[KI]){
				vLcdSetCursor(0,0);
				vLcdWriteString("Ki->Set");
				vLcdSetCursor(1,0);
				vLcdWriteString("                ");
				vLcdSetCursor(1,0);
				vLcdWriteString((char *)ucValue);
			}
			else if(cMenuIndex[KD]){
				vLcdSetCursor(0,0);
				vLcdWriteString("Kd->Set");
				vLcdSetCursor(1,0);
				vLcdWriteString("                ");
				vLcdSetCursor(1,0);
				vLcdWriteString((char *)ucValue);
			}
			else if(cMenuIndex[CONTROL]){
				vLcdSetCursor(0,0);
				vLcdWriteString("Control->Set");
				vLcdSetCursor(1,0);
				vLcdWriteString("    (1=On,0=Off)");
				vLcdSetCursor(1,0);
				vLcdWriteString((char *)ucValue);
			}
			else if(cMenuIndex[SPEED]){
				vLcdSendCommand(CMD_CLEAR);
				vLcdSetCursor(0,0);
				vLcdWriteString("Erro");
				vBuzzerPlay();
			}
			else
			{
				vLcdSendCommand(CMD_CLEAR);
				vLcdSetCursor(0,0);
				vLcdWriteString("Erro");
				vBuzzerPlay();
			}
			break;
		default:
			break;

		}
	}
}

//	Function name	: 	vAppPIDControl
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	This function calculates the PID controller response fPidUpdateData and update
//						the process variables
//-----------------------------------------------------------------------------------------------------//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppPIDControl(){
	if(cCtrlOn){
		if (!(usTimeCounter%5)){
			float fAppPIDHeaterPWM;
			fAppPIDHeaterPWM = fPidUpdateData(fTemperature, fSetPointValue);
			fHeaterPWM = fAppPIDHeaterPWM*100;

			if(fTemperature > fSetPointValue + 0.7 ){
				fCoolerPWM = 50;
			}else{
				fCoolerPWM = 0;
			}
			vHeaterPWMDuty(fHeaterPWM/100);
			vCoolerfanPWMDuty(fCoolerPWM/100);
		}
	}

}

//	Function name	: 	vAppLedTemperatureStatus
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	Set representative leds to show the proportion of temperature reach by the sensor
//					
//-----------------------------------------------------------------------------------------------------//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vAppLedTemperatureStatus (){
	if(fTemperature > fSetPointValue + 2.0){
		vLedUp(RED);vLedDown(BLUE); vLedDown(YELLOW); vLedDown(GREEN1);
	}
	else if (fTemperature > fSetPointValue + 1.0 && fTemperature < fSetPointValue + 2.0){
		vLedDown(RED);vLedDown(BLUE); vLedUp(YELLOW); vLedDown(GREEN1);
	}
	else if (fTemperature < fSetPointValue - 1.0){
		vLedDown(RED);vLedUp(BLUE); vLedDown(YELLOW); vLedDown(GREEN1);
	}
	else if (fTemperature > fSetPointValue - 1.0 && fTemperature < fSetPointValue + 1.0){
			vLedDown(RED);vLedDown(BLUE); vLedDown(YELLOW); vLedUp(GREEN1);
	}
	else{
		vLedDown(RED);vLedDown(BLUE); vLedDown(YELLOW); vLedDown(GREEN1);
	}
}

//	Function name	: 	vAppChangeState
//-----------------------------------------------------------------------------------------------------//		
//	 Description	:	This function is used to change the state machine actual state
//					
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	enum state xNewState
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
enum state vAppChangeState(enum state xNewState){
	xAppState = xNewState;
	return xAppState;
}


