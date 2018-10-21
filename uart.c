/*
 * UART.c
 *
 *  Created on: Oct 18, 2018
 *      Author: yliu60
 */
#include <msp430.h>
#include <stdint.h>
#include "uart.h"
#include <stdio.h>
#include <string.h>

void UART_init()
{
    __enable_interrupt();
    UCA1CTLW0 = UCSWRST; // reset USCI_A
//    UCA1CTLW0 = 0b0010000010000001;
    UCA1CTLW0 = UCSSEL__SMCLK | UCSWRST; // no parity; MSB first; 8-bit; 1 stop bit; UART; async; SMCLK;
    UCA1BRW = 0x0006; // UCBR = 6
    UCA1MCTLW = 0x2080 | UCOS16; // UCBRF = 9; UCBRS = 0x20, UCOS16 = true (16x oversampling)


    P2SEL1 = 0x00;
    P2SEL0 = BIT5 | BIT6; // activate P2.5, 2.6 primary function
//    P2DIR &= ~BIT5; // set P2.5 as input
//    P2DIR |= BIT6; // set P2.6 as output
//    P2OUT &= 0x00; // clear outputs
    UCA1CTLW0 &= ~UCSWRST; // clear the bit to start UART
}

int fputc(int _c, register FILE *_fp)
{
    UART_write(_c);
}

int fputs(const char *_ptr, register FILE *_fp)
{

    int len = strlen(_ptr);
    int i;
    for(i=0; i<len;i++)
        UART_write(_ptr[i]);
}

uint8_t UART_read()
{
    while(UCA1IFG & UCRXIFG == 0)
    {

    }
    uint8_t val = UCA1RXBUF & 0x00FF;
    return val;
}

void UART_write(uint8_t val)
{
    UCA1IFG &= !UCTXCPTIFG;
    UCA1TXBUF = val;
    while(!(UCA1IFG & UCTXCPTIFG))
    {

    }
}
