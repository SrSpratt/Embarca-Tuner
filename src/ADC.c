#include <tunerADC.h>


void ConfigADC(const uint8_t pin, const uint8_t channel){
    adc_init();
    adc_gpio_init(pin);
    adc_select_input(channel);
}

uint16_t ReadADC(){
    return adc_read();
}
