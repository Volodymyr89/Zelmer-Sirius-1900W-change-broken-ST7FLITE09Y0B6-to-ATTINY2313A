#include "peripheryinit.h"



// init output PINs
pin_init_status_t Output_Pins_Init(void){
	
	 DDRD |= (1 << DDD5); // PD5 as output for TMR0
	
	return OUT_INIT_OK;
}

// init input PINs
pin_init_status_t Input_Pins_Init(void){
	
	
	return IN_INIT_OK;
}
// init timer

void Timer_Init(void){
	TCCR0B |= (1<<WGM00) | (1<<WGM01) | (1<<COM0B1); // fast PWM mode, Clear OC0A on Compare Match, set OC0B at TOP
	TCCR0B |= 1<<CS01; // clkI/O/8 (From prescaler)
	OCR0B = 10;// initial duty cycle
}


