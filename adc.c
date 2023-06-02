/*
 * adc.c
 *
 * Created: 14.03.2022 15:25:35
 *  Author: Alexei
 */ 

#include "adc.h"

void ADC_Init(void){
	  ADCSRA = (1<<ADEN) | (1<<ADPS2);//prescaler 16 (62.5kGz)
	  ADMUX = (1<<REFS0);
	  SFIOR = 0;
}


void switch_ADC(int num_ADC){
	// ADMUX &= (1<<REFS0);//AVCC with external capacitor at AREF pin
	switch(num_ADC){
		case 0:
			ADMUX = 0b01000011;
			break;
		case 1:
			ADMUX = 0b01000100;
			break;
		case 2:
			ADMUX = 0b01000101;
			break;
	}
	ADCSRA |= (1<<ADSC);//start		
}

float ADC_result(){
	while((ADCSRA & (1<<ADSC)));//end
	unsigned int adc_value = ADC;
	
	return (float)adc_value / 204.8;
}
	
