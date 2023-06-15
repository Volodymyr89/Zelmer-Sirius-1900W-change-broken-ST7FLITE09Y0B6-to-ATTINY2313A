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

bool button2_latch=false, button3_latch=false;// latch for buttons

int main(void)
{	
	Output_Pins_Init(); // init output PINs
	//set filter LEDs for operation check 
	SET_LED5;// set LED
	SET_LED6;// set LED
	//set filter LEDs for operation check end
	Input_Pins_Init(); // init input pins
	Timer0_Init(); // init Timer0
	Timer1_Init(); // init Timer1
	sei();//enable global interrupts
	Soft_Start_and_Run_to_Max(); // start motor and increase power up to max
	RESET_LED5;// reset LED
	RESET_LED6;// reset LED
	
    while (1) 
    {		//check if increment button is pressed
		if((!(PIND&(1<<PIND2))) && (!button2_latch)){
			button2_latch=true;
			while((uint8_t)1==Delay_ms(200,(PIND&(1<<PIND2)))){} // deglitch button
				Increment_Power_and_LEDs(); increment LED status bar and power to motor
			}
	       //check if decrement button is pressed
		else if((!(PIND&(1<<PIND3))) && (!button3_latch)){
				button3_latch=true;
				while((uint8_t)1==Delay_ms(200,(PIND&(1<<PIND3)))){} // deglitch button
				Decrement_Power_and_LEDs(); decrement LED status bar and power to motor
		}
		if(PIND&(1<<PIND2)){
			button2_latch=false; // release latch
		}
		if(PIND&(1<<PIND3)){
			button3_latch=false; // release latch
		}
		if(!(PINA&(1<<PINA1))){
			SET_LED5;   // set LED set led if filter is dirty
		}
		else{
			RESET_LED5;// reset LED
		}
		if(!(PIND&(1<<PIND1))){
			SET_LED6;  // set LED set led if filter is dirty
		}
		else{
			RESET_LED6;// reset LED
		}
		if(!(PINA&(1<<PINA0))){
			SET_SOCKET;   // turn ON socket for brush
		}
		else{
			RESET_SOCKET; // turn OFF socket for brush
		}	
	}
		
 }

