/*
 * RTC.c
 *
 *  Created on: Oct 26, 2018
 *      Author: yliu60
 */

#include <msp430.h>
#include "rtc.h"

void RTC_init(){
    RTCCTL = RTCSR;                         // real time software reset the RTC
    RTCCTL = RTCSS_3 | RTCPS__1024;         // CLOCLK; pre-divider = 1024;
    RTCMOD = 0xFFFF;                        // overflow matching value
}
