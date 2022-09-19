/*
    Define a thread ref_model
*/

#include "matrix.h"

Matrix calc_ym_dot(Matrix ref, Matrix ym); // Cálculo dos valores de ym_dot

Matrix calc_ym(Matrix ym_dot, Matrix last_ym_dot, double t); // Cálculo dos valores de ym

void* ref_model_thread(void*args); // Thread para execução da referência