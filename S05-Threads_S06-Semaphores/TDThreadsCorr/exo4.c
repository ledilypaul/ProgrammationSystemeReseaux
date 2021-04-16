#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define N 2

/*
 * M = a  b
 *     c  d
 * 
 * 
 * 
 * M² = a*a+ b*c   a*b+b*d
 *      a*c+b*d    b*c+b*d 
 */

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int M[N][N];
int carre[N][N];

void * calculCarre(void * arg)
{
    int a,b,c,d;
    a = M[0][0]; 
    b = M[0][1];
    c = M[1][0];
    d = M[1][1];
    
    switch (*(int*)arg)
    {
        case 0:
            carre[0][0] =  a*a+b*c;
            pthread_exit(0);
        case 1:
            carre[0][1] =  a*b+b*d;
            pthread_exit(0);
        case 2:
            carre[1][0] =  a*c+b*d;
            pthread_exit(0);
        case 3:
            carre[1][1] =  b*c+b*d;
            pthread_exit(0);
    }
}


int main(int argc, char** argv)
{
    int i, ret;
    int * args;
    pthread_t * threads;
    
    
    M[0][0] = 1; 
    M[0][1] = 2;
    M[1][0] = 3;
    M[1][1] = 4;
    
    threads = malloc (4 * sizeof(pthread_t));
    args = malloc (4 * sizeof(int));
    
    for (i = 0; i < 4; i++)
    {
        args[i] = i;
        if ((ret = pthread_create(&threads[i], NULL, calculCarre, &args[i])) != 0)
        {
            fprintf(stderr, "%s\n", strerror(ret));
            exit (EXIT_FAILURE);
        }
    }
    
    
    
    for (i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }
     printf("Fin du traitement ...\n");

	for (i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			printf("%d ", M[i][j]);

	printf("\n");

	for (i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			printf("%d ", carre[i][j]);
    
    printf("\n");
     
    return EXIT_SUCCESS;
}