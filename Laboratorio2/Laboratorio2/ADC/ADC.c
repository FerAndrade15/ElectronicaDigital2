/*******************************************************************
/ Universidad del Valle de Guatemala
/ IE2023: Programación de microcontroladores
/ Autor: María Andrade
/ Proyecto: Librería ADC
/ Archivo: ADC.c
/ Hardware: ATMEGA328P
/ Created: 15/04/2024 9:36:36
// ******************************************************************/

#include "ADC.h"

void adc_init(uint8_t v_reference, uint8_t adjust, uint8_t canal, uint8_t start, uint8_t enable_autotrigger, uint8_t enable_interrupt, uint8_t prescaler){
	ADMUX = 0;
	switch(v_reference){											//Reference Voltage												//AREF
		case avcc:
			ADMUX |= (1<<REFS0);
			break;													//AVcc
		case areference1:
			ADMUX |= (1<<REFS1)|(1<<REFS0);
			break;													//Internal 1.1V Reference
		default:
			break;
	}
	ADMUX |= (adjust==left)?(1<<ADLAR):0;							//Adjust Left
	ADMUX |= ((canal>=0)&&(canal<=7))?(canal):0;					//Canal Selected
	ADCSRA |= (start==1)?(1<<ADEN):0;								//Enable-Start ADC
	ADCSRA |= (enable_autotrigger==1)?(1<<ADATE):0;					//ADC Auto Trigger Enable
	ADCSRA |= (1<<ADIE);											//ISR ADC
	ADCSRA |= ((prescaler>=0)&&(prescaler<=7))?(prescaler):0;		//ADC Prescaler 128: 125kHz
}

void changechannel(uint8_t newchannel){
	ADMUX &= 0xF0;
	ADMUX |= ((newchannel>=0)&&(newchannel<=7))?(newchannel):0;					//Canal Selected
}