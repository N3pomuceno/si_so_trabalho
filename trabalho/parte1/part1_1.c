#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

void *identifier(void *id){
    // Pegando parâmetro de identificação e passando para casting de long.
    char *nome = (char *)id;

    // printf para colocar a frase desejada.
    printf ("Eu sou a %s e meu ID é %lu.\n", nome, thrd_current());
}

int main (void){

    // Definindo número de threads;
    int num_de_threads;
    char nome_da_thread[10];

    printf("Quantas threads deseja criar?\n");
    scanf("%d", &num_de_threads);

    // Criando threads:
    thrd_t threads[num_de_threads];

    //Variavel auxiliar para reconhecimento de error;
    int prot;

    for (int i = 0; i < num_de_threads; i++){

        // Função para criação de thread: thrd_create
        // Primeiro Argumento: thrd_t *__thr => Ponteiro para identificador da thread
        // Segundo  Argumento: thrd_start_t __func => Ponteiro para função que a thread irá executar
        // Terceiro Argumento: void *__arg => Argumento que pode ser levado para a função. 

        sprintf(nome_da_thread, "Thread_%d", (i+1));
        prot = thrd_create(&threads[i], (thrd_start_t)identifier, (void *)nome_da_thread);
        if (prot == thrd_error){
            printf("Erro na criação da thread\n");
            exit(1);
        }
        thrd_join(threads[i], NULL);
    }
    // Finaliza a atual execução de thread e libera recurso.
    return 0;
}