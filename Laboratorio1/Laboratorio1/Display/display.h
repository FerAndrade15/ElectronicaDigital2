/*
 * headers_display.h
 *
 * Created: 28/01/2025 16:56:12
 *  Author: ferch
 */ 

//Libraries --------------------------------------------------------//
#define F_CPU 16000000
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef DISPLAY_H_
#define DISPLAY_H_

void display_settings(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7);
void display(uint8_t number);

#endif /* HEADERS_DISPLAY_H_ */