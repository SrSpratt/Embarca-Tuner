#include <stdio.h>
#include <test.h>
#include "pico/stdlib.h"



int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        printf("%s", Test());
        sleep_ms(1000);
    }
}
