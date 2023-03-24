#include"stm32f4xx.h"

#define GPIODEN 				 (1U<<3)
#define PIN12                    (1U<<12)


void delay()
{
	volatile unsigned int i=0;
	for(i=0;i<1000000;i++);
}
int main(void)
{
	RCC->AHB1ENR |= GPIODEN;

	 GPIOD->MODER &= ~(0X3<<26);
	 GPIOD->MODER |= (0X1<<26);

	while(1)
	{
		GPIOD->ODR ^= (1<<13);
		delay();
	}
}



