/*
	main.c: Entrada para a simulação
	author: Andre Cavalcante
	date: agosto, 2022
	license: CC BY-SA
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include "mutexes.h"

#include "ref.h"
#include "control.h"
#include "linear.h"
#include "ref_model.h"
#include "robo.h"

//os buffers serão as variaveis entre os blocos, vão ser dados por matrizes
double TempMax = 14;
// //Contadores de Jitter
// double JitterRef120[400];
// double JitterModeloRef[400];
// double JitterControle[400];
// double JitterLinearizacao[400];
// double JitterRobo[400];

// int contRef120=0;
// int contModeloRef=0;
// int contControle=0;
// int contLinearizacao=0;
// int contRobo=0;


void* print_outs (void* args){
    // 
    // while (t<TempMax)
    // {           

      
    // }
    double tref = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 200;      //milissegundos
    struct timespec ts1, ts2, ts3={0};
    
    Matrix bufferRef, bufferYm, bufferYmdot, bufferV, bufferU, bufferX, bufferY, bufferXdot; 

    while(tref <= TempMax*1000) {
        clock_gettime(CLOCK_REALTIME, &ts1);
        tm = 1000000 * ts1.tv_nsec - tm;
        tref = tref + T;


        mutexes_getRef(&bufferRef);
        mutexes_getYm(&bufferYm);
        mutexes_getYmdot(&bufferYmdot);
        mutexes_getV(&bufferV);
        mutexes_getU(&bufferU);
        mutexes_getX(&bufferX);
        mutexes_getY(&bufferY);
        mutexes_getXdot(&bufferXdot);
        printf("%.4f, %.4f, %.4f, ", tref, VALUES(bufferRef,0,0),VALUES(bufferRef,1,0));
        printf("%.4f, %.4f, ", VALUES(bufferYm,0,0),VALUES(bufferYm,1,0));
        printf("%.4f, %.4f, ", VALUES(bufferYmdot,0,0),VALUES(bufferYmdot,1,0));
        printf("%.4f, %.4f, ", VALUES(bufferV,0,0),VALUES(bufferV,1,0));
        printf("%.4f, %.4f, ", VALUES(bufferU,0,0),VALUES(bufferU,1,0));
        printf("%.4f, %.4f, %.4f, ", VALUES(bufferX,0,0),VALUES(bufferX,1,0), VALUES(bufferX,2,0));
        printf("%.4f, %.4f, %.4f, ", VALUES(bufferXdot,0,0),VALUES(bufferXdot,1,0),VALUES(bufferXdot,2,0));
        printf("%.4f, %.4f\n", VALUES(bufferY,0,0),VALUES(bufferY,1,0));

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
    return 0;
} 


int main(){
    mutexes_init();

    //Nomeando as Threads
    pthread_t TRef120, TModeloRef, TControle, TLinearizacao, TRobo, Print_mostra;

    //Criando as Threads
    pthread_create(&TRef120, NULL, Ref120, NULL);
    pthread_create(&TModeloRef, NULL, ModeloRef, NULL);
    pthread_create(&TControle, NULL, Controle, NULL);
    pthread_create(&TLinearizacao, NULL, Linear, NULL); 
    pthread_create(&TRobo, NULL, Robo, NULL);
    pthread_create(&Print_mostra, NULL, print_outs, NULL);


    // Finalizando as Threads
    pthread_join(TRef120, NULL);
    pthread_join(TModeloRef, NULL);
    pthread_join(TControle, NULL);
    pthread_join(TLinearizacao, NULL);
    pthread_join(TRobo, NULL);
    pthread_join(Print_mostra, NULL);
    
    mutexes_destroy();
    // Statistics_Calculing(JitterRef120,JitterModeloRef,JitterControle,JitterLinearizacao,JitterRobo,TempMax);
    exit(0);
}