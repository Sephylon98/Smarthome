/*
 * UART.h
 *
 * Created: 2/3/2021 7:54:27 PM
 *  Author: Mohamed
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#define BaudRate 9600

#define DoubleSpeed  0

#if (DoubleSpeed == 0)
   #define MyUBRR ((F_CPU/(16UL * BaudRate))-1)
#else 
   #define MyUBRR ((F_CPU/(8UL * BaudRate))-1
#endif

void UART_INIT(void);
void UART_TxChar(unsigned char data);
void UART_TxString(char * string);
unsigned char UART_RxChar(void);

#endif /* UART_H_ */