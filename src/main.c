// main.c
// stepper-lights

#include "pinout.h"

#include <stdbool.h>
#include <util/delay.h>

#include "adc.h"
#include "iocontrol.h"
#include "spi.h"
/* #include "uart.h" // debug terminal */

#define NMOTORS 5

#define SPEEDMIN 10 //20
#define SPEEDMAX 100 //380
#define SPEEDRANGE (SPEEDMAX-SPEEDMIN)

#define DIR_DOWN 0
#define DIR_UP 1

typedef struct {
    bool         isrunning; // whether currently running or not
    uint16_t     position;  // STEPs taken from top (0)
    bool         bu;        // button up pressed
    bool         bd;        // button down pressed
    uint16_t     pot;       // speed pot raw reading
    int16_t      trgspeed;  // target speed
    int16_t      curspeed;  // current speed
    uint16_t     counter;   // countdown timer for STEP phase toggling
} motor_t;


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
	else if (motor == 1) { output_low(MOTOR1_PORT, MOTOR1_DIR); }
	else if (motor == 2) { output_low(MOTOR2_PORT, MOTOR2_DIR); }
	else if (motor == 3) { output_low(MOTOR3_PORT, MOTOR3_DIR); }
	else if (motor == 4) { output_low(MOTOR4_PORT, MOTOR4_DIR); }
    } else {
	if (motor == 0) { output_high(MOTOR0_PORT, MOTOR0_DIR); }
	else if (motor == 1) { output_high(MOTOR1_PORT, MOTOR1_DIR); }
	else if (motor == 2) { output_high(MOTOR2_PORT, MOTOR2_DIR); }
	else if (motor == 3) { output_high(MOTOR3_PORT, MOTOR3_DIR); }
	else if (motor == 4) { output_high(MOTOR4_PORT, MOTOR4_DIR); }
    }
    
    return;
}

// TODO: unused, remove
inline uint16_t motor_read_pot (uint8_t motor) {
    uint16_t pot;
    
    // HACK: FIXME: first used symbol for arduino nano
    // had ADC port (PORTC proper, port "A" in weirdoland)
    // reversed, so had to improvise with jumpers
    if (motor == 0) pot = adc_read(6);
    else if (motor == 1) pot = adc_read(1);
    else if (motor == 2) pot = adc_read(2);
    else if (motor == 3) pot = adc_read(3);
    else if (motor == 4) pot = adc_read(7);

    return pot;
}

// TODO: signed int
inline uint16_t motor_adj_speed (uint16_t speed) {
    uint32_t tmp;

    // avoid stepper resonance regions (determined experimentally)
    tmp = (uint32_t)speed * SPEEDRANGE;
    speed = SPEEDMIN + (uint16_t)(tmp / 1023);
    
    return speed;
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
    _delay_us(0.02); // 74165's datasheet says 15 ns minimum
    output_high(SPI_PORT, SPI_SS);
    _delay_us(0.02);
    
    return;
}

// didn't work as a #define, probably optimizer's fault
// TODO: replace with bit_is_set(byte, bit)
inline bool pressed (uint8_t buttons, uint8_t motor) {
    if (buttons & _BV(motor)) {
	return true;
    } else {
	return false;
    }
}


int main (void) {
    uint8_t bu, bd;      // buttons up, buttons down (read-in buffers)
    uint8_t i;           // iterator
    uint8_t ramp, cycle; // iterators
    uint8_t adcchan = 0;
    
    motor_t motor[NMOTORS];

    for (i = 0; i < NMOTORS; i++) {
	motor[i].isrunning = false;
	motor[i].position = 0;
	motor[i].bu = false;
	motor[i].bd = false;
	motor[i].pot = 0;
	motor[i].trgspeed = 0;
	motor[i].curspeed = 0;
	motor[i].counter = 0;
    }
    
    led_init();
    spi_init();
    adc_init();
    motors_init();

    /* // debug */
    /* uart_init(); */
    /* stdout = &uart_output; */

    adc_set_chan(adcchan);
    adc_start();

    while (1) {
	// keep the ADC running "in background"
	if ( !( adc_is_running() )) {
	    motor[adcchan].pot = adc_get();
	    motor[adcchan].trgspeed =
		motor_adj_speed(motor[adcchan].pot);

	    adcchan++;
	    if (adcchan >= 5) adcchan = 0;

	    // HACK with lame pins
	    if (adcchan == 0) adc_set_chan(6);
	    if (adcchan == 1) adc_set_chan(1);
	    if (adcchan == 2) adc_set_chan(2);
	    if (adcchan == 3) adc_set_chan(3);
	    if (adcchan == 4) adc_set_chan(7);

	    adc_start();
	}

	// read in buttons
	shiftreg_load();
	bu = spi_transmit(SPI_TRANSMIT_DUMMY);
	bd = spi_transmit(SPI_TRANSMIT_DUMMY);
	for (i = 0; i < NMOTORS; i++) {
	    motor[i].bu = pressed(bu, i) ? true : false;
	    motor[i].bd = pressed(bd, i) ? true : false;
	}
	
	led_off();

	for (ramp = 0; ramp < 16; ramp++) {
	    for (cycle = 0; cycle < 255; cycle++) {
		for (i = 0; i < NMOTORS; i++) {		
		    // both buttons pressed
		    if (motor[i].bu && motor[i].bd) {
			led_on();
			motor[i].trgspeed = 0;
		    }
		    
		    // either button pressed
		    if (motor[i].bu != motor[i].bd) {
			if (motor[i].counter > 0) {
			    motor[i].counter -= 1;
			} else {
			    // reset counter
			    motor[i].counter = motor[i].curspeed;
			    
			    // set dir
			    if (motor[i].bu) {
				motor_set_dir(i, DIR_UP);
			    } else /* if (motor[i].bd) */ {
				motor_set_dir(i, DIR_DOWN);
			    }
			    
			    motor_step(i);
			}
		    }
		}
	    }
	}
    }    
    return 0;
}
