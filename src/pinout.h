// pin definitions

#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>

#define F_CPU 16000000

// motor control - data direction
#define MOTORS_DDR DDRD
#define MOTOR0_STEP_DD DDD2
#define MOTOR0_DIR_DD DDD3
//#define MOTOR1_STEP_DD DDD?
//#define MOTOR1_DIR_DD DDD?
//#define MOTOR2_STEP_DD DDD?
//#define MOTOR2_DIR_DD DDD?
//#define MOTOR3_STEP_DD DDD?
//#define MOTOR3_DIR_DD DDD?
//#define MOTOR4_STEP_DD DDD?
//#define MOTOR4_DIR_DD DDD?

// motor control - output ports
#define MOTORS_PORT PORTD
#define MOTOR0_STEP PORTD2 // D3 on arduino
#define MOTOR0_DIR  PORTD3 // D4 on arduino
//#define MOTOR1_STEP PD?
//#define MOTOR1_DIR PD?
//#define MOTOR2_STEP PD?
//#define MOTOR2_DIR PD?
//#define MOTOR3_STEP PD?
//#define MOTOR3_DIR PD?
//#define MOTOR4_STEP PD?
//#define MOTOR4_DIR PD?

// motor buttons
// TODO: testing, remove
#define MOTOR0_UP_DD   DDD6
#define MOTOR0_DOWN_DD DDD7
#define MOTOR0_PIN     PIND
#define MOTOR0_UP      PIND6
#define MOTOR0_DOWN    PIND7

// leds
// TODO: remove unneeded
#define LED_0 0
#define LED_1 1
#define LEDS_DDR DDRD
#define LED0_DDR DDD4
#define LED1_DDR DDD5

#define LEDS_PORT PORTD
#define LEDBASE   PD4

#define leds_init() LEDS_DDR |= _BV(LED0_DDR)|_BV(LED1_DDR)
#define led_on(led)     LEDS_PORT &= ~(_BV( LEDBASE+led ))
#define led_off(led)    LEDS_PORT |=   _BV( LEDBASE+led )
#define led_toggle(led) LEDS_PORT ^=   _BV( LEDBASE+led )


// shift register to read in buttons - uses SPI
/* #define SHIFTREG_DDR     DDRB */
/* #define SHIFTREG_LOAD_DD DDB2 */

/* #define SHIFTREG_PORT PORTB */
/* #define SHIFTREG_LOAD PB2 // D10 on arduino (aka SPI_SS) */

#define SPI_DDR      DDRB
#define SPI_SS_DD    DDB2  // ~ slave select
#define SPI_MOSI_DD  DDB3  // 
#define SPI_MISO_DD  DDB4  // 
#define SPI_SCK_DD   DDB5  // clock

#define SPI_PORT     PORTB
#define SPI_SS       PORTB2   // D10
#define SPI_MOSI     PORTB3   // D11
#define SPI_SCK      PORTB5   // D13

#define SPI_PIN      PINB
#define SPI_MISO     PINB4   // D12


#endif /* _MAIN_H_ */
