/*******************************************************************
/ Universidad del Valle de Guatemala
/ IE2023: Programación de microcontroladores
/ Autor: María Andrade
/ Proyecto: Librería ADC
/ Archivo: ADC.c
/ Hardware: ATMEGA328P
/ Created: 15/04/2024 9:36:36
// ******************************************************************/

#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define enable	1
#define disable 0
#define areference	0
#define avcc		1
#define areference1 2
#define left		1
#define right		0
#define ADC0		0
#define ADC1		1
#define ADC2		2
#define ADC3		3
#define ADC4		4
#define ADC5		5
#define ADC6		6
#define ADC7		7
#define adcprescaler1		0
#define adcprescaler2		1
#define adcprescaler4		2
#define adcprescaler8		3
#define adcprescaler16		4
#define adcprescaler32		5
#define adcprescaler64		6
#define adcprescaler128		7

void adc_init(uint8_t v_reference, uint8_t adjust, uint8_t canal, uint8_t start, uint8_t enable_autotrigger, uint8_t enable_interrupt, uint8_t prescaler);
void changechannel(uint8_t newchannel);

#endif /* ADC_H_ */