#include<stdio.h>
#include<stdint.h>
#include"adc.h"
#include"stm32f4xx.h"
#include "uart.h"
#include "systick.h"
#include "tim.h"

void ToggleLed(GPIO_TypeDef *GPIO,uint8_t PIN_NO);

int main(void)
{
	uart2_rxtx_init();
	tim2_1hz_init();
	while(1)
	{
		/*Checking whether the UIF Flag is Set*/
		/* UIF flag is set only when the Timer Overflows or Underflows */
		while(!(TIM2->SR & SR_UIF));
		/* Clear the UIF Bit manually */
		TIM2->SR &= ~(1U<<SR_UIF);
		/* Now toggle the led for 1 second*/
		printf("A Second Passed !! \n\r");
		ToggleLed(GPIOD, 12);
	}
}

void ToggleLed(GPIO_TypeDef *GPIO,uint8_t PIN_NO)
{
	if(GPIO == GPIOD)
	{
		RCC->AHB1ENR |= (1<<3);
		GPIO->MODER &= ~(0x3<<(PIN_NO*2));
		GPIO->MODER |= (0x1<<(PIN_NO*2));
		GPIO->ODR ^= (0x1<<PIN_NO);
	}
}


