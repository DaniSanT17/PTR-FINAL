#include <stdio.h>
#include <time.h>
#include "mutexes.h"
#include "matrix.h"
#include "parameters.h"
#include "ref_model.h"

#define ALPHA1 3.0
#define ALPHA2 3.0

Matrix calc_ym_dot(Matrix ref, Matrix ym){

  Matrix ym_dot = matrix_zeros(2,1);
  VALUES(ym_dot, 0 , 0) = ALPHA1*(VALUES(ref,0,0)-VALUES(ym,0,0));
  VALUES(ym_dot, 1 , 0) = ALPHA2*(VALUES(ref,1,0)-VALUES(ym,1,0));
  return ym_dot;

}

Matrix calc_ym(Matrix ym_dot, Matrix last_ym_dot, double ts)
{
    Matrix ym = matrix_zeros(2,1);
    VALUES(ym, 0,0) = (ts)*(VALUES(ym_dot,0,0)+VALUES(last_ym_dot,0,0))/2;
    VALUES(ym, 1,0) = (ts)*(VALUES(ym_dot,1,0)+VALUES(last_ym_dot,1,0))/2;

    return ym;
}

// Thread do Bloco Controle
void* ref_model_thread(void*args)
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

        // Acesso aos mutexes
        mutexes_getRef(&bufferRef);
        mutexes_getYmdot(&auxBuffer);
        mutexes_getYm(&auxBuffer2);
        bufferYmLinha=calc_ym_dot(bufferRef,auxBuffer2);
        bufferYm=calc_ym(bufferYmLinha, auxBuffer, 0.03);
        mutexes_setYmdot(bufferYmLinha);
        mutexes_setYm(bufferYm);

        // Dormindo a thread
        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);

    }
    return 0;
}





