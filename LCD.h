/*
 * LCD.h
 *
 *  Created on: 10 Sep 2022
 *      Author: Hassan Ghandoor
 */

#ifndef LCD_H_
#define LCD_H_
#define clear_display 0x01
#define display_mode 0x38
#define display_on 0x0C
#define cursor_auto_increment 0x06
#define return_home 0x80
#define control_port PORTC_NUM
#define RS PIN0
#define RW PIN1
#define E PIN2
#define data_port PORTB_NUM
//function prototypes
void LCD_Send_Command (u8 command);
void LCD_INIT (void);
void LCD_SEND_CHAR (u16 data);
void LCD_PRINT_INTEGER(u16 x);

#endif /* LCD_H_ */
