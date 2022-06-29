#include <unistd.h> 
#include <fcntl.h> 
#include <stdio.h>

int main () {
    printf("pid: %d\n",getpid());
    printf("filho - pid pai: %d\n",getppid());

}
