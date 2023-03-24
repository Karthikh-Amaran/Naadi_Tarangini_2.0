/*
 * 6_uart_rx_tx.c
 *
 *  Created on: 26-Jan-2023
 *      Author: Karthikh Amaran
 */




#include<stdio.h>
#include"stm32f411xe.h"
#include<stdint.h>
#include "uart.h"
// PA2 TX
// PA3 RX
void DigitalOUT(GPIO_TypeDef *GPIO,uint8_t PIN_NO,uint8_t STATUS);
void delay()
{
	volatile int i=0;
	for(i=0;i<1000000;i++);
}
int main()
{
	uart2_rxtx_init();
	while(1)
	{
		switch(uart2_read())
		{
		case 'Y': DigitalOUT(GPIOD,12,1); delay(); DigitalOUT(GPIOD,12,0); break;
		case 'y': DigitalOUT(GPIOD,13,1); delay(); DigitalOUT(GPIOD,13,0); break;
		default: DigitalOUT(GPIOD,12,1); DigitalOUT(GPIOD,13,1); delay();
		         DigitalOUT(GPIOD,12,0); DigitalOUT(GPIOD,13,0); break;
		}
		if(uart2_read()=='Y') // 0x59
		{
			DigitalOUT(GPIOD,12,1); delay(); DigitalOUT(GPIOD,12,0);
		}
		else if(uart2_read()=='y') // 0x79
		{
			DigitalOUT(GPIOD,13,1); delay(); DigitalOUT(GPIOD,13,0);
		}

		/*if(uart2_read()=='Y') // 0x59
		{
			DigitalOUT(GPIOD,12,1);
			delay();
		}
		if(uart2_read()!='Y')
		{
			DigitalOUT(GPIOD,12,0);
		}*/

	}
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




