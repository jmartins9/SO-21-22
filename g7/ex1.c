#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
typedef void (*sighandler_t)(int);


int should_exit = 0;
int seconds = 0;
int count_controlC = 0;


void sigint_handler (int signum) {
    printf("seconds: %d\n", seconds);
    count_controlC ++;
}

void sigquit_handler (int signum) {
    printf("Contador de CRTL+C: %d\n",count_controlC);
    should_exit = 1;                
}

void inc_second (int signum) {
    seconds++;
    alarm(1);
}



int main(int argc, char *argv[]) {    

    if (signal(SIGINT,sigint_handler)==SIG_ERR) {
        perror("SIGINT Error");      
        return 1;  
    }
    if (signal(SIGQUIT,sigquit_handler)==SIG_ERR) {
        perror("SIGQUIT Error");
        return 1;
    }
    if (signal(SIGALRM,inc_second)==SIG_ERR) {
        perror("SIGALRM Error");
        return 1;
    }


    alarm(1);

    while (!should_exit) pause();
    
    
}
