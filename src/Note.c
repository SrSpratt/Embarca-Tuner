#include <tunerNote.h>
#include <stdio.h>

// Tabela de notas musicais (A4 = 440 Hz)
MusicalNote notes[] = {
    {"A", 440.00, 'A'}, 
    {"A#", 466.16, 'A'},
    {"B", 493.88, 'B'},
    {"C", 523.25, 'C'},  
    {"C#", 554.37, 'C'}, 
    {"D", 587.33, 'D'},  
    {"D#", 622.25, 'D'}, 
    {"E", 659.25, 'E'},  
    {"F", 698.46, 'F'},  
    {"F#", 739.99, 'F'}, 
    {"G", 783.99, 'G'}, 
    {"G#", 830.61, 'G'}, 
};

int numNotes = sizeof(notes) / sizeof(notes[0]);

char ToLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32; // Converte para minúscula na tabela ASCII
    }
    return c; // Retorna o próprio caractere se não for maiúsculo
}


double Fabs(double x) {
    if (x < 0) {
        return -x; // Retorna o valor positivo se x for negativo
    }
    return x; // Retorna o próprio valor se x for positivo ou zero
}

// Função para normalizar a frequência para a oitava base
double NormalizeFrequency(double frequency) {
    // Encontra a oitava correta dividindo ou multiplicando por 2
    if (frequency == 0)
        return 0;
    while (frequency < notes[0].frequency) {
        frequency *= 2.0; // Dobra a frequência até atingir a oitava base
    }
    while (frequency >= notes[0].frequency * 2.0) {
        frequency /= 2.0; // Divide a frequência até atingir a oitava base
    }
    return frequency;
}

char GetLetterFromFrequency(float frequency) {
    // Normaliza a frequência para a oitava base
    double normalizedFrequency = NormalizeFrequency(frequency);
    // Encontra a nota correspondente
    for (int i = 0; i < numNotes; i++) {
        double tolerance = 10.0; // Tolerância para ajustes pequenos
        if (Fabs(normalizedFrequency - notes[i].frequency) <= tolerance) {
            return notes[i].letter;
        }
    }
    return 'o'; // Retorna '?' se a frequência não corresponder a nenhuma nota
}