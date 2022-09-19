#include "matrix.h"
#include "Matrix.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "mutexes.h"
#include "matrix.h"
#include "parameters.h"
#include "linear.h"


Matrix calc_ut(Matrix x, Matrix v, double R)
{
    Matrix L=matrix_zeros(2,2);
    VALUES(L,0,0) = cos(VALUES(x,2,0));
    VALUES(L,0,1) = -R*sin (VALUES(x,2,0));
    VALUES(L,1,0) = sin(VALUES(x,2,0));
    VALUES(L,1,1) = R*cos(VALUES(x,2,0));
    
    Matrix LInvers=matrix_inverse(L);
    return matrix_mul(LInvers,v);
}

// Implementação da thread do bloco de linearização
void* linear_thread(void*args)
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
        
        // Acesso aos mutexes
        mutexes_getX(&bufferX);
        mutexes_getV(&bufferV);
        bufferU=calc_ut(bufferX, bufferV, R);
        mutexes_setU(bufferU);

        // Dormindo thread
        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
    return 0;
 }