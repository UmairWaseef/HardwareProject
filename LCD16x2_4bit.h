/*
 * LCD16x2_4bit.h
 *
 * http://www.electronicwings.com
 */ 


#ifndef LCD16X2_4BIT_H_
#define LCD16X2_4BIT_H_
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define LCD_DPRT PORTA
#define LCD_DDDR DDRA
#define LCD_RS 0
#define LCD_EN 1

void LCD_Command(unsigned char cmnd);
void LCD_Char(unsigned char data);
void LCD_Init();
void LCD_String_xy(unsigned char, unsigned char, char *);
void LCD_String(char *str);
void LCD_Clear();
void lcddata(unsigned int data);




#endif /* LCD16X2_4BIT_H_ */