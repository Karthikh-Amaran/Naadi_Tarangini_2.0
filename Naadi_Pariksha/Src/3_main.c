/*
 * 002_2main.c
 *
 *  Created on: Jan 21, 2023
 *      Author: Karthikh Amaran
 */


#include"stm32f4xx.h"

#define GPIODEN 				 (1U<<3)
#define GPIOAEN 				 (1U<<0)
#define PIN12                    (1U<<12)


void delay()
{
	volatile unsigned int i=0;
	for(i=0;i<1000000;i++);
}
int main(void)
{
	// Enabling the clock for GPIOA (Built in Switch)
	// and for GPIOD (Built in LED)
	RCC->AHB1ENR |= GPIODEN;
	RCC->AHB1ENR |= GPIOAEN;
    // Setting the mode as Output for GPIOD
	GPIOD->MODER &= ~(0X3<<26);
	GPIOD->MODER |= (0X1<<26);
	// Setting the mode as Input for GPIOA
	GPIOA->MODER &= ~(0X3<<0);

	 while(1)
	 {
		 if((GPIOA->IDR&0x1) == 0x1) // Scanning the Switch connected Pin
		 {
			 delay(); // to avoid button de-bouncing
			 //GPIOD->ODR ^= (1<<13);
			 GPIOD->BSRR |= (1<<13);
		 }
		 else
		 {
			 GPIOD->BSRR |= (1<<29);
		 }
	 }
}
