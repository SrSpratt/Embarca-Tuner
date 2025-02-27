#include <tunerNote.h>
#include <stdio.h>

MusicalNote notes[] = {
    {"A", 440.00, 'A'}, 
    {"A#", 466.16, 'H'},
    {"B", 493.88, 'B'},
    {"C", 523.25, 'C'},  
    {"C#", 554.37, 'I'}, 
    {"D", 587.33, 'D'},  
    {"D#", 622.25, 'J'}, 
    {"E", 659.25, 'E'},  
    {"F", 698.46, 'F'},  
    {"F#", 739.99, 'K'}, 
    {"G", 783.99, 'G'}, 
    {"G#", 830.61, 'L'}, 
};

int numNotes = sizeof(notes) / sizeof(notes[0]);

ClosestNoteResult FindClosestNote(double frequency) {
    ClosestNoteResult result;
    result.letter = 'n'; // Nota padrão (caso não encontre)
    result.frequency = frequency; // Frequência normalizada

    if (frequency == 0)
        return result;

    double minDifference = 1e30; // Valor grande para representar "infinito"

    // Itera sobre todas as notas na tabela
    for (int i = 0; i < numNotes; i++) {
        double noteFrequency = notes[i].frequency;

        // Considera todas as oitavas possíveis (multiplicando ou dividindo por 2)
        while (noteFrequency > frequency * 2.0) {
            noteFrequency /= 2.0; // Divide a frequência da nota para chegar a uma oitava inferior
        }
        while (noteFrequency < frequency / 2.0) {
            noteFrequency *= 2.0; // Multiplica a frequência da nota para chegar a uma oitava superior
        }

        // Calcula a diferença entre a frequência e a nota na oitava correta
        double difference = Fabs(frequency - noteFrequency);
        if (difference < minDifference) {
            minDifference = difference;
            result.letter = notes[i].letter;
            CopyNote(result.note, notes[i].note);
            result.difference = minDifference;
            result.frequency = noteFrequency;
        }
    }

    return result;
}

void CopyNote(char first[4], char second[4]){
    for(int i = 0; i < 4; i++)
        first[i] = second[i];
}

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
    ClosestNoteResult result = FindClosestNote(frequency);
    return result.frequency; // Retorna a frequência normalizada
}

char GetLetterFromFrequency(float frequency) {
    ClosestNoteResult result = FindClosestNote(frequency);

    // Tolerância proporcional à frequência da nota (10%)
    double tolerance = result.frequency * 0.1; // 10% da frequência normalizada
    if (Fabs(frequency - result.frequency) <= tolerance) {
        return result.letter;
    }

    return 'n'; // Retorna '?' se a frequência não corresponder a nenhuma nota
}