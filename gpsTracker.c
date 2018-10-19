#include <msp430.h>
#include "spi.h"
#include "nrf.h"

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    uint8_t data[] = {0x13};
    uint8_t len = 1;
    NRF_init();
    while(1){
        NRF_transmit(data, len);
    }
}
