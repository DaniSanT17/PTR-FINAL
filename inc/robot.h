#include "matrix.h"

Matrix calc_x_dot(Matrix x, Matrix u);

Matrix calc_x(Matrix x_dot, Matrix last_x_dot, double t);

Matrix calc_y(Matrix x, double R);

void* robot_thread(void*args);

