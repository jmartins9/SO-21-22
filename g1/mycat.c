#include <unistd.h> 
#include <stdio.h>
#include <fcntl.h>

#define MAX_BUF 1024*1024


int main (int argc, char *argv[]) {

    char buffer[MAX_BUF]; 
    int bytes_read;

    while ((bytes_read = read(0,buffer,MAX_BUF)) > 0) {
        write(1,buffer,bytes_read);
    }
}
