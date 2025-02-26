#include <tunerPIO.h>
#include <stdio.h>

void PrintArraySketch(double* array, int size){

    for (int i = 1; i <= size; i++){
        if (i % 5 == 1)
            printf("\n");
        printf("%.1lf ", array[i-1]);
    }
}

double* SketchArray(char character) {
    static double reset[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0
    };
    static double figureA[] = {
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0
    };
    static double figureB[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0
    };
    static double figureC[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0
    };
    static double figureD[] = {
        0.0, 0.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 1.0, 0.0
    };
    static double figureE[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0
    };
    static double figureF[] = {
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0
    };
    static double figureG[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        1.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0
    };
    static double figureAs[] = {
        1.0, 0.0, 1.0, 0.0, 1.0,
        1.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 1.0, 1.0,
        1.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0
    };
    static double figureCs[] = {
        1.0, 0.0, 1.0, 1.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 1.0, 1.0
    };
    static double figureDs[] = {
        1.0, 0.0, 0.0, 1.0, 1.0,
        1.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 1.0,
        1.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 1.0
    };
    static double figureFs[] = {
        1.0, 0.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 1.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 1.0
    };
    static double figureGs[] = {
        1.0, 0.0, 1.0, 1.0, 1.0,
        1.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 1.0, 1.0
    };

    switch (character) {
        case 'a':
            return figureA;
        case 'b':
            return figureB;
        case 'c':
            return figureC;
        case 'd':
            return figureD;
        case 'e':
            return figureE;
        case 'f':
            return figureF;
        case 'g':
            return figureG;
        case 'h':
            return figureAs;
        case 'i':
            return figureCs;
        case 'j':
            return figureDs;
        case 'k':
            return figureFs;
        case 'l':
            return figureGs;
        default:
            return reset;
    }
}

void ArrayCopySameSize(double* firstVector, double* secondVector, int size){

    for(int i = 0; i < size; i++){
        firstVector[i] = 0.0;
        firstVector[i] = secondVector[i];
    }
}

uint32_t RGBMatrix(RGB color){
    unsigned char R, G, B;
    R = color.Red * 255;
    G = color.Green * 255;
    B = color.Blue * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void Draw(Sketch sketch, uint32_t ledConf, PIORefs pio){
    pio_sm_restart(pio.Address, pio.StateMachine);
    //PrintSketch(sketch);
    for (int16_t i = 0; i < VECTORSIZE; i++){
        if (sketch.Figure[i] == 1.0)
            ledConf = RGBMatrix(sketch.MainColor);
        else
            ledConf = RGBMatrix(sketch.BackgroundColor);

        pio_sm_put_blocking(pio.Address, pio.StateMachine, ledConf);
    }
}