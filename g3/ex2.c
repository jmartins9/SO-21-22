#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
    
    if (fork() == 0) {
        if (execl("/bin/ls","bin/ls","-l",NULL) < 0) {
            perror("execl");
        }
        _exit(0);
    }
    wait(NULL);

    printf("Done\n");

    return 0;
}