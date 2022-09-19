/*
    Define a thread linear
*/

#include "matrix.h"

double* getJitterLinear();

double* getTLinear();

Matrix calc_ut(Matrix x, Matrix v, double R);

void* linear_thread(void*args);