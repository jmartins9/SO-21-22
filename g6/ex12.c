#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define MAXBUF 1024


int main (int argc, char *argv[]) {

    int fd = open ("fifo", O_RDONLY);
    int fd_write = open ("fifo",O_WRONLY);

    char buffer[MAXBUF];
    
    int br;

    while (1) {
        printf("ola\n");
        br = read(fd,buffer,MAXBUF);
        write(1,buffer,br);
    }   
    
    close(fd);

    unlink("fifo");
}
