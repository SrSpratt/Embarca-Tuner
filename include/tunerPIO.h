#ifndef TUNERPIO_H
#define TUNERPIO_H

#include "tunerGeneral.h"

#define VECTORSIZE 25 

typedef struct Drawing {
    double Figure[25];           
    int Index;                   
    RGB MainColor;               
    RGB BackgroundColor;         
} Sketch;

void PrintArraySketch(double*, int);

void PrintSketch(Sketch);

double* SketchArray(char);

void ArrayCopySameSize(double*, double*, int);

uint32_t RGBMatrix(RGB);

void Draw(Sketch, uint32_t, PIORefs);


#endif
