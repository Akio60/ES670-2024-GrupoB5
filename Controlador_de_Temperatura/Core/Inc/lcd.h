/* ***************************************************************** */
/* File name:        lcd.h                                           */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for handling the LCD hardware from   */
/*                   the hardware kit                                */
/* Author name:      dloubach, bacurau                               */
/* Creation date:    16out2015                                       */
/* Revision date:    03apr2023                                       */
/* ***************************************************************** */

#ifndef SOURCES_LCD_H_
#define SOURCES_LCD_H_

#include "stm32g4xx_hal.h"
#include <strings.h>
#include <stdio.h>

/* lcd basic commands list */
#define CMD_INIT_CONFIG         0x28 /* data length 4, 2 lines, character 5x8 */
#define CMD_LCDON_CURSORON      0x0F /* display on, cursor on, blink on */
#define CMD_LCDOFF_CURSOROFF    0x08 /* display off, cursor off */
#define CMD_LCDON_CURSOROFF     0x0C /* display on, cursor off */
#define CMD_CLEAR               0x01 /* clear display */
#define CMD_RETURN_HOME         0x02 /* return cursor to top left */
#define CMD_DECREMENT_CURSOR    0x04 /* shift cursor to left */
#define CMD_INCREMENT_CURSOR    0x06 /* shift cursor to right */


/* RS and Enable definitions*/
#define LCD_RS_DATA				1U
#define LCD_RS_CMD   			0U
#define LCD_ENABLED				1U
#define LCD_DISABLED			0U


/* LCD Bits on the PCF8574 IC */
#define LCD_BIT_RS              01U
#define LCD_BIT_RW              0x02U
#define LCD_BIT_E               0x04U
#define LCD_BIT_BACKLIGHT        0x08U



/* ************************************************ */
/* Method name:        vLcdInitLcd                  */
/* Method description: Initialize the LCD function  */
/* Input params:       n/a                          */
/* Output params:      *hi2c=>pointer to the i2c    */
/*                     cAddress=>LCD I2C address    */
/* ************************************************ */
void vLcdInitLcd(I2C_HandleTypeDef *hi2c, char cAddress);


/* ************************************************ */
/* Method name:        vLcdWriteData                */
/* Method description: Write data to be displayed   */
/* Input params:       ucData => char to be written */
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdWriteData(unsigned char ucData);


/* ************************************************ */
/* Method name:        vLcdSendCommand              */
/* Method description: Write command to LCD         */
/* Input params:       ucCmd=>command to be executed*/
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdSendCommand(unsigned char ucCmd);


/* ************************************************ */
/* Method name:        vLcdWriteString              */
/* Method description: Write string to be displayed */
/* Input params:       cBuffer => string to be      */
/*                     written in LCD               */
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdWriteString(const char *cBuffer);


/* ************************************************ */
/* Method name:        vLcdSetCursor                */
/* Method description: Set cursor line and column   */
/* Input params:       cLine = LINE0..LINE1         */
/*                     cColumn = COLUMN0..MAX_COLUMN*/
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdSetCursor(unsigned char cLine, unsigned char cColumn);


/* ************************************************ */
/* Method name:        vLcdDummyText                */
/* Method description: Write a dummy hard coded text*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdDummyText(void);

/* ************************************************ */
/* Method name:        vLcdToggleBackLight          */
/* Method description: Toggle the backlight of LCD  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdToggleBackLight(void);

/* ************************************************ */
/* Method name:        vLcdBacklighOFF              */
/* Method description: Turn the LCD backlight off   */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdBacklighOFF(void);

/* ************************************************ */
/* Method name:        vLcdBacklighON               */
/* Method description: Turn the LCD backlight on    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdBacklighON(void);

//	Function name	: 	vLcdFloatToString
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Turns Float to Strings using atof functon and set a "." instead a ","
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	float fInputNumber
//		                int iDigits
//		                unsigned char * ucOutputNumber
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vLcdFloatToString(float fInputNumber, int iDigits, unsigned char * ucOutputNumber);
#endif /* SOURCES_LCD_H_ */
