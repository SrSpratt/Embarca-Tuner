#include <stdio.h>
#include <tunerADC.h>
#include <tunerInterfaces.h>
#include "pico/stdlib.h"
#define MICPIN 28 
#define ADCHCHANNEL 2


int main()
{
    ssd1306_t ssd;
    stdio_init_all();
    ConfigADC(28);
    I2CInit(&ssd);

    while (true) {
        printf("Mic reading: %d\n", ReadADC(2));
        CentralizeMessage(&ssd, "G");
    }
}
