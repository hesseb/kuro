#ifndef IO_H
#define IO_H

#include <stdint.h>
#include <pic32mx.h>

void initIO();
uint8_t getInputs();
void setLEDs(uint8_t leds);

#endif