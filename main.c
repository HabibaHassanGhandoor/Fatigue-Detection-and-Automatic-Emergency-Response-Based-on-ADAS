/*
* GccApplication123.c
*
* Created: 10/2/2022 9:44:53 PM
* Author : youssef rashad
*/

#include <avr/io.h>
#include "PWM_Servo.h"
#define F_CPU 16000000UL
#include <util/delay.h>



int main(void)
{
	/* Replace with your application code */
	ICR1 = 5000;
	Timer1_ServoPWM();
	while (1)
	{
		Servo(0);
		_delay_ms(500);
		//Servo(180);
	//	_delay_ms(500);
		//Servo(0);
	//	_delay_ms(500);
			Servo(180);
			_delay_ms(500);
			//Servo(-90);
			//_delay_ms(500);
			Servo(-90);
			_delay_ms(500);
	}
}

