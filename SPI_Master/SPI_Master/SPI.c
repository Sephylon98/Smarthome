/*
 * SPI.c
 *
 * Created: 2/5/2021 4:14:34 PM
 *  Author: Mohamed
 */ 


#include "SPI.h"            /*Include SPI header file */

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

void SPI_Write(unsigned char data)		/* SPI write data function */
{
	char flush_buffer;
	SPDR = data;			/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));	/* Wait till transmission complete */
	flush_buffer = SPDR;		/* Flush received data */
	/* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read */
}
