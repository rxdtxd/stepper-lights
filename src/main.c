// main.c
// stepper-lights

#include "main.h"

#include <util/delay.h>

#include "iocontrol.h"
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
	/* output_low(MOTORS_PORT,MOTOR0_STEP); */
	/* delay(42); */
	/* output_high(MOTORS_PORT,MOTOR0_STEP); */
	/* delay(42); */

	// TODO: func() read into shift registers from buttons
	shiftreg_mode_load();
	_delay_us(0.05); // min 15 ns
	shiftreg_mode_transmit();
	_delay_us(0.05);
	
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
	
	_delay_ms(10);
    }
    
    return 0;
}
