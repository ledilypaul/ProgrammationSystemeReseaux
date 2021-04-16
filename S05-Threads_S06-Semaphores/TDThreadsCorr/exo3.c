#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void printNum (int num)
{
    for (int i = 0; i < 3; i++)
    {
        sleep(1);
        printf("thread numero %d\n", num);
    }
    
}

void * helloworld(void * arg)
{
    pthread_mutex_lock(&mutex);
    printNum(* (int *)arg);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char** argv)
{
    int i, nb, ret;
    int * args;
    pthread_t * threads;
    if (argc == 2)
        nb = atoi(argv[1]);
    else
        nb = 4;
   
    threads = malloc (nb * sizeof(pthread_t));
    args = malloc (nb * sizeof(int));
    
    for (i = 0; i < nb; i++)
    {
        args[i] = i;
        if ((ret = pthread_create(&threads[i], NULL, helloworld, &args[i])) != 0)
        {
            fprintf(stderr, "%s\n", strerror(ret));
            exit (EXIT_FAILURE);
        }
    }
    for (i = 0; i < nb; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("Fin du traitement ...\n");
    
	return EXIT_SUCCESS;
}
