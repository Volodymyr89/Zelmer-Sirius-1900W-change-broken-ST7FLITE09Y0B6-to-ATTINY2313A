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
#ifndef DELAYCNTRL
#define DELAYCNTRL 2000
#endif

#ifndef DELAYSOFTSTART
#define DELAYSOFTSTART 400
#endif

#ifndef DELAYMAX
#define DELAYMAX 9000
#endif

#ifndef DELAYMIN
#define DELAYMIN 1000
#endif

volatile bool increment_flag=false, decrement_flag=false;
volatile uint16_t delay=DELAYMAX;

void Short_delay(void){
	volatile uint16_t delay=600;
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
	OCR1A = delay;// set delay time;
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
	for(uint8_t step=0; step<CYCLENUM; step++){
			if((uint8_t)0 == Delay_ms(200)){
				delay-=DELAYSOFTSTART;
				cnt++;
				if(cnt>=5){
					Increment_decrement_Duty_Cycle(INCREMENT, true);
					cnt=0;
				}
			}
		}
	
}

void Increment_decrement_Duty_Cycle(led_status_t led_status, bool softstart){
	static uint8_t LED=0;	
	if(led_status == INCREMENT){
		LED++;
		if(LED<=4 && delay>=DELAYMIN){
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
				delay-=DELAYCNTRL; // remove for soft start due different step during soft start 
			}
		}
	}
	else if (led_status == DECREMENT){
		if(LED>=1 && delay<=DELAYMAX){
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
			delay+=DELAYCNTRL;
			LED--;
		}	
	}
}



