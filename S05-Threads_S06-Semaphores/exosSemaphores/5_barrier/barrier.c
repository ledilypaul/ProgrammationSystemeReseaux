/**
 * Barrier ou rendezvous à n threads.
 *
 * Tout les threads doivent avoir finis les tâches 1 avant de faire les 2.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void* f(void* name)
{
    char* _name = (char*)name;
    printf(" ==== %s1 ====\n", _name);
    // TODO: Barrier ...
    printf(" ==== %s2 ====\n", _name);
    return NULL;
}

int main (void)
{
    pthread_t thread_a, thread_b, thread_c, thread_d;

    if (pthread_create(&thread_a, NULL, f, "a")) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_b, NULL, f, "b")) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_c, NULL, f, "c")) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_d, NULL, f, "d")) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread_a, NULL))
        perror("pthread_join");

    if (pthread_join(thread_b, NULL))
        perror("pthread_join");

    if (pthread_join(thread_c, NULL))
        perror("pthread_join");

    if (pthread_join(thread_d, NULL))
        perror("pthread_join");

    printf("End execution\n") ;
    return (EXIT_SUCCESS);
}
