/*
 * ADC.c
 *
 * Created: 1/25/2021 2:37:40 PM
 *  Author: Mohamed
 */ 

#include "ADC.h"

void ADC_Init()
{
	ADMUX |= ((1<<REFS1)|(1<<REFS0));  //Internal Voltage Reference
	ADCSRA |= ((1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2)); //ADC Enable , 128 Pre-Scaler
}

Uint16 ADC_Read(Uint8 channelID)
{
	Uint16 data = 0;
	ADMUX = ((ADMUX & 0b11100000)|(channelID & 0b00011111));
	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA & (1<<ADIF)));
	data = ADCL;
	data |= (ADCH<<8);
	return data;
}