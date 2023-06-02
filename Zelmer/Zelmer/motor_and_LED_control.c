#include <avr/io.h>
#include <stdbool.h>

// set LEDs macros
#define CNT0MAX (255)
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


uint8_t Delay_100ms (void){
	uint32_t delay = 100000;
	uint8_t return_status = 1;
	while(delay--){}
	return_status= 0;
	return return_status;
}

void Soft_Start_and_Run_to_Max(void){
	uint8_t duty_cycle = 10;
	
	SET_LED0;// turn ON LED0
	
	for(uint8_t step=0; step<25; step++){
		if(OCR0B<CNT0MAX){
			OCR0B = duty_cycle;
			Delay_100ms();
			duty_cycle+=10;
		}
		else{
			OCR0B=CNT0MAX;
		}
	}
}

void Set_LED(uint8_t LED){
	switch(LED){
		case 2:
		SET_LED1;
		break;
		case 3:
		SET_LED2;
		break;
		case 4:
		SET_LED3;
		break;
		case 5:
		SET_LED4;
		break;
	}
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

void Set_LED_Bar(bool increment){
	static uint8_t LED_num=1;
	if(increment){
		if(LED_num<5)
		LED_num+=1;
		Set_LED(LED_num);
	}
	else{
		if(LED_num>1)
		LED_num-=1;
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