#include <stdio.h> 
#include <unistd.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <fcntl.h> 
#include <string.h> 
#include <stdlib.h> 
#define TAILLE 20 

void Erreur(const char *); 

void main() { 
   int fd, retour_mkfifo; 
   char Message[TAILLE+1]; 
   printf("\t COMMUNICATION PAR UN TUBE NOMME\n"); 
   
   if ((retour_mkfifo = mkfifo("mytube", S_IRUSR|S_IWUSR)) == -1) 
       Erreur("Mkfifo"); 
   
   printf("Tube cree \n");  

   if((fd = open("mytube", O_WRONLY)) == -1) 
       Erreur("Open ecriture"); 
   
   strcpy(Message, "test tube nomme"); 
   write(fd,Message,strlen(Message)+1); 
   printf("Message envoye par le createur: %s\n",Message); 
   close(fd); 

   if((fd = open("mytube", O_RDONLY)) == -1) 
      Erreur("Open lecture"); 

   read(fd,Message,TAILLE+1); 

   printf("Message recu par le createur: %s\n",Message); 
   close(fd); 
   unlink("mytube"); 
} 


void Erreur(const char * Message) 
{ 
  perror(Message); 
  exit(-1); 
}

