/*
 * SPI.h
 *
 * Created: 2/5/2021 4:14:45 PM
 *  Author: Mohamed
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7

#define SS_Enable PORTB &= ~(1<<SS)			/* Define Slave enable */
#define SS_Disable PORTB |= (1<<SS)			/* Define Slave disable */

typedef enum{
	Slave = 0 , Master
	}SPI_StateType;

void SPI_Init(SPI_StateType state);
unsigned char SPI_Transeiver(unsigned char data);
void SPI_Write(unsigned char data);

#endif /* SPI_H_ */