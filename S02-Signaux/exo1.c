#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
    pid_t pid, ppid;
    
    struct sigaction action;

    pid = fork();

    switch (pid)
    {
    case -1:
        perror("fork");
        exit(-1);
    case 0:
        ppid = getppid();

    
    default:
        break;
    }
}