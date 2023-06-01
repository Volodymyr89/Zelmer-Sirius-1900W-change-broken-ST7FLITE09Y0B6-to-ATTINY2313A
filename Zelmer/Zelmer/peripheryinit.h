#ifndef _PERIPHERYINIT_H_
#define _PERIPHERYINIT_H_

typedef enum{
	OUT_INIT_OK,
	OUT_INIT_FAIL,
	IN_INIT_OK,
	IN_INIT_FAIL
}pin_init_status_t;

// function prototypes
pin_init_status_t Output_Pins_Init(void);
pin_init_status_t Input_Pins_Init(void);
void Timer_Init(void);
void Soft_Start_and_Run_to_Max(void);






#endif