// main.c
// stepper-lights

#include "pinout.h"

#include <util/delay.h>

#include "adc.h"
#include "iocontrol.h"
#include "spi.h"


// FIXME: move elsewhere
// FIXME: cycle overhead is huge for _delay_us()
void fakedelay (uint16_t times) {
    uint16_t i;
    for (i = 0; i < times; i++) {
	_delay_us(1); // FIXME: magicnum
    }
    return;
}


int main (void) {
    uint8_t i;
    uint16_t motorspeed;
    uint8_t buttonsup, buttonsdown;
    
    leds_init();
    spi_init();
    adc_init();
    
    // TODO: motors_init()
    set_output(MOTORS_DDR, MOTOR0_STEP_DD);
    set_output(MOTORS_DDR, MOTOR0_DIR_DD);
    output_low(MOTORS_PORT, MOTOR0_STEP);
    output_low(MOTORS_PORT, MOTOR0_DIR);

    // TODO: testing, remove
    set_input(MOTORS_DDR, MOTOR0_UP_DD);
    set_input(MOTORS_DDR, MOTOR0_DOWN_DD);
    
    while (1) {
	motorspeed = adc_read(6);

	buttonsup = MOTOR0_PIN & _BV(MOTOR0_UP);
	buttonsdown = MOTOR0_PIN & _BV(MOTOR0_DOWN);

	// debug
	if (buttonsup > 0) {
	    led_on(0);
	} else {
	    led_off(0);
	}
	if (buttonsdown > 0) {
	    led_on(1);
	} else {
	    led_off(1);
	}

	// FIXME: set dir
	if ((buttonsup > 0) && (buttonsdown == 0)) {
	    output_low(MOTORS_PORT, MOTOR0_DIR);
	}
	if ((buttonsup == 0) && (buttonsdown > 0)) {
	    output_high(MOTORS_PORT, MOTOR0_DIR);
	}
	
	// roll motor
	if ((buttonsup>0) != (buttonsdown>0)) {
	    for (i = 0; i < 255; i++) { // FIXME: 255 = max uint8_t
		output_high(MOTORS_PORT,MOTOR0_STEP);
		fakedelay(motorspeed);
		output_low(MOTORS_PORT,MOTOR0_STEP);
		fakedelay(motorspeed);
	    }
	}
        
	// TODO: func() read into shift registers from buttons
	shiftreg_mode_load();
	_delay_us(0.05); // 165 datasheet says 15 ns minimum
	shiftreg_mode_transmit();
	_delay_us(0.05);
	
	/* // read from shift registers into microcontroller */
	/* buttons_up = spi_transmit(SPI_TRANSMIT_DUMMY); */
	/* buttons_down = spi_transmit(SPI_TRANSMIT_DUMMY); */
    }
    
    return 0;
}
