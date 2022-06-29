#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>


/*
    ls | wc  
    ls | wc | wc | wc
    encaminhamos os dados produzidos do ls para o wc - como? pipe (canal de comunicação entre processos)
    fechar descritores não usados no início, caso contrário, bloqueia -> deadlock 
*/


int main (int argc,char *argv[]) {

    // Create pipe

    int pipe_fd[2];

    if (pipe(pipe_fd) < 0) {
        perror("pipe");
        return -1;
    }
 
    if (fork() > 0) {
        close(pipe_fd[1]);

        char buf[4];
        int read_bytes;
        while ((read_bytes = read(pipe_fd[0],buf,4))>0) {
            write(1,buf,read_bytes);
        }

        wait(NULL);
        return 0;
    }

    close(pipe_fd[0]);

    printf("sending...\n");
    write(pipe_fd[1],"data",4);

    close(pipe_fd[1]);
    _exit(0);

}