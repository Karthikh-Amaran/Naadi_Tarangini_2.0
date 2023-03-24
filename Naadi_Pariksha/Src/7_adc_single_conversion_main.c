/*
 * 7_adc_main.c
 *
 *  Created on: 26-Jan-2023
 *      Author: Karthikh Amaran
 */

#include<stdio.h>
#include<stdint.h>
#include"adc.h"
#include"stm32f4xx.h"
#include "uart.h"

uint32_tl sensor_value;
void delay()
{
	volatile int i=0;
	for(i=0;i<1000000;i++);
}
int main(void)
{
	uart2_rxtx_init(); // PA2 TX : PA3 RX
	pa1_adc_init();
	while(1)
	{
		start_single_conversion();
		sensor_value = adc_read();
		sprintf("Sensor Value (in Dec): %d (in Hex): %x. \r\n",(int)(sensor_value),(int)(sensor_value));
		delay();
	}
}
