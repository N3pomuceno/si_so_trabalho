#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>

mtx_t mutex;

typedef struct param {
    int *vet;
    int *tam;
    int ident;
} Param;

/* 
Serão 3 casos para serem verificados:
1 - Sem Threads;
2 - Com Threads com semáforos;

*/

void imprime(int *vet,int tam){
    for (int i=0; i < tam; i++){
        printf("%d ",vet[i]);
    }
    printf("\n");
}

void *copia (int *v1, int *v2, int tam) {
    for (int i = 0; i < tam; i++){
        v2[i] = v1[i];
    }
}

void *remover (void *param) {
    Param *p = (Param *) param;
    // printf("%d\n", p->ident);  // Múltiplo
    // printf("%d\n", *(p->tam));
    for (int m = (*(p->tam) - 1); m >= 0; m--){
        mtx_lock(&mutex);
        if (p->vet[m] % p->ident == 0) {
            for (int n = m; n < (*(p->tam) -1); n++){
                p->vet[n] = p->vet[n+1];
            }
            *(p->tam) -= 1;
        }
        mtx_unlock(&mutex);
    }
    //printf("%d\n", *(p->tam));
    // mtx_lock(&mutex);
    // imprime(p->vet, *(p->tam));
    // mtx_unlock(&mutex);
}

int correct(int *v1, int *v2, int tam){
    for (int i = 0; i < tam; i++){
        if (v1[i] != v2[i]){
            return 0;
        }
    }
    return 1;
}

int main () {
    //Marcação de tempo;
    struct timespec start, end;
    // CRIAÇÃO DO VETOR.
    int tam = 100000;
    int tam2 = tam;

    // Alocação dinâmica:
    int *vet = (int *)malloc(sizeof(int)*tam);
    int *vet2 = (int *)malloc(sizeof(int)*tam);


    //Para checar se o vai de 1 a 100: srand(time(0));
    for (int i = 0; i < tam; i++){
        vet[i] = (rand() % 100) + 1;
    }

    copia(vet, vet2, tam);

    Param com_semaphore[2];
    for (int i = 0; i < 2; i++){
        com_semaphore[i].vet = vet2;
        com_semaphore[i].tam = &tam2;
    }
    com_semaphore[0].ident = 2;
    com_semaphore[1].ident = 5;

    //Caso1: Sem threads
    //imprime(vet, tam);
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }
    for (int i = tam-1; i >= 0; i--) {
        if ((vet[i] % 2 == 0)||(vet[i] % 5 == 0)){
            for (int j = i; j < tam - 1; j++){
                vet[j] = vet[j+1];
            }
            tam--;
        }
    }
    
    if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }

    long tempo_levado_sem_thread = (end.tv_sec - start.tv_sec)*1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Quantidade de nanosegundos que levou para fazer sem thread:\n %'ld ns.\n", tempo_levado_sem_thread);
    // printf("%d\n", tam);
    // Explicação, não é possível fazer esse caso sem a utilização de semáforos pois vai dar xabu

    //Caso2: Com threads com semáforos
    //Precisaria criar um outro vetor?
    //Inicializar as threads.
    int num_de_threads = 2;
    thrd_t threads[num_de_threads];
    int prot;

    if (mtx_init(&mutex, mtx_plain) != thrd_success){
            printf("Error initializing the mutex.\n");
            exit(1);
        }

    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }

    for (int i = 0; i < num_de_threads; i++){
        //com_semaphore[i].ident = i;
        prot = thrd_create(&threads[i], (thrd_start_t)remover,(void *)&com_semaphore[i]);
        if (prot == thrd_error) {
            printf("Error creating thread!\n");
            exit(1);
        }
    }

    for (int i = 0; i < num_de_threads; i++){
        thrd_join(threads[i], NULL);
    }

    if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }

    mtx_destroy(&mutex);

    long tempo_levado_com_semaforo = (end.tv_sec - start.tv_sec)*1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Quantidade de nanosegundos que levou para fazer com thread com semáforo:\n %'ld ns.\n", tempo_levado_com_semaforo);

    double razao = tempo_levado_sem_thread / (float)tempo_levado_com_semaforo;
    printf("Razão entre tempos: \n %f\n", razao);

    int correcao = correct(vet, vet2, tam);
    printf("Correção, se 1 está correto, se 0 está errado:\n %d \n", correcao);
    // imprime(vet, tam);
    // imprime(vet2, tam);

    free(vet);
    free(vet2);
    return 0;
}