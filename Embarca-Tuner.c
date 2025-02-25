#include <stdio.h>
#include <tunerADC.h>
#include <tunerGeneral.h>
#include <tunerInterfaces.h>
#include <tunerFFT.h>
#include <tunerPIO.h>
#include <tunerNote.h>
#include <math.h>
#include "pico/stdlib.h"

#define MICPIN 28 
#define MATRIXPIN 7
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

    PIORefs pio; 

    Sketch sketch = { 
        .Figure = {
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0
        },
        .Index = -1,
        .MainColor = {
            .Red = 0.01,
            .Green = 0.0,
            .Blue = 0.0
        },
        .BackgroundColor = {
            .Red = 0.0,
            .Green = 0.0,
            .Blue = 0.0
        }
    };
    uint32_t ledConf = 0;

    Config(&pio); // Configuração da UART e da PIO

    InitPIO(&pio, MATRIXPIN); // Inizialização da PIO

    ArrayCopySameSize(sketch.Figure, SketchArray('o'), VECTORSIZE);
    Draw(sketch, ledConf, pio); //Desenha um quadrado azul

    CentralizeMessage(&ssd, "Inicio");

    while (true) {
        //printf("OLÁ!\n");
        //printf("Mic reading: %d\n", ReadADC());
        //CentralizeMessage(&ssd, "G");
        CaptureSignal(&fourierData, MICPIN, ADCHCHANNEL,SAMPLERATE);
        FastFourierTransform(&fourierData, FFTSIZE);
        dominantFrequency = FindDominantFrequency(&fourierData, SAMPLERATE);
        //printf("F: %f\n", dominantFrequency);
        char letter = GetLetterFromFrequency(dominantFrequency);
        sprintf(displayedFrequency, "F: %0.2fHz. %c", dominantFrequency, letter);
        letter = ToLower(letter);
        ArrayCopySameSize(sketch.Figure, SketchArray(letter), VECTORSIZE);
        Draw(sketch, ledConf, pio); //Desenha um quadrado azul
        //printf(displayedFrequency);
        //printf("\n");
        CentralizeMessage(&ssd, displayedFrequency);
    }
}
