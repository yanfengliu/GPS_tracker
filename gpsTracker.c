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
    RTC_init();

    // initialize variables
    uint8_t raw_data[50];
    uint8_t data[26];
    uint8_t raw_data_len = 50;
    uint8_t data_len = 26;
    uint8_t i;
    uint8_t j;
    uint8_t GPRMC_start = 19;
    uint8_t GPRMC_end = 44;

    while(1){
        raw_data[0] = UART_read();
        if (raw_data[0] == 0x24){                                   // look for start sign '$'
            for (i = 1; i < raw_data_len; i++){
                raw_data[i] = UART_read();                          // read in enough characters to extract latitude and longitude
            }
            if ((raw_data[4] == 'M') && (raw_data[5] == 'C')){      // look for GPRMC format
                j = 0;
                for (i = GPRMC_start; i < GPRMC_end+1; i++){        // read in latitude and longitude from pre-defined locations
                    data[j] = raw_data[i];
                    j = j + 1;
                }
                NRF_transmit(data, data_len);                       // transmit through nRF24L01
            }
        }
    }
}
