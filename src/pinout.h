// pin definitions

#ifndef _PINOUT_H_
#define _PINOUT_H_

#include <avr/io.h>

#define F_CPU 16000000UL

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
// FIXME: testing, change to proper
/* #define MOTOR0_UP_DD   DDD6 */
/* #define MOTOR0_DOWN_DD DDD7 */
/* #define MOTOR0_PIN     PIND */
/* #define MOTOR0_UP      PIND6 */
/* #define MOTOR0_DOWN    PIND7 */

// leds
#define LED_DDR DDRC
#define LED_DD DDC5

#define LED_PORT PORTC
#define LEDBASE  PORTC5  // A5

// TODO: move to iocontrol.h?
#define led_init()   LED_DDR |= _BV(LED_DD)
#define led_on()     LED_PORT &= ~(_BV( LEDBASE ))
#define led_off()    LED_PORT |=   _BV( LEDBASE )
#define led_toggle() LED_PORT ^=   _BV( LEDBASE )

// using SPI to read in shift registers (165s)
#define SPI_DDR      DDRB
#define SPI_SS_DD    DDB2    // ~ slave select
#define SPI_MOSI_DD  DDB3    // 
#define SPI_MISO_DD  DDB4    // 
#define SPI_SCK_DD   DDB5    // clock

#define SPI_PORT     PORTB
#define SPI_SS       PORTB2  // D10
#define SPI_MOSI     PORTB3  // D11
#define SPI_SCK      PORTB5  // D13

#define SPI_PIN      PINB
#define SPI_MISO     PINB4   // D12


#endif /* _PINOUT_H_ */
