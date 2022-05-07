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

void *remover () {

}

int correct(){

}

int main () {
    // CRIAÇÃO DO VETOR.
    int tam = 10;
    
    // Alocação dinâmica:
    int *vet = (int *)malloc(sizeof(int)*tam);

    //Para checar se o vai de 1 a 100: srand(time(0));
    for (int i = 0; i < tam; i++){
        vet[i] = (rand() % 100) + 1;
    }

    //Caso1:

    //Caso2:

    //Caso3:

    free(vet);
    return 0;
}