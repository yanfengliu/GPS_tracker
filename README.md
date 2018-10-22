# GPS_tracker
Project 1 for Advanced Embedded System class at University of Nebraska-Lincoln
Special thanks to [Jay Carlson](https://github.com/jaydcarlson), my instructor and mentor for this awesome class! 

Parts:
* MSP430FR2433 microcontroller
* nRF24L01 wireless transceiver
* NEO-6M GPS module
* MCP1700 linear voltage regulator

Specification:
* Can be mounted on the inside of a car
* Lasts up to 3 months on two 18650 batteries
* Wakes up periodically to acquire GPS data
* Transfers the whole day's record to a host wirelessly upon trigger
