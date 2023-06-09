#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "motor_and_LED_control.h"

// set CNT0MAX 
#ifndef CNT0MAX
	#define CNT0MAX 255
#endif
#ifndef CYCLENUM
	#define CYCLENUM 20
#endif
#ifndef DUTYCNTRL
#define DUTYCNTRL 2000
#endif

#ifndef DUTYSOFTSTART
#define DUTYSOFTSTART 500
#endif

volatile bool increment_flag=false, decrement_flag=false;
volatile uint16_t dutycyle=100; 

void Short_delay(void){
	volatile uint16_t delay=1000;
	while(delay--){}
}

void Short_Pulse(void){	
SET_TMR1OUT0;
Short_delay();
RESET_TMR1OUT0;
}

ISR(INT0_vect){
	increment_flag=true;
}

ISR(INT1_vect){
	decrement_flag=true;
}

ISR(PCINT2_vect){
	OCR1A = dutycyle;// set duty cycle;
	Timer1_Start();
}

ISR(TIMER1_COMPA_vect)
{
	Timer1_Stop();
	Short_Pulse();
}

uint8_t Delay_ms(uint8_t delay){
	uint8_t return_status = 1;
	if(delay<=250){
		uint8_t counterdata= (uint8_t)(delay*0.976);
		TCNT0 = (255-counterdata);
		while(!(TIFR&(1<<TOV0))){}// wait until counter reaches 255
		TIFR |= 1<<TOV0;
		return_status= 0;
		}
	return return_status;
}


void Soft_Start_and_Run_to_Max(void){
	uint8_t cnt=0;
	SET_LED0;// turn ON LED0
	dutycyle=100;//DUTYSOFTSTART;
	/*
	for(uint8_t step=0; step<CYCLENUM; step++){
			if((uint8_t)0 == Delay_ms(200)){
				dutycyle+=DUTYSOFTSTART;
				cnt++;
				if(cnt>=5){
					Increment_decrement_Duty_Cycle(INCREMENT, true);
					cnt=0;
				}
			}
		}
		*/
}

void Increment_decrement_Duty_Cycle(led_status_t led_status, bool softstart){
	static uint8_t LED=0;
	
	if(led_status == INCREMENT){
		LED++;
		if(LED<=4){
			switch(LED){
				case 1:
				SET_LED1;
				break;
				case 2:
				SET_LED2;
				break;
				case 3:
				SET_LED3;
				break;
				case 4:
				SET_LED4;
				break;
			}
			if(softstart==false){
				dutycyle+=DUTYCNTRL; // remove for soft start due different step during soft start 
			}
		}
	}
	else if (led_status == DECREMENT){
		if(LED>=1){
			switch(LED){
				case 1:
				dutycyle-=DUTYCNTRL;
				RESET_LED1;
				break;
				case 2:
				dutycyle-=DUTYCNTRL;
				RESET_LED2;
				break;
				case 3:
				dutycyle-=DUTYCNTRL;
				RESET_LED3;
				break;
				case 4:
				dutycyle-=DUTYCNTRL;
				RESET_LED4;
				break;
			}
			LED--;
		}	
	}
}



