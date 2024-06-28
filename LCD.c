#include "stdtypes.h"
#include "macros.h"
#include "DIO.h"
#include "LCD.h"
#include <avr/delay.h>
void LCD_Send_Command (u8 command) //For the 8 bit mode initialisation to send instructions
{ //to send any instr. RS & RW must be = 0 (Low)
	DIO_SET_PIN_VALUE (control_port, RS, LOW);
	DIO_SET_PIN_VALUE (control_port, RW, LOW);
	DIO_SET_PORT_VALUE (data_port, command); //according to command in datasheet data pins are set
	DIO_SET_PIN_VALUE (control_port, E, HIGH); //Enable needs a falling edge to send a command
_delay_ms (1); //for LCD to feel the high level of E
DIO_SET_PIN_VALUE (control_port, E, LOW);
_delay_ms (2); //LCD needs time between every two commands to make sure the 1st is finished (datasheet)
}
void LCD_INIT (void) //Do these steps once your LCD is on
{   DIO_SET_PORT_DIRECTION (data_port, OUTPUT); //to display your data on this port (8 bit mode)
_delay_ms(30);//(Datasheet 8 bit mode) don't take any instructions for 30ms
  	DIO_SET_PIN_DIRECTION (control_port, RS, OUTPUT);
	DIO_SET_PIN_DIRECTION (control_port, RW, OUTPUT);
	DIO_SET_PIN_DIRECTION (control_port, E, OUTPUT);
	LCD_Send_Command (display_mode);
	LCD_Send_Command (display_on);
	LCD_Send_Command (cursor_auto_increment);
	LCD_Send_Command (return_home);
	LCD_Send_Command (clear_display);

}
void LCD_SEND_CHAR (u16 data) //To send a character (data) to the LCD
{
	DIO_SET_PIN_VALUE (control_port, RS, HIGH);
		DIO_SET_PIN_VALUE (control_port, RW, LOW);
		DIO_SET_PORT_VALUE (data_port, data);
		DIO_SET_PIN_VALUE (control_port, E, HIGH); //Data is sent at -ve edge of E (Datasheet)
	_delay_ms (1);
	DIO_SET_PIN_VALUE (control_port, E, LOW);
}
void LCD_PRINT_INTEGER(u16 x)
{
	u8 arr[4]={0}; //define an array to save the nos. in to appear on LCD. initialise all by 0
	u8 i=4;
	if (x==0)
	{
		LCD_SEND_CHAR ('0');
	}
	while (x!=0) //the last division will definitely give 0 as remainder
	{
		arr[i-1]=(x%10)+'0'; //add ASCII of zero to get the ASCII of any no.
			x=x/10; // to keep the rest of the nos. in x after breaking one of them from x
		i--; //to go to the next part of the array to save the next broken no.
	}
	for( ; i<=3; i++)//whatever the last value of i is, start with it. to print whatever no. of digits wanted
	{
		LCD_SEND_CHAR (arr[i]); // print on LCD
	}
}
