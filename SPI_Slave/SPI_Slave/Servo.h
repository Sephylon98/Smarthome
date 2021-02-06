/*
 * Servo.h
 *
 * Created: 2/5/2021 8:37:25 PM
 *  Author: Mohamed
 */ 


#ifndef SERVO_H_
#define SERVO_H_

#include <avr/io.h>
#include <util/delay.h>



#define MaxAngle 90
#define MiniAngle 0
#define MaxCount 500
#define MiniCount 250

void Timer_Init(void);
void Door_Open(void);
void Door_Close(void);
void Servo(short Angle);

#endif /* SERVO_H_ */