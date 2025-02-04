/***********************
/ Universidad del Valle de Guatemala
/ IE3054: Electrónica Digital 2
/ Autor: María Andrade
/ Proyecto: Laboratorio 1
/ Archivo: main.c
/ Hardware: ATMEGA328P
/ Created: 1/28/2025 4:18:37 PM
// **********************/

// Librerías necesarias para el funcionamiento del microcontrolador y el display
#define F_CPU 16000000  // Frecuencia del reloj del microcontrolador
#include <avr/io.h>      // Biblioteca para manipulación de pines y registros
#include <stdint.h>      // Definición de tipos de datos enteros
#include <util/delay.h>  // Biblioteca para retardos
#include <avr/interrupt.h> // Biblioteca para manejo de interrupciones
#include "Display/display.h" // Librería externa para manejo del display

// Definición de estados para las posiciones de los jugadores
#define s1 0x01
#define s2 0x02
#define s3 0x04
#define s4 0x08

// Prototipos de funciones para configuración y control del juego
void io_setup(void);  // Configuración de pines de entrada y salida
void pcint_int(void); // Configuración de interrupciones por cambio de estado
void timer0_init(void); // Configuración del temporizador

// Variables globales para el control del juego
uint8_t counter = 0;       // Contador de tiempo
uint8_t manualdelay1 = 0;  // Retardo manual para el jugador 1
uint8_t manualdelay2 = 0;  // Retardo manual para el jugador 2
uint8_t state = 0;         // Estado del juego
uint8_t timercounter = 0;  // Contador del temporizador
uint8_t winner = 0;        // Variable que almacena al ganador
uint8_t delay = 0;         // Retardo auxiliar

int main(void){
	cli(); // Deshabilita interrupciones globales mientras se configura el sistema
	io_setup(); // Configura pines de entrada y salida
	pcint_int(); // Configura interrupciones por cambio de estado
	timer0_init(); // Configura el temporizador
	display_settings(3, 2, 6, 5, 4, 7, 1); // Inicializa el display de 7 segmentos
	sei(); // Habilita interrupciones globales

	while(1){
		if (state == 1) {
			display(counter); // Muestra el contador en el display
			state = 0; // Reinicia el estado
			if (counter == 0) {
				// Habilita interrupciones para botones de inicio y avance de jugadores
				PCMSK1 = (1<<PCINT12); // Habilita interrupción en PC4 y PC5
				PCMSK0 = (1<<PCINT0);  // Habilita interrupción en PB0
			}
		}
		// Determina si hay un ganador y enciende los LEDs correspondientes
		if (winner == 1) {
			PORTC |= 0x0F; // Enciende LEDs del jugador 1
			PORTB &= 0xE1; // Apaga LEDs del jugador 2
			display(1); // Muestra "1" en el display
		}
		if (winner == 2) {
			PORTC &= ~0x0F; // Apaga LEDs del jugador 1
			PORTB |= ~0xE1; // Enciende LEDs del jugador 2
			display(2); // Muestra "2" en el display
		}
	}
}

// Configuración de pines de entrada y salida
void io_setup(void){
	UCSR0B = 0; // Deshabilita comunicación UART
	DDRB = 0x1E; // Configura botones como entrada y LEDs como salida en PORTB
	PORTB = 0x01; // Habilita resistencias pull-up para los botones
	DDRC = 0x0F; // Configura botones como entrada y LEDs como salida en PORTC
	PORTC = 0x30; // Habilita resistencias pull-up en PORTC
	DDRD = 0xFE; // Configura el display de 7 segmentos como salida
	PORTD = 0;   // Reinicia el display
}

// Configuración de interrupciones por cambio de estado en los botones
void pcint_int(void){
	PCICR = (1<<PCIE1)|(1<<PCIE0); // Habilita interrupciones en PORTB y PORTC
	PCMSK1 = (1<<PCINT13); // Habilita interrupción en PC4 y PC5
}

// Configuración del temporizador para control del tiempo de carrera
void timer0_init(void){
	TIMSK0 = 0;
	TIMSK0 |= (1<<OCIE0A); // Habilita interrupción por comparación en Timer0
	TCCR0A = 0;
	TCCR0A |= (1<<OCIE0A); // Configura Timer0 en modo CTC
	OCR0A = 156; // Valor de comparación para interrupción periódica
	TCCR0B = 0;
	TCCR0B |= (1<<CS02)|(1<<CS00); // Configura prescaler en 1024
}

// Interrupción por cambio de estado en los botones de los jugadores
ISR(PCINT0_vect){
	// Avance del jugador 1
	if ((PINB & (1<<0)) == 0){
		manualdelay1 = 1;
		_delay_ms(15);
	}
	if ((manualdelay1 == 1) && ((PINB & (1<<0)) != 0)) {
		switch(PORTC & 0x0F) {
			case 0:
			PORTC |= (1<<0);
			break;
			case 0x01:
			PORTC &= 0xF0;
			PORTC |= (1<<1);
			break;
			case 0x02:
			PORTC &= 0xF0;
			PORTC |= (1<<2);
			break;
			case 0x04:
			PORTC &= 0xF0;
			PORTC |= (1<<3);
			winner = 1;
			break;
			default:
			break;
		}
		manualdelay1 = 0;
	}
}

ISR(PCINT1_vect){
	// Inicio de la carrera
	if ((PINC & (1<<5)) == 0){
		state = 1;
		timercounter = 0;
		counter = 5;
	}
	// Avance del jugador 2
	if ((PINC & (1<<4)) == 0){
		manualdelay2 = 1;
		_delay_ms(15);
	}
	if ((manualdelay2 == 1) && ((PINC & (1<<4)) != 0)) {
		switch(PORTB & 0x1E) {
			case 0:
			PORTB |= (1<<1);
			break;
			case 0x02:
			PORTB &= 0xE1;
			PORTB |= (1<<2);
			break;
			case 0x04:
			PORTB &= 0xE1;
			PORTB |= (1<<3);
			break;
			case 0x08:
			PORTB &= 0xE1;
			PORTB |= (1<<4);
			winner = 2;
			break;
			default:
			break;
		}
		manualdelay2 = 0;
	}
}

// Interrupción del temporizador para decrementar el contador
ISR(TIMER0_COMPA_vect){
	if (timercounter < 100){
		timercounter++;
		state = 2;
		} else {
		if (counter > 0){
			counter--;
			state = 1;
			timercounter = 0;
		} else {
			state = 3;
		}
	}
}

