/**
 * Le rendez-vous ou barrier à 2 threads.
 *
 * a1 doit être executé avant b2 et b1 avant a2.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void* f_ta ()
{
    printf(" ==== a1 ====\n");
    printf(" ==== a2 ====\n");
    return NULL;
}

void* f_tb ()
{
    printf(" ==== b1 ====\n");
    printf(" ==== b2 ====\n");
    return NULL;
}


int main (void)
{
    pthread_t thread_a, thread_b;

    if (pthread_create(&thread_b, NULL, f_tb, NULL)) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_a, NULL, f_ta, NULL)) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread_a, NULL))
        perror("pthread_join");

    if (pthread_join(thread_b, NULL))
        perror("pthread_join");

    printf("End execution\n") ;
    return (EXIT_SUCCESS);
}
