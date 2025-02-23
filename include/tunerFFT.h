#ifndef TUNERFFT_H
#define TUNERFFT_H

#include <stdint.h>

#define FFTSIZE 1024  // Tamanho da FFT
#define PI 3.14159265358979323846  // Definição de PI

// Estrutura para armazenar os dados da FFT
typedef struct {
    float real[FFTSIZE];  // Parte real
    float imag[FFTSIZE];  // Parte imaginária
} FFTData;

// Declarações das funções
void FastFourierTransform(FFTData *data, int N);
void CaptureSignal(FFTData *fourierTransform, uint8_t pin, uint8_t channel, uint16_t sampleRate);
float FindDominantFrequency(FFTData *fourierTransform, uint16_t sampleRate);

#endif 