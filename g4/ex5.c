#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

// implementar >,<,>>,2>,2>>
int mysystem(char** comando){
    
    pid_t pid = fork();
    if (pid==0){
        int r = execvp(comando[0],comando);
        _exit(r);
    }

    return pid;
}





char **parser (char *buffer, int *bin) {
    
    char *cp = strdup(buffer);
    char **comando = malloc(sizeof(char *)*100);
    int i = 0;
    char *token = strtok(cp," \n");
    int bool = 0;  


    while (token!=NULL) { 

        if (strcmp(token,"<")==0) bool = 1; 
        else if (strcmp(token,">")==0) bool = 2;
        else if (strcmp(token,">>")==0) bool = 3;
        else if (strcmp(token,"2>")==0) bool = 4; 
        else if (strcmp(token,"2>>")==0)  bool = 5;
        else if (strcmp(token,"&")==0) *bin = 1;
        else if (bool == 0) comando[i++] = strdup(token);
        else if (bool == 1) {
            int fd = open (token, O_RDONLY);
            int dp = dup2(fd,0);
            if (dp < 0) exit(1);
            close(fd);
            bool = 0;
        }
        else if (bool == 2) {
            int fd = open (token, O_CREAT | O_TRUNC | O_WRONLY , 0640);
            int dp = dup2(fd,1);
            if (dp < 0) exit(1);
            close(fd);
            bool = 0;
        }
        else if (bool == 3) {
            int fd = open (token, O_CREAT | O_WRONLY | O_APPEND , 0640);
            int dp = dup2(fd,1);
            if (dp < 0) exit(1);
            close(fd);
            bool = 0;
        }
        else if (bool == 4) {
            int fd = open (token, O_CREAT | O_TRUNC | O_WRONLY , 0640);
            int dp = dup2(fd,2);
            if (dp < 0) exit(1);
            close(fd);
            bool = 0;
        }
        else if (bool == 5) {
            int fd = open (token, O_CREAT | O_WRONLY | O_APPEND, 0640);
            int dp = dup2(fd,0);
            if (dp < 0) exit(1);
            close(fd);
            bool = 0;
        }
       
        token = strtok(NULL," \n");
    }
    comando[i]=NULL;

    return comando;
}




int main (int argc,char *argv[]) {

    char *buffer = malloc (sizeof(char)*1024);
    char **comando;
    
    int bin = 0;
    int fundo = 0;
    int count = 0;
    int i;
    int bytesRead;
    pid_t pid;
    while (!bin && (bytesRead = read(0,buffer,1024))>0) {

        int fd0 = dup(0);
        int fd1 = dup(1);
        int fd2 = dup(2);

        if (strcmp(buffer,"exit\n")==0) bin = 1;
        else { 
            comando = parser(buffer,&fundo);

            if (fundo) {
                count++;
                mysystem(comando);  // em plano de fundo
            }
            else {
                pid = mysystem(comando);  
                waitpid(pid,NULL,0);  
            }
        }
        
        dup2(fd0,0);
        dup2(fd1,1);
        dup2(fd2,2);

        free(buffer);
        buffer =  malloc (sizeof(char)*1024);
    }
    free(buffer);


    for (i=0;i<count;i++) {
        wait(NULL);
    }
    
    return 0;
}
