/*
* SPI.c
*
* Created: 2/4/2021 5:01:49 PM
*  Author: Mohamed
*/

#include "SPI.h"

void SPI_Init(SPI_StateType state)					/* SPI Initialize function */
{
	switch (state)
	{
		case Master:
		SS_Disable;
		DDRB |= (1<<MOSI)|(1<<SS)|(1<<SCK);
		DDRB &= ~(1<<MISO);
		SPCR |= (1<<SPE)|(1<<MSTR);
		//SPCR |= (1<<SPIE);
		break;
		case Slave:
		DDRB &= ~(1<<MOSI)|(1<<SS)|(1<<SCK);
		DDRB |= (1<<MISO);
		PORTB |= (1<<SS);
		SPCR |= (1<<SPE);
		//SPCR |= (1<<SPIE);
		break;
	}
}
/* POLLING */
unsigned char SPI_Transeiver(unsigned char data)		/* SPI Transmit & Receive data function */
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}

unsigned char SPI_Receive(void)			/* SPI Receive data function */
{
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}
