/*******************************************************************
/ Universidad del Valle de Guatemala
/ IE2023: Programación de microcontroladores
/ Autor: María Andrade
/ Proyecto: Librería UART
/ Archivo: UART.c
/ Hardware: ATMEGA328P
/ Created: 23/04/2024 6:07:16
// ******************************************************************/

// Headers with libraries
#include "UART.h"

//Variables
uint16_t UBRRValue[15] = {832, 416, 207, 138, 103, 68, 51, 34, 25, 16, 8, 7, 3, 1, 0};

void initUART0(uint8_t UARTmode, uint8_t ParityMode, uint8_t DataBits, uint8_t ClkPolarity, uint16_t BaudRate){
	DDRD &= ~(1<<DDD0);									//RX input
	DDRD |= (1<<DDD1);									//TX output
	//USART Control and Status Register A
	UCSR0A = 0;											//Clear	
	UCSR0A |= (UARTmode==Asynchronous_FM)?2:0;			//Fastmode U2X0 = 1 for Asynchronous Mode
	//USART Control and Status Register B
	UCSR0B = 0;											//Clear
	UCSR0B |= (1<<RXCIE0);								//Enable ISR RX Interrupt
	UCSR0B |= (1<<RXEN0);								//Enable (RX) Receiver
	UCSR0B |= (1<<TXEN0);								//Enable (TX) Transmitter
	UCSR0B |= (DataBits&0x04);							//Character Size MSB
	//USART Control and Status Register C	
	UCSR0C = 0;											//Clear
	UCSR0C |= (UARTmode == Synchronous)?(0x40):(0);		//USART Mode Select
	UCSR0C |= (ParityMode<<4);							//Parity Mode
	UCSR0C |= (DataBits<<1);							//Character Size LS2'B
	UCSR0C |= (UARTmode==Synchronous)?(0):(ClkPolarity);//Clock Polarity @ Synchronous Mode	
	//Baud Rate Registers
	if(UARTmode==Asynchronous_NM){
		UBRR0 = UBRRValue[BaudRate+1];
	}else if(UARTmode==Asynchronous_FM){
		UBRR0 = UBRRValue[BaudRate];
	}
}
void writeUART(char character){
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0 = character;
}

void writeTextUART(const char* text){
	for (uint8_t i=0; text[i]!='\0'; i++){
		while(!(UCSR0A&(1<<UDRE0)));
		UDR0 = text[i];
	}
}