#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "motor_and_LED_control.h"


volatile bool increment_flag=false, decrement_flag=false;
uint16_t TRIACdelay;
volatile bool SoftStart=false, set_power_max=false;
uint8_t LED=0;



 void Short_Pulse(void){	
	volatile uint16_t delay=10;
	RESET_TMR1OUT0;
	while(delay--){}
	SET_TMR1OUT0;
}

ISR(PCINT2_vect){
	if(SoftStart==true){
		OCR1A = TRIACdelay;// set delay time;
	}
	else if (increment_flag==true){
			if(OCR1A>TRIACdelay){
				OCR1A -=DELAYCNTRLSOFTTRANSITION;
			}
			else{
				increment_flag=false;
			}
	}
	else if (decrement_flag==true){
			 if(OCR1A<TRIACdelay){
				OCR1A +=DELAYCNTRLSOFTTRANSITION;
			}
			else{
				decrement_flag=false;
			}
	 }
	 if(OCR1A<DELAYMIN){
		 set_power_max=true;
	 }
	 else{
		 set_power_max=false;
	 }
	Timer1_Start();
}

ISR(TIMER1_COMPA_vect)
{
	Timer1_Stop();
	if(set_power_max==true){
		RESET_TMR1OUT0; // set max power
	}
	else{
		Short_Pulse();
	}
}

uint8_t Delay_ms(uint8_t delay, uint8_t reset){
	uint8_t return_status = 1;
	if(delay<=250){
		uint8_t counterdata= (uint8_t)(delay*0.976);
		TCNT0 = (255-counterdata);
		while(!(TIFR&(1<<TOV0))){
				if(reset==(uint8_t)1)
					return_status= 1;
				}// wait until counter reaches 255
		TIFR |= 1<<TOV0;
		return_status= 0;
	}
	return return_status;
}


void Soft_Start_and_Run_to_Max(void){
	uint8_t cnt=0;
	SoftStart=true;
	SET_LED0;// turn ON LED0
	for(TRIACdelay=DELAYMAXSOFTSTART; TRIACdelay>0; TRIACdelay-=DELAYSOFTSTART){
			if((uint8_t)0 == Delay_ms(100, 0)){
				cnt++;
				if(cnt>=5){
					Increment_decrement_LED(INCREMENT);
					cnt=0;
				}
			}
		}
	SoftStart=false;
}

void Increment_decrement_LED(led_status_t led_status){
	if(led_status == INCREMENT){
		if(LED<4){
			LED++;
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

void Increment_Power_and_LEDs(void){
	if (TRIACdelay>DELAYMIN){
		TRIACdelay-=(uint16_t)(DELAYCNTRL);
		increment_flag=true;
	}
	Increment_decrement_LED(INCREMENT);
}

void Decrement_Power_and_LEDs(void){
	if (TRIACdelay<DELAYMAX){
		TRIACdelay+=(uint16_t)(DELAYCNTRL);
		decrement_flag=true;
	}
	Increment_decrement_LED(DECREMENT);
}


