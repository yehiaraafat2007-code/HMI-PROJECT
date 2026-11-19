#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include <stdint.h>

void IO_Init(void);
uint8_t LL_Pressed(void);
uint8_t LH_Pressed(void);
void Alarm_Set(uint8_t alarm);

#endif