#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {

    int ofd = dup(1);

    int fd1 = open("/etc/passwd", O_RDONLY);
    int Dup1 = dup2(fd1,0);
    close(fd1);

    int fd2 = open("saida.txt", O_WRONLY | O_TRUNC |  O_CREAT, 0640);
    int Dup2 = dup2(fd2,1);
    close(fd2);

    int fd3 = open("erros.txt", O_WRONLY | O_TRUNC | O_CREAT, 0640);
    int Dup3 = dup2(fd3,2);
    close(fd3);

    write(ofd,"terminei\n",9);

    
    if (fork()==0) {

        char buf[16];
        
	    write(1,"Hello",5);
        write(2,"Erro",4);

  	    read(0,buf,16);

	    write(ofd,buf,16);
        
	    _exit(0);

    }
    wait(NULL);
     
    return 0;

}
