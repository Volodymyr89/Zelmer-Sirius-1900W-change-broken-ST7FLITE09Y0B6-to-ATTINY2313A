#ifndef _MOTOR_AND_CONTROL_H_
#define _MOTOR_AND_CONTROL_H_

#include <stdint.h>
#include <stdbool.h>

#ifndef DELAYCNTRLSOFTTRANSITION
	#define DELAYCNTRLSOFTTRANSITION 20
#endif

#ifndef DELAYCNTRL
	#define DELAYCNTRL 2000
#endif

#ifndef DELAYMIN
	#define DELAYMIN 500
#endif

#ifndef DELAYMAX
	#define DELAYMAX 6500
#endif

// reset LEDs macros
#if !defined (SET_LED0) || !defined (SET_LED1) || !defined (SET_LED2) || !defined (SET_LED3) || !defined (SET_LED4)
	#define RESET_LED0  PORTD |= (1 << PORTD5)
	#define RESET_LED1  PORTB |= (1 << PORTB3)
	#define RESET_LED2  PORTB |= (1 << PORTB2)
	#define RESET_LED3  PORTB |= (1 << PORTB1)
	#define RESET_LED4  PORTB |= (1 << PORTB0)
	//LEDs for filters
	#define RESET_LED5  PORTD |= (1 << PORTD6)
	#define RESET_LED6  PORTD |= (1 << PORTD4)
	//socket
	#define RESET_SOCKET PORTB |= 1 << PORTB7
// set LEDs macros
	#define SET_LED0   PORTD &= ~(1 << PORTD5)
	#define SET_LED1   PORTB &= ~(1 << PORTB3)
	#define SET_LED2   PORTB &= ~(1 << PORTB2)
	#define SET_LED3   PORTB &= ~(1 << PORTB1)
	#define SET_LED4   PORTB &= ~(1 << PORTB0)
	//LEDs for filters
	#define SET_LED5  PORTD &= ~(1 << PORTD6)
	#define SET_LED6  PORTD &= ~(1 << PORTD4)
	//set socket
	#define SET_SOCKET PORTB &= ~(1 << PORTB7)
	
//Timer1 PWM
	#define SET_TMR1OUT0 PORTB |= 1 << PORTB4 
	#define RESET_TMR1OUT0 PORTB &= ~(1 << PORTB4)
#endif

extern volatile bool increment_flag, decrement_flag;
extern volatile uint16_t delay;
extern volatile bool set_power_max;
extern uint16_t TRIACdelay;

typedef enum{
	INCREMENT,
	DECREMENT
}led_status_t;

// functions prototypes
uint8_t Delay_ms(uint8_t delay,uint8_t reset);
void Soft_Start_and_Run_to_Max(void);
void Increment_decrement_LED(led_status_t led_status);
void Increment_Duty_Cycle(void);
void Decrement_Duty_Cycle(uint8_t LED);
void Timer1_Start(void);
void Timer1_Stop(void);

#endif