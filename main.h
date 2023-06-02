#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "adc.h"

#define BUTTON_1      (1<<PINC0)
#define BUTTON_2      (1<<PINC1)
#define BUTTON_3      (1<<PINC2)

#define LED_BUTTON_1  (1<<PORTC3)
#define LED_BUTTON_2  (1<<PORTC4)
#define LED_BUTTON_3  (1<<PORTC5)
#define LED_BUTTON_OFF  ~(LED_BUTTON_1|LED_BUTTON_2|LED_BUTTON_3)

#define KNIFE_1_CLOSE (1<<PORTB0)
#define KNIFE_1_OPEN  (1<<PORTB1)
#define KNIFE_2_CLOSE (1<<PORTB2)
#define KNIFE_2_OPEN  (1<<PORTB3)
#define KNIFE_3_CLOSE (1<<PORTB4)

#define KNIFE_3_OPEN  (1<<PORTD4)

#define ADC_ON 1
#define ADC_OFF 0

#define MAX_COUNT_ADC 100

#define MAX_A_DOWN 0.08
#define MAX_A_UP 0.08
#define MAX_A_MID 1.0

#define DELAY_BLINK_LED 30

void timer_init();
void purka_init();