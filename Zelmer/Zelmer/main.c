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
	RESET_LED5;// set LED
	RESET_LED6;// set LED

    while (1) 
    {
		if(increment_flag_LED==true && decrement_flag_LED==false){
			while((uint8_t)1==Delay_ms(100,(PIND&(1<<PIND2)))){}
				increment_flag=true;
				increment_flag_LED=false;
				Increment_decrement_LED(INCREMENT);
			}
		else if(decrement_flag_LED==true && increment_flag_LED==false){
			while((uint8_t)1==Delay_ms(100,(PIND&(1<<PIND3)))){}
				decrement_flag=true;
				decrement_flag_LED=false;
				Increment_decrement_LED(DECREMENT);
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

