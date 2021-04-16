/**
 * Readers-writers problem
 *
 * 1. N'importe quel nombre de readers peut être dans la section critique simultanément.
 * 2. Les writers doivent avoir un accès exclusif à la section critique. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define ITER 3


void* writer(void* name)
{
    char* _name = (char*)name;

    for (int i = 0; i<ITER; i++){
        printf("%s writing ...", _name);
        sleep(1 + (int)(5.0*rand()/(RAND_MAX+1.0)));
        printf("end.\n");
        sleep(1 + (int)(5.0*rand()/(RAND_MAX+1.0)));
    }

    return NULL;
}

void* reader(void* name)
{
    char* _name = (char*)name;

    for (int i = 0; i<ITER; i++){

        printf("%s reading ... \n", _name);
        sleep(1 + (int)(5.0*rand()/(RAND_MAX+1.0)));
        printf(" %s end reading.\n", _name);

        sleep(1 + (int)(5.0*rand()/(RAND_MAX+1.0)));

    }

    return NULL;
}

int main (void)
{
    pthread_t thread_a, thread_b, thread_c, thread_d;

    if (pthread_create(&thread_a, NULL, writer, "wa")) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_b, NULL, writer, "wb")) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_c, NULL, reader, "rc")) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_d, NULL, reader, "rd")) {
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
