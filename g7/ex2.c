#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
typedef void (*sighandler_t)(int);

int shutdown = -1;

void shuttdown (int signum) {
    _exit(1);   
}


int main (int argc, char *argv[]) {
    if(signal(SIGINT,shuttdown)==SIG_ERR) {
        perror("SIGINT Error");
        return 1;
    }

    int i, pids[argc-2];
    for (i=2;i<argc;i++) {
        if ((pids[i-2] = fork())==0) {
            execlp("grep","grep",argv[1],argv[i],NULL);
            _exit(0);
        }

    }

    int status, pidAux;

    while (shutdown!=0) {
        pidAux = wait(&status);
        shutdown = WEXITSTATUS(status);
    }

    for (i=0;i<argc-2;i++) {
        if (pids[i]!=pidAux) kill(pids[i],SIGINT);
    }
    

} 