// main.h
// pin definitions

#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>

// motor control - data direction
#define MOTORS_DDR DDRD
#define MOTOR0_STEP_DD DD3
#define MOTOR0_DIR_DD DDD4
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
#define MOTOR0_STEP PD3
#define MOTOR0_DIR PD4
//#define MOTOR1_STEP PD?
//#define MOTOR1_DIR PD?
//#define MOTOR2_STEP PD?
//#define MOTOR2_DIR PD?
//#define MOTOR3_STEP PD?
//#define MOTOR3_DIR PD?
//#define MOTOR4_STEP PD?
//#define MOTOR4_DIR PD?

#endif // #define _MAIN_H_
