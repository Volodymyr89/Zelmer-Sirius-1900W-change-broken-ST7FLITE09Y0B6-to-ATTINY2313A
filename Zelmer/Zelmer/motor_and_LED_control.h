#ifndef _MOTOR_AND_CONTROL_H_
#define _MOTOR_AND_CONTROL_H_

uint8_t Delay_100ms (void);
void Soft_Start_and_Run_to_Max(void);
void Set_LED(uint8_t LED);
void ReSet_LED(uint8_t LED);
void Set_LED_Bar(bool increment);
void Increment_Duty_Cycle(void);
void Decrement_Duty_Cycle(void);

#endif