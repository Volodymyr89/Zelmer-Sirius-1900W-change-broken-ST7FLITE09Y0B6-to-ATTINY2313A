#include <avr/io.h>
#include "periphery_init.h"

// init output PINs
void Output_Pins_Init(void){
	
	 DDRD |= (1 << DDD5); // PD5 as output for TMR0
	 PORTD &= ~(1 << DDD5); // set to zero
	 DDRB |= (1 << DDB4); // LED0
	 DDRB |= (1 << DDB3); // LED1
	 DDRB |= (1 << DDB2); // LED2
	 DDRB |= (1 << DDB1); // LED3
	 DDRB |= (1 << DDB0); // LED4
}

// init input PINs
void Input_Pins_Init(void){

}

// init timer
void Timer0_Init(void){
	TCCR0B |= (1<<WGM00) | (1<<WGM01) | (1<<COM0B1); // fast PWM mode, Clear OC0A on Compare Match, set OC0B at TOP
	TCCR0B |= 1<<CS01; // clkI/O/8 (From prescaler)
	OCR0B = 10;// initial duty cycle
}


