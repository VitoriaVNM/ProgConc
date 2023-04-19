#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int vetor[10000]; //vetor com os valores a serem duplicados

void *duplicador(void *threads_id){
   
    if(threads_id == 0){
        for(int e = 0; e < 10000; e+=2){ //dobra os pares (even)
            vetor[e] = vetor[e]*2;
            //printf("Número %d duplicado pela thread %ld \n", vetor[e], (long) threads_id);
        }
    }

    else{
        for(int o = 1; o < 10000; o+=2){ //dobra os ímpares (odd)
            vetor[o] = vetor[o]*2;
            //printf("Número %d duplicado pela thread %ld \n",vetor[o], (long) threads_id);
        }
    }
    
    pthread_exit(NULL);
}


int main()
{
    pthread_t threads[2]; //vetor com os ids das threads
    srand(time(NULL));
    //printf("Vetor original...\n");
    
    for(int i = 0; i < 10000; i++){ //loop de iniciação do vetor
        vetor[i] = 2;
        //printf("%d \n", vetor[i]);
    }
    
    printf("Criando as threads...\n");
    for(long j = 0; j < 2; j++){
        pthread_create(&threads[j], NULL, duplicador, (void*) j);
    }

    printf("Finalizando as threads...\n");
    for(int f = 0; f < 2; f++){
        pthread_join(threads[f], NULL);
    }
    
    for(int k = 0; k < 10000; k++){
        if(vetor[k] / 2 != 2){
            if(k % 2 != 0) printf("Erro na thread ímpar");
            else { printf("Erro na thread par");}
        }
    }
    printf("Vetor dobrado com sucesso!");
    
    return 0;
}

