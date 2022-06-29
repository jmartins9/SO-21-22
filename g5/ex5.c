#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

// grep -v ˆ# /etc/passwd | cut -f7 -d: | uniq | wc -l
/*
    int pp[3][2];

    int i;
    for (i=0;i<3;i++){
        pipe(pp[i]);
    }

    // grep -v ^# /etc/passwd 
    if (fork()==0) {
        close(pp[1][1]);close(pp[1][0]);
        close(pp[2][1]);close(pp[2][0]);

        close(pp[0][0]);

        int dup_1 = dup(1);
        dup2(pp[0][1],1);

        execlp("grep","grep","-v","^#","/etc/passwd",NULL);

        dup2(dup_1,1);
        
        close(pp[0][1]);
        _exit(0);
    }
    // cut -f7 -d



    if (fork()==0) {
        close(pp[2][1]);close(pp[2][0]);

        close(pp[0][1]);
        close(pp[1][0]);

        int dup_1 = dup(0);
        dup2(pp[0][0],0);
        int dup_2 = dup(1);
        dup2(pp[1][1],1);

        execlp("cut","cut","-f7","-d:",NULL);

        dup2(dup_1,0);
        dup2(dup_2,1);

        close(pp[1][1]);
        close(pp[0][0]);
        _exit(1);
    }
    // uniq 
    if (fork()==0) {
        close(pp[0][1]);close(pp[0][0]);

        close(pp[1][1]);
        close(pp[2][0]);

        int dup_1 = dup(0);
        dup2(pp[1][0],0);
        int dup_2 = dup(1);
        dup2(pp[2][1],1);

        execlp("uniq","uniq",NULL);

        dup2(dup_1,0);
        dup2(dup_2,1);

        close(pp[2][1]);
        close(pp[1][0]);
        _exit(2);
    }
    // wc -l
    if (fork()==0) {
        close(pp[1][1]);close(pp[1][0]);
        close(pp[0][1]);close(pp[0][0]);

        close(pp[2][1]);

        int dup_1 = dup(0);
        dup2(pp[2][0],0);
        
        execlp("wc","wc","-l",NULL);

        dup2(dup_1,0);

        close(pp[2][0]);
        _exit(3);
        
    }

    close(pp[0][0]);close(pp[0][1]);
    close(pp[1][0]);close(pp[1][1]);
    close(pp[2][0]);close(pp[2][1]);

    wait(NULL);wait(NULL);wait(NULL);wait(NULL);
*/

/*
    int pp[3][2];

    int i;
    int dup_1;
    int dup_2;
    int dup_3;
    int dup_4;
    for(i=0;i<3;i++) pipe(pp[i]);


    for (i=0;i<=3;i++) {

        if (fork()==0) {
            if (i==0) {
                close(pp[1][0]);close(pp[1][1]);
                close(pp[2][0]);close(pp[2][1]);

                close(pp[0][0]);

                dup_1 = dup(1);
                dup2(pp[0][1],1);

            }
            else if (i==3) {
                close(pp[0][0]);close(pp[0][1]);
                close(pp[1][0]);close(pp[1][1]);

                close(pp[2][1]);

                dup_2 = dup(0);
                dup2(pp[2][0],0);
            }
            else {
                int j;
                for (j=0;j<i-1;j++) {
                    close(pp[j][0]);
                    close(pp[j][1]);
                }
                for (j=i+2;j<3;j++) {
                    close(pp[j][0]);
                    close(pp[j][1]);
                }
                
                close(pp[i-1][1]);
                close(pp[i][0]);

                dup_3 = dup(0);
                dup2(pp[i-1][0],0);
                dup_4 = dup(1);
                dup2(pp[i][1],1);
            }


            if (i==0) execlp("grep","grep","-v","^#","/etc/passwd",NULL);
            else if (i==1) execlp("cut","cut","-f7","-d:",NULL);
            else if (i==2) execlp("uniq","uniq",NULL);
            else if (i==3) execlp("wc","wc","-l",NULL);


            if (i==0) {
                dup2(dup_1,1);
                close(pp[0][1]);
            }
            else if (i==3) {
                dup2(dup_2,0);
                close(pp[2][0]);
            }
            else {
                dup2(dup_3,0);
                dup2(dup_4,1);

                close(pp[i][1]);
                close(pp[i-1][0]);
            }

            _exit(0);
        }

    }


    for (i=0;i<3;i++) {
        close(pp[i][0]);
        close(pp[i][1]);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);
*/



int main (int argc, char *argv[]) {

    int pps[3][2];
    int aux1,aux2,aux3,aux4,aux5,aux6;

    pipe(pps[0]);


    if (fork()==0) {
        close(pps[0][0]);

        aux1 = dup(1);
        dup2(pps[0][1],1);
        close(pps[0][1]);

        execlp("grep","grep","-v","^#","/etc/passwd",NULL);

        dup2(aux1,1);

        _exit(0);
    }

    close(pps[0][1]);

    pipe(pps[1]);

    if (fork()==0) {
        close(pps[1][0]);

        aux2 = dup(0);
        aux3 = dup(1);

        dup2(pps[1][1],1);
        dup2(pps[0][0],0);
        close(pps[0][0]);
        close(pps[1][1]);

        execlp("cut","cut","-f7","-d:",NULL);

        dup2(aux2,0);
        dup2(aux3,1);
                
        _exit(0);
    }

    close(pps[0][0]);
    close(pps[1][1]);

    pipe(pps[2]);

    if (fork()==0) {
        close(pps[2][0]);

        aux4 = dup(0);
        aux5 = dup(1);

        dup2(pps[2][1],1);
        dup2(pps[1][0],0);
        close(pps[1][0]);
        close(pps[2][1]);

        execlp("uniq","uniq",NULL);
              
        dup2(aux4,0);
        dup2(aux5,1);
        
    }

    close(pps[1][0]);
    close(pps[2][1]);

    if (fork()==0) {
        
        aux6 = dup(0);

        dup2(pps[2][0],0);
        close(pps[2][0]);
        
        execlp("wc","wc","-l",NULL);

        dup2(aux6,0);
        _exit(0);
    }


    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

}




/*  
    X - NÚMERO DE TRANFORMAÇÕES
    
    ABRIR X-1 PIPESaux2
    NO PRIMEIRO LEIO DO STDIN/ORIGIN PATH
    NO ULIMO ESCREVO NO STDOUT/DESTINY PATH

    ENTRE PROCESSOS LEIO/ESCREVE DE/PARA PIPES

    FECHAR TODOS AS ENTRADAS DOS PIPES QUE NAO SAO USADAS

*/

