#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>

void main()
{
  char ch;
  int nb_lu, p[2], retour;
  retour=pipe(p);

  if (retour==-1) 
    perror("erreur pipe:");
/*
   nb_lu=write(p[1], "A",1);
     if (nb_lu==-1) 
     perror("erreur write:");
   else 
     printf("Retour du write %d\n", nb_lu);
*/
   //close(p[1]); /*ligne une fois en commentaire une fois non */
   nb_lu=read(p[0], &ch,1);

   if (nb_lu==-1) 
     perror("erreur read:");
   else 
     printf("Retour du read %d\n", nb_lu);
   
   nb_lu=read(p[0], &ch,1);

   if (nb_lu==-1) 
     perror("erreur read:");
   else 
     printf("Retour du read %d\n", nb_lu);
   
   close(p[0]);
}
