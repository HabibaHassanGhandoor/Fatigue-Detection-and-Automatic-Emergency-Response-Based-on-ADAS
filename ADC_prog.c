#include "stdtypes.h"
#include "ADC_private.h"
#include "macros.h"
#include "ADC_iterface.h"
#include "ADC_config.h"
void ADC_vidinit(void) // ADC initialisation
{ // Register adjustment & Vref. selsction
	ADMUX = (RES_ADJ << ADLAR)|(Vref<<REFS0); // @vref = 3 in interface.h i.e 11 shift it 6 times bec. REF0=bit6. This chooses ref voltage = 2.56 (Datasheet)
	// ADC Enable and prescaler selection
	ADCSRA = (1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); // prescaler divison factor = 128
}
// Fuction to get the digital reading from the ADC
u16 ADC_GET_READING (u8 ch)
{
	ch = ch & 0b00000111; // u8 is from 0 to 255, but we only have 7 ADC channels, so if user entered a larger no. >> mask it to 7
	ADMUX=(ADMUX & 0xF8)|ch; // clears the channels in ADMUX not to overwrite on a previously saved value
	ADCSRA= (1<<ADEN)|(1<<ADSC); // ADC enable again to wake from sleep mode (if happened) & start conversion (Datasheet)
	while (GET_BIT(ADCSRA, ADIF) ==0);//Polling, if conversion is still not done with i.e flag=0 keep looping, but if condition not satisfied i.e flag = 1 (conversion done with) leave the loop
		return ADC_RES; // after leaving the loop return the result of the ADC
}
