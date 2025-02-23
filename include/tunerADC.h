#ifndef tunerADC_H
#define tunerADC_H

#include "hardware/adc.h"


void ConfigADC(const uint8_t, const uint8_t channel);

uint16_t ReadADC();



#endif