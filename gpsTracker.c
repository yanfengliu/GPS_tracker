#include <msp430.h>
#include "spi.h"
#include "nrf.h"
#include "uart.h"

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    uint8_t data[32];
    uint8_t len = 32;
    uint8_t i;
    NRF_init();
    UART_init();
    while(1){
        data[0] = UART_read();
        if (data[0] == 0x24){
            for (i = 1; i < 23; i++){
                data[i] = UART_read();
            }
            NRF_transmit(data, len);
        }
    }
}
