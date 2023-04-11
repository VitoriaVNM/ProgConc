#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int vetor[5]; //vetor com os valores a serem duplicados

void *duplicador(void *threads_id){
   
    if(threads_id == 0){
        for(int e = 0; e < 5; e+=2){ //dobra os pares (even)
            vetor[e] = vetor[e]*2;
            printf("Número %d duplicado pela thread %ld \n", vetor[e], (long) threads_id);
        }
    }

    else{
        for(int o = 1; o < 5; o+=2){ //dobra os ímpares (odd)
            vetor[o] = vetor[o]*2;
            printf("Número %d duplicado pela thread %ld \n",vetor[o], (long) threads_id);
        }
    }
    
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[2]; //vetor com os ids das threads 
    int vetor_f[5];
    
    srand(time(NULL));
    printf("Vetor original...\n");
    for(int i = 0; i < 5; i++){ //loop de iniciação do vetor
        vetor[i] = rand() % 10;
        vetor_f[i] = vetor[i]; //guarda o vetor original
        printf("%d ", vetor[i]);
    }
    
    printf("\nCriando as threads...\n");
    for(long j = 0; j < 2; j++){
        pthread_create(&threads[j], NULL, duplicador, (void*) j);
    }

    //finalizando as threads
    for(int f = 0; f < 2; f++){
        pthread_join(threads[f], NULL);
    }
    
    //verificação
    printf("Vetor resultado...\n");
    for(int i = 0; i < 5; i++){ //loop de verificação
        if(vetor[i] / 2 == vetor_f[i]){
            printf("valor orginal: %d valor dobrado: %d \n", vetor_f[i], vetor[i]);
        }
        
    }
    
    return 0;
}

