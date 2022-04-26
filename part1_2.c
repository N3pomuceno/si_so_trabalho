#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <threads.h>
#include <unistd.h>
#include <sys/syscall.h>

void *identifier(void *id){
    long ident = (intptr_t)id;
    long ident2 = syscall(SYS_gettid);
    printf ("Eu sou a thread %ld e meu ID pela threads.h é %lu,\njá pelo Sys/syscall é %lu.\n\n", ident, thrd_current(), ident2);
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

// Claramente os valores das ID's são diferentes e eles podem ser explicados por um cara online:
// Links de referência:
// https://stackoverflow.com/questions/19350212/which-linux-syscall-is-used-to-get-a-threads-id 
// https://linux.die.net/man/2/gettid
// https://www.delftstack.com/pt/howto/c/pthread-get-thread-id-in-c/ 
// https://stackoverflow.com/questions/21091000/how-to-get-thread-id-of-a-pthread-in-linux-c-program 
//
// Comentários importante:
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
// Há 3 tipos de thread ID: pid, pthread id e tid;
// - pid: Global e equivalente ao parent process id, pode ser pego utilizando getpid;
// - pthread id (POSIX thread ID): Valor único do dentro do processo e somente na duração da devida thread. 
// Não é único através do sistema, nem através das threads que já terminaram e começaram. NÃO é visível fora do programa.
// Também é chamada de ID de Thread POSIX.
//
// Basicamente quando utilizando o gettid do sys, nós pegamos um PID, que é uma thread única do processo.
// Já quando pegando o thrd_current, que está de acordo com os padrões do POSIX
// ( Portable Operating System Interface for Unix) estamos pegando o um outro valor, que seria um ponteiro que aponta para algum estrutura,
// dependendo da plataforma. 