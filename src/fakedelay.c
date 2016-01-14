// fakedelay.c
// TODO: replace with true delay

#include "fakedelay.h"

#include <avr/wdt.h>

void delay (uint16_t loops) {
    uint16_t delay_count = 1000;
    volatile uint16_t i;

    while (loops != 0) {
	for (i = 0; i != delay_count; i++) wdt_reset();
	loops--;
    }
}
