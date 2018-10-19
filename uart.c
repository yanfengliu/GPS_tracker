/*
 * UART.c
 *
 *  Created on: Oct 18, 2018
 *      Author: yliu60
 */
#include <msp430.h>
#include <stdint.h>
#include "uart.h"

void UART_init()
{
    UCA1CTLW0 |= 0x0001; // reset USCI_A
    UCA1CTLW0 = 0b0010000010000001; // no parity; MSB first; 8-bit; 1 stop bit; UART; async; SMCLK;
    UCA1BRW = 0x0006; // UCBR = 6
    UCA1MCTLW = 0x2080; // UCBRF = 9; UCBRS = 0x20
    P2SEL1 = 0b01100000; // activate P2.5, 2.6 primary function
}

uint8_t UART_read()
{
    while(UCA1IFG & 0x0001 == 0){

    }
    uint8_t val = UCA1RXBUF & 0x00FF;
    return val;
}
