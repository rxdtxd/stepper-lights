// 

#include "main.h"

//#include <inttypes.h>
//#include <avr/interrupt.h>

#include "iocontrol.h"
#include "fakedelay.h"


int main (void) {
    set_output(MOTORS_DDR,MOTOR0_STEP_DD);
    set_output(MOTORS_DDR,MOTOR0_DIR_DD);

    output_low(MOTORS_PORT,MOTOR0_STEP);
    output_low(MOTORS_PORT,MOTOR0_DIR);

    while (1) {
	output_low(MOTORS_PORT,MOTOR0_STEP);
	delay(42);
	output_high(MOTORS_PORT,MOTOR0_STEP);
	delay(42);
    }
    
    return 0;
}
