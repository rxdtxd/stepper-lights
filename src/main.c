// main.c
// stepper-lights

#include "pinout.h"

#include <stdbool.h>
#include <util/delay.h>

#include "adc.h"
#include "iocontrol.h"
#include "spi.h"
#include "uart.h"


// FIXME: move to separate file for reuse
// FIXME: cycle overhead is huge for _delay_us()
void fakedelay (uint16_t times) {
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
}

inline void motor_step (uint8_t motor, uint16_t speed) {
    uint8_t i;
    uint8_t port, pin;
    uint32_t tmp;

    // FIXME: unneeded indirection, factor into macro?..
    if (motor > 4) return;
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
    
    // debug
    //printf("motor %u pulse delay: %u\n", motor, speed);

    for (i = 0; i < 10; i++) { // FIXME: magicnum
	output_high(port, pin);
	fakedelay(speed);
	output_low(port, pin);
	fakedelay(speed);
    }
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


uint8_t main (void) {
    uint8_t motor;
    uint8_t port, pin;
    uint16_t speed[5];
    uint8_t buttonsup, buttonsdown;
    
    led_init();
    spi_init();
    adc_init();
    motors_init();

    led_off();
    
    // debug
    uart_init();
    stdout = &uart_output;
    
    while (1) {
	//led_off();
	// TODO: func()
	// read from buttons into shift registers
	shiftreg_mode_load();
	_delay_us(0.05); // 165 datasheet says 15 ns minimum
	shiftreg_mode_transmit();
	_delay_us(0.05);
	
	// read from shift registers into microcontroller
	buttonsup = spi_transmit(SPI_TRANSMIT_DUMMY);
	buttonsdown = spi_transmit(SPI_TRANSMIT_DUMMY);

	// debug
	//printf("up %u down %u\n", buttonsup, buttonsdown);

	led_off();
	for (motor = 0; motor < 5; motor++) {
	    // debug
	    //printf("%u\n", pressed(buttonsup, motor) ? 1 : 0);
	    //printf("%u\n", pressed(buttonsdown,motor) ? 1 : 0);

	    speed[motor] = adc_read(motor);

	    // debug
	    printf("MOTOR%u speed: %u\n", motor, speed[motor]);

	    // TODO: similar in motor_step(), so refactor
	    if (motor == 0) { port = MOTOR0_PORT; pin = MOTOR0_DIR; }
	    if (motor == 1) { port = MOTOR1_PORT; pin = MOTOR1_DIR; }
	    if (motor == 2) { port = MOTOR2_PORT; pin = MOTOR2_DIR; }
	    if (motor == 3) { port = MOTOR3_PORT; pin = MOTOR3_DIR; }
	    if (motor == 4) { port = MOTOR4_PORT; pin = MOTOR4_DIR; }
	    
	    // set dir
	    // TODO: buttons{up,down} check functions
	    // TODO: set_dir() functions
	    if (pressed(buttonsup, motor) &&
		pressed(buttonsdown, motor)) {
		led_on();
	    } else if (pressed(buttonsup, motor) &&
		       !(pressed(buttonsdown, motor))) {
		output_low(port, pin);
	    } else if (!(pressed(buttonsup, motor)) &&
		       pressed(buttonsdown, motor)) {
		output_high(port, pin);
	    }
	    
	    // roll motor
	    if (pressed(buttonsup, motor) !=
		pressed(buttonsdown, motor)) {
		motor_step(motor, speed[motor]);
	    }
	}
    }    
    return 0;
}
