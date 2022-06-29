#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {

    int pp[2];

    if(pipe(pp)<0) perror("pipe");

    if (fork()==0) {
        close(pp[1]);
        
        dup2(pp[0],0);
        close(pp[0]);
        
        execlp("wc","wc",NULL);

        _exit(1);
    }

    close(pp[0]);

    int rb;
    char buf[100];
    while ((rb = read(0,buf,100))>0) {
        write(pp[1],buf,rb);
    }

    close(pp[1]);
    wait(NULL);
    return 0;
}