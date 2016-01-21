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
    volatile uint16_t i;
    for (i = 0; i < times; i++) {
	_delay_us(1); // FIXME: magicnum
    }
    return;
}


inline void motor_step (uint8_t motor, uint16_t speed) {
    uint8_t i;
    uint8_t motorpin;

    // FIXME: due to pinout motorport will have to be set, too
    if (motor > 4) return;
    if (motor == 0) motorpin = MOTOR0_STEP;
    /* if (motor == 1) motorpin = MOTOR1_STEP; */
    /* if (motor == 2) motorpin = MOTOR2_STEP; */
    /* if (motor == 3) motorpin = MOTOR3_STEP; */
    /* if (motor == 4) motorpin = MOTOR4_STEP; */
	
    for (i = 0; i < 255; i++) { // FIXME: 255 = maxval uint8_t
	output_high(MOTORS_PORT,motorpin);
	fakedelay(speed);
	output_low(MOTORS_PORT,motorpin);
	fakedelay(speed);
    }
    return;
}


int main (void) {
    uint8_t i;
    uint16_t speed;
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
	speed = adc_read(6);  // FIXME: iterate through 5 ADC pins

	// debug (1 chan)
	buttonsup = MOTOR0_PIN & _BV(MOTOR0_UP);
	buttonsdown = MOTOR0_PIN & _BV(MOTOR0_DOWN);

	/* // TODO: func() read into shift registers from buttons */
	/* shiftreg_mode_load(); */
	/* _delay_us(0.05); // 165 datasheet says 15 ns minimum */
	/* shiftreg_mode_transmit(); */
	/* _delay_us(0.05); */
	
	/* // read from shift registers into microcontroller */
	/* buttonsup = spi_transmit(SPI_TRANSMIT_DUMMY); */
	/* buttonsdown = spi_transmit(SPI_TRANSMIT_DUMMY); */
	
	// set dir
	// FIXME: buttons{up,down} check functions
	// FIXME set_dir() functions
	led_off(0);
	if ((buttonsup > 0) && (buttonsdown == 0)) {
	    output_low(MOTORS_PORT, MOTOR0_DIR);
	} else if ((buttonsup == 0) && (buttonsdown > 0)) {
	    output_high(MOTORS_PORT, MOTOR0_DIR);
	} else if ((buttonsup > 0) && (buttonsdown > 0)) {
	    led_on(0);
	}
	
	// roll motor
	if ((buttonsup > 0) != (buttonsdown > 0)) {
	    motor_step(0, speed);
	}
    }
    
    return 0;
}
