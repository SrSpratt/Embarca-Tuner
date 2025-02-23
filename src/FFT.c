#include "tunerFFT.h"
#include "tunerADC.h"
#include <math.h>
#include <stdio.h>
#include "pico/stdlib.h"

// Implementação da FFT usando recursão
void FastFourierTransform(FFTData *data, int N) {
    if (N <= 1) return;

    // Divide os dados em pares e ímpares
    FFTData even, odd;
    for (int i = 0; i < N / 2; i++) {
        even.real[i] = data->real[2 * i];
        even.imag[i] = data->imag[2 * i];
        odd.real[i] = data->real[2 * i + 1];
        odd.imag[i] = data->imag[2 * i + 1];
    }

    // Recursão para as metades pares e ímpares
    FastFourierTransform(&even, N / 2);
    FastFourierTransform(&odd, N / 2);

    // Combina os resultados
    for (int k = 0; k < N / 2; k++) {
        double angle = -2 * PI * k / N;
        double tReal = cos(angle) * odd.real[k] - sin(angle) * odd.imag[k];
        double tImag = sin(angle) * odd.real[k] + cos(angle) * odd.imag[k];

        data->real[k] = even.real[k] + tReal;
        data->imag[k] = even.imag[k] + tImag;
        data->real[k + N / 2] = even.real[k] - tReal;
        data->imag[k + N / 2] = even.imag[k] - tImag;
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