//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------//
//	matrixKeyboard.h
//----------------------------------------------Desciption---------------------------------------------//
//
//	This header file indentify the functions there will be used to execute the requisits of the keyboard
//	sofware. Here we create the struct used to define the state of each button of the keyboard and a 
//	struct with almost the same form used before to count the time that the button has been pressed. 
//
//-----------------------------------------------Author------------------------------------------------//
//	João Vitor Mendes
//	Vitor Akio Isawa
//-----------------------------------------------Version-----------------------------------------------//
//	Created on :									05/04/24
//	Revised on :									13/04/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------Defines-----------------------------------------------//
#ifndef INC_MATRIXKEYBOARD_H_
#define INC_MATRIXKEYBOARD_H_

#define ROW_4_IN_Pin GPIO_PIN_11
#define ROW_4_IN_GPIO_Port GPIOB
#define ROW_3_IN_Pin GPIO_PIN_12
#define ROW_3_IN_GPIO_Port GPIOB
#define ROW_2_IN_Pin GPIO_PIN_13
#define ROW_2_IN_GPIO_Port GPIOB
#define ROW_1_IN_Pin GPIO_PIN_15
#define ROW_1_IN_GPIO_Port GPIOB
#define COLUMN_4_OUT_Pin GPIO_PIN_7
#define COLUMN_4_OUT_GPIO_Port GPIOC
#define COLUMN_3_OUT_Pin GPIO_PIN_8
#define COLUMN_3_OUT_GPIO_Port GPIOC
#define COLUMN_2_OUT_Pin GPIO_PIN_9
#define COLUMN_2_OUT_GPIO_Port GPIOC
#define COLUMN_1_OUT_Pin GPIO_PIN_10
#define COLUMN_1_OUT_GPIO_Port GPIOA

//-----------------------------------------------Includes----------------------------------------------//

//-----------------------------------------------Structs-----------------------------------------------//
typedef struct matrixButtons{
	char cBt1;			// row :1 	Column: 5
	char cBt2;			// row :1 	Column: 6
	char cBt3;			// row :1 	Column: 7
	char cBt4;			// row :2 	Column: 5
	char cBt5;			// row :2 	Column: 6
	char cBt6;			// row :2 	Column: 7
	char cBt7;			// row :3 	Column: 5
	char cBt8;			// row :3 	Column: 6
	char cBt9;			// row :3	Column: 7
	char cBt0;			// row :4 	Column: 6
	char cBtA;			// row :1 	Column: 8
	char cBtB;			// row :2 	Column: 8
	char cBtC;			// row :3 	Column: 8
	char cBtD;			// row :4 	Column: 8
	char cBtAsterisk;	// row :4 	Column: 5
	char cBtHash;	 	// row :4 	Column: 7
} matrixButtons, *pMatrixButtons;

typedef struct matrixButtonsTime{
	unsigned short int usBt1;			// row :1 	Column: 5
	unsigned short int usBt2;			// row :1 	Column: 6
	unsigned short int usBt3;			// row :1 	Column: 7
	unsigned short int usBt4;			// row :2 	Column: 5
	unsigned short int usBt5;			// row :2 	Column: 6
	unsigned short int usBt6;			// row :2 	Column: 7
	unsigned short int usBt7;			// row :3 	Column: 5
	unsigned short int usBt8;			// row :3 	Column: 6
	unsigned short int usBt9;			// row :3	Column: 7
	unsigned short int usBt0;			// row :4 	Column: 6
	unsigned short int usBtA;			// row :1 	Column: 8
	unsigned short int usBtB;			// row :2 	Column: 8
	unsigned short int usBtC;			// row :3 	Column: 8
	unsigned short int usBtD;			// row :4 	Column: 8
	unsigned short int usBtAsterisk;		// row :4 	Column: 5
	unsigned short int usBtHash;	 		// row :4 	Column: 7
	char cTimerThreeSec;
} matrixButtonsTime, *pMatrixButtonsTime;

enum matrixKeyboardDef {
	BT1=1,			// row :1 	Column: 5
	BT2,			// row :1 	Column: 6
	BT3,			// row :1 	Column: 7
	BT4,			// row :2 	Column: 5
	BT5,			// row :2 	Column: 6
	BT6,			// row :2 	Column: 7
	BT7,			// row :3 	Column: 5
	BT8,			// row :3 	Column: 6
	BT9,			// row :3	Column: 7
	BT0,			// row :4 	Column: 6
	BTA,			// row :1 	Column: 8
	BTB,			// row :2 	Column: 8
	BTC,			// row :3 	Column: 8
	BTD,			// row :4 	Column: 8
	BTAsterisk,		// row :4 	Column: 5
	BTHash		 	// row :4 	Column: 7
};
matrixButtons * pMatrixKeyboardGetKeys();

//----------------------------------------------Functions----------------------------------------------//
void vMatrixKeyboardInit();
void vMatrixKeyboardReset();
void vMatrixKeyboardTimeReset();
void vMatrixKeyboardUpdateCallback();
void vMatrixKeyboardSetPort();
void vMatrixKeyboardReadPorts();
void vMatrixKeyboardUpdateTimePressed();
void vMatrixKeyboardIncrementTimePressed(unsigned short int siTimePressed, char cButtonPressed);
void vMatrixKeyboardThreeSecPressedCallback(char cButton);
void vMatrixKeyboardHalfSecPressedCallback(char cButton);

//-----------------------------------------------------------------------------------------------------//
#endif /* INC_MATRIXKEYBOARD_H_ */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//