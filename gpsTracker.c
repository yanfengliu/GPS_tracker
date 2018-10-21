#include <msp430.h>
#include "spi.h"
#include "nrf.h"
#include "uart.h"

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    uint8_t data[] = {0x13};
    uint8_t len = 1;
    NRF_init();
    UART_init();
    volatile uint16_t i;
    uint8_t val = 0x55;
    while(1){
//        fputs("Hello, world!");
        data[0] = UART_read();
        NRF_transmit(data, len);
//        UART_write(val);
    }
}
