// main.c
// stepper-lights

#include "pinout.h"

#include <stdbool.h>
#include <util/delay.h>

#include "adc.h"
#include "iocontrol.h"
#include "spi.h"
/* #include "uart.h" // debug terminal */


// FIXME: move to separate file for reuse
// FIXME: cycle overhead is huge for _delay_us()
void fake_delay (uint16_t times) {
    volatile uint16_t i;
    for (i = 0; i < times; i++) {
	// NOTE: DRV8825 datasheet specifies 4 us minimum step period,
	// and 1.9 us minimum for either STEP high or STEP low
	_delay_us(1); // FIXME: magicnum
    }
    return;
}

inline void motors_init (void) {
    set_output(MOTOR0_DDR, MOTOR0_STEP_DD);
    set_output(MOTOR0_DDR, MOTOR0_DIR_DD);
    output_low(MOTOR0_PORT, MOTOR0_STEP);
    output_low(MOTOR0_PORT, MOTOR0_DIR);

    set_output(MOTOR1_DDR, MOTOR1_STEP_DD);
    set_output(MOTOR1_DDR, MOTOR1_DIR_DD);
    output_low(MOTOR1_PORT, MOTOR1_STEP);
    output_low(MOTOR1_PORT, MOTOR1_DIR);

    set_output(MOTOR2_DDR, MOTOR2_STEP_DD);
    set_output(MOTOR2_DDR, MOTOR2_DIR_DD);
    output_low(MOTOR2_PORT, MOTOR2_STEP);
    output_low(MOTOR2_PORT, MOTOR2_DIR);

    set_output(MOTOR3_DDR, MOTOR3_STEP_DD);
    set_output(MOTOR3_DDR, MOTOR3_DIR_DD);
    output_low(MOTOR3_PORT, MOTOR3_STEP);
    output_low(MOTOR3_PORT, MOTOR3_DIR);

    set_output(MOTOR4_DDR, MOTOR4_STEP_DD);
    set_output(MOTOR4_DDR, MOTOR4_DIR_DD);
    output_low(MOTOR4_PORT, MOTOR4_STEP);
    output_low(MOTOR4_PORT, MOTOR4_DIR);

    return;
}

inline void motor_set_dir (uint8_t motor, uint8_t dir) {
    if (dir == 0) {
	if (motor == 0) { output_low(MOTOR0_PORT, MOTOR0_DIR); }
	if (motor == 1) { output_low(MOTOR1_PORT, MOTOR1_DIR); }
	if (motor == 2) { output_low(MOTOR2_PORT, MOTOR2_DIR); }
	if (motor == 3) { output_low(MOTOR3_PORT, MOTOR3_DIR); }
	if (motor == 4) { output_low(MOTOR4_PORT, MOTOR4_DIR); }
    } else {
	if (motor == 0) { output_high(MOTOR0_PORT, MOTOR0_DIR); }
	if (motor == 1) { output_high(MOTOR1_PORT, MOTOR1_DIR); }
	if (motor == 2) { output_high(MOTOR2_PORT, MOTOR2_DIR); }
	if (motor == 3) { output_high(MOTOR3_PORT, MOTOR3_DIR); }
	if (motor == 4) { output_high(MOTOR4_PORT, MOTOR4_DIR); }
    }
    
    return;
}

inline void motor_step (uint8_t motor, uint16_t speed) {
    uint8_t i;
    uint8_t port, pin;
    uint32_t tmp;

    // FIXME: unneeded indirection, factor into macro?..
    if (motor == 0) { port = MOTOR0_PORT; pin = MOTOR0_STEP; }
    if (motor == 1) { port = MOTOR1_PORT; pin = MOTOR1_STEP; }
    if (motor == 2) { port = MOTOR2_PORT; pin = MOTOR2_STEP; }
    if (motor == 3) { port = MOTOR3_PORT; pin = MOTOR3_STEP; }
    if (motor == 4) { port = MOTOR4_PORT; pin = MOTOR4_STEP; }

    // avoid stepper resonance regions (determined experimentally)
#define SPEEDMIN 20 //135
#define SPEEDMAX 1023 //800
#define SPEEDRANGE (SPEEDMAX-SPEEDMIN)
    tmp = (uint32_t)speed * SPEEDRANGE;
    speed = SPEEDMIN + (uint16_t)(tmp / 1023);
    
    for (i = 0; i < 10; i++) { // FIXME: magicnum
	output_high(port, pin);
	fake_delay(speed);
	output_low(port, pin);
	fake_delay(speed);
    }
    return;
}

inline void shiftreg_load (void) {
    output_low(SPI_PORT, SPI_SS);
    _delay_us(0.05); // 74165's datasheet says 15 ns minimum
    output_high(SPI_PORT, SPI_SS);
    _delay_us(0.05);
    
    return;
}

// didn't work as a #define, probably optimizer's fault
inline bool pressed (uint8_t buttons, uint8_t motor) {
    if (buttons & _BV(motor)) {
	return true;
    } else {
	return false;
    }
}


int main (void) {
    uint8_t motor;
    uint16_t speed[5];
    uint8_t bu, bd;  // buttons up, buttons down
    
    led_init();
    spi_init();
    adc_init();
    motors_init();

    /* // debug */
    /* uart_init(); */
    /* stdout = &uart_output; */

    while (1) {
	// read from buttons into shift registers ...
	shiftreg_load();
	
	// ... and then microcontroller
	bu = spi_transmit(SPI_TRANSMIT_DUMMY);
	bd = spi_transmit(SPI_TRANSMIT_DUMMY);

	led_off();
	
	for (motor = 0; motor < 5; motor++) {
	    if (pressed(bu, motor) && pressed(bd, motor)) {
		led_on();
		continue;
	    }

	    // HACK: FIXME: first used symbol for arduino nano had
	    // ADC port (PORTC proper, port "A" in weirdoland) reversed,
	    // so had to improvise with jumpers on the board
	    if (motor == 0) speed[motor] = adc_read(6);
	    if (motor == 1) speed[motor] = adc_read(1);
	    if (motor == 2) speed[motor] = adc_read(2);
	    if (motor == 3) speed[motor] = adc_read(3);
	    if (motor == 4) speed[motor] = adc_read(7);
	    
	    // set dir
	    if (pressed(bu, motor) && !pressed(bd, motor)) {
		motor_set_dir(motor, 0); // FIXME: magicnum
	    } else if (!pressed(bu, motor) && pressed(bd, motor)) {
		motor_set_dir(motor, 1); // FIXME: magicnum
	    }
	    
	    // roll
	    if (pressed(bu, motor) != pressed(bd, motor)) {
		motor_step(motor, speed[motor]);
	    }
	}
    }    
    return 0;
}
