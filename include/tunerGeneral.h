#ifndef TUNERGENERAL_H
#define TUNERGENERAL_H

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include <tunerInterfaces.h>
#include <stdio.h>

typedef struct PIO {
    PIO Address; 
    int StateMachine; 
    int Offset; 
} PIORefs;

typedef struct RGB {
    double Red;   
    double Green; 
    double Blue;  
} RGB;

void PrintPIO(PIORefs pio);

void PrintRGB(RGB color);

void Config(PIORefs* pio);

void InitPIO(PIORefs* pio, int pin);


#endif
