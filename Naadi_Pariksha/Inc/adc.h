/*
 * adc.h
 *
 *  Created on: 26-Jan-2023
 *      Author: Karthikh Amaran
 */

#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>
void pa1_adc_init(void);
void start_single_conversion(void);
void start_continuous_conversion(void);
uint32_t adc_read(void);



#endif /* ADC_H_ */
