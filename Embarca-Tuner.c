#include <stdio.h>
#include <tunerADC.h>
#include "pico/stdlib.h"
#define MICPIN 28 
#define ADCHCHANNEL 2


int main()
{
    stdio_init_all();
    ConfigADC(28);

    while (true) {
        printf("Mic reading: %d\n", ReadADC(2));
    }
}
