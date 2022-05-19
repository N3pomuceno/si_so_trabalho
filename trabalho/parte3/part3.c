#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>

mtx_t *mtx;
int mtx_init(mtx_t *mtx, int mtx_plain);

typedef struct param {
    int *vet;
    int tam;
    int ident;
} Param;

/* 
Serão 3 casos para serem verificados:
1 - Sem Threads;
2 - Com Threads sem semáforos;
3 - Com Threads com semáforos;

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
    if (p->ident == 0){  // Caso múltiplo de 2
        for (int i = p->tam - 1; i >= 0; i--){
            if (p->vet[i] % 2 == 0) {
                int mtx_lock(mtx_t *mtx);
                for (int j = i; j < p->tam -1; j++){
                    p->vet[j] = p->vet[j+1];
                }
                p->tam--;
                int mtx_unlock(mtx_t *mtx);
            }
        }
    } else { // Caso múltiplo de 5
        for (int i = p->tam - 1; i >= 0; i--){
            if (p->vet[i] % 5 == 0) {
                int mtx_lock(mtx_t *mtx);
                for (int j = i; j < p->tam -1; j++){
                    p->vet[j] = p->vet[j+1];
                }
                p->tam--;
                int mtx_unlock(mtx_t *mtx);
            }
        }
    }
}

int correct(int *v1, int *v2, int tam){
    for (int i = 0; i < tam; i++){
        if (v1[i] != v2[2]){
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
    //imprime (vet, tam);

    copia(vet, vet2, tam);

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
    
    // imprime(vet, tam);
    if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }
    //imprime(vet, tam);
    long tempo_levado_sem_thread = (end.tv_sec - start.tv_sec)*1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Quantidade de nanosegundos que levou para fazer sem thread:\n %'ld ns.\n", tempo_levado_sem_thread);

    // Explicação, não é possível fazer esse caso sem a utilização de semáforos pois 

    //Caso2: Com threads com semáforos
    //Precisaria criar um outro vetor?
    //Inicializar as threads.
    Param *sem_semaphore;
    sem_semaphore->tam = tam2;
    sem_semaphore->vet = vet2;

    int num_de_threads = 2;
    thrd_t threads[num_de_threads];
    int prot;

    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }



    for (int i = 0; i < num_de_threads; i++){
        sem_semaphore->ident = i;
        prot = thrd_create(&threads[i], (thrd_start_t)remover, (void *)sem_semaphore);
        if (prot == thrd_error) {
            printf("Error creating thread!\n");
            exit(1);
        }
    }
    for (int i = 0; i < num_de_threads; i++){
        thrd_join(threads[i], NULL);
    }

    //Faz sentido colocar isso aqui?
    //void mtx_destroy(mtx_t *mtx);

    if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }
    long tempo_levado_com_semaforo = (end.tv_sec - start.tv_sec)*1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Quantidade de nanosegundos que levou para fazer com thread com semáforo:\n %'ld ns.\n", tempo_levado_com_semaforo);

    int correcao = correct(vet, sem_semaphore->vet, tam);

    free(vet);
    free(vet2);
    return 0;
}