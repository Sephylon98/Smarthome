/*
 * ADC.h
 *
 * Created: 1/25/2021 2:37:24 PM
 *  Author: Mohamed
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include "STD_Types.h"

void ADC_Init();
Uint16 ADC_Read(Uint8 channelID);

#endif /* ADC_H_ */