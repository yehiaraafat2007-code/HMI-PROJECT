#ifndef LCD_H
#define LCD_H

#include <stdint.h>

void LCD_Init(void);
void LCD_Command(uint8_t command);
void LCD_Char(char character);
void LCD_String(const char *text);
void LCD_Number(uint16_t number);

#endif