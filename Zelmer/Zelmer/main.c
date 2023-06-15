/*
 * Zelmer.c
 *
 * Created: 6/1/2023 11:29:15 AM
 * Author : VolodymyrBatih
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "periphery_init.h"
#include "motor_and_LED_control.h"

bool button2_latch=false, button3_latch=false, set_power_max_flag=false;

int main(void)
{	
	Output_Pins_Init();
	SET_LED5;// set LED
	SET_LED6;// set LED
	Input_Pins_Init();
	Timer0_Init();
	Timer1_Init();
	sei();//enable global interrupts
	Soft_Start_and_Run_to_Max();
	RESET_LED5;// reset LED
	RESET_LED6;// reset LED
	

    while (1) 
    {

		if((!(PIND&(1<<PIND2))) && (!button2_latch)){
			button2_latch=true;
			while((uint8_t)1==Delay_ms(200,(PIND&(1<<PIND2)))){}
				Increment_Power_and_LEDs();
			}
		else if((!(PIND&(1<<PIND3))) && (!button3_latch)){
				button3_latch=true;
				while((uint8_t)1==Delay_ms(200,(PIND&(1<<PIND3)))){}
				Decrement_Power_and_LEDs();
		}
		if(PIND&(1<<PIND2)){
			button2_latch=false;
		}
		if(PIND&(1<<PIND3)){
			button3_latch=false;
		}
		if(!(PINA&(1<<PINA1))){
				SET_LED5;// set LED
		}
		else{
			RESET_LED5;// reset LED
		}
		if(!(PIND&(1<<PIND1))){
			SET_LED6;// set LED
		}
		else{
			RESET_LED6;// reset LED
		}
		if(!(PINA&(1<<PINA0))){
			SET_SOCKET;// reset socket
		}
		else{
			 RESET_SOCKET;// reset socket
		}	
	}
		
 }

