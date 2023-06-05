#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "motor_and_LED_control.h"

// set CNT0MAX 
#ifndef CNT0MAX
	#define CNT0MAX 255
#endif
#ifndef CYCLENUM
	#define CYCLENUM 5
#endif

volatile bool increment_flag=false, decrement_flag=false;

ISR(INT0_vect){
	increment_flag=true;
}

ISR(INT1_vect){
	decrement_flag=true;
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
	uint8_t duty_cycle = 10;
	SET_LED0;// turn ON LED0
	for(uint8_t step=0; step<CYCLENUM; step++){
			if((uint8_t)0 == Delay_ms(200)){
				duty_cycle+=10;
				Increment_decrement_Duty_Cycle(INCREMENT);
			}
	}
}

void Increment_decrement_Duty_Cycle(led_status_t led_status){
	static uint8_t LED=1;
	
	if(led_status == INCREMENT){
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
			LED++;
		}
	}
	else if (led_status == DECREMENT){
		if(LED>=1){
			switch(LED){
				case 1:
				RESET_LED1;
				break;
				case 2:
				RESET_LED2;
				break;
				case 3:
				RESET_LED3;
				break;
				case 4:
				RESET_LED4;
				break;
			}
			LED--;
		}	
	}
}



