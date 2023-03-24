#include"stm32f4xx.h"
#include"adc.h"
#define GPIOAEN     	(1U<<0)
#define ADC1EN      	(1U<<8)
#define ADC1_CH1    	(1U<<0)
#define ADC1_SEQ_LEN	(0x0<<20)
#define CR2_ADON        (1U<<0)
#define CR2_SWSTART     (1U<<30)
#define CR2_CONT        (1U<<1)

/*
 *   ADC modules can only sample the inputs one by one
 *   So even though we have 16 channels each channels would be sampled sequentially
 *   This shows that we have to tell the order or sequence in which the Channels should be sampled using
 *   the sequence register.
 *   And we also tell the length or the number of channels we are going to get sampled by the ADC
 *
 *
 *   Say we use 3 channels (3 pins used as Analog pins)
 *   Say we use CH1 , CH10, CH13
 *   So we should arranged the order or rank for sampling in the ADC
 *   Say we need to sample
 *   10 first
 *   1 second
 *   13 third
 *   So in the Sequence register of ADC
 *   SQ1 - set with value 10 (0x1010)
 *   SQ2 - set with value 1  (0x0001)
 *   SQ3 - set with value 13 (0x1101)
 *   And L - set as three (3-1 value in binary)
 */

void pa1_adc_init(void)
{
	/* 1. Configure the ADC GPIO Pin */
	/* Enable Clock Access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;
	/* Set the mode of the PA1 to analog */
	GPIOA->MODER |= 0x3<<2;
	/* 2. Configure the ADC Module */
	/* Enable clock access to ADC */
	RCC->APB2ENR |= ADC1EN;
	/* Conversion sequence Configuration */
	ADC1->SQR3 |= ADC1_CH1; // Using CH1 (ADC1_CH1) - PA1
	/* Conversion Sequence length */
	ADC1->SQR1 |= ADC1_SEQ_LEN;
	/* Enable ADC Module */
	ADC1->CR2 |= CR2_ADON;
}

void start_single_conversion(void)
{
	/* Start ADC Conversion */
	ADC1->CR2 |= CR2_SWSTART;
}
void start_continuous_conversion(void)
{
	/* Start ADC Conversion */
	ADC1->CR2 |= CR2_CONT;
	/* Start ADC Conversion */
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void)
{
	/* Wait for Conversion to be complete */
	/* Check for the EOC Flag in ADC Status register */
	while(!((ADC1->SR)&(0x1<<1))); // Wait here until conversion completed
	/* Now return the ADC value */
	return (ADC1->DR);

}
