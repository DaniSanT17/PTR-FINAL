#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <math.h>

#include "statistics.h"

double mean(double* v, double T){
    double sum = 0;
    for(int i = 1; i < 14000/T;i++){
        sum += v[i];
    }
    return sum/(14000/T);
}

double max_min(double* v,double T, int mode){
    double min = v[1];
    double max = v[1];
    for(int i = 1; i < (14000/T); i++){
        if(min > v[i]){
            min = v[i];
        }
        if(max < v[i]){
            max = v[i];
        }
    }
    if(mode == 0){
        return min;
    }else{
        return max;
    }
}

double var_dp(double* v,double T, int mode){
    double var = 0;
    double mean_v = mean(v,T);

    for(int i = 1; i < 14000/T;i++){
        var += pow((v[i]-mean_v),2);
    }
    var = var/(14000/T);
    if(mode == 0){
        return var;
    }else{
        return sqrt(var);
    }
}

void calc_metrics(double* JitterRef, double* TRef, double* JitterModelRef, double* TModelRef,
double* JitterController, double* TController, double* JitterLinear, double* TLinear, 
double* JitterRobot, double* TRobot)
{
    double meanJRef, meanTRef, meanJMRef, meanTMRef, meanJCtrl, meanTCtrl, meanJLin, meanTLin, meanJRob, meanTRob;
    double varJRef, varTRef, varJMRef, varTMRef, varJCtrl, varTCtrl, varJLin, varTLin, varJRob, varTRob;
    double dpJRef, dpTRef, dpJMRef, dpTMRef, dpJCtrl, dpTCtrl, dpJLin, dpTLin, dpJRob, dpTRob;
    double maxJRef, maxTRef, maxJMRef, maxTMRef, maxJCtrl, maxTCtrl, maxJLin, maxTLin, maxJRob, maxTRob;
    double minJRef, minTRef, minJMRef, minTMRef, minJCtrl, minTCtrl, minJLin, minTLin, minJRob, minTRob;


    meanJRef = mean(JitterRef, 50); varJRef = var_dp(JitterRef, 50, 0); dpJRef = var_dp(JitterRef, 50, 1); 
    maxJRef = max_min(JitterRef, 50, 1); minJRef =  max_min(JitterRef, 50, 0);
    meanTRef = mean(TRef, 50); varTRef = var_dp(TRef, 50, 0); dpTRef = var_dp(TRef, 50, 1); 
    maxTRef = max_min(TRef, 50, 1); minTRef =  max_min(TRef, 50, 0);

    meanJMRef = mean(JitterModelRef, 30); varJMRef = var_dp(JitterModelRef, 30, 0); dpJMRef = var_dp(JitterModelRef, 30, 1); 
    maxJMRef = max_min(JitterModelRef, 30, 1); minJMRef =  max_min(JitterModelRef, 30, 0);
    meanTMRef = mean(TModelRef, 30); varTMRef = var_dp(TModelRef, 30, 0); dpTMRef = var_dp(TModelRef, 30, 1); 
    maxTMRef = max_min(TModelRef, 30, 1); minTMRef =  max_min(TModelRef, 30, 0);

    meanJCtrl = mean(JitterController, 30); varJCtrl = var_dp(JitterController, 30, 0); dpJCtrl = var_dp(JitterController, 30, 1); 
    maxJCtrl = max_min(JitterController, 30, 1); minJCtrl =  max_min(JitterController, 30, 0);
    meanTCtrl = mean(TController, 30); varTCtrl = var_dp(TController, 30, 0); dpTCtrl = var_dp(TController, 30, 1); 
    maxTCtrl = max_min(TController, 30, 1); minTCtrl =  max_min(TController, 30, 0);

    meanJLin = mean(JitterLinear, 20); varJLin = var_dp(JitterLinear, 20, 0); dpJLin = var_dp(JitterLinear, 20, 1); 
    maxJLin = max_min(JitterLinear, 20, 1); minJLin =  max_min(JitterLinear, 20, 0);
    meanTLin = mean(TLinear, 20); varTLin = var_dp(TLinear, 20, 0); dpTLin = var_dp(TLinear, 20, 1); 
    maxTLin = max_min(TLinear, 20, 1); minTLin =  max_min(TLinear, 20, 0);

    meanJRob = mean(JitterRobot, 10); varJRob = var_dp(JitterRobot, 10, 0); dpJRob = var_dp(JitterRobot, 10, 1); 
    maxJRob = max_min(JitterRobot, 10, 1); minJRob =  max_min(JitterRobot, 10, 0);
    meanTRob = mean(TRobot, 10); varTRob = var_dp(TRobot, 10, 0); dpTRob = var_dp(TRobot, 10, 1); 
    maxTRob = max_min(TRobot, 10, 1); minTRob =  max_min(TRobot, 10, 0);


    FILE *pont_arq;

    //abrindo o arquivo
    pont_arq = fopen("metrics.txt", "w");
    fprintf(pont_arq,"JRef\tJMRef\tJCtrl\tJLin\tJRob\n");
    fprintf(pont_arq,"Médias: %lf\t%lf\t%lf\t%lf\t%lf\n",meanJRef,meanJMRef,meanJCtrl,meanJLin,meanJRob);
    fprintf(pont_arq,"Variancias: %lf\t%lf\t%lf\t%lf\t%lf\n",varJRef,varJMRef,varJCtrl,varJLin,varJRob);
    fprintf(pont_arq,"DP: %lf\t%lf\t%lf\t%lf\t%lf\n",dpJRef,dpJMRef,dpJCtrl,dpJLin,dpJRob);
    fprintf(pont_arq,"Máximo: %lf\t%lf\t%lf\t%lf\t%lf\n",maxJRef,maxJMRef,maxJCtrl,maxJLin,maxJRob);
    fprintf(pont_arq,"Mínimo: %lf\t%lf\t%lf\t%lf\t%lf\n\n",minJRef,minJMRef,minJCtrl,minJLin,minJRob);
    fprintf(pont_arq,"TRef\tTMRef\tTCtrl\tTLin\tTRob\n");
    fprintf(pont_arq,"Médias: %lf\t%lf\t%lf\t%lf\t%lf\n",meanTRef,meanTMRef,meanTCtrl,meanTLin,meanTRob);
    fprintf(pont_arq,"Variancias: %lf\t%lf\t%lf\t%lf\t%lf\n",varTRef,varTMRef,varTCtrl,varTLin,varTRob);
    fprintf(pont_arq,"DP: %lf\t%lf\t%lf\t%lf\t%lf\n",dpTRef,dpTMRef,dpTCtrl,dpTLin,dpTRob);
    fprintf(pont_arq,"Máximo: %lf\t%lf\t%lf\t%lf\t%lf\n",maxTRef,maxTMRef,maxTCtrl,maxTLin,maxTRob);
    fprintf(pont_arq,"Mínimo: %lf\t%lf\t%lf\t%lf\t%lf\n\n",minTRef,minTMRef,minTCtrl,minTLin,minTRob);

    // fechando arquivo
    fclose(pont_arq);


}


