/**
 * Contrôle de flux
 *
 * Faites en sorte de controler le nombre de threads qui peuvent "faire quelque chose".
 * Autrement dit, LIMIT threads doivent être en section critique.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define LIMIT 2
#define ITER 5

void* do_something (void* name)
{
    char* _name = (char*)name;

    for (int i = 0; i<ITER; i++){
        printf("%s start doing something ...\n", _name);
        sleep(1 + (int)(5.0*rand()/(RAND_MAX+1.0)));
        printf("%s end.\n", _name);
        sleep(1 + (int)(5.0*rand()/(RAND_MAX+1.0)));
    }

    return NULL;
}

int main (void)
{
    pthread_t thread_a, thread_b, thread_c, thread_d;

    if (pthread_create(&thread_a, NULL, do_something, "A")) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_b, NULL, do_something, "B")) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_c, NULL, do_something, "C")) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_d, NULL, do_something, "D")) {
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
