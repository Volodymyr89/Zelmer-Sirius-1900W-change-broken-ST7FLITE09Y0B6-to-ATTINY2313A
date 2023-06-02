#include <avr/io.h>
#include <avr/interrupt.h>
#include "periphery_init.h"

ISR(INT0_vect){
	
	
	EIFR |= 1<<INTF0;// clear flag
}

ISR(INT1_vect){
	
	
	EIFR |= 1<<INTF1;// clear flag
}

// init output PINs
void Output_Pins_Init(void){
	// set of LEDs indicating power
	 DDRD |= (1 << DDD5); // PD5 as output for TMR0
	 PORTD &= ~(1 << DDD5); // set to zero
	 DDRB |= (1 << DDB4); // LED0
	 PORTB &= ~(1 << DDB4); // set to zero
	 DDRB |= (1 << DDB3); // LED1
	 PORTB &= ~(1 << DDB3); // set to zero
	 DDRB |= (1 << DDB2); // LED2
	 PORTB &= ~(1 << DDB2); // set to zero
	 DDRB |= (1 << DDB1); // LED3
	 PORTB &= ~(1 << DDB1); // set to zero
	 DDRB |= (1 << DDB0); // LED4
	 PORTB &= ~(1 << DDB0); // set to zero
	 //another set of LEDs indicating filters statuses
	 DDRD |= (1 << DDD6); // LED5
	 PORTD &= ~(1 << DDD6); // set to zero
	 DDRD |= (1 << DDD4); // LED6
	 PORTD &= ~(1 << DDD4); // set to zero
}

// init input PINs
void Input_Pins_Init(void){
	DDRD &= ~(1 << DDD2); // PD2 as input for ext interrupt
	PORTD |= 1 << DDD2; // pull up
	DDRD &= ~(1 << DDD3); // PD3 as input for ext interrupt
	PORTD |= 1 << DDD3; // pull up
	
	MCUCR &= ~(1<<ISC10) & (1<<ISC11) & (1<<ISC01) & (1<<ISC00); // The low level of INT0 and INT1 generates an interrupt request.
	GIMSK |= (1<<INT0) | (1<<INT1);// enable interrupts
	sei();//enable global interrupts
}

// init timer
void Timer0_Init(void){
	TCCR0B |= (1<<WGM00) | (1<<WGM01) | (1<<COM0B1); // fast PWM mode, Clear OC0A on Compare Match, set OC0B at TOP
	TCCR0B |= 1<<CS01; // clkI/O/8 (From prescaler)
	OCR0B = 10;// initial duty cycle
}


