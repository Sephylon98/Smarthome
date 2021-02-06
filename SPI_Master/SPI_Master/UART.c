/*
 * UART.c
 *
 * Created: 2/3/2021 7:54:12 PM
 *  Author: Mohamed
 */ 

#include "UART.h"


void UART_INIT(void)
{
	UCSRB |= (1<<RXEN)|(1<<TXEN); //TX & RX Enable
	UCSRC |= (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ2); //1 STOP BIT , 8 - BIT stream
	UBRRL = (char)MyUBRR;
	UBRRH = (char)(MyUBRR >> 8);
} 
void UART_TxChar(unsigned char data)
{
	while(!(UCSRA & (1<<UDRE)));
	UDR = data;
}
void UART_TxString(char * string)
{
	unsigned char i = 0;
	while(string[i]!='\0')
	{
        UART_TxChar(string[i]);
		i++;
	}
}
unsigned char UART_RxChar(void)
{
	while(!(UCSRA & (1<<RXC)));
	return UDR;
}