#include "tunerFFT.h"
#include "tunerADC.h"
#include <math.h>
#include <stdio.h>
#include "pico/stdlib.h"

// Implementação iterativa da FFT
void FastFourierTransform(FFTData *data, int N) {
    int i, j, k;
    float angle;
    float tReal, tImag;

    // Reordena os dados usando bit-reversal
    j = 0;
    for (i = 0; i < N - 1; i++) {
        if (i < j) {
            tReal = data->real[i];
            tImag = data->imag[i];
            data->real[i] = data->real[j];
            data->imag[i] = data->imag[j];
            data->real[j] = tReal;
            data->imag[j] = tImag;
        }
        k = N / 2;
        while (k <= j) {
            j -= k;
            k /= 2;
        }
        j += k;
    }

    // Calcula a FFT
    int stage, step, butterfly;
    for (stage = 1; stage <= log2(N); stage++) {
        step = 1 << stage;  // 2^stage
        int halfStep = step / 2;

        for (butterfly = 0; butterfly < halfStep; butterfly++) {
            angle = -2 * PI * butterfly / step;

            for (i = butterfly; i < N; i += step) {
                j = i + halfStep;
                tReal = cos(angle) * data->real[j] - sin(angle) * data->imag[j];
                tImag = sin(angle) * data->real[j] + cos(angle) * data->imag[j];

                data->real[j] = data->real[i] - tReal;
                data->imag[j] = data->imag[i] - tImag;
                data->real[i] += tReal;
                data->imag[i] += tImag;
            }
        }
    }
}

// Captura o sinal do ADC e prepara para a FFT
void CaptureSignal(FFTData *fourierTransform, uint8_t pin, uint8_t channel, uint16_t sampleRate) {
    ConfigADC(pin, channel);

    for (int i = 0; i < FFTSIZE; i++) {
        uint16_t rawValue = adc_read();  // Lê o valor do ADC
        fourierTransform->real[i] = (double)(rawValue - 2048);  // Centraliza em zero
        fourierTransform->imag[i] = 0.0;  // Parte imaginária zerada
        sleep_us(1000000 / sampleRate);  // Aguarda o tempo de amostragem
    }
}

// Encontra a frequência dominante no espectro
float FindDominantFrequency(FFTData *fourierTransform, uint16_t sampleRate) {
    double maxMagnitude = 0.0;
    int maxIndex = 0;

    // Calcula a magnitude de cada bin da FFT
    for (int i = 0; i < FFTSIZE / 2; i++) {
        double magnitude = sqrt(fourierTransform->real[i] * fourierTransform->real[i] +
                               fourierTransform->imag[i] * fourierTransform->imag[i]);

        if (magnitude > maxMagnitude) {
            maxMagnitude = magnitude;
            maxIndex = i;
        }
    }

    // Calcula a frequência correspondente ao índice máximo
    return (float)(maxIndex * sampleRate) / FFTSIZE;
}