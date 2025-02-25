#ifndef TUNERNOTE_H
#define TUNERNOTE_H

typedef struct {
    char note[4]; 
    double frequency;
    char letter; 
} MusicalNote;

char ToLower(char);

double Fabs(double);

double NormalizeFrequency(double);

char GetLetterFromFrequency(float);

#endif