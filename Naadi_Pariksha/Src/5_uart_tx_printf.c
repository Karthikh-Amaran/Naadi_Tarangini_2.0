/*
 * 5_uart_tx_printf.c
 *
 *  Created on: 24-Jan-2023
 *      Author: Karthikh Amaran
 */


#include<stdio.h>
#include"stm32f411xe.h"
#include<stdint.h>

#define SYS_FREQ       16000000
#define APB1_CLK       SYS_FREQ // Since we didn't configure any clock trees the default will bee same as system or Default Clock frequency
#define UART_BAUDRATE  115200

#define CR1_TE         (1U<<3)
#define CR1_UE         (1U<<13)
#define USART2EN       (1U<<17)
#define GPIOAEN        (1U<<0)
// PA2 TX
// PA3 RX
static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk,uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void uart2_tx_init(void);
void uart2_write(int ch);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

int main()
{
	uart2_tx_init();
	while(1)
	{
		printf("Hello World....\n\r"); // This method is by using the syscalls.c function usage
                         // The function used is __io_putchar(int ch)
	}
}



// Function for UART initialization
void uart2_tx_init(void)
{
	//********* CONFIGURE GPIO UART PINS *********
	// First Configuring the GPIOS for UART2
	// GPIOA PIN2 in AF07 - TX
	// GPIOA PIN3 in AF07 - RX
	// 1. Enabling the clock for GPIOA and USART2 Peripherals*/
	RCC->AHB1ENR |= GPIOAEN;
	// 2. Set the Mode as Alternate function
	GPIOA->MODER &= ~(0xf<<4);
	GPIOA->MODER |= (10<<4);// 0x1010 0000
	// 3. Set Alter function register for those pins
	GPIOA->AFR[0] &= ~(0xff<<8);
	GPIOA->AFR[0] |= (0x77<<8); // 0x0111 0111 0000 0000

	/********** CONFIGURE GPIO UART PINS **********/
	// 1. Enable the clock access to uart2
	RCC->APB1ENR |= USART2EN;


	// 2. Configure Baud-rate
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);
	// 3. Configure the transfer direction
	USART2->CR1 = CR1_TE; // Clear all the bits and only set TE bit; TE - Transmitter Enable
	// 4. Enable the UART Module
	USART2->CR1 |= CR1_UE; // UART Enable
}


static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk,uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk,BaudRate);
}
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk+(BaudRate/2U))/BaudRate);
}

// Function to UART2 Write or Transmit
/*void uart2_write(int ch)
{
	// 1. Check whether the Transmission Data Register is empty
	while(!(USART2->SR & 1<<7));
	// 2. Write the Data to the Data register
		USART2->DR = (ch&0xFF); // To get only the bits;
}*/




