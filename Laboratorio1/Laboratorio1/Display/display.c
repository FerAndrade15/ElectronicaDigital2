/*
 * display.c
 *
 * Created: 28/01/2025 16:55:55
 *  Author: ferch
 */ 

#include "display.h"

uint8_t a = 0;
uint8_t b = 0;
uint8_t c = 0;
uint8_t d = 0;
uint8_t e = 0;
uint8_t f = 0;
uint8_t g = 0;


void display_settings(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7){
	a = b1;
	b = b2;
	c = b3;
	d = b4;
	e = b5;
	f = b6;
	g = b7;
}

void display(uint8_t number){
	PORTD &= 0x01;
	switch (number){
		case 0:
			PORTD |= (1<<a)|(1<<b)|(1<<c)|(1<<d)|(1<<e)|(1<<f);
		break;
		case 1:
			PORTD |= (1<<b)|(1<<c);
		break;
		case 2:
			PORTD |= (1<<a)|(1<<b)|(1<<d)|(1<<e)|(1<<g);
		break;
		case 3:
			PORTD |= (1<<a)|(1<<b)|(1<<c)|(1<<d)|(1<<g);
		break;
		case 4:
			PORTD |= (1<<b)|(1<<c)|(1<<f)|(1<<g);
		break;
		case 5:
			PORTD |= (1<<a)|(1<<c)|(1<<d)|(1<<f)|(1<<g);
		break;
		case 6:
			PORTD |= (1<<a)|(1<<c)|(1<<d)|(1<<e)|(1<<f)|(1<<g);
		break;
		case 7:
			PORTD |= (1<<a)|(1<<b)|(1<<c);
		break;
		case 8:
			PORTD |= (1<<a)|(1<<b)|(1<<c)|(1<<d)|(1<<e)|(1<<f)|(1<<g);
		break;
		case 9:
			PORTD |= (1<<a)|(1<<b)|(1<<c)|(1<<d)|(1<<f)|(1<<g);
		break;
		default:
		break;
	}
}
	