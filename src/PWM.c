#include <tunerPWM.h>

void InitPWM(uint8_t pin, uint8_t *slice) {
    // Configura o pino como saída PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);
    
    // Obtém o número do slice PWM correspondente ao pino
    *slice = pwm_gpio_to_slice_num(pin);

    printf("slice: %d\n", *slice);
}

void ConfigPWM(uint8_t slice) {
    // Configurar a frequência do PWM para 50 Hz (Período = 20ms)
    pwm_set_wrap(slice, PWM_WRAP);  // Período de 20ms
    pwm_set_clkdiv(slice, PWM_CLKDIV);  // Divisor de clock para 50Hz
    
    // Ativar PWM
    pwm_set_enabled(slice, true);
}

void SetPulseWidth(uint8_t pin, uint16_t pulseWidth) {
    // Ajusta o servo motor para a largura de pulso fornecida
    pwm_set_gpio_level(pin, pulseWidth);
}