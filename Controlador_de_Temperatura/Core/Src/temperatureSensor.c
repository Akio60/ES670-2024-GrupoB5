//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//----------------------------------------------File Name----------------------------------------------//
//	temperatureSensor.c
//----------------------------------------------Desciption---------------------------------------------//
//
//		This File implements the code in c of the functions of the temperature sensor, the 
//		inicials functions are: Inicialize and setting up the component, collecting data 
//		from the component and converting the data recieved to Celsium
//
//-----------------------------------------------Author------------------------------------------------//
//	João Vitor Mendes
//	Vitor Akio Isawa
//-----------------------------------------------Version-----------------------------------------------//
//	Created on :									17/05/24
//	Revised on :									24/05/24
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------Library-----------------------------------------------// 
#include "temperatureSensor.h"

//-------------------------------------------Variable and definitions----------------------------------//
temperatureSensor tempSensor;


//----------------------------------------------Functions----------------------------------------------//

//	Function name	: 	vTemperatureSensorInit
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Inicialize the functions of the temperature sensor
//-----------------------------------------------------------------------------------------------------//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vTemperatureSensorInit(ADC_HandleTypeDef *hadc){
	tempSensor.pADCTemperature = hadc;
	HAL_ADCEx_Calibration_Start(tempSensor.pADCTemperature, ADC_SINGLE_ENDED); //calibra o sensor
	HAL_ADC_Start_DMA(tempSensor.pADCTemperature, &tempSensor.iSensorMeasureDMA, 1);
	tempSensor.fTemperature = 0;
}

//	Function name	: 	fTemperatureSensorGetTemperature
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	returns the float value given from the temperature sensor
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
float fTemperatureSensorGetTemperature(void){
	tempSensor.fTemperature = fTemperatureSensorConversion(tempSensor.iSensorMeasureDMA);
	return tempSensor.fTemperature;
}

//	Function name	: 	vTemperatureSensorInit
//-----------------------------------------------------------------------------------------------------//
//	 Description	:	Convert a value given in int to float, passing by the ADC MAX Convert Value
//-----------------------------------------------------------------------------------------------------//
//	      Inputs	:	int iTemperature
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
float fTemperatureSensorConversion (int iTemperature){
	float fVoltage;
	fVoltage = _TEMPERATURE_SENSOR_SCALE * iTemperature / _ADC_MAX_CONVERTER;
	return fVoltage/0.01;
}
