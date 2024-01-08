
#include "LCD16x2_4bit.h"
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<string.h>
#include <stdlib.h>

uint8_t hx711H=0; //Load Scale High Bits
uint16_t hx711L=0;//Load Scale Low Bits
float loadCellRead();
#define Load_data 2
#define Load_clk 3


float loadCellRead();


int main(void)
{
	float weight ;
	DDRC|=(1<<Load_clk); //Load cell clock pin
	PORTC&=~(1<<Load_clk);//Clock pin low
	DDRC|=(1<<4);
	while(1){
    weight = loadCellRead();
	char string[10];
	
	//Displaying weight
	LCD_Init();
	LCD_String_xy(1, 0, "Weight Sensor");
	dtostrf(weight, 2, 2, string);/* distance to string */
	strcat(string, " g   ");	/* Concat unit i.e.cm */
	LCD_String_xy(2, 0, "Weight = ");
	LCD_String_xy(2, 7, string);	/* Print distance */
	_delay_ms(300);
	lcd_clear();
	}
	
}


float loadCellRead(){
	hx711H=0;hx711L=0;  //clear variables
	for(uint8_t i=0;i<8;i++){  // Load cell data high 8 bits
		PORTC|=(1<<Load_clk); //Clock pin high
		_delay_us(10);
		if ((PINC&(1<<Load_data))>>Load_data)  //read data pin
		{hx711H|=(1<<(7-i));//set hx 711 varible
		}
		else
		{hx711H&=~(1<<(7-i));
		}
		PORTC&=~(1<<Load_clk); //Clock pin low
		_delay_us(5);
	}
	
	
	for(uint8_t i=0;i<16;i++){ // Load cell data low 16 bits
		PORTC|=(1<<Load_clk); //Clock pin high
		_delay_us(10);
		if ((PINC&(1<<Load_data))>>Load_data) //read data pin
		{hx711L|=(1<<(15-i));
		}
		else
		{hx711L&=~(1<<(15-i));
		}
		PORTC&=~(1<<Load_clk); //Clock pin low
		_delay_us(5);
	}
	
	hx711L=hx711L>>1; //shift bits
	
	if (hx711H&1)  //bit setup
	{hx711L|=(1<<15);
	}
	else
	{hx711L&=~(1<<15);
	}
	hx711H=hx711H>>1;
	
	return (hx711H*(65536/18029.6))+hx711L/18029.6; //load cell calibration
}
