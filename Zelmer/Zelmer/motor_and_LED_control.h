#ifndef _MOTOR_AND_CONTROL_H_
#define _MOTOR_AND_CONTROL_H_

#include <stdint.h>

extern uint8_t currentLEDnumber;

uint8_t Delay_100ms (void);
void Soft_Start_and_Run_to_Max(void);
uint8_t Set_LED(void);
void ReSet_LED(uint8_t LED);
void Increment_Duty_Cycle(void);
void Decrement_Duty_Cycle(void);

#endif