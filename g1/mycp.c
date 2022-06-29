#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <errno.h>
#include <string.h>
#include <stdio.h>

#define MAX_BUF 1024*1024

int main (int argc, char *argv[]) {

    char buffer[MAX_BUF];
    int fd_origem, fd_destino;

    fd_origem = open (argv[1], O_RDONLY);
    if (fd_origem == -1) return -1;
    // no trabalho erros nao usamos perror, nem printf 
    // strerror(errno)  - mensagem 
    // errno - numero do erro

    fd_destino = open (argv[2], O_CREAT | O_TRUNC | O_WRONLY , 0640);
    if (fd_destino == -1) return -1;

    int bytes_read;

    while ((bytes_read = read(fd_origem,buffer,MAX_BUF)) > 0) {
          write(fd_destino,buffer,bytes_read);
    }

    close(fd_origem);
    close(fd_destino);
}
