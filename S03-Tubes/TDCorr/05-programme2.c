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
 int fd_access, fd;
 char Message[TAILLE + 1];
 
 do
   fd_access = access("mytube",R_OK);
 while(fd_access == -1);

 if((fd = open("mytube",O_RDONLY))== -1)
     Erreur("Open lecture:");
 
 read(fd,Message,TAILLE+1);
 printf("Message recu par le consultant: %s\n",Message);
 close(fd);

 if ((fd = open("mytube",O_WRONLY)) == -1)
    Erreur("open ecriture");

 strcpy(Message, "retour test");
 write(fd,Message,strlen(Message)+1);
 printf("Message envoye par le consultant : %s\n",Message);
 close(fd);
}
 
 void Erreur (const char * Message){
   perror(Message);
   exit(-1);
}
