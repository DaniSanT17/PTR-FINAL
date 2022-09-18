#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "ref.h"
#include "parameters.h"
#include "matrix.h"
#include "robo.h"
#include "mutexes.h"
//Bloco robo


Matrix RoboXtLinha(Matrix xt, Matrix ut)
{
    Matrix Aux= matrix_zeros(3,2);//criei uma 2x2
    VALUES(Aux,0,0) = cos(VALUES(xt,2,0));
    VALUES(Aux,0,1) = 0;
    VALUES(Aux,1,0) = sin(VALUES(xt,2,0));
    VALUES(Aux,1,1) = 0;
    VALUES(Aux,2,0) = 0;
    VALUES(Aux,2,1) = 1;
    return matrix_mul(Aux,ut);//retornei a multiplicação
}

Matrix RoboXt(Matrix XtLinha, Matrix XtLinhaAntigo, double ts)
{
    Matrix Xt = matrix_zeros(3,1);
    VALUES(Xt,0,0) = (ts)*(VALUES(XtLinha,0,0)+VALUES(XtLinhaAntigo,0,0))/2;
    VALUES(Xt,1,0) = (ts)*(VALUES(XtLinha,1,0)+VALUES(XtLinhaAntigo,1,0))/2;
    VALUES(Xt,2,0) = (ts)*(VALUES(XtLinha,2,0)+VALUES(XtLinhaAntigo,2,0))/2;
    // VALUES(Xt,0,0) = ts*(VALUES(XtLinha,0,0));
    // VALUES(Xt,1,0) = ts*(VALUES(XtLinha,1,0));
    // VALUES(Xt,2,0) = ts*VALUES(XtLinha,2,0);
    return Xt;
}

Matrix RoboYt(Matrix xt, double R)
{
    Matrix Aux=matrix_zeros(2,3);
    VALUES(Aux,0,0) = 1;
    VALUES(Aux,0,1) = 0;
    VALUES(Aux,0,2) = 0;
    VALUES(Aux,1,0) = 0;
    VALUES(Aux,1,1) = 1;
    VALUES(Aux,1,2) = 0;

    Matrix Aux2 = matrix_zeros(2, 1);
    VALUES(Aux2,0,0) = R*cos(VALUES(xt,2,0));
    VALUES(Aux2,1,0) = R*sin(VALUES(xt,2,0));

    Aux = matrix_mul(Aux, xt);
    Matrix res;
    res = matrix_sum(Aux, Aux2);
    return res;
}

void* Robo(void*args)
{
    double R = 0.3;
    double tref = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 10;      //milissegundos
    struct timespec ts1, ts2, ts3={0};
    
    Matrix auxBuffer, bufferX, bufferY, bufferU, XtLinha;

    while(tref <= TempMax*1000) {
        clock_gettime(CLOCK_REALTIME, &ts1);
        tm = 1000000 * ts1.tv_nsec - tm;
        tref = tref + T;
        
        mutexes_getXdot(&auxBuffer);
        mutexes_getX(&bufferX);
        mutexes_getU(&bufferU);
        XtLinha=RoboXtLinha(bufferX, bufferU);
        bufferX=RoboXt(XtLinha, auxBuffer, 0.01);
        bufferY=RoboYt(bufferX, R);

        mutexes_setXdot(XtLinha);
        mutexes_setX(bufferX);
        mutexes_setY(bufferY);


        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
    return 0;
}


