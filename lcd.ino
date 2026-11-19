#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
// Set the Arduino clock speed and add the libraries needed to control the registers, use delays,
// and operate the LCD.

static void LCD_Nibble(uint8_t n)
{
    
    PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5));
//the four LCD data pins are cleared before new data is sent
    if (n & 1) PORTD |= (1 << PD5);
    if (n & 2) PORTD |= (1 << PD4);
    if (n & 4) PORTD |= (1 << PD3);
    if (n & 8) PORTD |= (1 << PD2);
//Enable pin (E) goes HIGH and then LOW. This sends the data to the LCD.
    _delay_us(1);
    PORTB |= (1 << PB3);     // E = 1
    _delay_us(2);
    PORTB &= ~(1 << PB3);    // E = 0
    _delay_us(100);
}

static void LCD_Send(uint8_t value, uint8_t text)
//The RS pin determines whether the LCD receives a character to display or a command to execute.
{
    if (text)
        PORTB |= (1 << PB4);   
    else
        PORTB &= ~(1 << PB4);  
//The LCD uses 4-bit communication, so each byte is divided into two smaller parts.
    LCD_Nibble(value >> 4);
    LCD_Nibble(value & 15);
}
// Sends a command or character to the LCD depending on the selected mode.
void LCD_Command(uint8_t command)
{
    LCD_Send(command, 0);
    if (command == 1 || command == 2)
        _delay_ms(2);
}
// It sends the character to the LCD for display rather than sending a command.
void LCD_Char(char character)
{
    LCD_Send((uint8_t)character, 1);
}
//The while loop goes through the text one character at a time until it reaches the end of the string ('\0').
void LCD_String(const char *text)
{
    while (*text)
        LCD_Char(*text++);
}
//It separates hundreds, tens and units.
void LCD_Number(uint16_t number)
{
    if (number >= 100) LCD_Char('0' + (number / 100) % 10);
    if (number >= 10)  LCD_Char('0' + (number / 10) % 10);
    LCD_Char('0' + number % 10);
}
//These lines configure the LCD pins as outputs and set their initial LOW state.
void LCD_Init(void)
{
    DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);
    DDRB |= (1 << PB3) | (1 << PB4);
    PORTB &= ~((1 << PB3) | (1 << PB4));
//This is the LCD startup sequence. It prepares the LCD to communicate using 4-bit mode.
    _delay_ms(50);
    LCD_Nibble(3);
    _delay_ms(5);
    LCD_Nibble(3);
    _delay_us(200);
    LCD_Nibble(3);
    _delay_us(200);
    LCD_Nibble(2);
//These commands configure the LCD display, cursor behaviour and clear the screen.
    LCD_Command(0x28);  
    LCD_Command(0x0C);  
    LCD_Command(0x06);  
    LCD_Command(0x01);  
}
