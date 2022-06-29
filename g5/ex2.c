#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>


int main (int argc, char *argv[]) {

    // Create pipe

    int pipe_fd[2];

    if (pipe(pipe_fd) < 0) {
        perror("pipe");
        return -1;
    }
 
    if (fork() == 0) {
        close(pipe_fd[1]);

        char buf[4];
        int read_bytes;
        while ((read_bytes = read(pipe_fd[0],buf,4))>0) {
            write(1,buf,read_bytes);
        }

        _exit(0);
    }

    close(pipe_fd[0]);

    printf("sending...\n");
    write(pipe_fd[1],"data\n",5);
    write(pipe_fd[1],"message1\n",9);
    write(pipe_fd[1],"message2\n",9);
    write(pipe_fd[1],"message3\n",9);

    close(pipe_fd[1]);
    wait(NULL);

    return 0;
}