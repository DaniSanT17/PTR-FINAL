/*
	main.c: Implementação da Simulação do controle
	author: Daniel Santiago
	date: setembro, 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "mutexes.h"

#include "reference.h"
#include "controller.h"
#include "linear.h"
#include "ref_model.h"
#include "robot.h"
#include "print_outs.h"

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


int main(){
    // Iniciando os mutexes
    mutexes_init();

    //Definindo as Threads usadas
    pthread_t TRef_thread, TRef_model, TController, TLinear, TRobot, TPrint_outs;

    
    // Criação das threads para execução
    pthread_create(&TRef_thread, NULL, ref_thread, NULL);
    pthread_create(&TRef_model, NULL, ref_model_thread, NULL);
    pthread_create(&TController, NULL, controller_thread, NULL);
    pthread_create(&TLinear, NULL, linear_thread, NULL); 
    pthread_create(&TRobot, NULL, robot_thread, NULL);
    pthread_create(&TPrint_outs, NULL, print_outs, NULL);


    // Encerrando a execução das Threads
    pthread_join(TRef_thread, NULL);
    pthread_join(TRef_model, NULL);
    pthread_join(TController, NULL);
    pthread_join(TLinear, NULL);
    pthread_join(TRobot, NULL);
    pthread_join(TPrint_outs, NULL);
    
    // Destruindo os Mutexes
    mutexes_destroy();

    // Calculando a extatística
    // Statistics_Calculing(JitterRef120,JitterModeloRef,JitterControle,JitterLinearizacao,JitterRobo,TempMax);

    exit(0);
}