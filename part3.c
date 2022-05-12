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
    // CRIAÇÃO DO VETOR.
    int tam = 30;
    
    // Alocação dinâmica:
    int *vet = (int *)malloc(sizeof(int)*tam);

    //Para checar se o vai de 1 a 100: srand(time(0));
    for (int i = 0; i < tam; i++){
        vet[i] = (rand() % 100) + 1;
    }
    imprime (vet, tam);

    //Caso1: Sem threads
    // Deve adicionar o comando de tempo.

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
    imprime(vet, tam);
    imprime(vet_result, cont);

    //Caso2: Com threads sem semáforos
    // Deve adicionar o comando de tempo.


    //Caso3: Com threads com semáforos
    // Deve adicionar o comando de tempo.

    free(vet_result);
    free(vet);
    return 0;
}