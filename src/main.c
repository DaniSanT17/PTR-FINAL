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

// //Contadores de Jitter
// double JitterRef120[400];
// double JitterModeloRef[400];
// double JitterControle[400];
// double JitterLinearizacao[400];
// double JitterRobo[400];

int contRef120=0;
int contModeloRef=0;
int contControle=0;
int contLinearizacao=0;
int contRobo=0;

/*
void* imprimi (void* args){

    while (t<TempMax)
    {           
    
        printf("%.2f\t%.4f\t%.4f\t \n",t,MVAL(bufferYm,0,0),MVAL(bufferYm,1,0));
      
    }
    
}
*/

int main(){
    mutexes_init();

    //Nomeando as Threads
    pthread_t TRef120, TModeloRef, TControle, TLinearizacao, TRobo; //Print_mostra;

    //Criando as Threads
    pthread_create(&TRef120, NULL, Ref120, NULL);
    pthread_create(&TModeloRef, NULL, ModeloRef, NULL);
    pthread_create(&TControle, NULL, Controle, NULL);
    pthread_create(&TLinearizacao, NULL, Linear, NULL); 
    pthread_create(&TRobo, NULL, Robo, NULL);
    // pthread_create(&Print_mostra, NULL, imprimi, NULL);


    //Finalizando as Threads
    pthread_join(TRef120, NULL);
    pthread_join(TModeloRef, NULL);
    pthread_join(TControle, NULL);
    pthread_join(TLinearizacao, NULL);
    pthread_join(TRobo, NULL);
    // pthread_join(Print_mostra, NULL);
    
    mutexes_destroy();
    // Statistics_Calculing(JitterRef120,JitterModeloRef,JitterControle,JitterLinearizacao,JitterRobo,TempMax);
    exit(0);
}