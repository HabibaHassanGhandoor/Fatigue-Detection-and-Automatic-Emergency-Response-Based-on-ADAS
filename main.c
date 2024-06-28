#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include"stdtypes.h"
#include <stdbool.h>
#include "DIO.h"
#include "LCD.h"
#include "ADC_iterface.h"
#include "ADC_config.h"

#define false 0
#define true 1

volatile u16 signal; // To store ADC data
volatile u16 threshold = 550;   // To know which signal to count as a beat
u16 BPM = 0; // used to hold the pulse rate. Updated every 2 ms
volatile u16 IBI=600; // Inter-beat interval (The time between 2 beats) used to find instant moment of heart beat
volatile u8 pulse = false; // true when pulse wave is high, false when it's low
// these variables are volatile because they are used during the interrupt service routine
volatile QS = false; //false
volatile u16 rate[10]; //array to hold the last 10 IBI values
volatile u32 samplecounter = 0; // used to determine pulse timing
volatile u32 lastbeattime = 0; //used to find IBI
volatile u16 P = 512; //To find peak in pulse wave
volatile u16 T = 512; //Used to find trough in pulse wave
volatile u8 amp = 100; // to hold amplitude of pulse wave
volatile firstbeat = true; // Used to start from a reasonable beat (used to seed the rate array so we startup with reasonable BPM)
volatile secondbeat = false; // used to seed the rate array so we startup with reasonable BPM
u16 array[4] = {'B','P','M',':'};
int main(void)
{ // To set the pin on which the sensor will be connected to ADC port
DIO_SET_PIN_DIRECTION(PORTA, PIN5, INPUT);
DIO_SET_PIN_VALUE(PORTA, PIN5, ACTIVATE_PULLUP);
// To blink a LED with every heart beat
DIO_SET_PIN_DIRECTION(PORTB, PIN0, OUTPUT);
ADC_vidinit(); // ADC initialisation
LCD_INIT(); // LCD initialisation
// Timer 0 setup to trigger an interrupt every 2 ms
//TCNT0 = 0; // Initialisation of counter register
TCCR0 |= (1<<WGM01)| (1<<CS02); //  | (1<<COM01) //  Go To CTC Mode & 256 prescaler
OCR0 = 0X7C; // Set the max no. of counts to 124 for 500 Hz sample rate
TIMSK |= (1<<OCIE0); // Emanle Interrupt on match between TCNT0 Register & OCR0
SREG  |= (1<<7); // Enable Global Interrupt
	while (1)
	{
		// DIO_SET_PIN_VALUE(PORTB, PIN0, HIGH);
		 if (QS == true) // A Heart beat Was Found
		 {
		      // BPM and IBI have been Determined
		      // Quantified Self "QS" true when avr finds a heart beat
			for(u8 j=0; j<4; j++)
				{
			 	LCD_SEND_CHAR (array[j]);
				}
			    LCD_PRINT_INTEGER (BPM); // Show BPM On LCD
		      QS = false; // reset the Quantified Self flag for next time
	 }

		  _delay_ms (2000);  //  take a break



		  LCD_Send_Command (clear_display);

		  LCD_Send_Command (return_home);
	}
}


ISR (TIMER0_COMP_vect)

{
SREG  |= (0<<7); // Disable global interrupt so nothing interrupts the BPM calculation
signal = ADC_GET_READING(5); // Get the now digital reading from the ADC (Signal coming from pulse sensor)
samplecounter +=2; // This counter keeps track of time (Interrupt triggered every 2 ms)
u16 N = samplecounter - lastbeattime; // Monitors the time since the last beat to avoid noise & Helps to find peak & trough of pulse wave

 if(signal < threshold && N > (IBI/5)*3) // Avoid Dichrotic noise by waiting 3/5 of the last IBI
{
	if(signal < T) // T = Trough
	{
		T = signal; // Keep track of the lowest point in pulse wave
	}
}

  if(signal > threshold && signal > P) // Threshold condition helps avoid noise
{
	P = signal; // keep track of the highest point of pulse wave
}
// Time to look for a heart beat
  if (N > 250) // Avoiding High Frequency Noise at low time value i.e. 0.25 seconds
{
	if ((signal > threshold) && (pulse == false) && (N > (IBI/5)*3)) // Signal already shifted to 3/5 of IBI
	{
		pulse = true; // Set the pulse flag upon sensing a pulse
		IBI = samplecounter - lastbeattime; // Measure the time between beats in ms
		lastbeattime = samplecounter; // keep track of time for next pulse

		if(secondbeat) // If this is the 2nd beat i.e If second beat = True (because we do not count the 1st beat)
		{
			secondbeat = false; // Clear the 2nd beat flag
			for(u8 i=0; i<=9; i++) // Seed the running total to get a realistic BPM at startup (seed = cause to begin or grow)
			{
				rate[i] = IBI; // Get 10 IBI readings and save in "rate" array
			}
		}

		if(firstbeat) // If it's the first time we've found a beat
		{
			firstbeat = false; // Clear 1st beat flag
			secondbeat = true; // Set the 2nd beat flag
			SREG  |= (1<<7); // Enable global interrupt
			return; // Discard IBI value because it's unreliable still unstable
		}
		// Keep a running total of the last 10 IBI values
		u32 runningtotal = 0; // clear the running total variable
		for(u8 i=0; i<=8; i++)
		{ // shift data in the rate array and:
			rate[i] = rate[i+1]; // Drop the oldest IBI value to make room for a new one
			runningtotal += rate[i]; // Add up the remaining 9 IBI values
		}
		rate[9] = IBI; // add the latest IBI to the rate array
		runningtotal += rate[9]; // add the latest IBI to the running total
		runningtotal /= 10; // average the last 10 IBI values
		BPM = 60000/runningtotal; // How many beats can fit into a minute ? that's BPM
		QS = true; // Set the Quantified Self flag. We've found a beat!!
	}
}
   if (signal < threshold && pulse == true) // When the values are going down i.e The beat is over
{
	pulse = false; // Return the pulse flag to 0 so we can do this again
	amp = P-T; // Get the amplitude of the pulse wave
	threshold = amp/2 + T; // set the threshold at 50% of the pulse wave
	P = threshold; // reset those for next time
	T = threshold;
}
    if (N > 2500) // If 2.5 seconds go by without a beat
{
threshold = 512; // set threshold to default
P = 512; // set peak default
T = 512; // set trough default
lastbeattime = samplecounter; // Bring the last beat time up to date
firstbeat = true; // set these to avoid noise (1st beat not counted to avoid noise)
secondbeat = false;
}
SREG  |= (1<<7); // Enable Global Interrupt

}
