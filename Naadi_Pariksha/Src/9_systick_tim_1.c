/*
 * 9_systick_tim_1.c
 *
 *  Created on: 30-Jan-2023
 *      Author: Karthikh Amaran
 */

#include<stdio.h>
#include<stdint.h>
#include"adc.h"
#include"stm32f4xx.h"
#include "uart.h"
#include "systick.h"
void ToggleLed(GPIO_TypeDef *GPIO,uint8_t PIN_NO);

int main(void)
{
	uart2_rxtx_init();
	while(1)
	{
	printf("One Second Over \n\r");
	/*Blinking the LED for 1ms */
	ToggleLed(GPIOD, 12);
	SysTickMsDelay(1000);
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
