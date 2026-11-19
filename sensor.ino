#include <stdint.h>
#include"adc.h"
#include "sensor.h"


uint16_t Sensor_ReadTemperature(void)//this function reads and calculates the lm35 temperature
{
  uint32_t total=0;//creates a variable to store the total adc reading 

  for (uint8_t i=0; i<8; i++)//repats 8 times to get 8 adc readings
  {
      total +=ADC_ReadChannel(0);//reads the sensor from a0 and adds each reading
  }

  


 //convert the adc readings to temeparture , lm35 gives about 10mV for every 1 degreee c 
uint32_t temperature=(total*500UL +4092UL)/8184UL;
//500 used to convert adc value into degrees 
//4092 for round the result 
//8184 comes from 8 readings multiplied by 1023
if (temperature >150)//limit max to 150 c 
{
 temperature=150;

}
return (uint16_t)temperature;//returns this to main

}
