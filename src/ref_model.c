#include <stdio.h>
#include <time.h>
#include "mutexes.h"
#include "matrix.h"
#include "parameters.h"
#include "ref_model.h"

#define ALPHA1 3.0
#define ALPHA2 3.0

Matrix y_m(Matrix ref, Matrix Ym){

  Matrix ymLinha = matrix_zeros(2,1);
  VALUES(ymLinha, 0 , 0) = ALPHA1*(VALUES(ref,0,0)-VALUES(Ym,0,0));
  VALUES(ymLinha, 1 , 0) = ALPHA2*(VALUES(ref,1,0)-VALUES(Ym,1,0));
  return ymLinha;

}

Matrix ModeloRefYm(Matrix YmLinha, Matrix YmLinhaAntigo, double ts)
{
    Matrix ym = matrix_zeros(2,1);
    VALUES(ym, 0,0) = (ts)*(VALUES(YmLinha,0,0)+VALUES(YmLinhaAntigo,0,0))/2;
    VALUES(ym, 1,0) = (ts)*(VALUES(YmLinha,1,0)+VALUES(YmLinhaAntigo,1,0))/2;
    return ym;
}


void* ModeloRef(void*args)
{
    double tref = 0;    //tempo calculado
    double tm = 0;      //tempo medido
    double T = 30;      //milissegundos
    struct timespec ts1, ts2, ts3={0};
    Matrix bufferRef, bufferYm, bufferYmLinha, auxBuffer, auxBuffer2;
    while(tref<=TempMax*1000)
    {   
        clock_gettime(CLOCK_REALTIME, &ts1);
        tm = 1000000 * ts1.tv_nsec - tm;
        tref = tref + T;

        mutexes_getRef(&bufferRef);
        mutexes_getYmdot(&auxBuffer);
        mutexes_getYm(&auxBuffer2);
        bufferYmLinha=y_m(bufferRef,auxBuffer2);
        bufferYm=ModeloRefYm(bufferYmLinha, auxBuffer, 0.03);
        mutexes_setYmdot(bufferYmLinha);
        mutexes_setYm(bufferYm);
        // printf("ym: %lf, %lf, %lf\n", tref,VALUES(bufferYm, 0, 0), VALUES(bufferYm, 0, 1));

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);

    }
    return 0;
}





