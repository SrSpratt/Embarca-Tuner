#ifndef TUNERNOTE_H
#define TUNERNOTE_H

typedef struct {
    char note[4]; 
    double frequency;
    char letter; 
} MusicalNote;

typedef struct {
    char letter; // Letra da nota mais próxima
    double frequency; // Frequência normalizada
    char note[4];
    double difference;
} ClosestNoteResult;

// Tabela de notas musicais (A4 = 440 Hz)
extern MusicalNote notes[];

extern int numNotes;

char ToLower(char c);
double Fabs(double x);
void CopyNote(char[4], char[4]);
double NormalizeFrequency(double frequency);
char GetLetterFromFrequency(float frequency);
ClosestNoteResult FindClosestNote(double frequency);

#endif