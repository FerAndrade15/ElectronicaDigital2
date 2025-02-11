/*******************************************************************
/ Universidad del Valle de Guatemala
/ IE3054: Electrónica Digital 2
/ Autor: María Andrade
/ Proyecto: Laboratorio 2
/ Archivo: main.c
/ Hardware: ATMEGA328P
/ Created: 2/4/2025 4:47:18 PM
// ******************************************************************/

#include "UART/UART.h"
#include "LCD/LCD.h"
#include "ADC/ADC.h"
#define startposition 13

// ADC Variables
uint8_t selectedadc = ADC3;
double pot1value;
double pot2value;
char potentiometer_value1[100];
char potentiometer_value2[100];
char * send_string1;
char * send_string2;

// UART Variables
volatile char bufferRX; // Variable for reading or manipulating serial communication

// Counter -- Sensor 3
float counter = 0;
uint8_t change=0;
char counter_value[100];
char * counter_reg;
uint8_t position;
uint8_t sizetest;
const char * empty = "    ";

int main(void){
	cli(); // Disable global interrupts during setup
	// LCD Settings
	init_8bits(_PortD2, _PortD4, _PortD5, _PortD6, _PortD7, _PortB0, _PortB1, _PortB2, _PortB3, _PortB4); // Set Pins and Start LCD
	LCD_SetCursor_8bits(2,1);			// Set cursor for first title
	LCD_WriteString_8bits("S1:");		// First Sensor Title
	LCD_SetCursor_8bits(8,1);			// Set cursor for second title
	LCD_WriteString_8bits("S2:");		// Second Sensor Title
	LCD_SetCursor_8bits(14,1);			// Set cursor for third title
	LCD_WriteString_8bits("S3:");		// Third Sensor Title
	
	// Display the initial counter value
	sprintf(counter_value, "%.0f ", counter);	// Convert float to char
	sizetest = strlen(counter_value)-1;
	counter_reg = counter_value;
	position = (sizetest==1)?(startposition+2):((sizetest>=4)?(startposition):(startposition+1));
	LCD_SetCursor_8bits(position,2);
	LCD_WriteString_8bits(counter_reg);

	// UART Settings
	initUART0(Asynchronous_FM, Disable, _8bit, Disable, BR9600);

	// ADC Settings	
	adc_init(avcc, right, selectedadc, enable, disable, enable, adcprescaler128);	// Start and configure ADC
	ADCSRA |= (1<<ADSC);															// Start ADC conversion
	sei(); // Enable global interrupts
	
	while(1){
	}
}

// ADC Interrupt Service Routine -----------------------------------------------------------------------------------------
ISR(ADC_vect){
	switch(selectedadc){
		case ADC3:
			// Read ADC value and convert to voltage
			pot1value = (double)ADC * 5.0 / 1023.0;
			sprintf(potentiometer_value1, "%.2fV", pot1value); // Convert float to string
			send_string1 = potentiometer_value1;
			
			// Display value on LCD
			LCD_SetCursor_8bits(1,2);
			LCD_WriteString_8bits(send_string1);
			
			// Switch to next ADC channel
			selectedadc = ADC5;
			changechannel(selectedadc);
			
			// Restart ADC conversion
			ADCSRA |= (1<<ADSC);
			break;
		case ADC5:
			// Read ADC value and convert to voltage
			pot2value = (double)ADC * 5.0 / 1023.0;
			sprintf(potentiometer_value2, "%.2fV ", pot2value); // Convert float to string
			send_string2 = potentiometer_value2;
			
			// Display value on LCD
			LCD_SetCursor_8bits(7,2);
			LCD_WriteString_8bits(send_string2);
			
			// Switch back to the first ADC channel
			selectedadc = ADC3;
			changechannel(selectedadc);
			
			// Restart ADC conversion
			ADCSRA |= (1<<ADSC);
			break;
		default:
			break;
	}
}

// UART Receive Interrupt Service Routine -----------------------------------------------------------------------------------------
ISR(USART_RX_vect){
	bufferRX = UDR0; // Read received character from UART buffer
	while(!(UCSR0A & (1<<UDRE0))); // Wait until the transmit buffer is empty
	char temp = bufferRX;
	change = 0;

	// Process received character
	switch(temp){
		case '+':
			counter++; // Increment counter
			break;
		case '-':
			counter--; // Decrement counter
			break;
		default:
			change = 1;
			break;
	}

	// If counter was changed, update LCD display
	if (change != 1){
		LCD_SetCursor_8bits(startposition,2);
		LCD_WriteString_8bits(empty); // Clear previous counter value
		
		sprintf(counter_value, "%.0f ", counter); // Convert float to string
		sizetest = strlen(counter_value)-1;
		counter_reg = counter_value;
		position = (sizetest==1)?(startposition+2):((sizetest>=4)?(startposition):(startposition+1));
		LCD_SetCursor_8bits(position,2);
		LCD_WriteString_8bits(counter_reg);
	}
}
