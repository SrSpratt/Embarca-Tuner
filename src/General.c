#include <tunerGeneral.h>
#include <stdio.h>
#include "hardware/clocks.h"
#include "tunerPIO.pio.h"

void PrintPIO(PIORefs pio){
    printf("---- PIO ----\n");
    printf("Address: %d\n", pio.Address);
    printf("Offset: %d\n", pio.Offset);
    printf("State Machine: %d\n", pio.StateMachine);
    printf("---- PIO ----\n");
}

void PrintRGB(RGB color){
    printf("---- RGB ----\n");
    printf("Red: %lf\n", color.Red);
    printf("Green: %lf\n", color.Green);
    printf("Blue: %lf\n", color.Blue);
    printf("---- RGB ----\n");
}

void Config(PIORefs* pio){
    stdio_init_all();

    pio->Address = pio0;
    if(!set_sys_clock_khz(128000, false))
        printf("clock errado!");
    pio->Offset = pio_add_program(pio->Address, &pio_tuner_program);
    pio->StateMachine = pio_claim_unused_sm(pio->Address, true);
}

void InitPIO(PIORefs* pio, int pin){
    pio_tuner_program_init(pio->Address, pio->StateMachine, pio->Offset, pin);
}