#include <msp430.h>
#include "spi.h"
#include "nrf.h"
#include "uart.h"

void main(void) {
    // system initialization
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
    NRF_init();
    UART_init();

    // initialize variables
    uint8_t raw_data[50];
    uint8_t data[26];
    uint8_t raw_data_len = 50;
    uint8_t data_len = 26;
    uint8_t i;
    uint8_t j;
    uint8_t GPGGA_start = 19;
    uint8_t GPGGA_end = 44;

    while(1){
        raw_data[0] = UART_read();
        if (raw_data[0] == 0x24){                                   // look for start sign '$'
            for (i = 1; i < raw_data_len; i++){
                raw_data[i] = UART_read();                          // read in enough characters to extra latitude and longitude
            }
            if ((raw_data[4] == 'M') && (raw_data[5] == 'C')){      // speccifically look for GPRMC format
                j = 0;
                for (i = GPGGA_start; i < GPGGA_end+1; i++){        // only read in latitude and longitude information
                    data[j] = raw_data[i];
                    j = j + 1;
                }
                NRF_transmit(data, data_len);                       // transmit through nRF24L01
            }
        }
    }
}
