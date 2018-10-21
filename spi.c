/*
 * spi.c
 *
 *  Created on: Oct 17, 2018
 *      Author: yliu60
 */
#include <msp430.h>
#include "spi.h"

void SPI_init()
{
    // to activate previously configured port settings
    UCA0CTL1 = UCSWRST; // reset USCI_A
    // initialize USCI registers
    UCA0CTLW0 = 0b1010101110000011;
    UCA0IE |= 0x03;
    // configure ports
    P1SEL0 = 0b01110000; // P1.4, 1.5, 1.6 primary function (SPI)
    // clear USCWRST and initiate SPI transmit and receive
    UCA0CTL1 &= ~UCSWRST;
    // pick CS
    P1DIR |= BIT1; // P1.1 as Chip Select (CS)
    // start high
    P1OUT |= BIT1;
    // set P1.5 as input for MISO
    P1DIR &= ~BIT5;
}

uint8_t SPI_transfer(uint8_t value)
{
    // write to USCI_A transmit buffer and start transmitting
    UCA0TXBUF = value;
    while(UCB0STATW & UCBUSY == UCBUSY){
        // wait for UCTXIFG to be set, which means the transmitter is ready
        // for the next byte. Data written to UCxTXBUF when UCTXIFG = 0 may
        // result in erroneous data transmission.
    }
    return UCA0RXBUF;
}

void SPI_csLow()
{
    P1OUT &= ~BIT1;
}

void SPI_csHigh()
{
    P1OUT |= BIT1;
}
