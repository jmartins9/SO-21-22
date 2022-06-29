#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main (int argc, char *argv[]) {

    int er = mkfifo("fifo",0664);
    if (er == -1) return 1;
    

    int r = open("fifo",O_RDONLY);
    
    
}