#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<signal.h>

void handler_SigPipe(int sig);
void main() 
{

 struct sigaction action;
 int nb_ecrit, p[2], retour;
 action.sa_handler=handler_SigPipe;
 retour=sigaction(SIGPIPE, &action, NULL);

 if (retour==-1) 
     perror("erreur sigaction:");

 retour=pipe(p);
 if (retour==-1) 
     perror("erreur pipe:");

 //close(p[0]); /*ligne une fois en commentaire une fois non*/
 nb_ecrit=write(p[1], "A",1);

 if (nb_ecrit==-1) 
     perror("erreur write:");
 else 
     printf("Retour du write %d\n", nb_ecrit);

 close(p[1]);
 //sleep(3);
}

void handler_SigPipe(int sig) 
{
 printf("Signal intercepte %d\n",sig);
}
