#include <stdio.h>
#include <time.h>

#include "mutexes.h"
#include "jitter.h"
#include "matrix.h"
#include "parameters.h"


void* print_outs (void* args){

    double tref = 0;    //tempo calculado
    double tm = 0;      //tempo medido
    double T = 100;      //milissegundos
    struct timespec ts1, ts2, ts3={0};
    
    Matrix bufferRef, bufferYm, bufferYmdot, bufferV, bufferU, bufferX, bufferY, bufferXdot; 

    while(tref <= TempMax*1000) {
        clock_gettime(CLOCK_REALTIME, &ts1);

        tm = (double) ts1.tv_nsec/1000000;
        tref = tref + T;
        mutexes_getRef(&bufferRef);
        mutexes_getYm(&bufferYm);
        mutexes_getYmdot(&bufferYmdot);
        mutexes_getV(&bufferV);
        mutexes_getU(&bufferU);
        mutexes_getX(&bufferX);
        mutexes_getY(&bufferY);
        mutexes_getXdot(&bufferXdot);
        printf("%.4f, %.4f, %.4f, ", tref, VALUES(bufferRef,0,0),VALUES(bufferRef,1,0));
        printf("%.4f, %.4f, ", VALUES(bufferYm,0,0),VALUES(bufferYm,1,0));
        printf("%.4f, %.4f, ", VALUES(bufferYmdot,0,0),VALUES(bufferYmdot,1,0));
        printf("%.4f, %.4f, ", VALUES(bufferV,0,0),VALUES(bufferV,1,0));
        printf("%.4f, %.4f, ", VALUES(bufferU,0,0),VALUES(bufferU,1,0));
        printf("%.4f, %.4f, %.4f, ", VALUES(bufferX,0,0),VALUES(bufferX,1,0), VALUES(bufferX,2,0));
        printf("%.4f, %.4f, %.4f, ", VALUES(bufferXdot,0,0),VALUES(bufferXdot,1,0),VALUES(bufferXdot,2,0));
        printf("%.4f, %.4f\n", VALUES(bufferY,0,0),VALUES(bufferY,1,0));

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
    return 0;
} 
