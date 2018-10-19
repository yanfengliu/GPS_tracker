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
    P2SEL0 = 0b01100000; // activate P2.5, 2.6 primary function
    P2DIR |= BIT6; // set P2.6 as output
    P2DIR &= ~BIT5; // set P2.5 as input
}

uint8_t UART_read()
{
    while(UCA1IFG & 0x0001 == 0x0000)
    {

    }
    uint16_t full_val = UCA1RXBUF & 0xFFFF;
    uint8_t val = UCA1RXBUF & 0x00FF;
    return val;
}

void UART_write(uint8_t val)
{
    UCA1TXBUF = val;
    while(UCA1IFG & 0x0002 == 0x0000)
    {

    }
}
