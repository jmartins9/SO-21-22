#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {

   char *args[argc];
   int i;
   for (i=1;i<argc;i++) {
      args[i-1]=strdup(argv[i]);
   }
   args[i-1]=NULL;

   int status;
   if (fork()==0) {
      int res = execvp(args[0],args);
      _exit(res);
   }
   wait(&status);
    
   return WEXITSTATUS(status);
}