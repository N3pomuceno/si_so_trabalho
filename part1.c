#include <stdio.h>
#include <threads.h>

void identifier (void *id){
    long ident;
    ident = (long) id;

    printf ("Eu sou a thread %ld e meu ID é %lu", ident, thrd_current());
}

int main (void){
    // Definindo número de threads;
    int num_de_threads;
    scanf("%d", &num_de_threads);

    // Criando threads:
    thrd_t threads[num_de_threads];

    //Variavel auxiliar para reconhecimento de error;
    int prot;

    for (int i = 0; i < num_de_threads; i++){

        // Função para ciração de thread: thrd_create
        // Primeiro Argumento: thrd_t *__thr => Ponteiro para identificador da thread
        // Segundo Argumento : thrd_start_t __func => Ponteiro para função que a thread irá executar
        // Terceiro Argumento: void *__arg => Argumento que pode ser levado para a função. 
        prot = thrd_create(&threads[i], (thrd_start_t) identifier, (void *) i);
        if (prot == thrd_error){
            printf("Erro na criação da thread\n");
            exit(1);
        }
    }
    return 0;
}