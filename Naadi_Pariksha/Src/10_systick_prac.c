#include<stdio.h>
#include<stdint.h>
#include"adc.h"
#include"stm32f4xx.h"
#include "uart.h"
#include "systick.h"
void DigitalOUT(GPIO_TypeDef *GPIO,uint8_t PIN_NO,uint8_t STATUS);

int main(void)
{
	SysTick->LOAD = 10;
	SysTick->CTRL = (1U<<2);
	SysTick->CTRL = (1U<<0);
	SysTick->VAL = 0;
	//int value = (SysTick->CTRL & 0x1<<16);
	while((SysTick->CTRL & 0x1<<16)==0)
	{
		printf("COUNT FLAG Value :%d\n",SysTick->CTRL & 0x1<<16);
	}
	printf("COUNT FLAG Value :%d\n",SysTick->CTRL & 0x1<<16);
	/* Disable the Timer */
	SysTick->CTRL &= ~(1U<<0);
}

void DigitalOUT(GPIO_TypeDef *GPIO,uint8_t PIN_NO,uint8_t STATUS)
{
	if(GPIO == GPIOD)
	{
		RCC->AHB1ENR |= (1<<3);
		GPIO->MODER &= ~(0x3<<(PIN_NO*2));
		GPIO->MODER |= (0x1<<(PIN_NO*2));

		if(STATUS == 1)
			GPIO->ODR |= (0x1<<PIN_NO);
		else
			GPIO->ODR &= ~(0x01<<PIN_NO);
	}
}
