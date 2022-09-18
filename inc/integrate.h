/* ADT INTEGRAL */

#ifndef _INTEGRATE_H
#define _INTEGRATE_H

typedef double (*FPoly)(double);

double do_integration(FPoly f, double upperl, double lowerl, double step);

#endif
