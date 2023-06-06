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
#include "periphery_init.h"
#include "motor_and_LED_control.h"



int main(void)
{	
	Output_Pins_Init();
	Input_Pins_Init();
	Timer0_Init();
	Timer1_Init();
	Soft_Start_and_Run_to_Max();
    while (1) 
    {
		if(increment_flag){
			while(!(PIND&(1<<PIND2))&&((uint8_t)0==Delay_ms(70))){}
				Increment_decrement_Duty_Cycle(INCREMENT, false);
				increment_flag=false;
			}
		else if(decrement_flag){
			while(!(PIND&(1<<PIND3))&&((uint8_t)0==Delay_ms(70))){}
				Increment_decrement_Duty_Cycle(DECREMENT, false);
				decrement_flag=false;
			}
		}
		
    }

