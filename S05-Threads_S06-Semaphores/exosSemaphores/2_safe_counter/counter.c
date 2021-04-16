/**
 * Mutex sur un counter
 * 
 * Protégez la mémoire partagée pour qu'il n'y ai pas de colision durant 
 * l'incrémentation du counter.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define ITER 10000

void* inc (void* counter_p)
{
    int* _counter_p = (int*)counter_p;
    for (int i = 0; i<ITER; i++)
        *_counter_p += 1;
    return NULL;
}


int main (void)
{
    pthread_t thread_a, thread_b, thread_c;
    int counter = 0;

    if (pthread_create(&thread_a, NULL, inc, &counter)) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_b, NULL, inc, &counter)) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_c, NULL, inc, &counter)) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread_a, NULL))
        perror("pthread_join");

    if (pthread_join(thread_b, NULL))
        perror("pthread_join");

    if (pthread_join(thread_c, NULL))
        perror("pthread_join");
    printf("Counter value %d: ", counter);

    printf("End execution\n") ;
    return (EXIT_SUCCESS);
}
