double mean(double* v, double T);

double max_min(double* v,double T, int mode);

double var_dp(double* v,double T, int mode);

void calc_metrics(double* JitterRef, double* TRef, double* JitterModelRef, double* TModelRef,
double* JitterController, double* TController, double* JitterLinear, double* TLinear, 
double* JitterRobot, double* TRobot);