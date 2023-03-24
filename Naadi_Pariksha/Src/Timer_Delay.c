/*
 *
 *  Created on: 26-Jan-2023
 *      Author: Karthikh Amaran
 */

#include<stdio.h>
#include<stdint.h>
#include"adc.h"
#include"stm32f4xx.h"
#include "uart.h"
#include "systick.h"
uint32_t sensor_value;
int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

void delay()
{
	volatile int i=0;
	for(i=0;i<16000000;i++);
}
int main(void)
{
	int count =0;
	uart2_rxtx_init(); // PA2 TX : PA3 RX
	pa1_adc_init();
	start_continuous_conversion();
	printf("TimeStamp,Value");
	while(1)
	{
		count++;
		sensor_value = adc_read(); // ADC IN PA1
		printf("%d,",(int)(sensor_value)); fflush(stdout);
		delay();
		//SysTickMsDelay(2);
		SysTickMsDelay(200);
		if(count == 107)
		{
			printf("%d",(int)(sensor_value)); fflush(stdout);
			break;
		}
	}
}
