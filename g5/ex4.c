#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

int main (int argc,char *argv[]) {


    int pp[2];

    if (pipe(pp)<0) perror("pipe");


    if (fork()==0) {
        close(pp[1]);

        dup2(pp[0],0);
        close(pp[0]);
        execlp("wc","wc","-l",NULL);

        _exit(1);
    }

    if (fork()==0) {
        close(pp[0]);

        dup2(pp[1],1);
        close(pp[1]);
        
        execlp("ls","ls","/etc",NULL);

        _exit(1);
    }


    close(pp[0]);
    close(pp[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}