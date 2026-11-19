
#include <avr/io.h>
#include "adc.h"

void ADC_Init(void)
{
    ADMUX = (1 << REFS0);   // A0 selected and use 5V as reference
    ADCSRA = (1 << ADEN) | (1 << ADPS2) |
             (1 << ADPS1) | (1 << ADPS0); // ADC on and solw clock(/128KHZ) which is better  
}

uint16_t ADC_ReadChannel(uint8_t channel)
{
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);// choose the pin (0=A0)
    ADCSRA |= (1 << ADSC);  // Start reading one measurement at a time 
    while (ADCSRA & (1 << ADSC)) { } // Wait for ADC untile its done measuring 
    return ADC; // result is from 0 to 1023
}
