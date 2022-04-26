#include <stdio.h>
#include <threads.h>

void imprime(int *mat){
    for (int i = 0; i <10; i++){
        for (int j = 0; j < 10; j++){
            printf("%d ", mat[i][j]);
        }
    }
}

void *soma(){

}

int main(void) {
    // Criação de matrizes A, B, C.
    int A[10][10], B[10][10], C[10][10];

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }
    imprime(&A);

    // Criação de 4 threads

    // Impressão da matriz
}