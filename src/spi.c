// spi.c

#include "spi.h"

uint8_t spi_transmit (uint8_t data) {
    SPDR = data;                  // start transmission
    while( !(SPSR & _BV(SPIF)) ); // wait for transmission complete 
    return SPDR;
}

