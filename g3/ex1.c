#include <unistd.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
  /*  
  if (execl("/bin/ls","bin/ls","-l",NULL) < 0) {
      perror("execl");
  }


  if (execlp("ls","ls","-l",NULL) < 0) {
      perror("execlp");
  }
  */  

  char *exec_args[] = {"/bin/ls",
                     "-l",
                     NULL
                     };
                     
  if (execv("/bin/ls",exec_args) < 0) {
      perror("execv");
  }

  return 0;
}

//lsof - lista de descritores abertos deste processo



