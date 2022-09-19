#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "parameters.h"
#include "matrix.h"
#include "robot.h"
#include "mutexes.h"

//Bloco robo

Matrix calc_x_dot(Matrix x, Matrix u)
{
    Matrix aux= matrix_zeros(3,2);//criei uma 2x2
    VALUES(aux,0,0) = cos(VALUES(x,2,0));
    VALUES(aux,0,1) = 0;
    VALUES(aux,1,0) = sin(VALUES(x,2,0));
    VALUES(aux,1,1) = 0;
    VALUES(aux,2,0) = 0;
    VALUES(aux,2,1) = 1;
    return matrix_mul(aux,u);//retornei a multiplicação
}

Matrix calc_x(Matrix x_dot, Matrix last_x_dot, double ts)
{
    Matrix x = matrix_zeros(3,1);
    VALUES(x,0,0) = (ts)*(VALUES(x_dot,0,0)+VALUES(last_x_dot,0,0))/2;
    VALUES(x,1,0) = (ts)*(VALUES(x_dot,1,0)+VALUES(last_x_dot,1,0))/2;
    VALUES(x,2,0) = (ts)*(VALUES(x_dot,2,0)+VALUES(last_x_dot,2,0))/2;

    return x;
}

Matrix calc_y(Matrix x, double R)
{
    Matrix aux=matrix_zeros(2,3);
    VALUES(aux,0,0) = 1;
    VALUES(aux,0,1) = 0;
    VALUES(aux,0,2) = 0;
    VALUES(aux,1,0) = 0;
    VALUES(aux,1,1) = 1;
    VALUES(aux,1,2) = 0;

    Matrix aux2 = matrix_zeros(2, 1);
    VALUES(aux2,0,0) = R*cos(VALUES(x,2,0));
    VALUES(aux2,1,0) = R*sin(VALUES(x,2,0));

    aux = matrix_mul(aux, x);
    Matrix res;
    res = matrix_sum(aux, aux2);
    return res;
}

void* robot_thread(void*args)
{
    double R = 0.3;
    double tref = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 10;      //milissegundos
    struct timespec ts1, ts2, ts3={0};
    
    Matrix auxBuffer, bufferX, bufferY, bufferU, x_dot;

    while(tref <= TempMax*1000) {
        clock_gettime(CLOCK_REALTIME, &ts1);
        tm = 1000000 * ts1.tv_nsec - tm;
        tref = tref + T;
        
        mutexes_getXdot(&auxBuffer);
        mutexes_getX(&bufferX);
        mutexes_getU(&bufferU);
        x_dot=calc_x_dot(bufferX, bufferU);
        bufferX=calc_x(x_dot, auxBuffer, 0.03);
        bufferY=calc_y(bufferX, R);

        mutexes_setXdot(x_dot);
        mutexes_setX(bufferX);
        mutexes_setY(bufferY);


        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
    return 0;
}


