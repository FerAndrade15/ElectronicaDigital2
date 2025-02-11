/*******************************************************************
/ Universidad del Valle de Guatemala
/ IE3054: Electrónica Digital 2
/ Autor: María Andrade
/ Proyecto: Laboratorio 2
/ Archivo: PORT_SETTINGS.h
/ Hardware: ATMEGA328P
/ Created: 09/02/2025 18:37:20
// ******************************************************************/

#ifndef PORT_SETTINGS_H_
#define PORT_SETTINGS_H_

// Libraries
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

//Structure to create the tuples of the ports and pins
typedef struct {
	char port;
	int pin;
} PinDefinition;

// Macro to set the pin as output by using the structure PinDefinition
#define PIN_OUTPUT(port_pin) do { \
	if (port_pin.port == 'B') DDRB |= (1 << port_pin.pin); \
	else if (port_pin.port == 'C') 	DDRC |= (1 << port_pin.pin); \
	else if (port_pin.port == 'D') 	DDRD |= (1 << port_pin.pin);  \
} while(0)

// Macro to set the pin
#define PIN_HIGH(port_pin) do { \
	if (port_pin.port == 'B') PORTB |= (1 << port_pin.pin); \
	else if (port_pin.port == 'C') 	PORTC |= (1 << port_pin.pin); \
	else if (port_pin.port == 'D') 	PORTD |= (1 << port_pin.pin);  \
} while(0)

// Macro to clear the pin
#define PIN_LOW(port_pin) do { \
	if (port_pin.port == 'B') PORTB &= ~(1 << port_pin.pin); \
	else if (port_pin.port == 'C') 	PORTC &= ~(1 << port_pin.pin); \
	else if (port_pin.port == 'D') 	PORTD &= ~(1 << port_pin.pin);  \
} while(0)

// Pin Definitions
extern PinDefinition _PortB0; // D8
extern PinDefinition _PortB1; // D9
extern PinDefinition _PortB2; // D10
extern PinDefinition _PortB3; // D11
extern PinDefinition _PortB4; // D12
extern PinDefinition _PortB5; // D13

extern PinDefinition _PortC0; // A0
extern PinDefinition _PortC1; // A1
extern PinDefinition _PortC2; // A2
extern PinDefinition _PortC3; // A3
extern PinDefinition _PortC4; // A4
extern PinDefinition _PortC5; // A5

extern PinDefinition _PortD0; // D0
extern PinDefinition _PortD1; // D1
extern PinDefinition _PortD2; // D2
extern PinDefinition _PortD3; // D3
extern PinDefinition _PortD4; // D4
extern PinDefinition _PortD5; // D5
extern PinDefinition _PortD6; // D6
extern PinDefinition _PortD7; // D7

#endif /* PORT_SETTINGS_H_ */
