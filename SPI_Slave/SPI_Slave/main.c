/*
* SPI_Slave.c
*
* Created: 2/5/2021 1:02:02 AM
* Author : Mohamed
*/

//

#define F_CPU 16000000UL	/* Define CPU Frequency 16MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <avr/interrupt.h>  /* Include AVR interrupt file */
#include <util/delay.h>		/* Include Delay header file */
#include <stdio.h>			/* Include Std. i/p o/p file */
#include <stdlib.h>         /* Include Std library file */
#include <string.h>			/* Include String header file */
#include "LCD.h"            /* Include LCD header file */
#include "SPI.h"            /* Include SPI header file */
#include "ADC.h"            /* Include ADC header file */
#include "Servo.h"          /* Include Servo motor header file */

volatile unsigned int door_flag = 0;
Uint16 temp = 0;
Sint8 buffer[50];
void PrintADC(void);

int main(void)
{
	/* Enable Global Interrupt */
	//sei();
	/* *********************** */
	
	/* Initialization */
	DIO_Init();
	LCD_Init();
	ADC_Init();
	Timer_Init();
	/* *************** */
	
	//unsigned char buffer0 = 0;
	
	LCD_StringPos("Slave Device",1,0);
	LCD_StringPos("Rx Data: ",2,0);
	
	DDRC |= (1<<0)|(1<<1)|(1<<2);
	/* Enable Slave */
	SPI_Init(Slave);
	
	while (1)
	{
		switch(SPI_Receive())
		{
			case '0':
			LCD_Cmd(CLR);
			/* Print CMD on LCD */
			LCD_StringPos("Slave Device",1,0);
			LCD_StringPos("Rx Data: ",2,0);
			LCD_CharPos('0',2,13);
			LCD_Cmd(CLR);
			/* **************** */
			/* ADC */
			LCD_StringPos("Rx Data: ",1,0);
			LCD_CharPos('0',1,13);
			PORTC |= (1<<2);
			PrintADC();
			PORTC &= ~(1<<2);
			/* ADC */
			break;
			
			case '1':
			LCD_Cmd(CLR);
			switch(door_flag) //if door is closed
			{
				case 0:
				PORTC |= (1<<0);
				Door_Open();
				door_flag ++;
				LCD_Cmd(CLR);
				LCD_StringPos("Door Open",1,0);
				LCD_StringPos("Rx Data: ",2,0);
				LCD_CharPos('1',2,13);
				PORTC &= ~(1<<0);
				break;
				
				case 1:
				PORTC |= (1<<0);
				LCD_Cmd(CLR);
				LCD_StringPos("Already Open",1,0);
				PORTC &= ~(1<<0);
				break;
			}
			break;
			
			case '2':
			LCD_Cmd(CLR);
			switch(door_flag) // if door is opened
			{
				case 1:
				PORTC |= (1<<1);
				Door_Close();
				door_flag --;
				LCD_StringPos("Door Close",1,0);
				LCD_StringPos("Rx Data: ",2,0);
				LCD_CharPos('2',2,13);
				PORTC &= ~(1<<1);
				break;
				
				case 0:
				PORTC |= (1<<1);
				LCD_Cmd(CLR);
				LCD_StringPos("Already Closed",1,0);
				PORTC &= ~(1<<1);
				break;
			}
			break;
			
			/* Add more cases ( features) here */
		}
	}
}
void PrintADC(void)
{
	temp = ADC_Read(1);
	temp /= 4;
	itoa(temp,buffer,10);
	LCD_StringPos("Temperature: ",2,0);
	LCD_String(buffer);
}
/*
ISR(SPI_STC_vect)
{
data = SPDR;
}
*/