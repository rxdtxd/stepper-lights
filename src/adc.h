// adc.h
// analog-to-digital converter

#ifndef _ADC_H_
#define _ADC_H_

#include <avr/io.h>

// either convert once; or start free running mode
#define adc_start() ADCSRA |= _BV(ADSC)

// ADMUX contains settings, so mask in carefully
#define adc_set_chan(chan) ADMUX = (ADMUX & 0b11100000) | (chan & 0b00001111)

#define adc_get_chan() ADMUX & 0b00001111

// 
#define adc_is_running() ADCSRA & _BV(ADSC)

//
#define adc_get() ADC

// set up ADC hardware
void adc_init (void);

// blocking-read wrapper
uint16_t adc_read (uint8_t);

#endif /* _ADC_H_ */
