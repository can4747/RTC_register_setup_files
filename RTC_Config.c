#include "stm32f4xx.h"                  // Device header

typedef struct{
  uint8_t Hours;           
  uint8_t Minutes;         
  uint8_t Seconds;         
	
}RTC_TimeTypeDef;


typedef struct{
  uint8_t Month;    
  uint8_t Day;     
  uint8_t Year;  
	
}RTC_DateTypeDef;


	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;

void RTC_Init(void){

	RCC->APB1ENR |= RCC_APB1ENR_PWREN;					//enable peripheral clock power
	PWR->CR |= PWR_CR_DBP;											//enable access to the RTC registers
	
	RCC->CSR |= RCC_CSR_LSION;									//enable LSI
	while(!(RCC->CSR & RCC_CSR_LSIRDY));				//wait for LSI ready flag

	RCC->BDCR |= 0x8200;												//select LSI and enable RTC
	
	RTC->WPR |= 0xCA;														//enter key to unlock write protection
	RTC->WPR |=	0x53;
	
	RTC->ISR |= RTC_ISR_INIT;
	while(!(RTC->ISR & RTC_ISR_INITF));					//wait for RTC init ready flag
	
	RTC->PRER |=0xF9;
	RTC->PRER |=0x7F<<16;
	
	RTC->TR |= 0x130000;						//set hour as 13
	RTC->TR |= 0x5700;							//set minute as 57
	
	RTC->DR |=0x215124;							//SET date as 21/11/25 thuesday
	RTC->CR |= RTC_CR_BYPSHAD;
	
	RTC->ISR &= ~RTC_ISR_INIT;			//clear init bit
	
	PWR->CR &= ~PWR_CR_DBP;					// disable access to RTC registers

}


void RTC_get_time (void){
	
	sTime.Seconds=(((RTC->TR & 0x7f) >> 4)*10)+(RTC->TR & 0xf);
	sTime.Minutes=((RTC->TR & 0x7f00) >> 8);
	sTime.Minutes=(((sTime.Minutes & 0x7f)>>4)*10)+(sTime.Minutes & 0xf);
	sTime.Hours=((RTC->TR & 0x7f0000) >> 16);
	sTime.Hours=(((sTime.Hours & 0x7f)>>4)*10)+(sTime.Hours & 0xf);

}

void RTC_get_date(void){

	sDate.Year=((RTC->DR >> 20)*10) + ((RTC->DR >>16) & 0xf);
	sDate.Month=((RTC->DR >> 12) & 1)*10 + ((RTC->DR >>8) & 0xf);
	sDate.Day=((RTC->DR >> 4) & 3)*10 + (RTC->DR & 0xf);

}

