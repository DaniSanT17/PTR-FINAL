#include "Matrix.h"
#include <stdio.h>
#include <time.h>
#include "mutexes.h"
#include "matrix.h"
#include "parameters.h"
#include "controller.h"
#include "jitter.h"

#define ALPHA1 3.0
#define ALPHA2 3.0


double TController[TempMax*1000/30-1];
double JitterController[TempMax*1000/30-1];

double* getTController(){
    return TController;
}
double* getJitterController(){
    return JitterController;
}

Matrix calc_vt(Matrix ym_dot, Matrix ym, Matrix y)
{
    Matrix v = matrix_zeros(2,1);
    VALUES(v, 0, 0) = VALUES(ym_dot,0,0) + ALPHA1 * (VALUES(ym,0,0) - VALUES(y,0,0));
    VALUES(v, 1, 0) = VALUES(ym_dot,1,0) + ALPHA2 * (VALUES(ym,1,0) - VALUES(y,1,0));
    return v;
}

// Thread do Bloco Controle
void* controller_thread(void*args)
{   
    double tref = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 30;      //milissegundos
    int i = 0;
    struct timespec ts1, ts2, ts3={0};
    Matrix bufferV, bufferYmDot, bufferYm, bufferY;
    while(tref <= TempMax*1000) {
        clock_gettime(CLOCK_REALTIME, &ts1);
        if(tref>0){
            TController[i] = calc_lat(ts1.tv_nsec, tm);
            JitterController[i] = calc_jitter(TController[i], T);
            i++;
        }
        tm = (double) ts1.tv_nsec/1000000;
        tref = tref + T;

        // Acesso aos mutexes
        mutexes_getYmdot(&bufferYmDot);
        mutexes_getYm(&bufferYm);
        mutexes_getY(&bufferY);
        bufferV=calc_vt(bufferYmDot, bufferYm, bufferY);
        mutexes_setV(bufferV);

        // Dormindo a thread
        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
    return 0;
}