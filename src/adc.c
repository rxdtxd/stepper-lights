// adc.c

#include "adc.h"

#include "pinout.h"

#include <inttypes.h>
#include <avr/io.h>


void adc_init (void) {
    // AVCC /w cap @ AREF, left-adjust result (we're using just 8 bits)
    ADMUX |= _BV(REFS0) /* | _BV(ADLAR) */;

    // slow ADC down 128 times (compared to system clock)
    ADCSRA = _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);

    // enable ADC
    ADCSRA |= _BV(ADEN);
}


uint16_t adc_read (uint8_t channel) {
    adc_set_chan(channel);
    adc_start();
    
    while( adc_is_running() );
    return ADC;
}
