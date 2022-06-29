#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h> 
#define LINHAS 10
#define COLUNAS 10000

int main (int argc,char *argv[]) {
    int matriz[LINHAS][COLUNAS];
    int numero;
    int status;
    int pids[LINHAS];
    pid_t pid;

    int fd = open("matriz",O_RDWR | O_CREAT, 0600);
    if (fd<0) {
        perror("Erro na abertura do ficheiro");
        return -1;
    }
    
    srand(time(NULL));
    for(int i=0;i<LINHAS;i++) {
        for(int j=0;j<COLUNAS;j++) {
            matriz[i][j]=rand()%10000;
            write(fd,&(matriz[i][j]),sizeof(int));
        }
    }
    close(fd);


    for(int i=0;i<LINHAS;i++) {
        pid = fork();
        pids[i]=pid;

        if(pid==0) {
            int fdf = open("matriz",O_RDWR);
            if (fdf<0) _exit(255);
            

            off_t ofs = lseek(fdf,i*COLUNAS*sizeof(int),SEEK_SET);
            if (ofs<0) _exit(255);
            
            for(int j=0;j<COLUNAS;j++) {
                int br = read(fdf,&numero,sizeof(int));
                if (br<=0) _exit(255);

                if (numero == atoi(argv[1])) {
                    close(fdf);
                    _exit(1);
                    }
                }   
            close(fdf);
            _exit(0);

        }
    }
        


    for (int i=0;i<LINHAS;i++) {
        pid_t terminated_pid = waitpid(pids[i],&status,0);
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status)<255) printf("Pai: recebi o valor %d para o pid %d\n",WEXITSTATUS(status),terminated_pid);
            else printf("Algo correu mal");
        }
        else {
            printf("erro\n");
        }
    }
    return 0;
}
