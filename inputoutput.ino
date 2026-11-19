
#define F_CPU 16000000UL //CPU speed for the delay 
#include <avr/io.h>
#include <util/delay.h>
#include "inputoutput.h"

void IO_Init(void)
{
    DDRD &= ~((1 << PD7) | (1 << PD6)); // Buttons are inputs
    PORTD |= (1 << PD7) | (1 << PD6);   // Internal pull-up

    DDRB |= (1 << PB5) | (1 << PB2);    // D13 LED, D10 buzzer driver
    PORTB &= ~((1 << PB5) | (1 << PB2)); // led and buzzer start at off
}

uint8_t LL_Pressed(void)
{
    static uint8_t oldState = 0; // remembers the last state 
    uint8_t pressed = !(PIND & (1 << PD7)); // pin is 0 and when pressed=1

    if (pressed != oldState) // asks did the button change 
    {
        _delay_ms(25); // Ignore button bounce and waits for bounce to stop 
        pressed = !(PIND & (1 << PD7));//read it again 
        if (pressed != oldState) // if it still changes so its equal real change 
        {
            oldState = pressed; // saves the new state 
            if (pressed) return 1; // returns 1 only when only when the button goes down 
        }
    }
    return 0; // nothing new 
}

uint8_t LH_Pressed(void)
{
    static uint8_t oldState = 0;
    uint8_t pressed = !(PIND & (1 << PD6));

    if (pressed != oldState)
    {
        _delay_ms(25);
        pressed = !(PIND & (1 << PD6));
        if (pressed != oldState)
        {
            oldState = pressed;
            if (pressed) return 1;
        }
    }
    return 0;
}

void Alarm_Set(uint8_t on)
{
    if (on)
        PORTB |= (1 << PB5) | (1 << PB2);   // turns Both on the buzzeer and led 
    else
        PORTB &= ~((1 << PB5) | (1 << PB2)); // turns both off the buzzeer and led 
}
