// pin definitions

#ifndef _PINOUT_H_
#define _PINOUT_H_

#include <avr/io.h>

#define F_CPU 16000000UL

// avr gcc fixup - for some reason, pin 7 of port C is not defined
#ifndef DDC7
#define DDC7 7
#endif
#ifndef PORTC7
#define PORTC7 7
#endif

// motor control - data direction
#define MOTOR0_DDR     DDRD
#define MOTOR1_DDR     DDRD
#define MOTOR2_DDR     DDRD
#define MOTOR3_DDR     DDRB
#define MOTOR4_DDR     DDRC

#define MOTOR0_STEP_DD DDD2
#define MOTOR0_DIR_DD  DDD3
#define MOTOR1_STEP_DD DDD4
#define MOTOR1_DIR_DD  DDD5
#define MOTOR2_STEP_DD DDD6
#define MOTOR2_DIR_DD  DDD7
#define MOTOR3_STEP_DD DDB0
#define MOTOR3_DIR_DD  DDB1
#define MOTOR4_STEP_DD DDC6
#define MOTOR4_DIR_DD  DDC7

// motor control - output ports
#define MOTOR0_PORT    PORTD
#define MOTOR1_PORT    PORTD
#define MOTOR2_PORT    PORTD
#define MOTOR3_PORT    PORTB
#define MOTOR4_PORT    PORTC

#define MOTOR0_STEP    PORTD2  // D2
#define MOTOR0_DIR     PORTD3  // D3
#define MOTOR1_STEP    PORTD4  // D4
#define MOTOR1_DIR     PORTD5  // D5
#define MOTOR2_STEP    PORTD6  // D6
#define MOTOR2_DIR     PORTD7  // D7
#define MOTOR3_STEP    PORTB0  // D8
#define MOTOR3_DIR     PORTB1  // D9
#define MOTOR4_STEP    PORTC6  // A6
#define MOTOR4_DIR     PORTC7  // A7

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
