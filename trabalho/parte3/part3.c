#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <semaphore.h>
#include <time.h>

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

void *remover () {

}

int correct(){

}

int main () {
    //Marcação de tempo;
    struct timespec start, end;
    // CRIAÇÃO DO VETOR.
    int tam = 100000;
    
    // Alocação dinâmica:
    int *vet = (int *)malloc(sizeof(int)*tam);
    int *vet2 = (int *)malloc(sizeof(int)*tam);
    int *vet3 = (int *)malloc(sizeof(int)*tam);

    //Para checar se o vai de 1 a 100: srand(time(0));
    for (int i = 0; i < tam; i++){
        vet[i] = (rand() % 100) + 1;
    }
    //imprime (vet, tam);

    copia(vet, vet2, tam);
    copia(vet, vet3, tam);

    //Caso1: Sem threads
    //REFAZER
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }
    

    // imprime(vet, tam);
    // imprime(vet_result, cont);
    if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }
    long tempo_levado_sem_thread = (end.tv_sec - start.tv_sec)*1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Quantidade de nanosegundos que levou para fazer sem thread:\n %'ld ns.\n", tempo_levado_sem_thread);


    //Caso2: Com threads sem semáforos
    //Precisaria criar um outro vetor?
    //Inicializar as threads.

    int num_de_threads = 2;
    thrd_t threads[num_de_threads];
    int prot;

    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }
    for (int i = 0; i < 2; i++){
        prot = thrd_create(&threads[i], (thrd_start_t)remover, (void *)vet);
    }

    if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }
    long tempo_levado_com_thread = (end.tv_sec - start.tv_sec)*1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Quantidade de nanosegundos que levou para fazer com thread sem semáforo:\n %'ld ns.\n", tempo_levado_sem_thread);


    //Caso3: Com threads com semáforos


    free(vet);
    free(vet2);
    free(vet3);
    return 0;
}