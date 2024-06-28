/*
 * ADC_config.h
 *
 *  Created on: 1 Oct 2022
 *      Author: Hassan Ghandoor
 */
//user configurations
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_
// The user can change here i.e choose right or left adjustment and choose what vref he wants
#define RES_ADJ RIGHT //Register adjustment: Right (ADCL then ADCH) or Left (ADCH then ADCL)
#define Vref INTERNAL_VCC // choose vref. = 2.56 (Datasheet)

#endif /* ADC_CONFIG_H_ */
