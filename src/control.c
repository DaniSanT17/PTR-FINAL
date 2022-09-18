#include "Matrix.h"
#include <stdio.h>
#include <time.h>
#include "mutexes.h"
#include "matrix.h"
#include "parameters.h"
#include "control.h"

#define ALPHA1 3.0
#define ALPHA2 3.0

Matrix ControleBloco(Matrix YmLinha, Matrix Ym, Matrix Yt)
{
    Matrix Vt = matrix_zeros(2,1);
    VALUES(Vt, 0, 0) = VALUES(YmLinha,0,0) +ALPHA1 * (VALUES(Ym,0,0) - VALUES(Yt,0,0));
    VALUES(Vt, 1, 0) = VALUES(YmLinha,1,0) +ALPHA2 * (VALUES(Ym,1,0) - VALUES(Yt,1,0));
    return Vt;
}

//Bloco Controle
void* Controle(void*args)
{   
    double tref = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 30;      //milissegundos
    struct timespec ts1, ts2, ts3={0};
    Matrix bufferV, bufferYmLinha, bufferYm, bufferY;
    while(tref <= TempMax*1000) {
        clock_gettime(CLOCK_REALTIME, &ts1);
        tm = 1000000 * ts1.tv_nsec - tm;
        tref = tref + T;
        mutexes_getYmdot(&bufferYmLinha);
        mutexes_getYm(&bufferYm);
        mutexes_getY(&bufferY);
        bufferV=ControleBloco(bufferYmLinha, bufferYm, bufferY);
        mutexes_setV(bufferV);
        // printf("ctrl: %lf, %lf, %lf\n", tref, VALUES(bufferV, 0,0), VALUES(bufferV,1,0));

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
    return 0;
}