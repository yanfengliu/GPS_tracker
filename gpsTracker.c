#include <msp430.h>
#include "spi.h"
#include "nrf.h"
#include "uart.h"

uint8_t counter = 0;

void main(void) {
    // system initialization
    WDTCTL = WDTPW | WDTHOLD;                       // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                           // Disable the GPIO power-on default high-impedance mode
    // peripheral init
    P1DIR |= BIT2;
    P1OUT &= ~BIT2;
    P1DIR |= BIT0;
    UART_init();
    NRF_init();

    // timer interrupt init
    __enable_interrupt();                           // enable global interrupts
    // default source of ACLK = 32768 Hz
    TA0CTL = TASSEL_1 | MC_2 | TAIE;                // ACLK; continuous mode; interrupt enabled;

    // variables def
    uint8_t raw_data[50];
    uint8_t data[26];
    uint8_t raw_data_len = 50;
    uint8_t data_len = 26;
    uint8_t i;
    uint8_t j;
    uint8_t GPRMC_start = 19;
    uint8_t GPRMC_end = 44;
    uint8_t correct_format = 0;

    while(1){
        if (counter % 10 == 0){
            P1OUT &= ~BIT2;
            while(correct_format == 0){
                raw_data[0] = UART_read();
                if (raw_data[0] == 0x24){                                       // look for start sign '$'
                    for (i = 1; i < raw_data_len; i++){
                        raw_data[i] = UART_read();                              // read in enough characters to extract latitude and longitude
                    }
                    if ((raw_data[4] == 'M') && (raw_data[5] == 'C')){          // look for GPRMC format
                        if (raw_data[GPRMC_start] != ','){                      // check for meaningful data
                            correct_format = 1;
                            j = 0;
                            for (i = GPRMC_start; i < GPRMC_end+1; i++){        // read in latitude and longitude from pre-defined locations
                                data[j] = raw_data[i];
                                j = j + 1;
                            }
                            NRF_init();
                            NRF_transmit(data, data_len);                       // transmit through nRF24L01
                        }
                    }
                }
            }
            correct_format = 0;
            P1OUT |= BIT2;
        }
        LPM3;
    }
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIM_1_IT(void){
    TA0CTL &= ~TAIFG;                               // clear flag to acknowledge that we handled the interrupt
    LPM3_EXIT;
    counter++;
}
