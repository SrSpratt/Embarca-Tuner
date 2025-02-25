#include <stdio.h>
#include <tunerADC.h>
#include <tunerInterfaces.h>
#include <tunerFFT.h>
#include "pico/stdlib.h"

#define MICPIN 28 
#define ADCHCHANNEL 2
#define SAMPLERATE 8000 //Taxa de amostragem

int main()
{
    FFTData fourierData;

    ssd1306_t ssd;
    stdio_init_all();
    ConfigADC(MICPIN, ADCHCHANNEL);
    I2CInit(&ssd);

    float dominantFrequency = 0.0f;
    char displayedFrequency[10] = "F: 0.0Hz";

    while (true) {
        //printf("OLÁ!\n");
        //printf("Mic reading: %d\n", ReadADC());
        //CentralizeMessage(&ssd, "G");
        CaptureSignal(&fourierData, MICPIN, ADCHCHANNEL,SAMPLERATE);
        FastFourierTransform(&fourierData, FFTSIZE);
        dominantFrequency = FindDominantFrequency(&fourierData, SAMPLERATE);
        //printf("F: %f\n", dominantFrequency);
        sprintf(displayedFrequency, "F: %0.2fHz", dominantFrequency);
        printf(displayedFrequency);
        printf("\n");
        CentralizeMessage(&ssd, displayedFrequency);
    }
}
