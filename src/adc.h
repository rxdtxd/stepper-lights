// adc.h
// analog-to-digital converter

#ifndef _ADC_H_
#define _ADC_H_

#include <avr/io.h>

// either convert once; or start free running mode
#define adc_start() ADCSRA |= _BV(ADSC)

// ADMUX contains settings, so mask in carefully
#define adc_select_chan(chan) ADMUX = (ADMUX & 0b11100000) | (chan & 0b00001111)

// 
#define adc_is_running() ADCSRA & _BV(ADSC)

// set up ADC hardware
void adc_init (void);

// read one value
uint16_t adc_read (uint8_t);

#endif /* _ADC_H_ */
