#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUF 1024
#define MAX_AUX 10
char aux[MAX_AUX];
int pos=0,end=0;


int readc (int fd, char *c) {                      
    if (pos == end) {
        end = read(fd,aux,MAX_AUX);
        switch (end) {
            case -1: return -1;
                break;
            case 0: return 0;
                break;
            default: pos=0; 
        }
    }

    *c = aux[pos++];

    return 1;
}


ssize_t readln (int fd, char *line, size_t size) { 
    int i = 0;
    int bytes_read = 0; 

    while (bytes_read < size && (bytes_read += readc(fd,&line[i])) > 0) {
        if (line[i]=='\n') break;
        i++;
    }   

    return bytes_read; 
}


int main (int argc,char *argv[]) {
    char buffer[MAX_BUF];
    char line[1024];
    int bytes_read,bw;
    int count = 1, countant=0;
    int fd_origem=0,fd_destino=1; 


    if (argc>1) {
        fd_origem = open (argv[1], O_RDONLY);
        if (fd_origem == -1) return -1;
    }

    while ((bytes_read = readln(fd_origem,buffer,MAX_BUF)) > 0) {
        if (count != countant && bytes_read>1) {
            bw = snprintf(line,1024,"   %d ",count);
            write(fd_destino,line,bw);
        }

        
        if (buffer[bytes_read-1]=='\n' && countant != count && bytes_read==1)  {
            write(fd_destino,buffer,bytes_read);
        } 
        else if (buffer[bytes_read-1]=='\n' && bytes_read>0) {
            write(fd_destino,buffer,bytes_read);
            countant = count;
            count++;
        }
        else if (bytes_read>0) {
            write(fd_destino,buffer,bytes_read);
            countant = count;
        }
    }    
    close(fd_origem);
    close(fd_destino);
}

