/*
    Implementação dos mutexes e das variáveis
*/

#include <pthread.h>

#include "matrix.h"
#include "mutexes.h"

static Matrix Ref;
static Matrix Y;
static Matrix Ym;
static Matrix Ymdot;
static Matrix V;
static Matrix U;
static Matrix X;
static Matrix Xdot;

static pthread_mutex_t mutexRef     = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexY       = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexYm      = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexYmdot   = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexV   = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexU   = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexX   = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexXdot   = PTHREAD_MUTEX_INITIALIZER;


void mutexes_init() {
    Ref     = matrix_zeros(2,1);
    Y       = matrix_zeros(2,1);
    Ym      = matrix_zeros(2,1);
    Ymdot   = matrix_zeros(2,1);
    X   = matrix_zeros(3,1);
    Xdot   = matrix_zeros(3,1);
    U   = matrix_zeros(2,1);
    V   = matrix_zeros(2,1);
}

void mutexes_destroy() {
    pthread_mutex_destroy(&mutexRef);
    pthread_mutex_destroy(&mutexY);
    pthread_mutex_destroy(&mutexYm);
    pthread_mutex_destroy(&mutexYmdot);
    pthread_mutex_destroy(&mutexU);
    pthread_mutex_destroy(&mutexV);
    pthread_mutex_destroy(&mutexX);
    pthread_mutex_destroy(&mutexXdot);
}

void mutexes_setRef(Matrix ref) {
    pthread_mutex_lock(&mutexRef);
        Ref = ref;
    pthread_mutex_unlock(&mutexRef);
}


void mutexes_getRef(Matrix *ref) {
    if(!ref) return;
    pthread_mutex_lock(&mutexRef);
        *ref = Ref;
    pthread_mutex_unlock(&mutexRef);
}


void mutexes_setY(Matrix y) {
    pthread_mutex_lock(&mutexY);
        Y = y;
    pthread_mutex_unlock(&mutexY);
}

void mutexes_getY(Matrix *y) {
    if(!y) return;
    pthread_mutex_lock(&mutexY);
        *y = Y;
    pthread_mutex_unlock(&mutexY);
}


void mutexes_setYm(Matrix  ym){
    pthread_mutex_lock(&mutexYm);
        Ym = ym;
    pthread_mutex_unlock(&mutexYm);
}
void mutexes_getYm(Matrix *ym){
    if(!ym) return;
    pthread_mutex_lock(&mutexYm);
        *ym = Ym;
    pthread_mutex_unlock(&mutexYm);
}


void mutexes_setYmdot(Matrix  ymdot){
    pthread_mutex_lock(&mutexYmdot);
        Ymdot = ymdot;
    pthread_mutex_unlock(&mutexYmdot);
}
void mutexes_getYmdot(Matrix *ymdot){
    if(!ymdot) return;
    pthread_mutex_lock(&mutexYmdot);
        *ymdot = Ymdot;
    pthread_mutex_unlock(&mutexYmdot);
}


void mutexes_setV(Matrix  v){
    pthread_mutex_lock(&mutexV);
        V = v;
    pthread_mutex_unlock(&mutexV);
}
void mutexes_getV(Matrix *v){
    if(!v) return;
    pthread_mutex_lock(&mutexV);
        *v = V;
    pthread_mutex_unlock(&mutexV);
}


void mutexes_setU(Matrix  u){
    pthread_mutex_lock(&mutexU);
        U = u;
    pthread_mutex_unlock(&mutexU);
}
void mutexes_getU(Matrix *u){
    if(!u) return;
    pthread_mutex_lock(&mutexU);
        *u = U;
    pthread_mutex_unlock(&mutexU);
}


void mutexes_setX(Matrix  x){
    pthread_mutex_lock(&mutexX);
        X = x;
    pthread_mutex_unlock(&mutexX);
}
void mutexes_getX(Matrix *x){
    if(!x) return;
    pthread_mutex_lock(&mutexX);
        *x = X;
    pthread_mutex_unlock(&mutexX);
}


void mutexes_setXdot(Matrix  xdot){
    pthread_mutex_lock(&mutexXdot);
        Xdot = xdot;
    pthread_mutex_unlock(&mutexXdot);
}
void mutexes_getXdot(Matrix *xdot){
    if(!xdot) return;
    pthread_mutex_lock(&mutexXdot);
        *xdot = Xdot;
    pthread_mutex_unlock(&mutexXdot);
}

