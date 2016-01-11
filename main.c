// 

//#include <inttypes.h>
#include <avr/io.h>
//#include <avr/interrupt.h>

#include "iocontrol.h"
#include "fakedelay.h"


int main (void) {
    // step
    set_output(DDRD,DDD3);
    // dir
    set_output(DDRD,DDD4);

    output_low(PORTD,PD3);
    output_low(PORTD,PD4);

    while (1) {
	output_low(PORTD,PD3);
	delay(42);
	output_high(PORTD,PD3);
	delay(42);
    }
    
    return 0;
}
