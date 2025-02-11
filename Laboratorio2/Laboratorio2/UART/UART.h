/*******************************************************************
/ Universidad del Valle de Guatemala
/ IE2023: Programación de microcontroladores
/ Autor: María Andrade
/ Proyecto: Librería UART
/ Archivo: UART.h
/ Hardware: ATMEGA328P
/ Created: 23/04/2024 6:07:16
// ******************************************************************/
#ifndef UART_H_
#define UART_H_

//Libraries
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

//Constants
#define _5bit			0
#define _6bit			1
#define _7bit			2
#define _8bit			3
#define _9bit			7
#define Enable			1
#define Disable			0
#define Enable_EP		2
#define Disable_EP		3
#define Synchronous		0
#define Asynchronous_NM	1
#define Asynchronous_FM	2
#define	BR2400			0
#define	BR4800			1
#define	BR9600			2
#define	BR14400			3
#define	BR19200			4
#define	BR28800			5
#define	BR38400			6
#define	BR57600			7
#define	BR76800			8
#define	BR115200		9
#define	BR230400		10
#define	BR250000		11
#define	BR0_5M			12
#define	BR1M			13
#define TX_Rising		0
#define TX_Falling		1
#define Buffer_Size		128


//Mode: Asynchronous or Synchronous;  ParityMode: Enable, Disable, Enable_EP, Disable_EP; DataBits: _#bit; BaudRate: BR###
void initUART0(uint8_t UARTmode, uint8_t ParityMode, uint8_t DataBits, uint8_t ClkPolarity, uint16_t BaudRate);	
void writeUART(char character);				//Character
void writeTextUART(const char* text);				//String

#endif /* UART_H_ */