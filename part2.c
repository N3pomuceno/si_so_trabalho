#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <threads.h>

/* 
COISAS PARA FAZER:
referência: https://stackoverflow.com/questions/19527965/cast-to-pointer-from-integer-of-different-size-pthread-code

- Começar a escrever a função soma, levando em conta os parâmetros dentro do struct para poder aplicar 
as somas das duas matrizes levando em conta qual thread está, tentando mudar de quadrante a partir do número k.
- Ler o material de prioridade e troca de prioridade sobre o processo.
Links: 
https://www.tecmint.com/set-linux-process-priority-using-nice-and-renice-commands/amp/ 
https://www.ibm.com/docs/en/aix/7.2?topic=processes-changing-priority-running-process-renice-command
- Talvez ter que descobrir o PID para ter que alguma ideia de como alterar a prioridade do programa.

*/

// Struct para enviar vários parâmetros dentro da função de thrd_create : https://stackoverflow.com/questions/1352749/multiple-arguments-to-function-called-by-pthread-create 
typedef struct arg_struct {
    int **arg1; // Matriz A
    int **arg2; // Matriz B
    int **arg3; // Matriz C
    int arg4;   // Dimensão
    int arg5;   // Identificação de Thread
}Args;

// void imprime(int **mat){
//     for (int i = 0; i <1000; i++){
//         for (int j = 0; j < 1000; j++){
//             printf("%d ", mat[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }



void *soma(void *param){
    int i, j;
    Args *args = (Args *)param;
    if (args-> arg4 == 1) {
        for (i=0; i <500; i++){
            for (j = 0; j <500; j++){
                args->arg3[i][j] = args->arg1[i][j] + args->arg2[i][j];
            }
        }
    } else if ( args -> arg4 == 2 ) {
        for (i=500; i <1000; i++){
            for (j = 0; j <500; j++){
                args->arg3[i][j] = args->arg1[i][j] + args->arg2[i][j];
            }
        }
    } else if ( args -> arg4 == 3 ) {
        for (i=0; i <500; i++){
            for (j = 500; j <1000; j++){
                args->arg3[i][j] = args->arg1[i][j] + args->arg2[i][j];
            }
        }
    } else {
        for (i=500; i < 1000; i++){
            for (j = 500; j <1000; j++){
                args->arg3[i][j] = args->arg1[i][j] + args->arg2[i][j];
            }
        }
    }

}

int main(void) {
    // Para marcação de tempo
    struct timespec start, end;

    // Criação de matrizes A, B, C.
    int **A, **B, **C;
    int dim = 1000;

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

    // CALCULO SEM THREAD (falta adicionar o tempo ainda)
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
        if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
        printf("Error: clock_gettime failed\n");
        exit(1);
    }
    // Tempo levado:
    long tempo_levado_sem_thread = (end.tv_sec - start.tv_sec)*1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Quantidade de nanosegundos que levou para fazer a soma sem thread:\n %ld ns.\n", tempo_levado_sem_thread);


    // CALCULO COM 4 THREADS:
    // Argumentos:
    Args argumentos;
    argumentos.arg1 = A;
    argumentos.arg2 = B;
    argumentos.arg3 = dim;

    int num_de_threads = 4;
    thrd_t threads[num_de_threads];
    int prot;

    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
    printf("Error: clock_gettime failed\n");
    exit(1);
    }
    for (int k = 0; k < num_de_threads; k++) {
        argumentos.arg4 = k;
        prot = thrd_create(&threads[k], (thrd_start_t)soma, (void *)&argumentos);
    }
    for (int l = 0; l < num_de_threads; l++) {
        thrd_join(threads[l], NULL);
    }

    if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
    printf("Error: clock_gettime failed\n");
    exit(1);
    }

    // Tempo levado:
    long tempo_levado_com_thread = (end.tv_sec - start.tv_sec)*1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Quantidade de nanosegundos que levou para fazer a soma com thread:\n %ld ns.\n", tempo_levado_com_thread);

    // Liberando as matrizes
    for (int i = dim -1; i >=0; i--){
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    thrd_exit(0);
}