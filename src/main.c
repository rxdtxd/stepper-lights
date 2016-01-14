// 

#include "main.h"

//#include <inttypes.h>
//#include <avr/interrupt.h>

#include "iocontrol.h"
#include "fakedelay.h"
#include "spi.h"


int main (void) {
    uint8_t buttons_up, buttons_down;
    
    leds_init();
    spi_init();
    
    // TODO: motors_init()
    set_output(MOTORS_DDR, MOTOR0_STEP_DD);
    set_output(MOTORS_DDR, MOTOR0_DIR_DD);
    output_low(MOTORS_PORT, MOTOR0_STEP);
    output_low(MOTORS_PORT, MOTOR0_DIR);
    
    while (1) {
	// roll motor
	output_low(MOTORS_PORT,MOTOR0_STEP);
	delay(42);
	output_high(MOTORS_PORT,MOTOR0_STEP);
	delay(42);

	// read into shift registers from buttons
	shiftreg_mode_load();
	delay(1);
	shiftreg_mode_transmit();
	delay(1);
	// read from shift registers into microcontroller
	buttons_up = spi_transmit(SPI_TRANSMIT_DUMMY);
	buttons_down = spi_transmit(SPI_TRANSMIT_DUMMY);

	if (buttons_up > 0) {
	    led_on(0);
	} else {
	    led_off(0);
	}

	if (buttons_down > 0) {
	    led_on(1);
	} else {
	    led_off(1);
	}
	
	// sleep
	delay(42);
    }
    
    return 0;
}
