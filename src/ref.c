/*
    Implementação de Ref
*/

#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "ref.h"
#include "parameters.h"

#include "mutexes.h"

// int contRef120=0;
// // double t = 0;
// //Semaforos para os Produtores
// sem_t ProduzRef;

// //Semaforos Para os Consumidores
// sem_t ConsomeRef;

// Matrix bufferRef;

// // T = 0.5;

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

void *ref_thread(void *a) {
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 50;      //milissegundos
    struct timespec ts1, ts2, ts3={0};
    
    Matrix ref;

    while(t <= 13000) {
        clock_gettime(CLOCK_REALTIME, &ts1);
        tm = 1000000 * ts1.tv_nsec - tm;
        t = t + T;
        
        ref = calc_ref(tm);
        // ref = calc_ref(tm);
        mutexes_setRef(ref);
        printf("%lf, %lf, %lf\n", t, VALUES(ref,0,0), VALUES(ref,1,0));

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
    return 0;
}


void* Ref120(void*args)
{
    double tref = 0;    //tempo calculado
    double tm = 0;      //tempo medido
    double T = 50;      //milissegundos
    struct timespec ts1, ts2, ts3={0};
    Matrix bufferRef;
    while(tref<=TempMax*1000)
    {   
        clock_gettime(CLOCK_REALTIME, &ts1);
        tm = 1000000 * ts1.tv_nsec - tm;
        tref = tref + T;

        bufferRef = calc_ref(tref/1000);
        mutexes_setRef(bufferRef);
        // printf("ref: %lf, %lf, %lf\n", tref, VALUES(bufferRef, 0, 0), VALUES(bufferRef, 0, 1));

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);

    }
    return 0;
}