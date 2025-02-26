#ifndef TUNERNOTE_H
#define TUNERNOTE_H

typedef struct {
    char note[4]; 
    double frequency;
    char letter; 
} MusicalNote;

// Tabela de notas musicais (A4 = 440 Hz)
extern MusicalNote notes[];

extern int numNotes;

char ToLower(char c);
double Fabs(double x);
double NormalizeFrequency(double frequency);
char GetLetterFromFrequency(float frequency);

#endif