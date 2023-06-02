#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include "motor_and_LED_control.h"

// set CNT0MAX 
#ifndef CNT0MAX
	#define CNT0MAX 255
#endif
#ifndef CYCLENUM
	#define CYCLENUM 25
#endif
	
// set LEDs macros
#if !defined (SET_LED0) || !defined (SET_LED1) || !defined (SET_LED2) || !defined (SET_LED3) || !defined (SET_LED4)
	#define SET_LED0  DDRB |= (1 << DDB4)
	#define SET_LED1  DDRB |= (1 << DDB3)
	#define SET_LED2  DDRB |= (1 << DDB2)
	#define SET_LED3  DDRB |= (1 << DDB1)
	#define SET_LED4  DDRB |= (1 << DDB0)
	// reset LEDs macros
	#define RESET_LED0  DDRB &= ~(1 << DDB4)
	#define RESET_LED1  DDRB &= ~(1 << DDB3)
	#define RESET_LED2  DDRB &= ~(1 << DDB2)
	#define RESET_LED3  DDRB &= ~(1 << DDB1)
	#define RESET_LED4  DDRB &= ~(1 << DDB0)
#endif


 uint8_t currentLEDnumber=0;

uint8_t Delay_100ms (void){
	uint32_t delay = 100000;
	uint8_t return_status = 1;
	while(delay--){}
	return_status= 0;
	return return_status;
}

uint8_t Set_LED(void){
	static uint8_t LED=0;
	LED+=1;
	if(LED<4){
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
		return LED;
}

void ReSet_LED(uint8_t LED){
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
}

void Soft_Start_and_Run_to_Max(void){
	uint8_t duty_cycle = 10;
	SET_LED0;// turn ON LED0
	for(uint8_t step=0; step<CYCLENUM; step++){
		uint8_t cnt=0;// divider
		if(OCR0B<CNT0MAX){
			OCR0B=duty_cycle;
			if((uint8_t)0 == Delay_100ms()){
				duty_cycle+=10;
				cnt++;
				if(cnt>=5){
					currentLEDnumber=Set_LED();
				}
			}
		}
		else if (OCR0B>=250){
			OCR0B=CNT0MAX;
		}
	}
}

void Increment_Duty_Cycle(void){
	if(OCR0B<(uint8_t)CNT0MAX){
		OCR0B +=10;
	}
}

void Decrement_Duty_Cycle(void){
	if(OCR0B>(uint8_t)0){
		OCR0B -=10;
	}
}
