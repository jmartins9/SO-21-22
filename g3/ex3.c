#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main (int argc, char *argv[]) {

    int i;
    for (i=1;i<argc;i++) {
        if (fork()==0) {
            if (execlp(argv[1],argv[1],NULL) < 0) {
                perror("execlp");
            }
            _exit(0);
        }
    }

    for(i=1;i<argc;i++) {
        wait(NULL);
    }

    return 0;
}