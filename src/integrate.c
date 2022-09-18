#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "integrate.h"


double do_integration(FPoly func, double upperl, double lowerl, double step){
    if(func){
        double sum = func(lowerl);
        for(double i=lowerl+step;i<upperl-step;i+=step){
            sum = sum + 2*(func(i));
        }
        sum = sum + func(upperl);

        return (step/2)*sum;
    }
    return 0;
}




