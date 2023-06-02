/*
 * purka.c
 *
 * Created: 10.03.2022 16:02:45
 *  Author: Alexei
 */ 

#include "main.h"

volatile uint8_t button_1_count = 0;
volatile uint8_t button_2_count = 0;
volatile uint8_t button_3_count = 0;

volatile uint8_t led_blink = 0;//blink(1 - led 1, 2 - led 2, 3 - led 3, 4 - all led)
volatile uint8_t count_led_blink = 0;

volatile uint8_t num_ADC = 0;

volatile uint8_t counter_ADC[6] = {0,0,0};

#define MAX_COUNT_BUTTON 100

const float MAX_A_ADC[3] = {MAX_A_DOWN, MAX_A_UP, MAX_A_MID};//down, up, mid V

volatile uint8_t phase = 0;

int main(void)
{
	cli();
	PORTC = BUTTON_1 | BUTTON_2 | BUTTON_3;
	DDRC = LED_BUTTON_1 | LED_BUTTON_2 | LED_BUTTON_3;
	PORTB = 0;
	DDRB = KNIFE_1_OPEN | KNIFE_1_CLOSE | KNIFE_2_OPEN | KNIFE_2_CLOSE | KNIFE_3_CLOSE;
	PORTD = 0;
	DDRD = KNIFE_3_OPEN;
	
	
	timer_init();
	ADC_Init();	
	
	_delay_ms(1000);
	sei();
	_delay_ms(1000);	
		
	//TEST purka (press button 1 to start)	
	if(button_1_count == MAX_COUNT_BUTTON){
		while(1){
			PORTC |= LED_BUTTON_2;
			PORTB |= KNIFE_2_OPEN;
			_delay_ms(1500);
			
			PORTC |= LED_BUTTON_1;
			PORTB |= KNIFE_1_OPEN;
			_delay_ms(1500);
			
			PORTC |= LED_BUTTON_3;
			PORTD |= KNIFE_3_OPEN;
			_delay_ms(12500);
			
			PORTB = 0;
			PORTD = 0;
			
			PORTC  ^= LED_BUTTON_2;
			PORTB |= KNIFE_2_CLOSE;
			_delay_ms(1500);
			
			PORTC ^= LED_BUTTON_1;
			PORTB |= KNIFE_1_CLOSE;
			_delay_ms(1500);
			
			PORTC ^= LED_BUTTON_3;
			PORTB |= KNIFE_3_CLOSE;
			_delay_ms(12500);
			
			PORTB = 0;
			PORTD = 0;
		}	
	}
	
	purka_init();
		
    while(1)
    {
		switch(phase){
			case 0:
				if(button_1_count == MAX_COUNT_BUTTON){
					led_blink = 1;
					//open 1 knife
					PORTB |= KNIFE_1_OPEN;
					_delay_ms(12000);
					PORTB = 0;
					PORTD = 0;
					_delay_ms(500);
					
					//close 2 knife
					PORTB |= KNIFE_2_CLOSE;
					_delay_ms(15000);
					PORTB = 0;
					PORTD = 0;					
					_delay_ms(500);

					//open 3 knife
					PORTD |= KNIFE_3_OPEN;
					_delay_ms(5000);
					PORTB = 0;
					PORTD = 0;
					_delay_ms(500);			
			
					phase = 1;
					led_blink = 0;
					PORTC &= LED_BUTTON_OFF;
					PORTC |= LED_BUTTON_2;
				}
			break;
			case 1:
				//ready to measuring
				if(button_2_count == MAX_COUNT_BUTTON){
					led_blink = 2;
					//open 2 knife
					PORTB |= KNIFE_2_OPEN;
					_delay_ms(15000);
					PORTB = 0;
					PORTD = 0;
					_delay_ms(500);					
			
					//close 1, 3 knife
					PORTB |= KNIFE_1_CLOSE;
					_delay_ms(2500);					
					PORTB |= KNIFE_3_CLOSE;
					_delay_ms(2500);					
					PORTB ^= KNIFE_1_CLOSE;
					_delay_ms(2500);
					PORTB = 0;
					PORTD = 0;
					_delay_ms(500);					
			
					phase = 0;
					led_blink = 0;
					PORTC &= LED_BUTTON_OFF;
					PORTC |= LED_BUTTON_1;
				}			
			break;
		}
    }
}

void purka_init(){
	led_blink = 4;
	PORTB = 0;
	PORTD = 0;
	
	PORTB |= KNIFE_2_OPEN;
	_delay_ms(2500);
	PORTB |= KNIFE_1_CLOSE;
	_delay_ms(2500);
	PORTB |= KNIFE_3_CLOSE;
	_delay_ms(7500);
	
	PORTB = 0;
	PORTD = 0;
	
	led_blink = 0;
	PORTC &= LED_BUTTON_OFF;
	PORTC |= LED_BUTTON_1;
}

void timer_init()
{
	TCCR1A = TCCR1B = 0;
	TCCR1B = (1<<WGM12) | (1<<CS10);
	OCR1AH = 0b00010111;
	OCR1AL = 0b01110000;
		
	//timer blink LED
	TCCR0 = 0;
	TCCR0 = (1<<WGM01)|(1<<CS02)|(1<<CS00);
	OCR0 = 0b11111111;
	
	TIMSK |= (1<<OCIE0) | (1<<OCIE1A);
}

ISR (TIMER0_COMP_vect)//blink LED
{
	if(count_led_blink > DELAY_BLINK_LED){
		switch (led_blink){
			case 1:
			if(!(PINC&LED_BUTTON_1)){
				PORTC &= LED_BUTTON_OFF;
				PORTC |= LED_BUTTON_1;
			}
			else
				PORTC ^= LED_BUTTON_1;
			break;
		
			case 2:
			if(!(PINC&LED_BUTTON_2)){
				PORTC &= LED_BUTTON_OFF;
				PORTC |= LED_BUTTON_2;
			}
			else
				PORTC &= LED_BUTTON_OFF;
			break;
		
			case 3:
			if(!(PINC&LED_BUTTON_3)){
				PORTC &= LED_BUTTON_OFF;				
				PORTC |= LED_BUTTON_3;				
			}
			else
				PORTC &= LED_BUTTON_OFF;
			break;
			
			case 4:
			if(!(PINC&LED_BUTTON_1)){
				PORTC &= LED_BUTTON_OFF;
				PORTC |= LED_BUTTON_1;
				PORTC |= LED_BUTTON_2;
				PORTC |= LED_BUTTON_3;
			}
			else{
				PORTC &= LED_BUTTON_OFF;
			}
			break;	
		}
		count_led_blink = 0;		
	}else{
		count_led_blink++;
	}
}

ISR (TIMER1_COMPA_vect)
{	
	float overload;
	
	overload = ADC_result();
	switch_ADC(num_ADC);	
	
	//protection
	if(ADC_ON){
		if(overload > MAX_A_ADC[num_ADC]){
			if(counter_ADC[num_ADC] < MAX_COUNT_ADC){
			counter_ADC[num_ADC]++;
			}
			else{
				PORTB = 0;
				PORTC = 0;
				PORTD = 0;
				
				PORTB |= KNIFE_2_OPEN;
				_delay_ms(2500);
				PORTB |= KNIFE_1_OPEN;
				_delay_ms(2500);
				PORTD |= KNIFE_3_OPEN;
			
				_delay_ms(8000);
			
				while(1){
					PORTC |= LED_BUTTON_3;
					_delay_ms(500);
					PORTC = 0;
					_delay_ms(500);
				}
			}
		}
		else{
			counter_ADC[num_ADC] = 0;
		}
	
		if(num_ADC < 2){
			num_ADC++;
		}
		else{
			num_ADC = 0;
		}		
	}

	//count button		
	if (!(PINC&BUTTON_1)){
		if(button_1_count < MAX_COUNT_BUTTON){
			button_1_count++;
		}
	}
	else{
		button_1_count = 0;
	}
	
	if (!(PINC&BUTTON_2)){
		if(button_2_count < MAX_COUNT_BUTTON){
			button_2_count++;
		}
	}
	else{
		button_2_count = 0;
	}
	
	if (!(PINC&BUTTON_3)){
		if(button_3_count < MAX_COUNT_BUTTON){
			button_3_count++;
		}
		else{		
			PORTB = 0;
			PORTD = 0;			
			PORTC &= LED_BUTTON_OFF;
			
			PORTB |= KNIFE_2_OPEN;
			_delay_ms(500);
			PORTB |= KNIFE_1_OPEN;
			_delay_ms(500);
			PORTD |= KNIFE_3_OPEN;
			
			while (1)			
			{
				PORTC |= LED_BUTTON_3;
				_delay_ms(500);
				PORTC &= LED_BUTTON_OFF;
				_delay_ms(500);
			}
		}
	}
	else{
		button_3_count = 0;
	}
}