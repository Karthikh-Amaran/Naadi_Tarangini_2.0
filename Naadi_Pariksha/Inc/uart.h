/*
 * uart.h
 *
 *  Created on: 26-Jan-2023
 *      Author: Karthikh Amaran
 */

#ifndef UART_H_
#define UART_H_

#include<stdint.h>
#include "stm32f4xx.h"
void uart2_rxtx_init(void);
void uart2_write(int ch);
int8_t uart2_read(void);
void uart2_tx_init(void);
#endif /* UART_H_ */
