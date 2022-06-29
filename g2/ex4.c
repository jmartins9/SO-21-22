#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>

int main () {
   
   pid_t pid;
   int i;
   int status;
   
   for(i=1;i<=10;i++) {
        
        pid = fork();
        if (pid == 0) {
            printf("filho - pid: %d\n",getpid());
            printf("filho - pid pai %d\n",getppid());
            _exit(i);
        }
   }
   
   for(i=0;i<10;i++) {
        pid_t terminated_pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("Pai: recebi o valor %d para o pid %d\n",WEXITSTATUS(status),terminated_pid);
        }
        else {
            printf("erro\n");
        }
   }
   
}