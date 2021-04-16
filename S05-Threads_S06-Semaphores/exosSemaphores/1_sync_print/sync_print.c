/**
 * Sérialiser deux threads
 *
 * Faites en sorte que le message "hello" soit affiché avant "bye".
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


void* hello()
{
    pthread_t t_id= pthread_self();
    printf("%s(from thread %lu)\n", "hello", t_id);
    return NULL;
}

void* bye()
{
    pthread_t t_id= pthread_self();
    printf("%s(from thread %lu)\n", "bye", t_id);
    return NULL;
}


int main (void)
{
    pthread_t thread_a, thread_b;

    if (pthread_create(&thread_a, NULL, bye, NULL)) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_b, NULL, hello, NULL)) {
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
