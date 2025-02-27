#include <stdio.h>
#include <tunerADC.h>
#include <tunerGeneral.h>
#include <tunerInterfaces.h>
#include <tunerFFT.h>
#include <tunerPIO.h>
#include <math.h>
#include <tunerNote.h>
#include <tunerPWM.h>
#include "pico/stdlib.h"

#define MICPIN 28 
#define MATRIXPIN 7
#define ADCHCHANNEL 2
#define RLED 13
#define BLED 12
#define GLED 11
#define SAMPLERATE 8000 //Taxa de amostragem

int main()
{
    FFTData fourierData;

    ssd1306_t ssd;
    ConfigADC(MICPIN, ADCHCHANNEL);
    I2CInit(&ssd);

    float dominantFrequency = 0.0f;
    char displayedFrequency[10] = "F: 0.0Hz";
    char displayedNote[10] = "N: n/a";
    char naNote[5] = "n/a";

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

    InitPIO(&pio, MATRIXPIN); // Iniciação da PIO

    uint8_t slices[3];
    uint8_t pinsRGB[3] = {GLED, BLED, RLED};
    for (int i = 0; i <  3; i++){
        InitPWM(pinsRGB[i], &slices[i]);
        ConfigPWM(slices[i]);
    }


    ArrayCopySameSize(sketch.Figure, SketchArray('o'), VECTORSIZE);
    Draw(sketch, ledConf, pio); //Desenha um quadrado azul

    // char a[10];
    // sprintf(a, "%d", numNotes);
    // CentralMessages(&ssd, a);

    char letter = 'n';
    ClosestNoteResult closestNote;

    while (true) {
        //printf("OLÁ!\n");
        //printf("Mic reading: %d\n", ReadADC());
        //CentralizeMessage(&ssd, "G");
        CaptureSignal(&fourierData, MICPIN, ADCHCHANNEL,SAMPLERATE);
        FastFourierTransform(&fourierData, FFTSIZE);
        dominantFrequency = FindDominantFrequency(&fourierData, SAMPLERATE);
        //printf("F: %f\n", dominantFrequency);
        letter = GetLetterFromFrequency(dominantFrequency);
        closestNote = FindClosestNote(dominantFrequency);
        sprintf(displayedFrequency, "F: %0.2fHz", dominantFrequency);
        sprintf(displayedNote, "N: %s", dominantFrequency > 0 ? closestNote.note : naNote);
        ArrayCopySameSize(sketch.Figure, SketchArray(ToLower(letter)), VECTORSIZE);
        Draw(sketch, ledConf, pio); //Desenha um quadrado azul
        if (dominantFrequency == 0){
            SetPulseWidth(GLED, 1000);
            SetPulseWidth(BLED, 1000);
            SetPulseWidth(RLED, 1000);
        } else if (closestNote.difference < 2){
            SetPulseWidth(GLED, 1000);
            SetPulseWidth(BLED, 0);
            SetPulseWidth(RLED, 0);
            printf("Difference: %lf\n\n", closestNote.difference);
        } else {
            SetPulseWidth(GLED, 0);
            SetPulseWidth(BLED, 0);
            SetPulseWidth(RLED, 1000);
            printf("Difference: %lf\n\n", closestNote.difference);
        }
        //printf(displayedFrequency);
        //printf("\n");
        CentralMessages(&ssd, displayedFrequency, displayedNote);
    }
}
