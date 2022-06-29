#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

// & sem wait e exit ou control-D para sair
int mysystem(char* comando){
    int i=0;
    
    char *cp = strdup(comando);
    char *guarda[50];

    char *token = strtok(cp," \n");
    while (token!=NULL && strcmp("&",token)!=0) {
        guarda[i++]=strdup(token);
        token = strtok(NULL," \n");
    }
    guarda[i]=NULL;
    
    pid_t pid = fork();
    if (pid==0){
        int r = execvp(guarda[0],guarda);
        _exit(r);
    }

    return pid;
}


int main (int argc,char *argv[]) {

    char *buffer = malloc (sizeof(char)*1024);
    
    int bin = 0;
    int count = 0;
    int i;
    int bytesRead;
    pid_t pid;
    while (!bin && (bytesRead = read(0,buffer,1024))>0) {
        if (strcmp(buffer,"exit\n")==0) bin = 1;
        if (buffer[bytesRead-2]!='&') {
            pid = mysystem(buffer); // em primeiro plano 
            waitpid(pid,NULL,0);
        }
        else {
            count++;
            mysystem(buffer);  // em plano de fundo  
        }

        free(buffer);
        buffer =  malloc (sizeof(char)*1024);
    }
    free(buffer);


    for (i=0;i<count;i++) {
        wait(NULL);
    }
    
    return 0;

}
