/*
 * spi.h
 *
 *  Created on: Oct 17, 2018
 *      Author: yliu60
 */

#pragma once
#include <stdint.h>


void SPI_init();
uint8_t SPI_transfer(uint8_t value);
void SPI_csLow();
void SPI_csHigh();
