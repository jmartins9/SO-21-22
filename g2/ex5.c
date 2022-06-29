#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 10
#define COLUNAS 100


void quick_sort(int *a, int left, int right) {
    int i, j, x, y;
     
    i = left;
    j = right;
    x = a[(left + right) / 2];
     
    while(i <= j) {
        while(a[i] < x && i < right) {
            i++;
        }
        while(a[j] > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}








int main (int argc,char *argv[]) {
    int matriz[LINHAS][COLUNAS];
    int i;
    int j;
    int status;
    int exit=0;
    int array[COLUNAS];
    pid_t pid;

    srand(time(NULL));

    for(i=0;i<LINHAS;i++) {
        for(j=0;j<COLUNAS;j++) {
            matriz[i][j]=rand()%100;
        }
    }
    
    for(i=0;i<LINHAS;i++) {
        pid = fork();
        if (pid == 0) {
            for(j=0;j<COLUNAS;j++) {
                array[j]=matriz[i][j];
                if (matriz[i][j]==atoi(argv[1])) exit=1;
            }
            if (exit==1) {
                quick_sort(array,0,COLUNAS-1);
                printf("[Array filho %d] ",getpid());
                for(j=0;j<COLUNAS;j++) {
                    printf("%d ",array[j]);
                }  
                printf("\n");
            }
            _exit(exit);
        }
    }

    for(i=0;i<LINHAS;i++) {
        pid_t terminated_pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("Pai: recebi o valor %d para o pid %d\n",WEXITSTATUS(status),terminated_pid);
        }
        else {
            printf("erro\n");
        }
    }

//array de inteiros com pids dos filhos 
//pids[i] = pid (processo que acabou de ser criado)

//waitpid(pids[i],&status,0)
//para esperar pelos processos por ordem

}
