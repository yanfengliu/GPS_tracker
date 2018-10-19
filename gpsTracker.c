#include <msp430.h>
#include "spi.h"
#include "nrf.h"

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    uint8_t data[] = {0x55};
    uint8_t len = 1;
    NRF_init();
    volatile uint8_t i;
    while(1){
        // data[0] = UART_read();
        NRF_transmit(data, len);
        for (i=0; i<10000; i++){

        }
    }
}
