#include "stm32f4xx.h"                  // Device header
#include "delay.h" 
#include "ClockConfig.h"
#include "RTC_Config.h"

int main (void){

	ClockConfig();
	TIM6_Config();
	RTC_Init();

	while(1){
		
			RTC_get_date();
			RTC_get_time();
		
			Delay_ms(1000);
	
	
	}

}
