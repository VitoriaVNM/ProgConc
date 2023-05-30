#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5 //tamamho do buffer
#define prod 3 //numero de produtores
#define cons 3 //numero de consumidores

sem_t bufferFULL, bufferEMPTY; //variaveis condicionais
sem_t mutexProd, mutexCons; //variaveis de exclusão mutua
int buffer[N];

void* insere(void *idt){
    static int in = 0;
    static int elemento = 0;
    int *idp = (int*) idt;
    
    printf("thread produtora %d: Pode inserir o item?\n", *idp);
    sem_wait(&bufferEMPTY); //aguarda buffer vazio.
    sem_wait(&mutexProd); //exclusão mutua: trava as produtoras depois dela
    printf("thread produtora %d: Inserindo item...\n", *idp);
    
    elemento++;
    buffer[in] = elemento;
    in = (in + 1) % N;
    
    printf("thread produtora %d: O elemento inserido é %d\n", *idp, elemento);
    printf("thread produtora %d: Sinalizando buffer cheio.\n", *idp);
    sem_post(&mutexProd); //exclusão mutua: libera a proxima produtora
    sem_post(&bufferFULL); //sinaliza para os consumidores
 
    pthread_exit(NULL);
}

void* retira(void *idt){
    static int out = 0;
    static int soma = 0;
    int *idc = (int*) idt;
    int item;
    
    printf("thread consumidora %d: Pode retirar o item?\n", *idc);
    sem_wait(&bufferFULL);
    sem_wait(&mutexCons);//exclusão mutua: trava as consumidoras depois dela
    printf("thread consumidora %d: Retirando item...\n", *idc);
    item = buffer[out];
    out = (out + 1) % N;
    printf("thread consumidora %d: O item retirado é o %d\n", *idc, item);
    printf("thread consumidora %d: Sinalizando buffer vazio.\n", *idc);
    sem_post(&mutexCons); //exclusão mutua: libera a proxima consumidora
    sem_post(&bufferEMPTY); //sinaliza para as produtoras

    pthread_exit(NULL);
}


int main()
{
    
    //vetor de threads
    pthread_t threads[prod+cons];
    int idt[prod+cons]; 
    
    //inicia os semaforos
    sem_init(&bufferFULL, 0,0);
    sem_init(&bufferEMPTY, 0, N);
    sem_init(&mutexProd, 0,1);
    sem_init(&mutexCons, 0, 1);
    
    
    //cria as threads produtoras
    for(int p = 0; p < prod; p++){
        idt[p] = p+1;
        pthread_create(&threads[p], NULL, insere, (void*) &idt[p]);
    }
    
    //cria as trheads consumidoras
    for(int c = 0; c < cons; c++){
        idt[c+prod] = c+1;
        pthread_create(&threads[c+prod], NULL, retira, (void*) &idt[c+prod]);
    }
    
    //espera as threads finalizarem
    for(int f = 0; f < prod+cons; f ++){
        pthread_join(threads[f], NULL);
    }
    
    
    //finaliza os semaforos
    sem_destroy(&bufferFULL);
    sem_destroy(&bufferEMPTY);
    sem_destroy(&mutexProd);
    sem_destroy(&mutexCons);


    return 0;
}