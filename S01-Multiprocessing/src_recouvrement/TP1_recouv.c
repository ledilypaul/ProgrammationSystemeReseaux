#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	pid_t pid;

	if (argc != 4) {
		printf("usage: %s <nom_du_programme_calcul> <operande_1> <operande_2>\n", argv[0]);
		exit(10);
	}
	switch(pid=fork()) {
		case -1:
			printf("fork impossible...\n");
			exit(5);
		case 0:
			execlp(argv[1], argv[1], argv[2], argv[3], NULL);
			printf("Recouvrement du code de %s impossible...", argv[1]);
			exit(15);
		default:
			wait(NULL);
	}
	return 0;
}
