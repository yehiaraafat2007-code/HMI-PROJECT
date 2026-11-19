#define F_CPU 16000000UL //sets the arduino clock speed to 16 Mhz
#include <util/delay.h>//allows us to use delay functions like delay 
#include<stdint.h>//makes us use the uint8_t and uint16_t
#include"lcd.h"//contains the lcd functions
#include"adc.h"//contains the adc functions
#include"sensor.h"//contains the lm35 sensor functions
#include"inputoutput.h"//contains the button , led and buzzer function

int main (void)//here this where the program starts 
{
 uint8_t lowerLimit=20;//sets the starting temp limit to 20
 uint8_t upperLimit=35;//sets the higher temperature limit to 35
//here means start all components 
 IO_Init();//sets up the buttons , led , buzzer pins
 ADC_Init();//starts the to read the lm35
 LCD_Init();//start in 4 bit mode 
//main loop runs for ever
 while(1)
 {
  //checks lower limit button
   if(LL_Pressed()&& lowerLimit +1<upperLimit)//checks if the lower limit button is pressed
   {                                          //also makes sure LL stays below LH
      lowerLimit++;//incraeses the lower limit by 1 C
   }
//here check highr limit button
   if (LH_Pressed()&& upperLimit<99)//also make sure it doesnt go above 99
    {  
      upperLimit++;//incrase the higher limit by 1C
    }
//read temperature from lm35
   uint16_t temperature= Sensor_ReadTemperature();//read temp from lm35,and stores the temp in the variable temperature 
   //check temperature limits
   uint8_t alarm=(temperature< lowerLimit||//sees if temp  is below LL or above LH,|| means or
                   temperature>upperLimit);//alarm becomes 1 if the temperature is outside the limits ,0 if the temeparture is inside limits
  
  Alarm_Set(alarm);//led and buzzer turn on/off together,1 means both on,0 means both off
//display temperature on the first lcd row
  LCD_Command(0x80);//row 1 
  LCD_String("                ");//clear row
  LCD_Command(0x80);//moves the cursor bcak to the start of row 1
  LCD_String("Temp:");//write temp on lcd 
  LCD_Number(temperature);//display the measured temperature 
  LCD_String("C ");//C for celsius 
  LCD_String(alarm ?"NOK":"OK");//if alarm 1 =1,displays NOK ,if 0 displays OK

  LCD_Command(0xC0);//row 2
  LCD_String("                ");//clear row 2 
  LCD_Command(0xC0);//moves the cursor  to the start of row 2 
  LCD_String("LL:");//clear row 2
  LCD_Number(lowerLimit);//display the current lower temperature 
  LCD_String("  LH:");
  LCD_Number(upperLimit);//wait 100 milliseconds 

  _delay_ms(100);
  

 }//ends the while loop



}//here this means end the main function