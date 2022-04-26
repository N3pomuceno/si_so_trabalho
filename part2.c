#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

void imprime(int **mat){
    for (int i = 0; i <10; i++){
        for (int j = 0; j < 10; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void *soma(){

}

int main(void) {
    // Criação de matrizes A, B, C.
    int **A, **B, **C;
    int dim = 10;

    A = (int **)malloc(sizeof(int *)*dim);
    B = (int **)malloc(sizeof(int *)*dim);
    C = (int **)malloc(sizeof(int *)*dim);

    for (int i = 0; i < dim; i++){
        A[i] = (int *)malloc(sizeof(int)*dim);
        B[i] = (int *)malloc(sizeof(int)*dim);
        C[i] = (int *)malloc(sizeof(int)*dim);
    }

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }
    imprime(A);

    // Criação de 4 threads

    // Liberando a matriz
    for (int i = dim -1; i > 0; i--){
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}