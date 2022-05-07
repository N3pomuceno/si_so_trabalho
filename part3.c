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
    // Criação de vetor.
    int tam = 10;
    int vet[tam];
    for (int i = 0; i < tam; i++){
        vet[i] = (rand() % 100) + 1;
    }
    //Checagem de vetor:
    srand(time(0));
    for (int i = 0; i < tam; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");

    return 0;
}