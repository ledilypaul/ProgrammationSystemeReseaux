#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>



int main (void)
{
	FILE * question;
	FILE * reponse;
	int fd;
	char nom_fifo[128];
	char chaine[128];
	
	fprintf(stdout, "Chaîne à traiter : ");
	if (fgets (chaine, 128, stdin) == NULL)
		exit (0);
	
	sprintf(nom_fifo, "anagramme.%ld", (long) getpid());
	if (mkfifo(nom_fifo, 0644) != 0)
	{
		fprintf(stderr, "Impossible de créer le noeud Fifo \n");
		exit(EXIT_FAILURE);
	}
	if ((fd = open("anagramme.fifo", O_WRONLY)) < 0)
	{
		fprintf(stderr, "Impossible d’ouvrir la Fifo \n");
		exit(EXIT_FAILURE);
	}

	question = fdopen(fd, "w");
	fprintf(question, "%s\n%s", nom_fifo, chaine);
	fclose(question);
//	sleep(4);
	fd = open(nom_fifo, O_RDONLY);
	reponse = fdopen(fd, "r");

	if (fgets(chaine, 128, reponse) != NULL)
		fprintf(stdout, "Réponse = %s\n", chaine);
	else
		perror("fgets");
	
	fclose(reponse);
	unlink(nom_fifo);
	
	return EXIT_SUCCESS;
}
