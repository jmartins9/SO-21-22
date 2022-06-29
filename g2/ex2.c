#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>

int main () {
    pid_t pid;
    int status;
    int i = 0;

    pid = fork();
  
    if (pid==0) {
        i++;

        printf("filho %d\n",i);
        printf("filho - pid: %d\n",getpid());
        printf("filho - pid pai: %d\n",getppid());
        
        _exit(0); //só numeros entre 0 e 255 
    }
    else {
        
        i--;
        printf("pai %d\n",i);
        printf("pai - pid: %d\n",getpid());
        printf("pai - pid pai: %d\n",getppid());
         
        pid_t terminated_pid = wait(&status);

        if (WIFEXITED(status)) {
            printf("Pai: recebi o valor %d para o pid %d\n",WEXITSTATUS(status),terminated_pid);
        }
        else {
            printf("erro\n");
        }
    
    }
     
    printf("pai - terminei\n");
  
    return 0;

}
