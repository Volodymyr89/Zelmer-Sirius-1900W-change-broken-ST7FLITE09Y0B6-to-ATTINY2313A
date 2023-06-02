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
	Timer0_Init();
	Soft_Start_and_Run_to_Max();
	
    while (1) 
    {
    }
}

