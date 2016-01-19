// spi.h
// SPI communications: read buttons

#ifndef _SPI_H_
#define _SPI_H_

#include <inttypes.h>

#include "pinout.h"
#include "iocontrol.h" // TODO: using output_high(), don't

// data to transmit if you only really want to read data
#define SPI_TRANSMIT_DUMMY 0b01010101

// shift register PL (parallel load) line operation
#define shiftreg_mode_load()     output_low(SPI_PORT, SPI_SS)
#define shiftreg_mode_transmit() output_high(SPI_PORT, SPI_SS)

// configure i/o for proper spi transmissions
inline void spi_init (void) {

    // MOSI, SCK, ~SS are outputs, MISO remains input
    SPI_DDR |= _BV(SPI_MOSI_DD) | _BV(SPI_SCK_DD) | _BV(SPI_SS_DD);
    /* set_output(SPI_DDR, SPI_MOSI_DD); */
    /* set_output(SPI_DDR, SPI_SCK_DD); */
    /* set_output(SPI_DDR, SPI_SS_DD); */
    
    output_high(SPI_PORT, SPI_SS);  // ~SS inactive

    // Enable SPI, Master, SCK=fosc/128
    // TODO: increase SCK
    SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR1) | _BV(SPR0);
    // polarity/phase for reading 165
    SPCR |= _BV(CPOL) /* | _BV(CPHA) */;
    // LSB first
    SPCR |= _BV(DORD);
}

// send and/or receive data
uint8_t spi_transmit (uint8_t data);


#endif /* _SPI_H_ */
