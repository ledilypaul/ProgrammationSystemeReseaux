#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>



void * helloworld(void * arg)
{
    printf("Hello world de %d ! pid = %d pthread_self = %p \n", *(int *) arg, getpid(), (void *) pthread_self());
    //printf("Hello world ! pid = %d pthread_self = %p \n", getpid(), (void *) pthread_self());
    //sleep(5);
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
        //if ((ret = pthread_create(&threads[i], NULL, helloworld, (void *)i)) != 0)
        {
            fprintf(stderr, "%s\n", strerror(ret));
            exit (EXIT_FAILURE);
        }
    }
    
    
    
    for (i = 0; i < nb; i++)
    {
        pthread_join(threads[i], NULL);
    }
     printf("Fin du traitement ...\n");
     return EXIT_SUCCESS;
}