/*
 * systick.c
 *
 *  Created on: 30-Jan-2023
 *      Author: Karthikh Amaran
 */
#include "stm32f4xx.h"
void SysTickMsDelay(uint32_t delay)
{
	/* Load the Reload Value register */
	/* The value should be creating 1ms delay */
	/* The So for internal clock 16MHz to create 1ms delay */
	/* We need to Load with the value 16000 (Delay = N/Sysclk) */
	SysTick->LOAD = 1900;

	/* Set the clock source and enable the timer */
	SysTick->CTRL = (1U<<2);
	SysTick->CTRL = (1U<<0);
	/* Clear the Current Value register */
	SysTick->VAL = 0;

	/* Wait until Count Flag is Set */
	/* Count Flag sets if the counting is over */
	/* After it is read it will again set to zero */
	/* And the timers don't care about anything it will be always reloading and counting until they get disabled */
	for(uint32_t i=0;i<delay;i++)
	{
		while(!(SysTick->CTRL & 0x1<<16));
	}

	/* Disable the Timer */
	SysTick->CTRL &= ~(1U<<0);
}

