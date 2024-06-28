/*
 * DIO.c
 *
 *  Created on: 10 Sep 2022
 *      Author: Hassan Ghandoor
 */
#include <avr/io.h>
#include <avr/delay.h>
#include <stdlib.h>
#include "stdtypes.h"
#include "macros.h"
#include "DIO.h"
u8 DIO_SET_PIN_DIRECTION (u8 PORT_NUM, u8 PIN_NUM, u8 PIN_DIRECTION)
{
	u8 return_value = OK;
	if ((PORT_NUM > PORTD_NUM) || (PIN_NUM > PIN7) || (PIN_DIRECTION > OUTPUT))
	{
		return_value = NOK;
	}
	else
	{
		switch (PORT_NUM)
		{
		case PORTA_NUM:
			if (PIN_DIRECTION == OUTPUT)
			{
				SET_BIT (DDRA,PIN_NUM);
			}
			else
			{
				CLR_BIT (DDRA,PIN_NUM);
			}
			break;
		case PORTB_NUM:
				if (PIN_DIRECTION == OUTPUT)
				{
					SET_BIT (DDRB,PIN_NUM);
				}
				else
				{
					CLR_BIT (DDRB,PIN_NUM);
				}
				break;
		case PORTC_NUM:
				if (PIN_DIRECTION == OUTPUT)
				{
					SET_BIT (DDRC,PIN_NUM);
				}
				else
				{
					CLR_BIT (DDRC,PIN_NUM);
				}
				break;
		case PORTD_NUM:
				if (PIN_DIRECTION == OUTPUT)
				{
					SET_BIT (DDRD,PIN_NUM);
				}
				else
				{
					CLR_BIT (DDRD,PIN_NUM);
				}
		}

	}
	return return_value;
}
u8 DIO_SET_PIN_VALUE (u8 PORT_NUM, u8 PIN_NUM, u8 PIN_VALUE)
{
	u8 return_value = OK;
		if ((PORT_NUM > PORTD_NUM) || (PIN_NUM > PIN7) || (PIN_VALUE > OUTPUT))
		{
			return_value = NOK;
		}
		else
		{
			switch (PORT_NUM)
			{
			case PORTA_NUM:
				if (PIN_VALUE == HIGH)
				{
					SET_BIT(PORTA,PIN_NUM);
				}
				else
				{
					CLR_BIT (PORTA, PIN_NUM);
				}
				break;
			case PORTB_NUM:
					if (PIN_VALUE == HIGH)
					{
						SET_BIT (PORTB, PIN_NUM);
					}
					else
					{
						CLR_BIT (PORTB, PIN_NUM);
					}
					break;
			case PORTC_NUM:
					if (PIN_VALUE == HIGH)
					{
						SET_BIT (PORTC, PIN_NUM);
					}
					else
					{
						CLR_BIT (PORTC, PIN_NUM);
					}
					break;
			case PORTD_NUM:
					if (PIN_VALUE == HIGH)
					{
						SET_BIT (PORTD,PIN_NUM);
					}
					else
					{
						CLR_BIT (PORTD,PIN_NUM);
					}
			}

		}
		return return_value;
}
u8 DIO_SET_PORT_DIRECTION (u8 PORT_NUM, u8 PORT_DIRECTION )
{u8 return_value=OK;
if ((PORT_NUM > PORTD_NUM) || (PORT_DIRECTION > OUTPUT) )
{
	return_value=NOK;
}
else
{
	switch(PORT_NUM)
	{
	case PORTA_NUM:
	if(PORT_DIRECTION == OUTPUT)
	{
		DDRA=0xFF;  //or 255
	}
	else
	{
		DDRA=0;
	}
	break;
		case PORTB_NUM:
		if(PORT_DIRECTION == OUTPUT)
		{
			DDRB = 0xFF;  //or 255
		}
		else
		{
			DDRB = 0;
		}
		break;
		case PORTC_NUM:
				if(PORT_DIRECTION == OUTPUT)
				{
					DDRC = 0xFF;  //or 255
				}
				else
				{
					DDRC = 0;
				}
				break;
				case PORTD_NUM:
						if(PORT_DIRECTION == OUTPUT)
						{
							DDRD = 0xFF;  //or 255
						}
						else
						{
							DDRD = 0;
						}
	}
}
return return_value;
}
u8 DIO_SET_PORT_VALUE (u8 PORT_NUM, u8 PORT_VALUE )
{u8 return_value=OK;
if(PORT_NUM > PORTD_NUM)
{
	return_value=NOK;
}
else
{
	switch (PORT_NUM)
	{
	case PORTA_NUM:
		PORTA=PORT_VALUE;
		break;
	case PORTB_NUM:
			PORTB=PORT_VALUE;
			break;
	case PORTC_NUM:
			PORTC=PORT_VALUE;
			break;
	case PORTD_NUM:
			PORTD=PORT_VALUE;

	}
}
return return_value;
}
