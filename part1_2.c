#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <threads.h>
#include <unistd.h>
#include <sys/syscall.h>

void *identifier(void *id){
    long ident = (intptr_t)id;
    long ident2 = syscall(SYS_gettid);
    printf ("Eu sou a thread %ld e meu ID pela threads.h é %lu,\njá pelo Sys/syscall é %lu.\n", ident, thrd_current(), ident2);
    printf ("\n");
}

int main (void){

    // Definindo número de threads;
    int num_de_threads;
    printf("Quantas threads deseja criar?\n");
    scanf("%d", &num_de_threads);

    // Criando threads:
    thrd_t threads[num_de_threads];

    //Variavel auxiliar para reconhecimento de error;
    int prot;

    for (int i = 0; i < num_de_threads; i++){

        prot = thrd_create(&threads[i], (thrd_start_t)identifier, (void *)(intptr_t)i);
        if (prot == thrd_error){
            printf("Erro na criação da thread\n");
            exit(1);
        }
    }
    // Finaliza a atual execução de thread e libera recurso.
    thrd_exit(0);
}