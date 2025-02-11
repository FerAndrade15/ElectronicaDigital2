/***********************
/ Universidad del Valle de Guatemala
/ IE3054: Electrónica Digital 2
/ Autor: María Andrade
/ Proyecto: Librería LCD
/ Archivo: LCD.h
/ Hardware: ATMEGA328P
/ Created: 04/02/2025 16:53:21
// **********************/

#ifndef LCD_H_
#define LCD_H_

//Libraries
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>								//Definición de tipos de datos enteros
#include <string.h>
#include <util/delay.h>							//Biblioteca para delays
#include <avr/interrupt.h>						//Biblioteca para manejo de interrupciones
#include "../Ports_Settings/PORT_SETTINGS.h"

//Prototipos de funciones
void init_8bits(PinDefinition RS, PinDefinition E, PinDefinition DISPLAY_D0, PinDefinition DISPLAY_D1, PinDefinition DISPLAY_D2, PinDefinition DISPLAY_D3, PinDefinition DISPLAY_D4, PinDefinition DISPLAY_D5, PinDefinition DISPLAY_D6, PinDefinition DISPLAY_D7); //Add ports as _PORTB#, _PORTC# or _PORTD# 
void LCD_Port_8bits(char a);
void LCD_Command_8bits(char a);
void LCD_WriteChar_8bits(char c);
void LCD_WriteString_8bits(const char *a);
void LCD_ShiftRight_8bits(void);
void LCD_ShiftLeft_8bits(void);
void LCD_SetCursor_8bits(char c, char f);

//General list of pins
PinDefinition required_pins[10];

#endif /* LCD_H_ */