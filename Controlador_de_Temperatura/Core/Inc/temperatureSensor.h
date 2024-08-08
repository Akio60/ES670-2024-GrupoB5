//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------//
//	temperatureSensor.c
//----------------------------------------------Desciption---------------------------------------------//
//
//		This is a header file "temperatureSensor.c" which configure the functions used in this component
//
//-----------------------------------------------Author------------------------------------------------//
//	João Vitor Mendes
//	Vitor Akio Isawa
//-----------------------------------------------Version-----------------------------------------------//
//	Created on :									17/05/24
//	Revised on :									24/05/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------Defines-----------------------------------------------//
#ifndef INC_TEMPERATURESENSOR_H_
#define INC_TEMPERATURESENSOR_H_
#define _TEMPERATURE_SENSOR_SCALE 3.25
#define _ADC_MAX_CONVERTER 4095

#include "adc.h"

typedef struct temperatureSensor{
	ADC_HandleTypeDef * pADCTemperature;
	int iSensorMeasureDMA;
	float fTemperature;
} temperatureSensor;

//-----------------------------------------------Includes----------------------------------------------//


//----------------------------------------------Functions----------------------------------------------//


//	Function name	: 	vTemperatureSensorInit
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Inicialize the functions of the temperature sensor
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	TIM_HandleTypeDef *hadc , pointer to a adc type
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
float fTemperatureSensorConversion (int iTemperature);

//	Function name	: 	fTemperatureSensorGetTemperature
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	returns the float value given from the temperature sensor
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vTemperatureSensorInit(ADC_HandleTypeDef *hadc);


//	Function name	: 	vTemperatureSensorInit
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Convert a value given in int to float, passing by the ADC MAX Convert Value
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	int iTemperature
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
float fTemperatureSensorGetTemperature(void);


#endif /* INC_TEMPERATURESENSOR_H_ */
