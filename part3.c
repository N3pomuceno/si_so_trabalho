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

    //Para checar se o vai de 1 a 100: srand(time(0));
    for (int i = 0; i < tam; i++){
        vet[i] = (rand() % 100) + 1;
    }
    //imprime (vet, tam);

    //Caso1: Sem threads
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }
    //NÃO ESTÁ FUNCIONANDO AINDA
    int cont = 0;
    for (int i = 0; i < tam; i++){
        if((vet[i] % 2 == 0) || (vet[i] % 5 == 0)){
            vet[i] = 0;          
        } else {
            cont++;
        }
    }
    printf("%d\n", cont);
    int *vet_result = (int *)malloc(sizeof(int)*(cont));
    int cont2 = 0;
    for (int i = 0; i < tam; i++){
        if (vet[i] != 0){
            vet_result[cont2] = vet[i];
            cont2++;
        }
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
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }

    if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }
    long tempo_levado_sem_thread = (end.tv_sec - start.tv_sec)*1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Quantidade de nanosegundos que levou para fazer sem thread:\n %'ld ns.\n", tempo_levado_sem_thread);


    //Caso3: Com threads com semáforos
    // Deve adicionar o comando de tempo.

    free(vet_result);
    free(vet);
    return 0;
}