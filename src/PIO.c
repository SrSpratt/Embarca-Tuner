#include <tunerPIO.h>
#include <stdio.h>

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
        0.0, 1.0, 0.0, 0.0, 1.0,
        1.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0
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