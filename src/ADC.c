#include <tunerADC.h>


void ConfigADC(const uint8_t pin){
    adc_init();
    adc_gpio_init(pin);
}

uint16_t ReadADC(const uint8_t channel){
    adc_select_input(channel);
    return adc_read();
}
