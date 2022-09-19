/*
	main.c: Implementação da Simulação do controle
	author: Daniel Santiago
	date: setembro, 2022
*/

#include <stdlib.h>
#include <pthread.h>


#include "mutexes.h"

#include "reference.h"
#include "controller.h"
#include "linear.h"
#include "ref_model.h"
#include "robot.h"
#include "print_outs.h"
#include "statistics.h"

//os buffers serão as variaveis entre os blocos, vão ser dados por matrizes
double TempMax = 14;


int main(){
    // Iniciando os mutexes
    mutexes_init();

    //Definindo as Threads usadas
    pthread_t TRef_thread, TRef_model_thread, TController_thread, TLinear_thread, TRobot_thread, TPrint_outs_thread;

    
    // Criação das threads para execução
    pthread_create(&TRef_thread, NULL, ref_thread, NULL);
    pthread_create(&TRef_model_thread, NULL, ref_model_thread, NULL);
    pthread_create(&TController_thread, NULL, controller_thread, NULL);
    pthread_create(&TLinear_thread, NULL, linear_thread, NULL); 
    pthread_create(&TRobot_thread, NULL, robot_thread, NULL);
    pthread_create(&TPrint_outs_thread, NULL, print_outs, NULL);


    // Encerrando a execução das Threads
    pthread_join(TRef_thread, NULL);
    pthread_join(TRef_model_thread, NULL);
    pthread_join(TController_thread, NULL);
    pthread_join(TLinear_thread, NULL);
    pthread_join(TRobot_thread, NULL);
    pthread_join(TPrint_outs_thread, NULL);

    
    // Destruindo os Mutexes
    mutexes_destroy();

    // Calculando a extatística
    double* TRef = getTRef();
    double* TMRef = getTModelRef();
    double* TCtrl = getTController();
    double* TLinear = getTLinear();
    double* TRob = getTRobot();

    double* JRef = getJitterRef();
    double* JMRef = getJitterModelRef();
    double* JCtrl = getJitterController();
    double* JLinear = getJitterLinear();
    double* JRob = getJitterRobot();

    calc_metrics(JRef,TRef,JMRef,TMRef,JCtrl,TCtrl,JLinear,TLinear,JRob,TRob);

    exit(0);
}