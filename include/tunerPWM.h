#ifndef TUNERPWM_H
#define TUNERPWM_H

#include <stdio.h>
#include "hardware/pwm.h"
#include "pico/stdlib.h"
#define PWM_WRAP 20000   // Período de 20ms
#define PWM_CLKDIV 125.0f // Divisor de clock para 50Hz

void InitPWM(uint8_t, uint8_t*);
void ConfigPWM(uint8_t);
void SetPulseWidth(uint8_t, uint16_t);

#endif