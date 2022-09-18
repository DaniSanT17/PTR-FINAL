#include "matrix.h"
#include "Matrix.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "mutexes.h"
#include "matrix.h"
#include "parameters.h"
#include "linear.h"


// Bloco de Linearização
Matrix Linearizacao(Matrix xt, Matrix vt, double R)
{
    Matrix L=matrix_zeros(2,2);
    VALUES(L,0,0) = cos(VALUES(xt,2,0));
    VALUES(L,0,1) = -R*sin (VALUES(xt,2,0));
    VALUES(L,1,0) = sin(VALUES(xt,2,0));
    VALUES(L,1,1) = R*cos(VALUES(xt,2,0));
    
    Matrix LInvers=matrix_inverse(L);
    return matrix_mul(LInvers,vt);
}

void* Linear(void*args)
{
    double R = 0.3;
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 20;      //milissegundos
    struct timespec ts1, ts2, ts3={0};
    
    Matrix bufferU, bufferX, bufferV;
    while(t <= TempMax*1000) {
        clock_gettime(CLOCK_REALTIME, &ts1);
        tm = 1000000 * ts1.tv_nsec - tm;
        t = t + T;
        
        mutexes_getX(&bufferX);
        mutexes_getV(&bufferV);

        bufferU=Linearizacao(bufferX, bufferV, R);

        mutexes_setU(bufferU);
        // printf("lin: %lf, %lf, %lf\n", t, VALUES(bufferU,0,0), VALUES(bufferU,1,0));
        // printf("lin: %lf\n", t);

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
    return 0;
 }