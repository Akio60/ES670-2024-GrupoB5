/* ***************************************************************** */
/* File name:		 lcd_hal.c							 			 */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related to the LCD HARDWARE based on the KS006U */
/*					 controller										 */
/* Author name:      dloubach										 */
/* Creation date:    16out2015										 */
/* Revision date:    03apr2023                                       */
/* ***************************************************************** */

#include <lcd.h>
#include <main.h>
#include "i2c.h"


/* line and columns */
#define LINE0		0U
#define COLUMN0		0U

#define L0C0_BASE	0x80 /* line 0, column 0 */
#define L1C0_BASE	0xC0 /* line 1, column 0 */
#define MAX_COLUMN  15U

I2C_HandleTypeDef * pHandlerI2c;
char cLCDAddress;
char cBacklight;

// Function with local scope
static void vLcdWrite2Lcd(unsigned char ucBuffer,  unsigned char cDataType);

/* ************************************************ */
/* Method name:        vLcdInitLcd                  */
/* Method description: Initialize the LCD function  */
/* Input params:       n/a                          */
/* Output params:      *hi2c=>pointer to the i2c    */
/*                     addrress=>LCD I2C address    */
/* ************************************************ */
void vLcdInitLcd(I2C_HandleTypeDef *hi2c, char cAddress)
{
	unsigned char ucTemp = 0;

	//TODO: register in a global variable the i2c handler and address
	pHandlerI2c = &hi2c;
	cLCDAddress = cAddress;
	// Time to the LCD's microcontroller start
	HAL_Delay(20);

	// set LCD to 4-bit mode
	ucTemp = 0x20 | LCD_BIT_E;
//	HAL_I2C_Master_Transmit_IT(&hi2c1, cAddress<<1, &ucTemp, 1);
	HAL_I2C_Master_Transmit(&hi2c1, cAddress<<1, &ucTemp, 1, 1000);
	HAL_Delay(1);
	ucTemp = 0x20;
//	HAL_I2C_Master_Transmit_IT(&hi2c1, cAddress<<1, &ucTemp, 1);
	HAL_I2C_Master_Transmit(&hi2c1, cAddress<<1, &ucTemp, 1, 1000);
	HAL_Delay(2);

	// turn-on LCD, with data length 4, 2 lines, character 5x8 */
	vLcdSendCommand(CMD_INIT_CONFIG);

	// init LCD
	vLcdSendCommand(CMD_LCDON_CURSOROFF);

	// clear LCD
	vLcdSendCommand(CMD_CLEAR);
}


/* ************************************************ */
/* Method name:        vLcdWriteData                */
/* Method description: Write data to be displayed   */
/* Input params:       ucData => char to be written */
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdWriteData(unsigned char ucData)
{
	/* just a relay to send data */
	vLcdWrite2Lcd(ucData, LCD_RS_DATA);
}


/* ************************************************ */
/* Method name:        vLcdSendCommand              */
/* Method description: Write command to LCD         */
/* Input params:       ucCmd=>command to be executed*/
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdSendCommand(unsigned char ucCmd)
{
	/* just a relay to send command */
	vLcdWrite2Lcd(ucCmd, LCD_RS_CMD);
}


/* ************************************************ */
/* Method name:        vLcdSetCursor                */
/* Method description: Set cursor line and column   */
/* Input params:       cLine = LINE0..LINE1         */
/*                     cColumn = COLUMN0..MAX_COLUMN*/
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdSetCursor(unsigned char cLine, unsigned char cColumn)
{
	char cCommand;

	if(LINE0 == cLine)
		/* line 0 */
		cCommand = L0C0_BASE;
	else
		/* line 1 */
		cCommand = L1C0_BASE;

	/* maximum MAX_COLUMN columns */
	cCommand += (cColumn & MAX_COLUMN);

	// send the command to set the cursor
	vLcdSendCommand(cCommand);
}

/* ************************************************ */
/* Method name:        vLcdWriteString              */
/* Method description: Write string to be displayed */
/* Input params:       cBuffer => string to be      */
/*                     written in LCD               */
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdWriteString(const char *cBuffer)
{
	while(*cBuffer)
	{
		vLcdWriteData(*cBuffer++);
	};
}


/* ************************************************ */
/* Method name:        vLCDDummyText                */
/* Method description: Write a dummy hard coded text*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdDummyText(void)
{
	// clear LCD
	vLcdSendCommand(CMD_CLEAR);

	// set the cursor line 0, column 1
	vLcdSetCursor(0,1);

	// send string
	vLcdWriteString("*** ES670 ***");

	// set the cursor line 1, column 0
	vLcdSetCursor(1,0);
	vLcdWriteString("Prj Sis Embarcad");
}

/* ************************************************ */
/* Method name: 	   vLcdWrite2Lcd         		*/
/* Method description: Send command or data to LCD  */
/* Input params:	   ucBuffer => byte to be send  */
/*                   cDataType => command LCD_RS_CMD*/
/*                     or data LCD_RS_DATA          */
/* Output params:	   n/a 							*/
/* ************************************************ */
static void vLcdWrite2Lcd(unsigned char ucBuffer,  unsigned char cDataType)
{
	// Vocês devem implementar essa função

	// cDataType indica se deve ser enviado um dado ou um comando ao display
	// Se cDataType for igual a LCD_RS_CMD, deve ser enviado um comando (Pino RS do display em nível baixo)
	// Se cDataType for igual a LCD_RS_DATA, deve ser enviado um dado (Pino RS do display em nível alto)
	unsigned char ucI2CTransmit = LCD_BIT_E;
	ucI2CTransmit |= LCD_BIT_BACKLIGHT;

	if(cDataType == LCD_RS_DATA){
		ucI2CTransmit |=LCD_BIT_RS ;
	}
	unsigned char ucMask = 0b11110000;
	ucMask &= ucBuffer;
	ucI2CTransmit |= ucMask;
	cBacklight =1;

	//send MSB
	HAL_I2C_Master_Transmit(&hi2c1, cLCDAddress << 1 , &ucI2CTransmit, 1, 1000);
	HAL_Delay(1);

	ucI2CTransmit &= (~ (LCD_BIT_E));
	HAL_I2C_Master_Transmit(&hi2c1, cLCDAddress << 1, &ucI2CTransmit, 1, 1000);
	HAL_Delay(2);



	ucI2CTransmit |= LCD_BIT_E;
	ucI2CTransmit &= 0b00001111; //clean the MSB data
	ucMask = (ucBuffer & 0b00001111) << 4;
	ucI2CTransmit |= ucMask;

	//send LSB
	HAL_I2C_Master_Transmit(&hi2c1, cLCDAddress << 1, &ucI2CTransmit, 1, 1000);
	HAL_Delay(1);
	ucI2CTransmit &= (~ (LCD_BIT_E));
	HAL_I2C_Master_Transmit(&hi2c1, cLCDAddress << 1, &ucI2CTransmit, 1, 1000);
	HAL_Delay(2);

	// Vocês irão enviar o byte de dados ou comando em duas etapas
	// Na primeira etapa serão enviados os 4 bits mais significativos
	// Na segunda etapa serão enviados os 4 bits menos significativos
	// Para enviar cada bloco de 4 bits, os dados devem ser colocados nos pinos D4-D7, e deve ser dado
	// um pulso de duração de 1 ms no pino Enable do display, em seguida, o pino Enable deve voltar
	// para nível baixo.
	// Para escrever um dado ou um comando o pino Write/Read do display deve estar em nível baixo

	// Na escrita vocês podem acender ou desligar o backlight do LCD (P3 do CI PCF8574). Registrem em uma
	// variável global se o backlight deve ficar aceso ou apagado. Essa variável global será atualizada nas
	// funções vLcdBacklighON() e vLcdBacklighOFF()
}

void vLcdBacklighON(){
	if(!cBacklight){
		unsigned char ucAux = 0xff;
		HAL_I2C_Master_Transmit(&hi2c1, cLCDAddress << 1, &ucAux, 1, 1000);
		cBacklight = 1;
	}
}

void vLcdBacklighOFF(){
	if(cBacklight){
		unsigned char ucAux = 0x00;
		HAL_I2C_Master_Transmit(&hi2c1, cLCDAddress << 1, &ucAux, 1, 1000);
		cBacklight = 0;
	}
}

void vLcdToggleBackLight(){
	if(cBacklight){
		vLcdBacklighOFF();
		cBacklight = 0;
	}
	else{
		vLcdBacklighON();
		cBacklight = 1;
	}
}

//	Function name	: 	vCommunicationFloatToString
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Turns Float to Strings using atof functon and set a "." instead a ","
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	float fInputNumber
//		                int iDigits
//		                unsigned char * ucOutputNumber
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vLcdFloatToString(float fInputNumber, int iDigits, unsigned char * ucOutputNumber){
	gcvt(fInputNumber, iDigits, ucOutputNumber);
	ucOutputNumber[17] = '\000';
	int iPos =0;
	while (iPos >= 0){
			if ('\000'!=ucOutputNumber[iPos]){
				if (ucOutputNumber[iPos] == '.'){
					ucOutputNumber[iPos] = ',';
				}
				iPos++;
			}
			else{
				iPos = -1;
			}
	}
}
