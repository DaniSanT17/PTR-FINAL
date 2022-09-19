#include <stdio.h>
#include "jitter.h"


double calc_lat(int t1, double t2){
    double t = (double) t1/1000000;
    double dif = t - t2;

    if( dif < 0){
        dif += 1000;
    }
    return dif;
}

double calc_jitter(double dif, double T){
    
    return dif - T;
}
