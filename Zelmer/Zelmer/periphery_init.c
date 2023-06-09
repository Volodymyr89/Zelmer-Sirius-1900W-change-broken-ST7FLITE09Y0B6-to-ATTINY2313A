#include <avr/io.h>
#include <avr/interrupt.h>
#include "periphery_init.h"
#include "motor_and_LED_control.h"


// init output PINs
void Output_Pins_Init(void){
// PWM output
	 DDRB |= (1 << DDB4); // as output for TMR1 PWM
	 RESET_TMR1OUT0;// set to zero
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
	//pins for filter sensors
	DDRD &= ~(1 << DDD1); // PD2 as input for ext interrupt
	PORTD |= 1 << PORTD1; // pull up
	DDRA &= ~(1 << DDA1); // PD2 as input for ext interrupt
	PORTA |= 1 << PORTA1; // pull up	
	
	//pin for ZCD
	DDRD &= ~(1 << DDD0); // PD0 as input for zero cross detector
	// Configure ext interrupt
	PCMSK2 |= 1<<PCINT11;
	GIMSK |= 1<<PCIE2;
	
	// Configure INT0 to trigger on falling edge
	MCUCR |= (1 << ISC01);
	MCUCR &= ~(1 << ISC00);
	// Configure INT1 to trigger on falling edge
	MCUCR |= (1 << ISC11);
	MCUCR &= ~(1 << ISC10);
	GIMSK |= (1<<INT0) | (1<<INT1);// enable interrupts
}

// init timers
void Timer0_Init(void){
	TCNT0 = 0;
	TCCR0B |= 1<<CS02 |1<<CS00; // clkI/O/1024 (From prescaler)

}

void Timer1_Init(void){
	 TCCR1B |= (1<<WGM12);  //CTC OCR1A, 
	 TIMSK |= (1 << OCIE1A);
}

void Timer1_Start(void){
	 TCCR1B |= 1<<CS10;// clkI/O/1 (No prescaling)
}

void Timer1_Stop(void){
	TCCR1B &= ~(1<<CS10);//clkI/O/1 (No prescaling)
}
