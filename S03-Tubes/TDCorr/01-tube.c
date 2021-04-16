#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>


/*
Fils : W
Pere : R
Pere : W
Fils : R
	
*/
/*
int main ()
{

	pid_t ppid, pid;
        int p[2];
        char msg[20];

        if (pipe(p) == -1)
        {
            perror ("pipe");
            exit(-1);
        }
        
	pid = fork();

	switch (pid)
	{
		case -1:
			perror ("fork");
			exit(-1);
		case  0:
			ppid = getppid();


			strcpy(msg, "Salut Papa");
                        if (write (p[1], msg, sizeof(msg)) == -1)
                            perror ("write");
                        
                        fprintf(stdout, "Fils : message envoye : %s\n",msg);
			sleep(3);

			if (kill(ppid, SIGCONT)== -1)
				perror ("kill");

			if (kill(getpid(), SIGSTOP)== -1)
				perror ("kill");

                        if (read (p[0], msg, sizeof(msg)) == -1)
                            perror ("read");
                        
                        fprintf(stdout, "Fils : message recu : %s\n",msg);
			sleep(3);

                        close(p[0]);
                        close(p[1]);
			break;
					
		default:
			if (kill(getpid(), SIGSTOP)== -1)
				perror ("kill");

                        if (read (p[0], msg, sizeof(msg)) == -1)
                            perror ("read");
                        
                        fprintf(stdout, "Pere : message recu : %s\n",msg);
			sleep(3);

                        strcpy(msg, "Salut Fils");
                        if (write (p[1], msg, sizeof(msg)) == -1)
                            perror ("write");
                        
                        fprintf(stdout, "Pere : message envoye : %s\n",msg);
			sleep(3);                        
			
			if (kill(pid, SIGCONT)== -1)
				perror ("kill");

			wait(NULL);

                        close(p[0]);
                        close(p[1]);
			break;
	}



	return EXIT_SUCCESS;
}

*/


/*
 * Fils --> p1 --> Pere
 * Fils <-- p2 <-- Pere
 * 
 * 
 */


int main ()
{
    int p1[2], p2[2];
    char msg [20];
    
    pipe(p1);
    pipe(p2);
    
    
    switch(fork())
    {
        case -1:
            perror ("fork");
            exit(-1);
        case  0:
            close(p1[0]);
            close(p2[1]);

            
            strcpy(msg, "Salut Papa");
            if (write (p1[1], msg, sizeof(msg)) == -1)
                perror ("write");
            
            fprintf(stdout, "Fils : message envoye : %s\n",msg);
            
            if (read (p2[0], msg, sizeof(msg)) == -1)
                perror ("read");
            
            fprintf(stdout, "Fils : message recu : %s\n",msg);
            
            close(p1[1]);
            close(p2[0]);
            break;
        default:
            close(p1[1]);
            close(p2[0]);
            
            sleep(3);           
            if (read (p1[0], msg, sizeof(msg)) == -1)
                perror ("read");
            
            fprintf(stdout, "Pere : message recu : %s\n",msg); 
            
           strcpy(msg, "Salut Fils");
            if (write (p2[1], msg, sizeof(msg)) == -1)
                perror ("write");
            
            fprintf(stdout, "Pere : message envoye : %s\n",msg); 
            
            wait(NULL);
            
            close(p1[0]);
            close(p2[1]);
    }
    
    
    
    
    return EXIT_SUCCESS;
}













