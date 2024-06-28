/*
 * ADC.h
 *
 *  Created on: 30 Sep 2022
 *      Author: Hassan Ghandoor
 */
//macros and function prototypes
#ifndef ADC_ITERFACE_H_
#define ADC_ITERFACE_H_
//It includes the function prototypes like DIO.h
void ADC_vidinit(void);
u16 ADC_GET_READING (u8 ch);
#define LEFT 1 // If ADLAR bit = 1 fill ADCH then ADCL
#define RIGHT 0 // If ADLAR bit = 0 fill ADCL then ADCH
#define INTERNAL_VCC 1 //to take 5v from the micro controller
#define INTERNAL_2_5 3
#define EXTERNAL 0 // set an external vref. (Datasheet)
#define ADLAR 5 // bit no. 5 in ADMUX
#define REFS0 6 // bit 6
#define ADEN 7 // ADC enable bit in ADCSRA
// prescaler bits
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
// start conversion bit
#define ADSC 6
//Conversion Flag
#define ADIF 4
#endif /* ADC_ITERFACE_H_ */
