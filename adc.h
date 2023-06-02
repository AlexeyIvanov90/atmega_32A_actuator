/*
 * adc.h
 *
 * Created: 14.03.2022 15:25:05
 *  Author: Алексей
 */ 
#ifndef ADC_H_
#define ADC_H_

#include "main.h"

void ADC_Init(void);
void switch_ADC(int num_ADC);
float ADC_result();

#endif /* ADC_H_ */