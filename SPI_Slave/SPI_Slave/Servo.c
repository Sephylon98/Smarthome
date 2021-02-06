/*
* Servo.c
*
* Created: 2/5/2021 8:37:10 PM
*  Author: Mohamed
*/

#define F_CPU 16000000UL
#include "Servo.h"

void Timer_Init(void)
{
	DDRD |= (1<<5);
	TCCR1A |= ((1<<WGM11)|(1<<COM1A1)); // Non Inverting Mode
	TCCR1B |= ((1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11)); // N=64 - FPWM ;
	ICR1 = 4999;
}
void Door_Open(void)
{
	Servo(0);
	_delay_ms(500);
	Servo(90);
	_delay_ms(500);
}

void Door_Close(void)
{
	Servo(90);
	_delay_ms(500);
	Servo(0);
	_delay_ms(500);
}

void Servo(short Angle)
{
	OCR1A = (((((unsigned short)Angle-MiniAngle)*(MaxCount-MiniCount))/(MaxAngle-MiniAngle))+MiniCount -1);
}