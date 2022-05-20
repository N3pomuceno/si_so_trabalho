#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <threads.h>
#include <unistd.h>
#include <sys/syscall.h>

void *identifier(void *id){
    char *nome = (char *)id;
    long ident2 = syscall(SYS_gettid);

    printf ("Eu sou a %s e meu ID pela threads.h é %lu,\njá pelo Sys/syscall é %lu.\n\n", nome, thrd_current(), ident2);
}

int main (void){

    // Definindo número de threads;
    int num_de_threads;
    printf("Quantas threads deseja criar?\n");
    scanf("%d", &num_de_threads);

    // Criando threads:
    thrd_t threads[num_de_threads];
    char nome_da_thread[10];

    //Variavel auxiliar para reconhecimento de error;
    int prot;

    for (int i = 0; i < num_de_threads; i++){

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

// Claramente os valores das ID's são diferentes e eles podem ser explicados por um cara online:
// Links de referência:
// https://stackoverflow.com/questions/19350212/which-linux-syscall-is-used-to-get-a-threads-id 
// https://linux.die.net/man/2/gettid
// https://www.delftstack.com/pt/howto/c/pthread-get-thread-id-in-c/ 
// https://stackoverflow.com/questions/21091000/how-to-get-thread-id-of-a-pthread-in-linux-c-program 
//
// Comentários importantes:
// gettid() returns the caller's thread ID (TID). In a single-threaded process, the thread ID is equal
// to the process ID (PID, as returned by getpid(2)).
// In a multithreaded process, all threads have the same PID, but each one has a unique TID. 
//
// POSIX thread IDs are not the same as the thread IDs returned by the Linux specific gettid() system call.
// POSIX thread IDs are assigned and maintained by the threading implementation.
// The thread ID returned by gettid() is a number (similar to a process ID) that is assigned by the kernel.
// Although each POSIX thread has a unique kernel thread ID in the Linux NPTL threading implementation,
// an application generally doesn’t need to know about the kernel IDs (and won’t be portable if it depends on knowing them).
// 
// Extra:
// Há 3 tipos de ID no Linux: pid, pthread id e tid;
// - pid: Global e equivalente ao parent process id, pode ser pego utilizando getpid; Num processo multithread
// todas as threads tem o mesmo pid, contudo cada uma tem um tid único.
// - pthread id (POSIX thread ID): Valor único do dentro do processo e somente na duração da devida thread. 
// Não é único através do sistema, nem através das threads que já terminaram e começaram. NÃO é visível fora do programa.
// Também é chamada de ID de Thread POSIX.
// - tid: É possível encontrá-lo como gettid, valor único através do processo e através do sistema, acrescentado no Linux 2.4
// e aparentemente não há em outras plataformas.
//
// Explicação:
// Tendo em vista 3 tipos de id, a diferença dos threads id está entre pthread id e tid. 
// Tid que é definido pela função do syscall, ele trás um número que é definido pelo kernel.
// Já o POSIX thread Id, que a gente pega pelo thrd_current, detalhe que a sua biblioteca é muito similar 
// em respeito com o POSIX standard, a gente vê que é definido pela implementação da thread. 
// A diferença do número é porque a definição vem de lugares diferentes. Um você pega do sistema e outro da implementação.
//