/***********************
/ Universidad del Valle de Guatemala
/ IE3054: Electrónica Digital 2
/ Autor: María Andrade
/ Proyecto: Librería LCD
/ Archivo: LCD.c
/ Hardware: ATMEGA328P
/ Created: 04/02/2025 16:53:10
// **********************/

// Header with the necessary libraries
#include "LCD.h"

void init_8bits(PinDefinition RS, PinDefinition E, PinDefinition DISPLAY_D0, PinDefinition DISPLAY_D1, PinDefinition DISPLAY_D2, PinDefinition DISPLAY_D3, PinDefinition DISPLAY_D4, PinDefinition DISPLAY_D5, PinDefinition DISPLAY_D6, PinDefinition DISPLAY_D7){
	//Save pin configurations
	PinDefinition temporal[] = {RS, E, DISPLAY_D0, DISPLAY_D1, DISPLAY_D2, DISPLAY_D3, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7};
	memcpy(required_pins, temporal, sizeof(temporal));
	for (int i = 0; i < sizeof(temporal) / sizeof(PinDefinition); i++) {
		PIN_OUTPUT(temporal[i]);        // Set the pin as output
	}
	//Cleaning Registers
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	_delay_ms(10);
	
	LCD_Command_8bits(0b10000000);
	//Function Set
	LCD_Command_8bits(0x38);
	
	//Display
	LCD_Command_8bits(0x0C);
	
	//Entry Mode
	LCD_Command_8bits(0x06);
	
	//Clear display
	LCD_Command_8bits(0x01);
}

void LCD_Port_8bits(char a){
	if(a&0b00000001){	//D0 = 1;
		PIN_HIGH(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 8]);
	}
	else {
		PIN_LOW(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 8]);
	}
	if(a&0b00000010){	//D1 = 2;
		PIN_HIGH(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 7]);
	}
	else {
		PIN_LOW(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 7]);
	}
	if(a&0b00000100){	//D2 = 3;
		PIN_HIGH(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 6]);
	}
	else {
		PIN_LOW(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 6]);
	}
	if(a&0b00001000){	//D3 = 4;
		PIN_HIGH(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 5]);
	}
	else {
		PIN_LOW(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 5]);
	}
	if(a&0b00010000){	//D4 = 5;
		PIN_HIGH(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 4]);
	}
	else {
		PIN_LOW(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 4]);
	}
	if(a&0b00100000){	//D5 = 6;
		PIN_HIGH(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 3]);
	}
	else {
		PIN_LOW(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 3]);
	}
	if(a&0b01000000){	//D6 = 7;
		PIN_HIGH(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 2]);
	}
	else {
		PIN_LOW(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 2]);
	}
	if(a&0b10000000){	//D7 = 8;
		PIN_HIGH(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 1]);
	}
	else {
		PIN_LOW(required_pins[sizeof(required_pins)/sizeof(required_pins[0]) - 1]);
	}
}
void LCD_Command_8bits(char a){
	PIN_LOW(required_pins[0]);
	LCD_Port_8bits(a);
	PIN_HIGH(required_pins[1]);
	_delay_ms(4);
	PIN_LOW(required_pins[1]);
}
void LCD_WriteChar_8bits(char c){
	PIN_HIGH(required_pins[0]);
	LCD_Port_8bits(c);
	PIN_HIGH(required_pins[1]);
	_delay_ms(4);
	PIN_LOW(required_pins[1]);
}
void LCD_WriteString_8bits(const char *a){
	int i;
	for (i=0; a[i] != '\0'; i++)
	LCD_WriteChar_8bits(a[i]);
}
void LCD_ShiftRight_8bits(void){
	LCD_Command_8bits(0x1C);
}

void LCD_ShiftLeft_8bits(void){
	LCD_Command_8bits(0x18);
}

void LCD_SetCursor_8bits(char c, char f){
	char temp;
	if (f==1){
		temp = 0x80 + c -1;
		LCD_Command_8bits(temp);		
	}
	else if (f==2){
		temp = 0xC0 + c -1;
		LCD_Command_8bits(temp);
	}
}