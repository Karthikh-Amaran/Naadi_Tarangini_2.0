/*
 * 000_MCO_Clock_Output.c
 *
 *  Created on: Jan 30, 2023
 *      Author: Karthikh Amaran
 */


#include "stm32f4xx.h"

int main()
{
	RCC->AHB1ENR |= 1<<0;
	GPIOA->MODER |= 1<<17;
	GPIOA->MODER &= ~(1<<16);
	GPIOA->AFR[1] &= ~(0xf<<0);
	while(1);
}
