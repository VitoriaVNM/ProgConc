#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;

void* OiMaria(void *t){
    //mensagem
    printf("Oi Maria!\n");
    pthread_mutex_lock(&x_mutex); //lock para alterar x
    x++;
    pthread_cond_broadcast(&x_cond); //desbloqueia as threads presas
    pthread_mutex_unlock(&x_mutex); //sai de x

    pthread_exit(NULL);
}

void* OiJose(void *t){
    //mensagem
    printf("Oi José!\n");
    pthread_mutex_lock(&x_mutex); //lock para alterar x
    x++;
    pthread_cond_broadcast(&x_cond); //desbloqueia as threads presas
    pthread_mutex_unlock(&x_mutex); //sai de x

    pthread_exit(NULL);
}

void* Senta(void *M){
    
    pthread_mutex_lock(&x_mutex);//lock para alterar x
    while(x < 2){
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    printf("Sente-se, Por favor.\n");
    x++;
    pthread_cond_broadcast(&x_cond); //desbloqueia as threads presas
    pthread_mutex_unlock(&x_mutex); //sai de x

    pthread_exit(NULL);
}

void* tchauMaria(void *M){
    
    pthread_mutex_lock(&x_mutex);//lock para alterar x
    while(x < 3){
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    printf("Tchau Maria!\n");
    x++;
    pthread_cond_broadcast(&x_cond); //desbloqueia as threads presas
    pthread_mutex_unlock(&x_mutex); //sai de x

    pthread_exit(NULL);
}

void* tchauJose(void *M){
    
    pthread_mutex_lock(&x_mutex); //lock para alterar x
    while(x < 3){
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    printf("Tchau Jose!\n");
    x++;
    pthread_cond_broadcast(&x_cond); //desbloqueia as threads presas
    pthread_mutex_unlock(&x_mutex); //sai de x

    pthread_exit(NULL);
}


int main()
{
    //cria o vetor de threads
    pthread_t threads[N];
    
    //inicializa a variavel de condição e de lock
    pthread_mutex_init(&x_mutex, NULL);
    pthread_cond_init(&x_cond, NULL);
    
    //cria as threads
    pthread_create(&threads[0], NULL, OiMaria, NULL);
    pthread_create(&threads[1], NULL, OiJose, NULL);
    pthread_create(&threads[2], NULL, Senta, NULL);
    pthread_create(&threads[3], NULL, tchauMaria, NULL);
    pthread_create(&threads[4], NULL, tchauJose, NULL);
    
    //espera terminar as threads
    for(int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }
    
    //desaloca a variavel de condição e de lock
    pthread_mutex_destroy(&x_mutex);
    pthread_cond_destroy(&x_cond);
    
    return 0;
}