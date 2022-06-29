#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define MAXBUF 1024


int main (int argc, char *argv[]) {

    int fd = open ("fifo",O_WRONLY);

    char buffer[MAXBUF];
    
    int br;

    while ((br = read(0,buffer,MAXBUF))>0) {

        write(fd,buffer,br);

    }
    
    close(fd); 
}


