#include <msp430.h>
#include "spi.h"
#include "nrf.h"
#include "uart.h"

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    uint8_t data[] = {0x55};
    uint8_t len = 1;
    NRF_init();
    UART_init();
    volatile uint16_t i;
    while(1){
        data[0] = UART_read();
        NRF_transmit(data, len);
//        UART_write(0x55);
//        for (i=0; i<254; i++){
//
//        }
    }
}
