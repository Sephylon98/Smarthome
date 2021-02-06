/*
* SPI_Master.c
*
* Created: 2/5/2021 1:01:18 AM
* Author : Mohamed
*/


/*
Important Note: DO NOT SEND COMMAND VIA BLUETOOTH WHEN THERE IS A LED ON.
This project can be edited to have more features than the ones it already have.
The project can use better coding styles and methods but due to time shortage I performed it as a proof of concept.
*/

/*
Project has 3 commands for now: Read Temperature Sensor , Open a door and close a door.
Each command is sent via bluetooth to MASTER ATMEGA32 and then the command is passed onto the SLAVE ATMEGA32 through SPI Serial comm.
Each command will be printed on both LCDs when it gets recieved from bluetooth and SPI Master device.
*/

#define F_CPU 16000000UL	/* Define CPU Frequency 16MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <avr/interrupt.h>  /* Include AVR interrupt file */
#include <util/delay.h>		/* Include Delay header file */
#include <stdio.h>			/* Include Std. i/p o/p file */
#include <string.h>			/* Include String header file */
#include "LCD.h"            /* Include LCD header file */
#include "SPI.h"            /* Include SPI header file */
#include "UART.h"           /* Include UART header file */

int main(void)
{
	
	/* Enable Global Interrupt */
	//sei();
	/* *********************** */
	
	/* Initialization */
	DIO_Init();
	LCD_Init();
	UART_INIT();
	/* ************** */
	
	unsigned char buffer = 0;
	
	LCD_StringPos("Master Device",1,0);
	LCD_StringPos("Tx Data: ",2,0);
	UART_TxString("Welcome Home");
	
	/* Enable Master */
	SPI_Init(Master);
	SS_Enable;
	
	while (1)
	{
		_delay_ms(500);
		buffer = UART_RxChar();
		//while(!(buffer == '\0'));
		switch(buffer)
		{
			case '0':
			LCD_Cmd(CLR);
			_delay_ms(100);
			SPI_Write('0');
			_delay_ms(100);
			/* Print CMD on LCD */
			//buffer = UART_RxChar();
			LCD_StringPos("Master Device",1,0);
			LCD_StringPos("Tx Data: ",2,0);
			LCD_CharPos('0',2,13);
			_delay_ms(500);
			/* *************** */
			break;
			
			case '1':
			LCD_Cmd(CLR);
			_delay_ms(100);
			SPI_Write('1');
			_delay_ms(100);
			/* Print CMD on LCD */
			//buffer = UART_RxChar();
			LCD_StringPos("Master Device",1,0);
			LCD_StringPos("Tx Data: ",2,0);
			LCD_CharPos('1',2,13);
			_delay_ms(500);
			/* *************** */
			break;
			
			case '2':
			LCD_Cmd(CLR);
			_delay_ms(100);
			SPI_Write('2');
			_delay_ms(100);
			/* Print CMD on LCD */
			//buffer = UART_RxChar();
			LCD_StringPos("Master Device",1,0);
			LCD_StringPos("Tx Data: ",2,0);
			LCD_CharPos('2',2,13);
			_delay_ms(500);
			/* *************** */
			break;
		}
	}
}

/*
ISR(SPI_STC_vect)
{
SPDR = UART_RxChar();
}
*/