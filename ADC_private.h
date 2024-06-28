/*
 * ADC_private.h
 *
 *  Created on: 1 Oct 2022
 *      Author: Hassan Ghandoor
 */
//location of registers in memory seen only in the program file & not seen by the user
#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_
// since we removed the avr library we have to tell it the addresses of the ADC registers in the memory by ourselves
#define ADMUX *((volatile u8*) 0x27)
#define ADCSRA *(( volatile u8*) 0x26)
#define ADC_RES *(( volatile u16*) 0x24)

#endif /* ADC_PRIVATE_H_ */
