// main.c
// stepper-lights

#include "pinout.h"

#include <stdbool.h>
#include <util/delay.h>

#include "adc.h"
#include "iocontrol.h"
#include "spi.h"
/* #include "uart.h" // debug terminal */


#define DIR_DOWN 0
#define DIR_UP 1


// motor desired speed and countdown timer for pulsing
uint16_t speed[5]; // TODO: can be factored out
uint16_t counter[5];


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
    if (dir == DIR_DOWN) {
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

inline uint16_t motor_get_speed (uint8_t motor) {
    uint16_t s;
    
    // HACK: FIXME: first used symbol for arduino nano
    // had ADC port (PORTC proper, port "A" in weirdoland)
    // reversed, so had to improvise with jumpers
    if (motor == 0) s = adc_read(6);
    else if (motor == 1) s = adc_read(1);
    else if (motor == 2) s = adc_read(2);
    else if (motor == 3) s = adc_read(3);
    else if (motor == 4) s = adc_read(7);

    return s;
}

inline uint16_t motor_adjust_speed (uint16_t s) {
    uint32_t tmp;

    // avoid stepper resonance regions (determined experimentally)
#define SPEEDMIN 20 //135
#define SPEEDMAX 1023 //800
#define SPEEDRANGE (SPEEDMAX-SPEEDMIN)
    tmp = (uint32_t)s * SPEEDRANGE;
    s = SPEEDMIN + (uint16_t)(tmp / 1023);
    
    return s;
}

inline void motor_step (uint8_t motor) {
    if (motor == 0) { output_toggle(MOTOR0_PORT, MOTOR0_STEP); }
    else if (motor == 1) { output_toggle(MOTOR1_PORT, MOTOR1_STEP); }
    else if (motor == 2) { output_toggle(MOTOR2_PORT, MOTOR2_STEP); }
    else if (motor == 3) { output_toggle(MOTOR3_PORT, MOTOR3_STEP); }
    else if (motor == 4) { output_toggle(MOTOR4_PORT, MOTOR4_STEP); }

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
    uint8_t bu, bd;  // buttons up, buttons down
    
    led_init();
    spi_init();
    adc_init();
    motors_init();

    /* // debug */
    /* uart_init(); */
    /* stdout = &uart_output; */

    for (motor = 0; motor < 5; motor++) {
	counter[motor] = 0;
    }
    
    while (1) {
	// read from buttons into shift registers ...
	shiftreg_load();
	
	// ... and then microcontroller
	bu = spi_transmit(SPI_TRANSMIT_DUMMY);
	bd = spi_transmit(SPI_TRANSMIT_DUMMY);

	led_off();

	for (motor = 0; motor < 5; motor++) {
	    if (!pressed(bu, motor) && !pressed(bd, motor)) {
		continue;
	    }

	    if (pressed(bu, motor) && pressed(bd, motor)) {
		led_on();
		continue;
	    }
	    	    
	    // 
	    if (pressed(bu, motor) != pressed(bd, motor)) {
		if (counter[motor] > 0) {
		    counter[motor] -= 1;
		} else {
		    // reset counter
		    speed[motor] = motor_get_speed(motor);
		    counter[motor] = motor_adjust_speed(speed[motor]);

		    // set dir
		    if (pressed(bu, motor)) {
			motor_set_dir(motor, DIR_UP);
		    } else if (pressed(bd, motor)) {
			motor_set_dir(motor, DIR_DOWN);
		    }

		    motor_step(motor);
		}
	    }
	}
    }    
    return 0;
}
