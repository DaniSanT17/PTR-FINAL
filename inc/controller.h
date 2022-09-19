/*
    Define a thread controller
*/


#include "matrix.h"


Matrix calc_vt(Matrix ym_dot, Matrix ym, Matrix y);

void* controller_thread(void*args);