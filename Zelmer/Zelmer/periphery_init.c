#include <avr/io.h>
#include <avr/interrupt.h>
#include "periphery_init.h"
#include "motor_and_LED_control.h"


// init output PINs
void Output_Pins_Init(void){
// PWM output
	 DDRB |= (1 << DDB4); // as output for TMR1 PWM
	   // set to zero
// set LEDs indicating power
	DDRD |= (1 << DDD5); // LED0
	  RESET_LED4;// set to zero
	 DDRB |= (1 << DDB3); // LED1
	  RESET_LED3;// set to zero
	 DDRB |= (1 << DDB2); // LED2
	  RESET_LED2;// set to zero
	 DDRB |= (1 << DDB1); // LED3
	  RESET_LED1;// set to zero
	 DDRB |= (1 << DDB0); // LED4
	  RESET_LED0;// set to zero
	 //another set of LEDs indicating filters statuses
	 DDRD |= (1 << DDD6); // LED5
	  RESET_LED5;// set to zero
	 DDRD |= (1 << DDD4); // LED6
	  RESET_LED6;// set to zero
}

// init input PINs
void Input_Pins_Init(void){
	//pins for min/max buttons
	DDRD &= ~(1 << DDD2); // PD2 as input for ext interrupt
	PORTD |= 1 << PORTD2; // pull up
	DDRD &= ~(1 << DDD3); // PD3 as input for ext interrupt
	PORTD |= 1 << PORTD3; // pull up
	
	// Configure INT0 to trigger on falling edge
	MCUCR |= (1 << ISC01);
	MCUCR &= ~(1 << ISC00);
	
	// Configure INT1 to trigger on falling edge
	MCUCR |= (1 << ISC11);
	MCUCR &= ~(1 << ISC10);
	GIMSK |= (1<<INT0) | (1<<INT1);// enable interrupts
	sei();//enable global interrupts
}

// init timers
void Timer0_Init(void){
	TCNT0 = 0;
	TCCR0B |= 1<<CS02 |1<<CS00; // clkI/O/1024 (From prescaler)

}

void Timer1_Init(void){
	TCCR1A |= (1<<WGM11) | (1<<WGM10) | (1<<COM1B1); // fast PWM mode, Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at TOP
	TCCR1B |= (1<<WGM12) | (1<<CS11) | (1<<CS10); //clkI/O/64 (From prescaler)
	OCR1BH = 10;// initial duty cycle
	OCR1BLa = 10;
}
