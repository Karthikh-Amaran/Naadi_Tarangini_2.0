#include"stm32f4xx.h"
#define TIM2EN (1U<<0)
#define CR1_EN (1U<<0)

void tim2_1hz_init(void)
{
	/* Enable the Clock access to tim2*/
	RCC->APB1ENR |= TIM2EN;
	/* Set the pre-scaler value  */
	TIM2->PSC = 48000-1; // 48 000 000/48 000 = 1000 = 1kHz = 1000 Cycles per second
	/* Set the Auto-Reload Value */
	TIM2->ARR = 1000-1; // 10 000 / 10 000 = 1Hz
	// Now here frequency is 10k and the value to be counted is also 10k.
	// Which implies the delay given will be 1 second
	// COunting 10k values per second by 10k cycles to give 1 second delay
	/* Clear Counter */
	TIM2->CNT = 0; // Since by default it is an Upcounter
	/* Enable Timer */
	TIM2->CR1 = CR1_EN;
}
