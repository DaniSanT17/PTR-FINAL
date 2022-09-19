/*
    Implementação de Ref
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "reference.h"
#include "parameters.h"
#include "jitter.h"
#include "mutexes.h"

double JitterRef[TempMax*1000/50-1];
double TRef[TempMax*1000/50-1];

double* getTRef(){
    return TRef;
}
double* getJitterRef(){
    return JitterRef;
}

Matrix calc_ref(double t) {
    Matrix ref;
    if(t < 0 && t >= 4*M_PI){
        ref = matrix_zeros(2,1);
    } else if(t >= 0  && t < 2*M_PI) {
        ref.nlins = 2;
        ref.ncols = 1;
        ref.values = malloc(ref.nlins * ref.ncols* sizeof(double));
        VALUES(ref,0,0) =  0.5-0.5*cos(t);
        VALUES(ref,1,0) = 0.5*sin(t);
    } else {
        ref.nlins = 2;
        ref.ncols = 1;
        ref.values = malloc(ref.nlins * ref.ncols* sizeof(double));
        VALUES(ref,0,0) = -0.5+0.5*cos(t);
        VALUES(ref,1,0) = -0.5*sin(t);
    }
    return ref;
}


// Thread do Bloco de Referência
void* ref_thread(void*args)
{   
    double tref = 0;    //tempo calculado
    double tm = 0;      //tempo medido
    double T = 50;      //milissegundos
    struct timespec ts1, ts2, ts3={0};
    int i = 0;
    double tmsum = 0;
    Matrix bufferRef;
    while(tref<=TempMax*1000)
    {   
        clock_gettime(CLOCK_REALTIME, &ts1);
        if(tref>0){
            TRef[i] = calc_lat(ts1.tv_nsec, tm);
            tmsum += TRef[i];
            JitterRef[i] = calc_jitter(TRef[i], T);
            // printf("%lf %lf\n", TRef[i], JitterRef[i]);
            i++;
        }
        
        tm = (double) ts1.tv_nsec/1000000;
        tref = tref + T;

        // Acesso aos mutexes
        bufferRef = calc_ref(tmsum/1000);
        mutexes_setRef(bufferRef);

        // Dormindo a thread
        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);

    }
    return 0;
}